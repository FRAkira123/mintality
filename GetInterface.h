#pragma once

typedef void* (*CreateInterface_t)(const char*, int*);


inline void* CaptureInterface(const char* chHandle, const char* chInterfaceName)
{
	volatile auto handlegotten = (GetModuleHandleA(chHandle) != nullptr);
	while (!GetModuleHandleA(chHandle)) Sleep(100);
	void* fnFinal = nullptr;
	auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
	auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(chHandle), XorStr("CreateInterface")));
	for (auto i = 100; i > 0; i--)
	{
		XorCompileTime::w_sprintf(PossibleInterfaceName, XorStr("%s%03i"), chInterfaceName, i);
		fnFinal = static_cast<void*>(TestInterface(PossibleInterfaceName, nullptr));

		if (fnFinal != nullptr)
			break;

	}
	delete PossibleInterfaceName;
	return fnFinal;
}

inline void* CaptureInterface(HMODULE Handle, const char* chInterfaceName)
{
	volatile auto handlegotten = (Handle != nullptr);
	void* fnFinal = nullptr;
	auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
	auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(Handle, XorStr("CreateInterface")));
	for (auto i = 100; i > 0; i--)
	{
		//XorCompileTime::w_sprintf(PossibleInterfaceName, XorStr("%s%03i"), chInterfaceName, i);
		fnFinal = static_cast<void*>(TestInterface(PossibleInterfaceName, nullptr));

		if (fnFinal != nullptr)
			break;
	}
	delete PossibleInterfaceName;
	return fnFinal;
}

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
DWORD FindPatternWithoutMask(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}


class VTHookManager
{
private:
	BOOL NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
	{
		typedef LONG * NTAPI LPFN_NtProtectVirtualMemory(HANDLE, PVOID *, PULONG, ULONG, PULONG);

		LPFN_NtProtectVirtualMemory * NtProtectVirtualMemory = (LPFN_NtProtectVirtualMemory*)(GetProcAddress(GetModuleHandleA(XorStr("ntdll.dll")), XorStr("NtProtectVirtualMemory")));

		if (!NtProtectVirtualMemory)
			return FALSE;

		NtProtectVirtualMemory(GetCurrentProcess(), (PVOID*)&lpAddress, (PULONG)&dwSize, flNewProtect, lpflOldProtect);

		return TRUE;
	}
public:
	VTHookManager()
	{
		DWORD oProtection;
		NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, PAGE_READWRITE, &oProtection);
		memset(this, 0, sizeof(VTHookManager));
		NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, oProtection, &oProtection);
	}

	explicit VTHookManager(PDWORD* ppdwClassBase)
	{
		bInitialize(ppdwClassBase);
	}

	~VTHookManager()
	{
		UnHook();
	}

	bool bInitialize(PDWORD* ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD[m_dwVMTSize];
		DWORD oProtection;
		NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, PAGE_READWRITE, &oProtection);
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD)* m_dwVMTSize);
		NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, oProtection, &oProtection);
		*ppdwClassBase = m_pdwNewVMT;
		return true;
	}

	bool bInitialize(PDWORD** pppdwClassBase)
	{
		return bInitialize(*pppdwClassBase);
	}

	void UnHook() const
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwOldVMT;
		}
	}

	void ReHook() const
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount() const
	{
		return static_cast<int>(m_dwVMTSize);
	}

	DWORD dwGetMethodAddress(int Index) const
	{
		if (Index >= 0 && Index <= static_cast<int>(m_dwVMTSize) && m_pdwOldVMT != nullptr)
		{
			return m_pdwOldVMT[Index];
		}
		return NULL;
	}

	PDWORD pdwGetOldVMT() const
	{
		return m_pdwOldVMT;
	}

	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex) const
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}

		return 0;
	}

	DWORD dwUnHookMethod(unsigned int iIndex) const
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = m_pdwOldVMT[iIndex];
			return m_pdwOldVMT[iIndex];
		}

		return NULL;
	}
	PDWORD m_pdwNewVMT, m_pdwOldVMT;
private:
	static DWORD dwGetVMTCount(PDWORD pdwVMT)
	{
		DWORD dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr(reinterpret_cast<FARPROC>(pdwVMT[dwIndex])))
			{
				break;
			}
		}
		return dwIndex;
	}

	PDWORD* m_ppdwClassBase;
	
	DWORD m_dwVMTSize;
};
