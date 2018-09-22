#pragma once
#pragma warning(disable : 4996) 

namespace DynNetVars
{
	DWORD m_iHealth = 0x0;
	DWORD m_flFlashMaxAlpha = 0x0;
	DWORD dwCompRanks = 0x0;
	DWORD dwCompWins = 0x0;
	DWORD m_iBulletsFired = 0x0;
	DWORD m_iTeamNum = 0x0;
	DWORD m_bGunGameImmunity = 0x0;
	DWORD m_lifeState = 0x0;
	DWORD m_fFlags = 0x0;
	DWORD m_Local = 0x0;
	DWORD m_nTickBase = 0x0;
	DWORD m_nForceBone = 0x0;
	DWORD m_nModelIndex = 0x0;
	DWORD m_viewPunchAngle = 0x0;
	DWORD m_aimPunchAngle = 0x0;
	DWORD m_vecOrigin = 0x0;
	DWORD m_vecViewOffset = 0x0;
	DWORD m_vecVelocity = 0x0;
	DWORD m_szLastPlaceName = 0x0;
	DWORD m_flNextPrimaryAttack = 0x0;
	DWORD m_hActiveWeapon = 0x0;
	DWORD m_fAccuracyPenalty = 0x0;
	DWORD m_Collision = 0x0;
	DWORD m_iWeaponID = 0x0;
	DWORD m_nHitboxSet = 0x0;
	DWORD m_bHasHelmet = 0x0;
	DWORD m_ArmorValue = 0x0;
	DWORD m_CollisionGroup = 0x0;
	DWORD m_iClass = 0x0;
	DWORD m_bIsBroken = 0x0;
	DWORD m_angEyeAngles = 0x0;
	DWORD m_hOwnerEntity = 0x0;
	DWORD m_flC4Blow = 0x0;
	DWORD m_flFlashDuration = 0x0;
	DWORD m_flLowerBodyYawTarget = 0x0;
	DWORD m_angEyeAnglesX = 0x0;
	DWORD m_angEyeAnglesY = 0x0;
	DWORD m_bIsScoped = 0x0;
	DWORD deadflag = 0x0;
	DWORD ViewModelIndex = 0x0;
	DWORD WorldModelIndex = 0x0;
	DWORD m_nFallbackPaintKit = 0x0;
	DWORD m_nFallbackSeed = 0x0;
	DWORD m_flFallbackWear = 0x0;
	DWORD m_nFallbackStatTrak = 0x0;
	DWORD m_AttributeManager = 0x0;
	DWORD m_Item = 0x0;
	DWORD m_iEntityLevel = 0x0;
	DWORD m_iItemIDHigh = 0x0;
	DWORD m_iItemIDLow = 0x0;
	DWORD m_iAccountID = 0x0;
	DWORD m_iEntityQuality = 0x0;
	DWORD m_OriginalOwnerXuidLow = 0x0;
	DWORD m_OriginalOwnerXuidHigh = 0x0;
	DWORD m_iItemDefinitionIndex = 0x0;
	DWORD m_iClip1 = 0x0;
	DWORD m_iClip2 = 0x0;
	DWORD m_bNadePinPulled = 0x0;
	DWORD m_fNadeThrowTime = 0x0;
	DWORD m_flPostponeFireReadyTime = 0x0;
	DWORD m_bReloadVisuallyComplete = 0x0;
	DWORD m_hObserverTarget = 0x0;
	DWORD m_vecMins = 0x0 ,m_vecMaxs = 0x0, m_rgflCoordinateFrame = 0x0, m_iObserverMode = 0x0;
	DWORD m_CrossId = 0x0;
	//end of offsets & netvars
}

class CNetVarManager
{
public:
	void Initialize();
	void GrabOffsets();
	int GetOffset(const char *tableName, const char *propName);
	bool HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun);
	void DumpNetvars();
private:
	int Get_Prop(const char *tableName, const char *propName, RecvProp **prop = 0);
	int Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop = 0);
	RecvTable *GetTable(const char *tableName);
	std::vector<RecvTable*> m_tables;
	void DumpTable(RecvTable *table, int depth);
	std::ofstream m_file;
};



void CNetVarManager::Initialize()
{
	m_tables.clear();

	ClientClass *clientClass = pClient->GetAllClasses();
	if (!clientClass)
		return;

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pTable;
		m_tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}
}

