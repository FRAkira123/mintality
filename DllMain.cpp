#include "stdafx.h"
#include "GetNetVar.h"

HMODULE hDll = nullptr;
DWORD ModuleBase = NULL;

HMODULE
h_Engine = nullptr,
h_Client = nullptr,
h_vstdlib = nullptr,
h_materialsystem = nullptr,
h_inputsystem = nullptr,
h_vgui2 = nullptr,
h_vguimatsurface = nullptr,
h_vphysics = nullptr;

void _fastcall interface_initializer(void)
{
	
	size_t sleep_time = 20;
	size_t sleep_interface = 10;

	JUNK_CODE_ONE


		HMODULE
		h_Engine = nullptr,
		h_Client = nullptr,
		h_vstdlib = nullptr,
		h_materialsystem = nullptr,
		h_inputsystem = nullptr,
		h_vgui2 = nullptr,
		h_vguimatsurface = nullptr,
		h_vphysics = nullptr;

	while (!(hWnd = FindWindowA(XorStr("Valve001"), NULL)))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	while (!h_Engine) {
		h_Engine = GetModuleHandleA(XorStr("engine.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_Client) {
		h_Client = GetModuleHandleA(XorStr("client.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_vstdlib) {
		h_vstdlib = GetModuleHandleA(XorStr("vstdlib.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_materialsystem) {
		h_materialsystem = GetModuleHandleA(XorStr("materialsystem.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_inputsystem) {
		h_inputsystem = GetModuleHandleA(XorStr("inputsystem.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_vgui2) {
		h_vgui2 = GetModuleHandleA(XorStr("vgui2.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_vguimatsurface) {
		h_vguimatsurface = GetModuleHandleA(XorStr("vguimatsurface.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	while (!h_vphysics) {
		h_vphysics = GetModuleHandleA(XorStr("vphysics.dll"));
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}


	JUNK_CODE_ONE
}

void _fastcall InitInterfaces(void)
{
	JUNK_CODE_ONE


	interface_initializer();

	m_pWindowProc = (WNDPROC)SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)myWndProc);

	if (pEngine == nullptr)
		pEngine = reinterpret_cast<IVEngineClient*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("VEngineClient"))));

	if (pEngineTrace == nullptr)
		pEngineTrace = reinterpret_cast<IEngineTrace*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("EngineTraceClient"))));

	if (pModelInfo == nullptr)
		pModelInfo = reinterpret_cast<CModelInfo*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("VModelInfoClient"))));

	if (ModelRender == nullptr)
		ModelRender = reinterpret_cast<IVModelRender*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("VEngineModel"))));

	if (RenderView == nullptr)
		RenderView = reinterpret_cast<IVRenderView*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("VEngineRenderView"))));

	if (pGameEventManager2 == nullptr)
		pGameEventManager2 = reinterpret_cast<GameEventManager2*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("GAMEEVENTSMANAGER"))));

	if (pClient == nullptr)
		pClient = reinterpret_cast<IBaseClientDLL*>(CaptureInterface(XorStr(__TEXT("client.dll")), XorStr(__TEXT("VClient"))));

	if (pClientEntList == nullptr)
		pClientEntList = reinterpret_cast<IClientEntityList*>(CaptureInterface(XorStr(__TEXT("client.dll")), XorStr(__TEXT("VClientEntityList"))));

	if (pGlobals == nullptr)
		pGlobals = **(CGlobalVarsBase***)((*(DWORD**)pClient)[0] + 0x1B);

	if (ClientMode == nullptr)
		ClientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<DWORD**>(pClient))[10] + 0x5);

	if (pCon == nullptr)
		pCon = reinterpret_cast<ConVar*>(CaptureInterface(XorStr(__TEXT("vstdlib.dll")), XorStr(__TEXT("VEngineCvar"))));

	if (pMatSystem == nullptr)
		pMatSystem = reinterpret_cast<IMaterialSystem*>(CaptureInterface(XorStr(__TEXT("materialsystem.dll")), XorStr(__TEXT("VMaterialSystem"))));

	if (pIInput == nullptr)
		pIInput = reinterpret_cast<IInputSystem*>(CaptureInterface(XorStr(__TEXT("inputsystem.dll")), XorStr(__TEXT("InputSystemVersion"))));

	if (pPanel == nullptr)
		pPanel = reinterpret_cast<IPanel*>(CaptureInterface(XorStr(__TEXT("vgui2.dll")), XorStr(__TEXT("VGUI_Panel"))));

	if (pSurface == nullptr)
		pSurface = reinterpret_cast<ISurface*>(CaptureInterface(XorStr(__TEXT("vguimatsurface.dll")), XorStr(__TEXT("VGUI_Surface"))));

//	if (PhysProps == nullptr)
//		PhysProps = reinterpret_cast<IPhysicsSurfaceProps*>(CaptureInterface(XorStr(__TEXT("vphysics.dll")), XorStr(__TEXT("VPhysicsSurfaceProps"))));
	
	if (pSound == nullptr)
		pSound = reinterpret_cast<IEngineSound*>(CaptureInterface(XorStr(__TEXT("engine.dll")), XorStr(__TEXT("IEngineSoundClient"))));




	JUNK_CODE_ONE
}

#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

