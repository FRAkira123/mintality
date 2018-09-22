//#pragma once
//
//using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
//using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);
//
//InitKeyValuesFn InitKeyValuesEx = nullptr;
//LoadFromBufferFn LoadFromBufferEx = nullptr;
//
//
//DWORD dwFunction1 = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 51 33 C0 C7 45"));
//
//void InitKeyValues(KeyValues* pKeyValues, const char* name)
//{
//	InitKeyValuesEx = reinterpret_cast<InitKeyValuesFn>(dwFunction1);
//	InitKeyValuesEx(pKeyValues, name);
//}
//DWORD dwFunction2 = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
//
//void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr)
//{
//	LoadFromBufferEx = reinterpret_cast<LoadFromBufferFn>(dwFunction2);
//	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
//}
//
//IMaterial* visible_tex = nullptr;
//IMaterial* hidden_tex = nullptr;
//IMaterial* visible_flat = nullptr;
//IMaterial* hidden_flat = nullptr;
//
//IMaterial* WireFreame_vis = nullptr;
//IMaterial* WireFreame_hid = nullptr;
//
//typedef void(__thiscall* IDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
//IDrawModelExecute oDrawModelExecute = nullptr;
//
//int created = 0;
//IMaterial* IMaterialSystem::CreateMaterial(bool flat, bool ignorez, bool wireframed)
//{
//	std::string type = (flat) ? XorStr("UnlitGeneric") : XorStr("VertexLitGeneric");
//
//	std::string matdata = XorStr("\"") + type + XorStr("\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"") + std::to_string(wireframed) + XorStr("\"\n\t\"$ignorez\" \"") + std::to_string(ignorez) + XorStr("\"\n}\n");
//
//	std::string matname = XorStr("custom_") + std::to_string(created);
//	++created;
//
//	KeyValues* pKeyValues = new KeyValues(matname.c_str());
//	InitKeyValues(pKeyValues, type.c_str());
//	LoadFromBuffer(pKeyValues, matname.c_str(), matdata.c_str());
//
//	typedef IMaterial*(__thiscall* OriginalFn)(void*, const char *pMaterialName, KeyValues *pVMTKeyValues);
//	auto* createdMaterial = call_vfunc<OriginalFn>(this, 83)(this, matname.c_str(), pKeyValues);
//
//	createdMaterial->IncrementReferenceCount();
//
//	return createdMaterial;
//}
//IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix)
//{
//	typedef IMaterial*(__thiscall* OriginalFn)(void*, char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
//	return call_vfunc<OriginalFn>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
//}
//
//
//void ForceMaterial(IMaterial* material, Color color)
//{
//	if (material != nullptr)
//	{
//		RenderView->SetColorModulation(color.Base());
//		ModelRender->ForcedMaterialOverride(material);
//	}
//}
//
//
//
//bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
//{
//	CMutant Mute;
//	Mute.MutantFunc((DWORD)Do_Chams);
//
//	static auto* Covered_Lit = pMatSystem->CreateMaterial(true, true, false);
//	static auto* Visable_Lit = pMatSystem->CreateMaterial(false, true, false);
//
//	auto* Model_Entity = pClientEntList->GetClientEntity(pInfo.entity_index);
//	auto LocalPlayer = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());
//
//	if (!Model_Entity || !LocalPlayer)
//		return false;
//
//	auto Model_Name = pModelInfo->GetModelName(const_cast< model_t* >(pInfo.pModel));
//
//	if (Vars.Visuals.Chams.Enabled)
//	{
//		if (pEngine->IsInGame() && LocalPlayer->GetHealth() > 0)
//		{
//			if (Model_Entity->IsPlayer())
//			{
//				if (Model_Entity->GetTeamNum() == LocalPlayer->GetTeamNum() && !Vars.Visuals.Chams.Enabled)
//					return false;
//
//
//				if (Model_Entity->GetTeamNum() != LocalPlayer->GetTeamNum())
//				{
//					if (IsVisible(Model_Entity))
//					{
//						if (Model_Entity->GetTeamNum() == 2)
//							Visable_Lit->ColorModulate(255.f / 255.f, 0.f / 255.f, 0.f / 255.f); // t colour Visable				
//						else
//							Visable_Lit->ColorModulate(0.f / 255.f, 0.f / 255.f, 255.f / 255.f); // ct colour Visable
//
//
//						if (Model_Entity->HasGunGameImmunity())
//							Visable_Lit->AlphaModulate(0.2f);
//						else
//							Visable_Lit->AlphaModulate(1.f);
//
//						ModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
//						oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//
//					}
//					else
//					{
//						if (Model_Entity->GetTeamNum() == 2)
//							Covered_Lit->ColorModulate(20.f / 255.f, 0.f / 255.f, 0.f / 255.f); // t colour				
//						else
//							Covered_Lit->ColorModulate(0.f / 255.f, 0.f /20.f, 180.f / 255.f); // ct colour
//
//
//						if (Model_Entity->HasGunGameImmunity())
//							Covered_Lit->AlphaModulate(0.2f);
//						else
//							Covered_Lit->AlphaModulate(1.0f);
//
//						ModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
//						oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//					}
//				}
//				
//
//				return true;
//			}
//
//		}
//
//	}
//	return false;
//}
//
//
//
//void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
//{
//
//	if (!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
//		oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//	ModelRender->ForcedMaterialOverride(nullptr, OVERRIDE_NORMAL);
//}
//
//