int CNetVarManager::GetOffset(const char *tableName, const char *propName)
{
	int offset = Get_Prop(tableName, propName);
	if (!offset)
	{
		return 0;
	}
	return offset;
}

bool CNetVarManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun)
{
	RecvProp *recvProp = 0;
	Get_Prop(tableName, propName, &recvProp);
	if (!recvProp)
		return false;

	recvProp->m_ProxyFn = fun;

	return true;
}

int CNetVarManager::Get_Prop(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);
	if (!recvTable)
		return 0;

	int offset = Get_Prop(recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int CNetVarManager::Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;
	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];
		RecvTable *child = recvProp->m_pDataTable;

		if (child && (child->m_nProps > 0))
		{
			int tmp = Get_Prop(child, propName, prop);
			if (tmp)
				extraOffset += (recvProp->m_Offset + tmp);
		}

		if (stricmp(recvProp->m_pVarName, propName))
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}

RecvTable *CNetVarManager::GetTable(const char *tableName)
{
	if (m_tables.empty())
		return 0;

	for each (RecvTable *table in m_tables)
	{
		if (!table)
			continue;

		if (stricmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return 0;
}

void CNetVarManager::DumpTable(RecvTable *table, int depth)
{
	std::string pre("");
	for (int i = 0; i<depth; i++)
		pre.append("\t");

	m_file << pre << table->m_pNetTableName << "\n";

	for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp *prop = &table->m_pProps[i];
		if (!prop) continue;

		std::string varName(prop->m_pVarName);

		if (varName.find(XorStr("baseclass")) == 0 || varName.find("0") == 0 || varName.find("1") == 0 || varName.find("2") == 0)
			continue;

		m_file << pre << "\t " << varName << " "
			<< std::setfill('_') << std::setw(60 - varName.length() - (depth * 4))
			<< "[0x" << std::setfill('0') << std::setw(8) << std::hex
			<< std::uppercase << prop->m_Offset << "]\n";

		if (prop->m_pDataTable)
			DumpTable(prop->m_pDataTable, depth + 1);
	}
}

void CNetVarManager::DumpNetvars()
{

	m_file.open("./netdump.txt");
	m_file << XorStr("NetVar Dump by VRedux \n\n");

	for (ClientClass *pClass = pClient->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext)
	{
		RecvTable *table = pClass->m_pTable;
		DumpTable(table, 0);
	}

	m_file.close();
}

CNetVarManager* NetVarManager = new CNetVarManager;

//это сделано для того, чтобы макросом вместо 100 одинаковых строк заменить 1 криптованой. экономия памяти.
const std::string DT_BasePlayer(XorStr("DT_BasePlayer"));
const std::string DT_CSPlayer(XorStr("DT_CSPlayer"));
const std::string DT_CollisionProperty(XorStr("DT_CollisionProperty"));
const std::string DT_BaseAttributableItem(XorStr("DT_BaseAttributableItem"));
const std::string DT_BaseCombatWeapon(XorStr("DT_BaseCombatWeapon"));
const std::string DT_CSPlayerResource(XorStr("DT_CSPlayerResource"));
const std::string DT_WeaponCSBase(XorStr("DT_WeaponCSBase"));
const std::string DT_BaseCSGrenade(XorStr("DT_BaseCSGrenade"));
const std::string DT_BaseEntity(XorStr("DT_BaseEntity"));


void CNetVarManager::GrabOffsets()
{
	DynNetVars::m_vecMins = NetVarManager->GetOffset(DT_CollisionProperty.c_str(), XorStr("m_vecMins"));
	DynNetVars::m_vecMaxs = NetVarManager->GetOffset(DT_CollisionProperty.c_str(), XorStr("m_vecMaxs"));

	DynNetVars::m_iHealth = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_iHealth"));
	DynNetVars::m_iTeamNum = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_iTeamNum"));
	DynNetVars::m_ArmorValue = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_ArmorValue"));
	DynNetVars::m_bHasHelmet = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_bHasHelmet"));
	DynNetVars::m_iClass = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_iClass"));
	DynNetVars::m_iBulletsFired = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_iShotsFired"));
	DynNetVars::m_bGunGameImmunity = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_bGunGameImmunity"));
	DynNetVars::m_lifeState = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_lifeState"));
	DynNetVars::m_fFlags = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_fFlags"));
	DynNetVars::m_nTickBase = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_nTickBase"));
	DynNetVars::m_nForceBone = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_nForceBone"));
	DynNetVars::m_angEyeAngles = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_angEyeAngles"));
	DynNetVars::m_flFlashDuration = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_flFlashDuration"));
	DynNetVars::m_flFlashMaxAlpha = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_flFlashMaxAlpha"));
	DynNetVars::m_vecViewOffset = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_vecViewOffset[0]"));
	DynNetVars::m_vecVelocity = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_vecVelocity[0]"));
	DynNetVars::m_szLastPlaceName = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_szLastPlaceName"));
	DynNetVars::m_hActiveWeapon = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_hActiveWeapon"));
	DynNetVars::m_angEyeAnglesX = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_angEyeAngles[0]"));
	DynNetVars::m_angEyeAnglesY = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_angEyeAngles[1]"));
	DynNetVars::m_bIsScoped = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_bIsScoped"));
	DynNetVars::m_CrossId = NetVarManager->GetOffset(DT_CSPlayer.c_str(), XorStr("m_bHasDefuser") + 92);

	DynNetVars::dwCompRanks = NetVarManager->GetOffset(DT_CSPlayerResource.c_str(), XorStr("m_iCompetitiveRanking"));
	DynNetVars::dwCompWins = NetVarManager->GetOffset(DT_CSPlayerResource.c_str(), XorStr("m_iCompetitiveWins"));
	
	DynNetVars::m_Local = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_Local"));
	DynNetVars::m_nModelIndex = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_nModelIndex"));
	DynNetVars::m_viewPunchAngle = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_viewPunchAngle"));
	DynNetVars::m_aimPunchAngle = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_aimPunchAngle"));
	DynNetVars::m_vecOrigin = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_vecOrigin"));

	DynNetVars::m_Collision = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_Collision"));
	DynNetVars::m_CollisionGroup = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_CollisionGroup"));
	DynNetVars::m_rgflCoordinateFrame = DynNetVars::m_CollisionGroup - 0x30;

	DynNetVars::m_nHitboxSet = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_nHitboxSet"));
	DynNetVars::deadflag = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("deadflag"));
	DynNetVars::m_hObserverTarget = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_hObserverTarget"));
	DynNetVars::m_iObserverMode = NetVarManager->GetOffset(DT_BasePlayer.c_str(), XorStr("m_iObserverMode"));

	


	DynNetVars::ViewModelIndex = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iViewModelIndex"));
	DynNetVars::WorldModelIndex = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iWorldModelIndex"));
	DynNetVars::m_flNextPrimaryAttack = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_flNextPrimaryAttack"));
	DynNetVars::m_nFallbackPaintKit = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_nFallbackPaintKit"));
	DynNetVars::m_nFallbackSeed = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_nFallbackSeed"));
	DynNetVars::m_flFallbackWear = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_flFallbackWear"));
	DynNetVars::m_nFallbackStatTrak = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_nFallbackStatTrak"));
	DynNetVars::m_AttributeManager = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_AttributeManager"));
	DynNetVars::m_Item = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_Item"));
	DynNetVars::m_iEntityLevel = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iEntityLevel"));
	DynNetVars::m_iItemIDHigh = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iItemIDHigh"));
	DynNetVars::m_iItemIDLow = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iItemIDLow"));
	DynNetVars::m_iAccountID = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iAccountID"));
	DynNetVars::m_iEntityQuality = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iEntityQuality"));
	DynNetVars::m_iClip1 = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iClip1"));
	DynNetVars::m_iClip2 = NetVarManager->GetOffset(DT_BaseCombatWeapon.c_str(), XorStr("m_iClip2"));

	DynNetVars::m_OriginalOwnerXuidLow = NetVarManager->GetOffset(DT_BaseAttributableItem.c_str(), XorStr("m_OriginalOwnerXuidLow"));
	DynNetVars::m_OriginalOwnerXuidHigh = NetVarManager->GetOffset(DT_BaseAttributableItem.c_str(), XorStr("m_OriginalOwnerXuidHigh"));
	DynNetVars::m_iItemDefinitionIndex = NetVarManager->GetOffset(DT_BaseAttributableItem.c_str(), XorStr("m_iItemDefinitionIndex"));

	DynNetVars::m_fAccuracyPenalty = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_fAccuracyPenalty"));
	DynNetVars::m_iWeaponID = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_fAccuracyPenalty")) + 0x30;
	DynNetVars::m_flPostponeFireReadyTime = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_flPostponeFireReadyTime"));
	DynNetVars::m_bReloadVisuallyComplete = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_bReloadVisuallyComplete"));

	//DynNetVars::m_rgflCoordinateFrame = DynNetVars::m_CollisionGroup - 0x30;
	DynNetVars::m_hOwnerEntity = NetVarManager->GetOffset(DT_BaseEntity.c_str(), XorStr("m_hOwnerEntity"));
	DynNetVars::m_bIsBroken = NetVarManager->GetOffset(XorStr("DT_BreakableSurface"), XorStr("m_bIsBroken"));
	DynNetVars::m_flC4Blow = NetVarManager->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_flC4Blow"));
	DynNetVars::m_bNadePinPulled = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_bPinPulled"));
	DynNetVars::m_fNadeThrowTime = NetVarManager->GetOffset(DT_WeaponCSBase.c_str(), XorStr("m_fThrowTime"));



}



