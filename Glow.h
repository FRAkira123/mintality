#pragma once

struct
{
	Color Weapon = Color(255, 0, 0, 255);
	Color Player = Color(255, 0, 0, 255);
	Color MyPlayer = Color(0, 255, 0, 255);
	Color C4 = Color(0, 255, 0, 255);
	Color PlantedC4 = Color(255, 0, 255, 255);
}GlowColors;

bool GlowVars[] = { 0,0,0,0 };
DWORD GlowManager = *reinterpret_cast<DWORD*>(FindPatternWithoutMask("client.dll", "0F 11 ? ? ? ? ? 83 C8 01 C7 05 ? ? ? ? ? ? ? ? 0F 28 ? ? ? ? ? 68") + 0x3);


void DrawGlow()
{

	auto GlowObjectManager = (CGlowObjectManager*)GlowManager;
	auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (!pLocalEntity || !GlowObjectManager)
		return;

	for (int i = 0; i < GlowObjectManager->size; ++i)
	{
		auto glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		auto Entity = glowEntity->getEntity();

		if (glowEntity->IsEmpty() || !Entity || Entity == pLocalEntity)
			continue;

		if (pLocalEntity->GetHealth() <= 0)
			continue;

		if (Vars.Visuals.Glows.c4 && (strstr(Entity->GetClientClass()->m_pName, XorStr("Planted")) || strstr(Entity->GetClientClass()->m_pName, XorStr("C4"))))
			glowEntity->set(GlowColors.C4);

		if (Vars.Visuals.Glows.player && strstr(Entity->GetClientClass()->m_pName, XorStr("CCSPlayer")) && (Entity->IsValid()))
			if (Vars.Visuals.Glows.ourPlayers)
			{
				if (Entity->GetTeamNum() != pLocalEntity->GetTeamNum())
					glowEntity->set(GlowColors.Player);
				else
					glowEntity->set(GlowColors.MyPlayer);
			}
			else
				if (Entity->GetTeamNum() != pLocalEntity->GetTeamNum())
					glowEntity->set(GlowColors.Player);

		if (Vars.Visuals.Glows.weapon)
			if (strstr(Entity->GetClientClass()->m_pName, XorStr("Weapon"))
				|| strstr(Entity->GetClientClass()->m_pName, XorStr("AK47"))
				|| strstr(Entity->GetClientClass()->m_pName, XorStr("DEagle"))
				|| strstr(Entity->GetClientClass()->m_pName, XorStr("Grenade"))
				)
				glowEntity->set(GlowColors.Weapon);

	}

}