DWORD D3DDevice()
{
	JUNK_CODE_ONE

	HMODULE hShader;
	MODULEINFO modShaderDll;

	do
	{
		hShader = GetModuleHandleA(XorStr("shaderapidx9.dll"));

	} while (hShader == NULL);

	GetModuleInformation(GetCurrentProcess(), hShader, &modShaderDll, sizeof(MODULEINFO));

	JUNK_CODE_ONE

	return **reinterpret_cast<PDWORD*>(FindPatternWithoutMask(XorStr("shaderapidx9.dll"), XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
}

//__TEXT макрос, указывающий компилятору, что мы не зависим от кодировок.
DWORD WINAPI MainThread(LPVOID)
{
	HANDLE hThread = GetCurrentThread();
	ThreadHiding(hThread);
	CloseHandle(hThread);

	JUNK_CODE_ONE


	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	

	HideModule(hDll);
	DestroyModuleHeader(hDll);
	AntiDumping();
	HideModuleXta(hDll);
	RemovePeHeader(ModuleBase);
	PushPopSS();

	InitInterfaces();

	NetVarManager->Initialize();
	Engine::Dynamic::Initialize();
	NetVarManager->GrabOffsets();

	DWORD d3dDevice = D3DDevice();

	Direct9Hook        = new VTHookManager(reinterpret_cast<PDWORD*>(d3dDevice));
	pPanelHook         = new VTHookManager(reinterpret_cast<PDWORD*>(pPanel));
	pClientMode        = new VTHookManager(reinterpret_cast<PDWORD*>(ClientMode));
	pModellHook        = new VTHookManager(reinterpret_cast<PDWORD*>(ModelRender));
	pEngine_sound_hook = new VTHookManager(reinterpret_cast<PDWORD*>(pSound));
	pSurface_hook      = new VTHookManager(reinterpret_cast<PDWORD*>(pSurface));


	if (Direct9Hook && !oReset) 
		oReset = reinterpret_cast<Reset_t>(Direct9Hook->dwHookMethod(reinterpret_cast<DWORD>(myReset), 16));	

	if (Direct9Hook && !oPresent)
		oPresent = reinterpret_cast<Present_t>(Direct9Hook->dwHookMethod(reinterpret_cast<DWORD>(myPresent), 17));

	if (pClientMode && !oCreateMove)
		oCreateMove = reinterpret_cast<CreateMoveFn>(pClientMode->dwHookMethod(reinterpret_cast<DWORD>(CreateMovesss), 24));

	if(pClientMode && !oOverrideView)
		oOverrideView = reinterpret_cast<OverrideViewFn>(pClientMode->dwHookMethod(reinterpret_cast<DWORD>(HookedOverrideView), 18));
	
	if (pPanelHook && !pPaintTraverse)
		pPaintTraverse = reinterpret_cast<PaintTraverseFn>(pPanelHook->dwHookMethod(reinterpret_cast<DWORD>(Hooked_PaintTraverse), 41));

	if (pModellHook && !oDrawModelExecute)
		oDrawModelExecute = reinterpret_cast<IDrawModelExecute>(pModellHook->dwHookMethod(reinterpret_cast<DWORD>(Hooked_DrawModelExecute), 21));

	if (pClientMode && !pGetViewModelFOV)
		pGetViewModelFOV = reinterpret_cast< GetViewModelFOVFn>(pClientMode->dwHookMethod(reinterpret_cast<DWORD>(hkGetViewModelFOV), 35));

	if (pEngine_sound_hook && !oEmitsound)
		oEmitsound = reinterpret_cast< Emitsound_fn>(pEngine_sound_hook->dwHookMethod(reinterpret_cast<DWORD>(Emitsound_Hook), 5));

	if (pSurface_hook && !oPlaySound)
		oPlaySound = reinterpret_cast<PlaySoundFn>(pSurface_hook->dwHookMethod(reinterpret_cast<DWORD>(OnPlaysound), 82));

	hitmarker::singleton()->initialize();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	//RandomBone
	HANDLE hThreadRandomBone = CreateThread(NULL, NULL, InitRandomBone, NULL, NULL, NULL);
	ThreadHiding(hThreadRandomBone);
	CloseHandle(hThreadRandomBone);
	//ProtectDll

	std::this_thread::sleep_for(std::chrono::milliseconds(200));


	JUNK_CODE_ONE
	return NULL;
}



BOOL APIENTRY DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID  lpvReserved)
{
	ModuleBase = (DWORD)hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		if (hDll == nullptr)
			hDll = hinstDLL;

		if (CreateDirectory("C:\\", NULL))
			BaseDir = "C:\\";

		CloseHandle(CreateThread(NULL, NULL, MainThread, NULL, NULL, NULL));
		
		return TRUE;
	}

	if (fdwReason == DLL_PROCESS_DETACH)
	{
		if(pClientMode)
			pClientMode->UnHook();

		if(Direct9Hook)
			Direct9Hook->UnHook();

		if (pPanelHook)
			pPanelHook->UnHook();

		if (pModellHook)
			pModellHook->UnHook();



		SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)m_pWindowProc);

		delete pClientMode;
		delete Direct9Hook;
		delete PCM;
		delete CMF;
		delete NetVarManager;

		return TRUE;
	}

	return FALSE;
}