#pragma once

using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);

InitKeyValuesFn InitKeyValuesEx = nullptr;
LoadFromBufferFn LoadFromBufferEx = nullptr;


DWORD dwnitKeyValuesEx = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 51 33 C0 C7 45"));
void InitKeyValues(KeyValues* pKeyValues, const char* name)
{
	InitKeyValuesEx = (InitKeyValuesFn)(dwnitKeyValuesEx);
	InitKeyValuesEx(pKeyValues, name);
}

DWORD dwLoadFromBufferEx = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr)
{
	LoadFromBufferEx = (LoadFromBufferFn)(dwLoadFromBufferEx);
	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}



using IDrawModelExecute = void*(__stdcall*)(void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
IDrawModelExecute oDrawModelExecute = nullptr;

//int created = 0;
IMaterial* IMaterialSystem::CreateMaterial(bool flat, bool ignorez, bool wireframed)
{
	std::string type = (flat) ? "UnlitGeneric" : "VertexLitGeneric";

	std::string matdata = "\"" + type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" + std::to_string(wireframed) + "\"\n\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n}\n";

	std::string materialName = "WhiteWhater_" + std::to_string(GetRandom(10, 100000));
	KeyValues* keyValues = new KeyValues(materialName.c_str());

	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, materialName.c_str(), matdata.c_str(), nullptr, NULL, nullptr);

	typedef IMaterial*(__thiscall* OriginalFn)(void*, const char *pMaterialName, KeyValues *pVMTKeyValues);
	IMaterial* createdMaterial = call_vfunc<OriginalFn>(this, 83)(this, materialName.c_str(), keyValues);


	return createdMaterial;

}
IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix)
{
	typedef IMaterial*(__thiscall* OriginalFn)(void*, char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
	return call_vfunc<OriginalFn>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}


void ForceMaterial(IMaterial* material, float* color)
{
	if (material != NULL)
	{
		RenderView->SetColorModulation(color);
		ModelRender->ForcedMaterialOverride(material);
	}
}


void ForceMaterial(IMaterial* material, Color color)
{
	if (material != NULL)
	{
		RenderView->SetColorModulation(color.Base());
		ModelRender->ForcedMaterialOverride(material);
	}
}

//
//bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
//{
//	static auto* Covered_Lit = pMatSystem->CreateMaterial(Vars.Visuals.Chams.Mode == 0 ? true : false, true, Vars.Visuals.Chams.Wireframe ? true : false);
//	static auto* Visable_Lit = pMatSystem->CreateMaterial(Vars.Visuals.Chams.Mode == 0 ? true : false, true, Vars.Visuals.Chams.Wireframe ? true : false);
//
//	auto Model_Entity = pClientEntList->GetClientEntity(pInfo.entity_index);
//	auto LocalPlayer = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());
//
//	if (!Model_Entity || !LocalPlayer)
//		return false;
//
//	auto Model_Name = pModelInfo->GetModelName(const_cast< model_t* >(pInfo.pModel));
//
//	if (Vars.Visuals.Chams.Enabled)
//	{
//		if (pEngine->IsInGame() && LocalPlayer->GetHealth() > 0)
//		{
//			if (Model_Entity->IsPlayer())
//			{
//				if (Model_Entity->GetTeamNum() == LocalPlayer->GetTeamNum() && !Vars.Visuals.Chams.Enabled)
//					return false;
//
//				if (IsVisible(Model_Entity))
//				{
//					if (Model_Entity->GetTeamNum() == 2)				
//						Visable_Lit->ColorModulate(int(Vars.Visuals.Chams.Visible[0] * 255.f), int(Vars.Visuals.Chams.Visible[1] * 255.f), int(Vars.Visuals.Chams.Visible[2] * 255.f)); // t colour Visable				
//					else	
//						Visable_Lit->ColorModulate(int(Vars.Visuals.Chams.Invisible[0] * 255.f), int(Vars.Visuals.Chams.Invisible[1] * 255.f), int(Vars.Visuals.Chams.Invisible[2] * 255.f)); // ct colour Visable				
//
//					if (Model_Entity->HasGunGameImmunity())
//						Visable_Lit->AlphaModulate(0.75f);
//					else
//						Visable_Lit->AlphaModulate(1.f);
//
//					ModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
//					oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//
//				}
//				else
//				{
//					if (Model_Entity->GetTeamNum() == 2)
//						Covered_Lit->ColorModulate(int(Vars.Visuals.Chams.Visible[0] * 255.f), int(Vars.Visuals.Chams.Visible[1] * 255.f), int(Vars.Visuals.Chams.Visible[2] * 255.f)); // t colour				
//					else
//						Covered_Lit->ColorModulate(int(Vars.Visuals.Chams.Invisible[0] * 255.f), int(Vars.Visuals.Chams.Invisible[1] * 255.f), int(Vars.Visuals.Chams.Invisible[2] * 255.f)); // ct colour
//					
//
//					if (Model_Entity->HasGunGameImmunity())
//						Covered_Lit->AlphaModulate(0.55f);
//					else
//						Covered_Lit->AlphaModulate(0.8f);
//
//					ModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
//					oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//				}
//
//				
//
//				return true;
//			}
//
//		}
//
//
//
//
//	}
//	return false;
//}
//
//
//
//void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
//{
//
//	if (!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
//		oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
//	ModelRender->ForcedMaterialOverride(nullptr, OVERRIDE_NORMAL);
//}
//
//

bool IClientEntity::IsEnemy()
{
	if (!pEngine->IsConnected())
		return false;

	return (this->GetTeamNum() == Global::LocalPlayer->GetTeamNum() || this->GetTeamNum() == 0 || this->GetIndex() == Global::LocalPlayer->GetIndex()) ? false : true;
}

void __stdcall Hooked_DrawModelExecute(void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld)
{
	pModellHook->UnHook();

	auto LocalPlayer = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!LocalPlayer)
		return;


	static auto	visible_flat = pMatSystem->CreateMaterial(true, false, false);
	static auto	visible_tex = pMatSystem->CreateMaterial(false, false, false);
	static auto	hidden_flat = pMatSystem->CreateMaterial(true, true, false);
	static auto	hidden_tex = pMatSystem->CreateMaterial(false, true, false);

	if (pEngine->IsInGame() && LocalPlayer && pEngine->IsConnected())
	{
		if (info.pModel && Vars.Visuals.Chams.Enabled)
		{
			if (!Vars.Visuals.AntiSS || !pEngine->IsTakingScreenshot() && Vars.Visuals.AntiSS)
			{
				std::string modelName = pModelInfo->GetModelName(info.pModel);
				const char* ModelName = pModelInfo->GetModelName((model_t*)info.pModel);

				if (Vars.Visuals.Enabled)
				{
					if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 1)
					{
						static IMaterial* Hands = pMatSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
						Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
						ModelRender->ForcedMaterialOverride(Hands);
					}
					else if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 2)
					{
						static IMaterial* Hands = pMatSystem->CreateMaterial(false, false, false);

						static int counter = 0;
						static float colors[4] = { 1.f, 0.f, 0.f, 1.f };


						ModelRender->ForcedMaterialOverride(Hands);
					}
					else if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 3)
					{
						static IMaterial* Hands = pMatSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
						Hands->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, true);
						Hands->ColorModulate(0.f, 0.f, 0.f);
						Hands->AlphaModulate(0.5f);
						ModelRender->ForcedMaterialOverride(Hands);
					}
					else if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 4)
					{
						static IMaterial* Hands = pMatSystem->CreateMaterial(false, false, true);

						static int counter = 0;
						static float colors[4] = { 0.f, 0.f, 0.f, 1.f };

						ModelRender->ForcedMaterialOverride(Hands);
					}
					else if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 5)
					{
						static IMaterial* Hands = pMatSystem->CreateMaterial(false, false, false);
						static IMaterial* Wireframe = pMatSystem->CreateMaterial(false, false, true);


						ModelRender->ForcedMaterialOverride(Hands);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

						ModelRender->ForcedMaterialOverride(Wireframe);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
					else if (modelName.find(XorStr("arms")) != std::string::npos && Vars.Visuals.HandsType == 6)
					{
						static IMaterial* Hands = pMatSystem->CreateMaterial(false, false, false);

						static int counter = 0;
						static float colors[3] = { 1.f, 0.f, 0.f };

						if (colors[counter] >= 1.0f)
						{
							colors[counter] = 1.0f;
							counter += 1;
							if (counter > 2)
								counter = 0;
						}
						else
						{
							int prev = counter - 1;
							if (prev < 0) prev = 2;
							colors[prev] -= 0.004f;
							colors[counter] += 0.004f;
						}

						RenderView->SetColorModulation(colors);
						RenderView->SetBlend(0.7f);
						ModelRender->ForcedMaterialOverride(Hands);
					}
				}

				if (modelName.find(("arms")) != std::string::npos && (Vars.Visuals.RemovalsHands || Vars.Visuals.Chams.hands || Vars.Visuals.Chams.RainbowHands))
				{
					auto pModelEntity = pClientEntList->GetClientEntity(info.entity_index);
					if (Vars.Visuals.Chams.RainbowHands)
					{
						IMaterial* Hands = pMatSystem->FindMaterial(modelName.c_str(), (TEXTURE_GROUP_MODEL));
						Hands->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						static float rainbow;
						rainbow += (Vars.Visuals.Chams.RainbowTime / 100000);
						if (rainbow > 1.f) rainbow = 0.f;
						Color render_color_visible = Color::FromHSB(rainbow, 1.f, 1.f);
						if (Vars.Visuals.Chams.Mode == 0)
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						else
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

						ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
					else
					{
						IMaterial* Hands = pMatSystem->FindMaterial(modelName.c_str(), (TEXTURE_GROUP_MODEL));
						if (Vars.Visuals.RemovalsHands) {
							Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
							ModelRender->ForcedMaterialOverride(Hands);
						}

						auto ChamsLV = Vars.g_iChamsLV;
						auto ChamsLH = Vars.g_iChamsLH;

						Color render_color_hidden = LocalPlayer->GetTeamNum() ? Color(int(ChamsLH[0] * 255.0f), int(ChamsLH[1] * 255.0f), int(ChamsLH[2] * 255.0f), 255) : Color(int(ChamsLH[0] * 255.0f), int(ChamsLH[1] * 255.0f), int(ChamsLH[2] * 255.0f), 255);
						Color render_color_visible = LocalPlayer->GetTeamNum() ? Color(int(ChamsLV[0] * 255.0f), int(ChamsLV[1] * 255.0f), int(ChamsLV[2] * 255.0f), 255) : Color(int(ChamsLV[0] * 255.0f), int(ChamsLV[1] * 255.0f), int(ChamsLV[2] * 255.0f), 255);

						if (LocalPlayer->IsScoped())
						{
							Color render_color_hidden = LocalPlayer->GetTeamNum() ? Color(int(ChamsLH[0] * 255.0f), int(ChamsLH[1] * 255.0f), int(ChamsLH[2] * 255.0f), 100) : Color(int(ChamsLH[0] * 255.0f), int(ChamsLH[1] * 255.0f), int(ChamsLH[2] * 255.0f), 100);
							Color render_color_visible = LocalPlayer->GetTeamNum() ? Color(int(ChamsLV[0] * 255.0f), int(ChamsLV[1] * 255.0f), int(ChamsLV[2] * 255.0f), 100) : Color(int(ChamsLV[0] * 255.0f), int(ChamsLV[1] * 255.0f), int(ChamsLV[2] * 255.0f), 100);

						}

						if (Vars.Visuals.Chams.hands)
						{
							if (Vars.Visuals.Chams.XQZ)
							{
								ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
								ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
							}

							if (Vars.Visuals.Chams.Mode == 0)
								hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							else
								hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
				}

				if (modelName.find(("models/player")) != std::string::npos && Vars.Visuals.Chams.Enabled)
				{
					player_info_t pInfo; player_info_t localinfo;
					pEngine->GetPlayerInfo(info.entity_index, &pInfo); pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &localinfo);

					auto pModelEntity = pClientEntList->GetClientEntity(info.entity_index);
					if (pModelEntity && pModelEntity->GetAlive() && !pModelEntity->IsDormant())
					{

						if ((Vars.Visuals.Filter.Friendlies && !pModelEntity->IsEnemy()) || (Vars.Visuals.Filter.Enemies && pModelEntity->IsEnemy()))
						{
							auto ChamsCTV = Vars.g_iChamsCTV; auto ChamsTV = Vars.g_iChamsTV;
							auto ChamsCTH = Vars.g_iChamsCTH; auto ChamsTH = Vars.g_iChamsTH;

							auto render_color_hidden = pModelEntity->GetTeamNum() == 2 ? ChamsTH : ChamsCTH;
							auto render_color_visible = pModelEntity->GetTeamNum() == 2 ? ChamsTV : ChamsCTV;

							if (Vars.Visuals.Chams.XQZ)
							{
								ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
								ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);


								if (Vars.Visuals.Chams.Mode == 0)
									hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
								else
									hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

							}

							if (Vars.Visuals.Chams.Mode == 0)
								visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
							else
								visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

							ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
							ModelRender->ForcedMaterialOverride(visible_flat);
							ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

						}

						if ((Vars.Visuals.Filter.Localplayer && pModelEntity == LocalPlayer))
						{
							auto ChamsLV = Vars.g_iChamsLV;
							auto ChamsLH = Vars.g_iChamsLH;

							if (LocalPlayer->IsScoped())
							{

								auto render_color_hidden = LocalPlayer->GetTeamNum() ? ChamsLH : ChamsLH;
								auto render_color_visible = LocalPlayer->GetTeamNum() ? ChamsLV : ChamsLV;

								if (Vars.Visuals.Chams.XQZ)
								{
									ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
									ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

									if (Vars.Visuals.Chams.Mode == 0)
										hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
									else
										hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

								}

								if (Vars.Visuals.Chams.Mode == 0)
									visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
								else
									visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

								ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
								ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

							}
							else
							{

								auto render_color_hidden = LocalPlayer->GetTeamNum() ? ChamsLH : ChamsLH;
								auto render_color_visible = LocalPlayer->GetTeamNum() ? ChamsLV : ChamsLV;

								if (Vars.Visuals.Chams.XQZ)
								{
									ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
									ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);


									if (Vars.Visuals.Chams.Mode == 0)
										hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
									else
										hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

								}

								if (Vars.Visuals.Chams.Mode == 0)
									visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
								else
									visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

								ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
								ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

							}


						}

					}
				}

				if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 1)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
						Weapon->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
						ModelRender->ForcedMaterialOverride(Weapon);
					}
				}
				else if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 2)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->CreateMaterial(false, false, false);
						static float colors[3] = { 1.f, 1.f, 0.f };

						RenderView->SetBlend(1.0f);
						ModelRender->ForcedMaterialOverride(Weapon);
					}
				}
				else if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 3)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->FindMaterial(modelName.c_str(), XorStr(TEXTURE_GROUP_MODEL));
						Weapon->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, true);
						Weapon->ColorModulate(0.f, 0.f, 0.f);
						Weapon->AlphaModulate(0.5f);
						ModelRender->ForcedMaterialOverride(Weapon);
					}
				}
				else if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 4)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->CreateMaterial(false, false, true);

						static int counter = 0;
						static float colors[4] = { 0.f, 0.f, 0.f, 1.f };

						ModelRender->ForcedMaterialOverride(Weapon);
					}
				}
				else if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 5)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->CreateMaterial(false, false, false);
						static IMaterial* Wireframe = pMatSystem->CreateMaterial(false, false, true);

						ModelRender->ForcedMaterialOverride(Weapon);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);


						ModelRender->ForcedMaterialOverride(Wireframe);
						ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
				}
				else if (modelName.find(("weapon")) != std::string::npos && Vars.Visuals.WeaponsType == 6)
				{
					if (!(modelName.find(("arms")) != std::string::npos))
					{
						static IMaterial* Weapon = pMatSystem->CreateMaterial(false, false, false);

						static int counter = 0;
						static float colors[3] = { 1.f, 0.f, 0.f };

						if (colors[counter] >= 1.0f)
						{
							colors[counter] = 1.0f;
							counter += 1;
							if (counter > 2)
								counter = 0;
						}
						else
						{
							int prev = counter - 1;
							if (prev < 0) prev = 2;
							colors[prev] -= 0.004f;
							colors[counter] += 0.004f;
						}

						RenderView->SetColorModulation(colors);
						RenderView->SetBlend(0.7f);
						ModelRender->ForcedMaterialOverride(Weapon);
					}
				}

				

				if (modelName.find(("flash")) != std::string::npos && Vars.Visuals.RemovalsFlash)
				{
					IMaterial* flash = pMatSystem->FindMaterial(("effects\\flashbang"), (TEXTURE_GROUP_CLIENT_EFFECTS));
					IMaterial* flashWhite = pMatSystem->FindMaterial(("effects\\flashbang_white"), (TEXTURE_GROUP_CLIENT_EFFECTS));
					flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					ModelRender->ForcedMaterialOverride(flash);
					ModelRender->ForcedMaterialOverride(flashWhite);
				}


			}
		}


	}


	ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
	ModelRender->ForcedMaterialOverride(NULL);
	pModellHook->ReHook();
}