namespace Engine
{


	DWORD_PTR GetTableOffset(const char* ClassName, const char* VarName, RecvTable* pTable, RecvProp** ppProp = nullptr)
	{
		DWORD_PTR dwReturn = 0;

		for (int i = 0; i < pTable->GetNumProps(); ++i)
		{
			RecvProp* pProp = pTable->GetPropA(i);

			if (!pProp)
				continue;

			if (ppProp)
				*ppProp = pProp;

			RecvTable* pChild = pProp->GetDataTable();

			if (pChild && pChild->GetNumProps())
				dwReturn += GetTableOffset(ClassName, VarName, pChild, ppProp);

			if (!strcmp(pTable->GetName(), ClassName) && !strcmp(pProp->GetName(), VarName))
			{
				dwReturn += pProp->GetOffset();
				break;
			}
		}

		return dwReturn;
	}

	DWORD_PTR GetNetVar(const char* ClassName, const char* VarName, RecvProp** ppProp = nullptr)
	{
		DWORD_PTR dwReturn = 0;

		ClientClass* pList = pClient->GetAllClasses();

		for (; pList; pList = pList->m_pNext)
		{
			RecvTable* pTable = (RecvTable*)pList->m_pTable;

			if (!pTable)
				continue;

			if (!pTable->GetNumProps())
				continue;

			if (!strstr(pTable->GetName(), /*DT_*/XorStr("DT_")))
				continue;

			dwReturn = GetTableOffset(ClassName, VarName, pTable, ppProp);

			if (dwReturn)
				break;
		}

		return dwReturn;
	}

