#pragma once
using OverrideViewFn = void(__fastcall*)(void*, void*, CViewSetup*);
OverrideViewFn oOverrideView = nullptr;

extern Variables Vars;
void __fastcall HookedOverrideView(void* ecx, void* edx, CViewSetup* pSetup)
{
	if (pEngine->IsInGame())
	{
		auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

		if (pLocalEntity == nullptr || pLocalEntity->IsValid() == false)
			return;

		if (Vars.Misc.FC == true && !pLocalEntity->IsScoped())
			pSetup->fov += Vars.Misc.FOV;

	}
	oOverrideView(ecx, edx, pSetup);
}

typedef float(__stdcall *GetViewModelFOVFn)();
GetViewModelFOVFn pGetViewModelFOV = nullptr;

float __stdcall hkGetViewModelFOV()
{
	auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocalEntity == nullptr || pLocalEntity->IsValid() == false)
		return pGetViewModelFOV();

	if (Vars.Misc.FCV && !pLocalEntity->IsScoped())
		return Vars.Misc.FOVV;
	else
		return pGetViewModelFOV();
}