	void LogToStringStream(const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss)
	{
		ss << std::setw(48)
			<< std::setfill('_')
			<< std::left
			<< tablename +/* -> */XorStr("->") + varname + /*: */XorStr(": ")
			<< std::right
			<< std::hex
			<< /* 0x*/XorStr("0x")
			<< std::setw(8)
			<< std::setfill('0')
			<< std::uppercase
			<< offset << std::endl;
	}

	namespace Dynamic
	{
		namespace Entity
		{
			DWORD_PTR
				m_iHealth = 0x0,
				m_iTeamNum = 0x0,
				m_nTickBase = 0x0,
				m_lifeState = 0x0,
				m_ArmorValue = 0x0,
				m_bHasHelmet = 0x0,
				m_Local = 0x0,
				m_vecOrigin = 0x0,
				m_vecViewOffset = 0x0,
				m_vecVelocity = 0x0,
				m_aimPunchAngle = 0x0,
				m_viewPunchAngle = 0x0,
				m_angEyeAngles = 0x0,
				m_fFlags = 0x0,
				m_hActiveWeapon = 0x0,
				m_flC4Blow = 0x0,
				m_bIsDefusing = 0x0,
				m_nHitboxSet = 0x0,
				m_iShotsFired = 0x0,
				m_bIsBroken = 0x0,
				m_rgflCoordinateFrame = 0x0,
				m_CollisionGroup = 0x0,
				m_Collision = 0x0,
				m_vecMins = 0x0,
				m_vecMaxs = 0x0,
				m_Move = 0x0,
				m_flFlashDuration = 0x0,
				m_bSpottedByMask = 0x0,
				m_iCrossHairID = 0x0,
				m_bDormant = 0x0,
				m_vecPunch = 0x0,
				m_GunGameImmunity = 0x0,
				m_bIsScoped = 0x0,
				m_flLowerBodyYawTarget = 0x0;
		}

		namespace Weapon
		{
			DWORD_PTR
				m_iClip1 = 0x0,
				m_flNextPrimaryAttack = 0x0,
				m_fAccuracyPenalty = 0x0,
				m_iItemDefinitionIndex = 0x0,
				m_OriginalOwnerXuidLow = 0x0,
				m_OriginalOwnerXuidHigh = 0x0,
				m_nFallbackSeed = 0x0,
				m_nFallbackPaintKit = 0x0,
				m_flFallbackWear = 0x0,
				m_iItemIDHigh = 0x0,
				m_nFallbackStatTrak = 0x0,
				m_hMyWeapons = 0x0,
				m_AttributeManager = 0x0,
				m_Item = 0x0,
				m_iAccountID = 0x0,
				m_iEntityQuality = 0x0,
				m_szCustomName = 0x0,
				m_iWeaponID = 0x0,
				m_hActiveWeapon = 0x0;
		}
		void Initialize()
		{
			Entity::m_iHealth = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_iHealth"));
			Entity::m_iTeamNum = GetNetVar(XorStr("DT_BaseEntity")/**/, XorStr("m_iTeamNum"));
			Entity::m_fFlags = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_fFlags"));
			Entity::m_lifeState = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_lifeState"));
			Entity::m_Local = GetNetVar(XorStr("DT_CSLocalPlayerExclusive")/**/, XorStr("m_Local"));
			//

			Entity::m_bIsScoped = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_bIsScoped"));

			Entity::m_aimPunchAngle = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_aimPunchAngle"));//
			Entity::m_viewPunchAngle = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_viewPunchAngle"));


			Entity::m_flLowerBodyYawTarget = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_flLowerBodyYawTarget"));

			Entity::m_vecOrigin = GetNetVar(XorStr("DT_CSLocalPlayerExclusive")/**/, XorStr("m_vecOrigin"));
			Entity::m_vecViewOffset = GetNetVar(XorStr("DT_CSLocalPlayerExclusive")/**/, XorStr("m_vecViewOffset[0]"));

			Entity::m_nTickBase = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_nTickBase"));//

			Entity::m_nHitboxSet = GetNetVar(XorStr("DT_BaseAnimating")/**/, XorStr("m_nHitboxSet"));
			Entity::m_hActiveWeapon = GetNetVar(XorStr("DT_BaseCombatCharacter")/**/, XorStr("m_hActiveWeapon"));
			Entity::m_flC4Blow = GetNetVar(XorStr("DT_PlantedC4")/**/, XorStr("m_flC4Blow"));

			Entity::m_vecVelocity = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_vecVelocity[0]"));


			Entity::m_angEyeAngles = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_angEyeAngles[0]"));
			Entity::m_ArmorValue = GetNetVar(XorStr("DT_CSPlayer")/*DT_CSPlayer*/, XorStr("m_ArmorValue"));
			Entity::m_bHasHelmet = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_bHasHelmet"));
			Entity::m_bIsDefusing = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_bIsDefusing"));
			Entity::m_flFlashDuration = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_flFlashDuration"));
			Entity::m_bSpottedByMask = GetNetVar(XorStr("DT_BaseEntity")/**/, XorStr("m_bSpottedByMask"));
			Entity::m_iCrossHairID = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_bHasDefuser")) + 0x5C;

			Entity::m_bDormant = GetNetVar(XorStr("DT_BaseEntity")/**/, XorStr("m_bDormant"));
			Entity::m_iShotsFired = GetNetVar(XorStr("DT_CSLocalPlayerExclusive")/**/, XorStr("m_iShotsFired"));
			Entity::m_bIsBroken = GetNetVar(XorStr("DT_BreakableSurface")/**/, XorStr("m_bIsBroken"));
			Entity::m_CollisionGroup = GetNetVar(XorStr("DT_BaseEntity")/**/, XorStr("m_CollisionGroup"));
			Entity::m_Collision = GetNetVar(XorStr("DT_BaseEntity")/**/, XorStr("m_Collision"));
			Entity::m_vecMins = GetNetVar(XorStr("DT_CollisionProperty")/**/, XorStr("m_vecMins"));
			Entity::m_vecMaxs = GetNetVar(XorStr("DT_CollisionProperty")/**/, XorStr("m_vecMaxs"));
			Entity::m_vecPunch = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_Local")) + 0x70;
			Entity::m_Move = GetNetVar(XorStr("DT_CSPlayer")/**/, XorStr("m_iMoveState"));
			Entity::m_rgflCoordinateFrame = Entity::m_CollisionGroup - 0x30;
			Entity::m_GunGameImmunity = GetNetVar(XorStr("DT_CSPlayer"), XorStr("m_bGunGameImmunity"));


			Weapon::m_flNextPrimaryAttack = GetNetVar(XorStr("DT_LocalActiveWeaponData")/**/, XorStr("m_flNextPrimaryAttack"));
			Weapon::m_iClip1 = GetNetVar(XorStr("DT_LocalWeaponData")/**/, XorStr("m_iClip1"));
			Weapon::m_fAccuracyPenalty = GetNetVar(XorStr("DT_WeaponCSBase")/**/, XorStr("m_fAccuracyPenalty"));
			Weapon::m_iItemDefinitionIndex = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_iItemDefinitionIndex"));
			Weapon::m_OriginalOwnerXuidLow = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_OriginalOwnerXuidLow"));
			Weapon::m_OriginalOwnerXuidHigh = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_OriginalOwnerXuidHigh"));
			Weapon::m_nFallbackPaintKit = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_nFallbackPaintKit"));
			Weapon::m_nFallbackSeed = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_nFallbackSeed"));
			Weapon::m_flFallbackWear = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_flFallbackWear"));
			Weapon::m_iItemIDHigh = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_iItemIDHigh"));
			Weapon::m_nFallbackStatTrak = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_nFallbackStatTrak"));
			Weapon::m_hMyWeapons = GetNetVar(XorStr("DT_BasePlayer")/**/, XorStr("m_hMyWeapons"));
			Weapon::m_AttributeManager = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_AttributeManager"));
			Weapon::m_Item = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_Item"));
			Weapon::m_iAccountID = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_iAccountID"));
			Weapon::m_iEntityQuality = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_iEntityQuality"));
			Weapon::m_szCustomName = GetNetVar(XorStr("DT_BaseAttributableItem")/**/, XorStr("m_szCustomName"));
			Weapon::m_hActiveWeapon = GetNetVar(XorStr("DT_BaseCombatCharacter")/**/, XorStr("m_hActiveWeapon"));
			Weapon::m_iWeaponID = GetNetVar(XorStr("DT_WeaponCSBase")/**/, XorStr("m_fAccuracyPenalty")) + 0x2C;

			//|DT_CSPlayer-> m_bInBombZone = 0x000038D0 (int)
			//| DT_CSPlayer->m_bInBuyZone = 0x000038D1 (int)
			// |DT_CSPlayer-> m_bHasDefuser = 0x0000AA14 (int)
			// |DT_CSPlayer-> m_bIsDefusing                            = 0x000038A4 (int)
			// |DT_CSPlayer-> m_bGunGameImmunity                       = 0x000038B0 (int)
			// |DT_CSPlayer                                 -> m_bHasHelmet                             = 0x0000A9FC (int)
			//| DT_CSPlayer->m_bHasHeavyArmor = 0x0000A9FD (int)
			//| | DT_BasePlayer->m_iFOV = 0x000031D4 (int)
			//	| | DT_BasePlayer->m_iFOVStart = 0x000031D8 (int)
			//	| | DT_BasePlayer->m_flFOVTime = 0x000031F8 (float)
			//	| | DT_BasePlayer->m_iDefaultFOV = 0x0000332C (int)
			//| DT_WeaponCSBaseGun->m_zoomLevel = 0x00003350 (int)

		}


	}
}