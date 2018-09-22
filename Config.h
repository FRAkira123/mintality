#pragma once

#include "IniReader.h"
#include "IniWriter.h"
//
//extern Variables Vars;
//
//
//namespace Config
//{
//	const char* config_path = "";
//	void SetupPath()
//	{
//		CreateDirectory("C:\\XVIIProject", NULL);
//		config_path = "C:\\XVIIProject\\XVIIProjectConfig.ini";
//	}
//
//	void Read()
//	{
//		CIniReader reader(config_path);
//
//		Vars.VisualMenu.Player2DBox = reader.ReadBoolean(XorStr("ESP"), XorStr("|2D Бокс"), false);
//		Vars.VisualMenu.Player3DBox = reader.ReadBoolean(XorStr("ESP"), XorStr("|3D Бокс"), false);
//
//		//Vars.VisualMenu.Player3DBox = reader.ReadFloat(XorStr("ESP"), XorStr("|3D Бокс"), 0.f);
//
//
//		//Options::Visuals::Chams::color[0] = reader.ReadInteger(XorStr("Chams"), XorStr("|VisibleColorR"), 0) / 255.f;
//
//	//	for (int i = 1; i < 520; i++)
//	//	{
//	//		char* section = U::GetConfigName(i);
//	//		if (strcmp(section, "") == 0)
//	//			continue;
//
//	//		weapons[i].Enabled = reader.ReadBoolean(section, XorStr("|Enabled"), weapons[i].Enabled);
//	//		weapons[i].Fov = reader.ReadFloat(section, XorStr("|Fov"), weapons[i].Fov);
//	//		weapons[i].Bone = reader.ReadInteger(section, XorStr("|Bone"), weapons[i].Bone);
//	//		weapons[i].Nearest = reader.ReadBoolean(section, XorStr("|Nearest"), weapons[i].Nearest);
//	//		weapons[i].NearestType = reader.ReadInteger(section, XorStr("|NearestType"), weapons[i].NearestType);
//	//		weapons[i].Smooth = reader.ReadFloat(section, XorStr("|Smooth"), weapons[i].Smooth);
//	//		weapons[i].FireDelayEnabled = reader.ReadBoolean(section, XorStr("|FireDelayEnabled"), weapons[i].FireDelayEnabled);
//	//		weapons[i].FireDelayRepeat = reader.ReadBoolean(section, XorStr("|FireDelayRepeat"), weapons[i].FireDelayRepeat);
//	//		weapons[i].FireDelay = reader.ReadFloat(section, XorStr("|FireDelay"), weapons[i].FireDelay);
//	//		weapons[i].StartBullet = reader.ReadInteger(section, XorStr("|StartBullet"), weapons[i].StartBullet);
//	//		weapons[i].EndBullet = reader.ReadInteger(section, XorStr("|EndBullet"), weapons[i].EndBullet);
//	//		weapons[i].RcsX = reader.ReadInteger(section, XorStr("|RcsX"), weapons[i].RcsX);
//	//		weapons[i].RcsY = reader.ReadInteger(section, XorStr("|RcsY"), weapons[i].RcsY);
//
//	//		weapons[i].pSilent = reader.ReadBoolean(section, XorStr("|pSilent"), weapons[i].pSilent);
//	//		weapons[i].pSilentBullet = reader.ReadInteger(section, XorStr("|pSilentBullet"), weapons[i].pSilentBullet);
//	//		weapons[i].pSilentHitchance = reader.ReadInteger(section, XorStr("|pSilentHitchance"), weapons[i].pSilentHitchance);
//	//		weapons[i].pSilentFov = reader.ReadFloat(section, XorStr("|pSilentFov"), weapons[i].pSilentFov);
//	//		weapons[i].pSilentSmooth = reader.ReadFloat(section, XorStr("|pSilentSmooth"), weapons[i].pSilentSmooth);
//
//	//		weapons[i].ChangerEnabled = reader.ReadBoolean(section, XorStr("|ChangerEnabled"), weapons[i].ChangerEnabled);
//	//		//reader.ReadString(section, XorStr("|ChangerName"), weapons[i].ChangerName, weapons[i].ChangerName);
//	//		weapons[i].ChangerSeed = reader.ReadInteger(section, XorStr("|ChangerSeed"), weapons[i].ChangerSeed);
//	//		weapons[i].ChangerSkin = reader.ReadInteger(section, XorStr("|ChangerSkin"), weapons[i].ChangerSkin);
//	//		weapons[i].ChangerStatTrak = reader.ReadInteger(section, XorStr("|ChangerStatTrak"), weapons[i].ChangerStatTrak);
//	//		weapons[i].ChangerWear = reader.ReadFloat(section, XorStr("|ChangerWear"), weapons[i].ChangerWear);
//	//	}
//	//}
//	}
//
//	void Save()
//	{
//		CIniWriter writer(config_path);
//
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|2D Бокс"), Vars.VisualMenu.Player2DBox);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|3D Бокс"), Vars.VisualMenu.Player3DBox);
//
//
//	//	Vars.VisualMenu.Player2DBox = reader.ReadBoolean(XorStr("ESP"), XorStr("|2D Бокс"), false);
//	//	Vars.VisualMenu.Player3DBox = reader.ReadBoolean(XorStr("ESP"), XorStr("|3D Бокс"), false);
//
//	/*	writer.WriteBoolean(XorStr("Aimbot"), XorStr("|DrawFov"), Options::Aimbot::DrawFov);
//		writer.WriteBoolean(XorStr("Aimbot"), XorStr("|Deathmatch"), Options::Aimbot::Deathmatch);
//		writer.WriteBoolean(XorStr("Aimbot"), XorStr("|SmokeCheck"), Options::Aimbot::SmokeCheck);
//		writer.WriteInteger(XorStr("Aimbot"), XorStr("|AimType"), Options::Aimbot::AimType);
//		writer.WriteBoolean(XorStr("Aimbot"), XorStr("|KillDelay"), Options::Aimbot::KillDelay);
//		writer.WriteFloat(XorStr("Aimbot"), XorStr("|KillDelayTime"), Options::Aimbot::KillDelayTime);
//
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|Enabled"), Options::Visuals::ESP::Enabled);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|EnemyOnly"), Options::Visuals::ESP::EnemyOnly);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|VisibleOnly"), Options::Visuals::ESP::VisibleOnly);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|SmokeCheck"), Options::Visuals::ESP::SmokeCheck);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|Box"), Options::Visuals::ESP::Box);
//		writer.WriteInteger(XorStr("ESP"), XorStr("|Style"), Options::Visuals::ESP::Style);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|Name"), Options::Visuals::ESP::Name);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|Health"), Options::Visuals::ESP::Health);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|Weapon"), Options::Visuals::ESP::Weapon);
//		writer.WriteBoolean(XorStr("ESP"), XorStr("|WeaponAmmo"), Options::Visuals::ESP::WeaponAmmo);
//
//		writer.WriteBoolean(XorStr("Chams"), XorStr("|Enabled"), Options::Visuals::Chams::Enabled);
//		writer.WriteBoolean(XorStr("Chams"), XorStr("|EnemyOnly"), Options::Visuals::Chams::EnemyOnly);
//		writer.WriteBoolean(XorStr("Chams"), XorStr("|VisibleOnly"), Options::Visuals::Chams::VisibleOnly);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|Style"), Options::Visuals::Chams::Style);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorR"), Options::Visuals::Chams::color[0] * 255);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorG"), Options::Visuals::Chams::color[1] * 255);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorB"), Options::Visuals::Chams::color[2] * 255);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorR"), Options::Visuals::Chams::coloriz[0] * 255);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorG"), Options::Visuals::Chams::coloriz[1] * 255);
//		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorB"), Options::Visuals::Chams::coloriz[2] * 255);
//
//
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorVisR"), Options::Visuals::ESP::EnemyColorVis[0]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorVisG"), Options::Visuals::ESP::EnemyColorVis[1]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorVisB"), Options::Visuals::ESP::EnemyColorVis[2]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorInvisibleR"), Options::Visuals::ESP::EnemyColorInvis[0]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorInvisibleG"), Options::Visuals::ESP::EnemyColorInvis[1]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|EnemyColorInvisibleB"), Options::Visuals::ESP::EnemyColorInvis[2]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorVisibleR"), Options::Visuals::ESP::TeamColorVis[0]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorVisibleG"), Options::Visuals::ESP::TeamColorVis[1]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorVisibleB"), Options::Visuals::ESP::TeamColorVis[2]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorInvisibleR"), Options::Visuals::ESP::TeamColorInvis[0]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorInvisibleG"), Options::Visuals::ESP::TeamColorInvis[1]);
//		writer.WriteFloat(XorStr("ESP"), XorStr("|TeamColorInvisibleB"), Options::Visuals::ESP::TeamColorInvis[2]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorVisibleR"), Options::Visuals::ESP::ChamsColorVis[0]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorVisibleG"), Options::Visuals::ESP::ChamsColorVis[1]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorVisibleB"), Options::Visuals::ESP::ChamsColorVis[2]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorInvisibleR"), Options::Visuals::ESP::ChamsColorInvis[0]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorInvisibleG"), Options::Visuals::ESP::ChamsColorInvis[1]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|EnemyColorInvisibleB"), Options::Visuals::ESP::ChamsColorInvis[2]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorVisibleR"), Options::Visuals::ESP::TChamsColorVis[0]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorVisibleG"), Options::Visuals::ESP::TChamsColorVis[1]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorVisibleB"), Options::Visuals::ESP::TChamsColorVis[2]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorInvisibleR"), Options::Visuals::ESP::TChamsColorInvis[0]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorInvisibleG"), Options::Visuals::ESP::TChamsColorInvis[1]);
//		writer.WriteFloat(XorStr("Chams"), XorStr("|TeamColorInvisibleB"), Options::Visuals::ESP::TChamsColorInvis[2]);
//		writer.WriteFloat(XorStr("Hands"), XorStr("|HandsColorR"), Options::Visuals::ESP::HandsColor[0]);
//		writer.WriteFloat(XorStr("Hands"), XorStr("|HandsColorG"), Options::Visuals::ESP::HandsColor[1]);
//		writer.WriteFloat(XorStr("Hands"), XorStr("|HandsColorB"), Options::Visuals::ESP::HandsColor[2]);
//		writer.WriteFloat(XorStr("Weapons"), XorStr("|WeaponsColorR"), Options::Visuals::ESP::WeaponsColor[0]);
//		writer.WriteFloat(XorStr("Weapons"), XorStr("|WeaponsColorG"), Options::Visuals::ESP::WeaponsColor[1]);
//		writer.WriteFloat(XorStr("Weapons"), XorStr("|WeaponsColorB"), Options::Visuals::ESP::WeaponsColor[2]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorVisibleR"), Options::Visuals::ESP::RadarColorVis[0]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorVisibleG"), Options::Visuals::ESP::RadarColorVis[1]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorVisibleB"), Options::Visuals::ESP::RadarColorVis[2]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorInvisibleR"), Options::Visuals::ESP::RadarColorInvis[0]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorInvisibleG"), Options::Visuals::ESP::RadarColorInvis[1]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|EnemyColorInvisibleB"), Options::Visuals::ESP::RadarColorInvis[2]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorVisibleR"), Options::Visuals::ESP::RadarTeamColorVis[0]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorVisibleG"), Options::Visuals::ESP::RadarTeamColorVis[1]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorVisibleB"), Options::Visuals::ESP::RadarTeamColorVis[2]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorInvisibleR"), Options::Visuals::ESP::RadarTeamColorInvis[0]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorInvisibleG"), Options::Visuals::ESP::RadarTeamColorInvis[1]);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|TeamColorInvisibleB"), Options::Visuals::ESP::RadarTeamColorInvis[2]);
//
//
//
//
//		writer.WriteBoolean(XorStr("Hands"), XorStr("|Enabled"), Options::Visuals::Hands::Enabled);
//		writer.WriteInteger(XorStr("Hands"), XorStr("|Style"), Options::Visuals::Hands::Style);
//		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorR"), Options::Visuals::Hands::color[0] * 255);
//		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorG"), Options::Visuals::Hands::color[1] * 255);
//		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorB"), Options::Visuals::Hands::color[2] * 255);
//
//		writer.WriteBoolean(XorStr("Radar"), XorStr("|Enabled"), Options::Radar::Enabled);
//		writer.WriteInteger(XorStr("Radar"), XorStr("|Style"), Options::Radar::Style);
//		writer.WriteInteger(XorStr("Radar"), XorStr("|Type"), Options::Radar::Type);
//		writer.WriteInteger(XorStr("Radar"), XorStr("|Alpha"), Options::Radar::Alpha);
//		writer.WriteBoolean(XorStr("Radar"), XorStr("|ViewCheck"), Options::Radar::ViewCheck);
//		writer.WriteBoolean(XorStr("Radar"), XorStr("|EnemyOnly"), Options::Radar::EnemyOnly);
//		writer.WriteBoolean(XorStr("Radar"), XorStr("|VisibleOnly"), Options::Radar::VisibleOnly);
//		writer.WriteBoolean(XorStr("Radar"), XorStr("|SmokeCheck"), Options::Radar::SmokeCheck);
//		writer.WriteFloat(XorStr("Radar"), XorStr("|Zoom"), Options::Radar::Zoom);
//
//		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledSkin"), Options::SkinChanger::EnabledSkin);
//		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledKnife"), Options::SkinChanger::EnabledKnife);
//		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledGlove"), Options::SkinChanger::EnabledGlove);
//		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|Knife"), Options::SkinChanger::Knife);
//		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|Glove"), Options::SkinChanger::Glove);
//		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|GloveSkin"), Options::SkinChanger::GloveSkin);
//
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|AntiAFK"), Options::Misc::AntiAFK);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|RevealRanks"), Options::Misc::RevealRanks);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|Bunnyhop"), Options::Misc::Bunnyhop);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|SpectatorList"), Options::Misc::SpectatorList);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|SpectatorListOnlyForYou"), Options::Misc::SpectatorListOnlyYou);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|HitInfo"), Options::Misc::HitInfo);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|ChatSpam"), Options::Misc::CSpam);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBot"), Options::Misc::KnifeBot);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBotAuto"), Options::Misc::KnifeBotAuto);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBot360"), Options::Misc::KnifeBot360);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|Copyright"), Options::Misc::Copyright);
//		writer.WriteFloat(XorStr("Misc"), XorStr("|SpeedControl"), Options::Misc::SpeedControl);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|RecoilCrosshair"), Options::Misc::RecoilCrosshair);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|SniperCrosshair"), Options::Misc::SniperCrosshair);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|AirStuck"), Options::Misc::AirStuck);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|DropESP"), Options::Visuals::Misc::DropESP);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|BombESP"), Options::Visuals::Misc::BombTimer);
//		writer.WriteInteger(XorStr("Misc"), XorStr("|BombESPtype"), Options::Visuals::Misc::BombTimerType);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|FovChanger"), Options::Visuals::Misc::FovChanger);
//		writer.WriteFloat(XorStr("Misc"), XorStr("|FovChangerValue"), Options::Visuals::Misc::FovChangerValue);
//		writer.WriteBoolean(XorStr("Misc"), XorStr("|ViewmodelChanger"), Options::Visuals::Misc::ViewmodelChanger);
//		writer.WriteFloat(XorStr("Misc"), XorStr("|ViewmodelChangerValue"), Options::Visuals::Misc::ViewmodelChangerValue);
//
//		for (int i = 1; i < 520; i++)
//		{
//			char* section = U::GetConfigName(i);
//			if (strcmp(section, "") == 0)
//				continue;
//
//			Weapon_t w = weapons[i];
//			if (std::string(section).find(XorStr("knife")) == std::string::npos)
//			{
//				writer.WriteBoolean(section, XorStr("|Enabled"), w.Enabled);
//				writer.WriteFloat(section, XorStr("|Fov"), w.Fov);
//				writer.WriteInteger(section, XorStr("|Bone"), w.Bone);
//				writer.WriteBoolean(section, XorStr("|Nearest"), w.Nearest);
//				writer.WriteInteger(section, XorStr("|NearestType"), w.NearestType);
//				writer.WriteFloat(section, XorStr("|Smooth"), w.Smooth);
//				writer.WriteBoolean(section, XorStr("|FireDelayEnabled"), weapons[i].FireDelayEnabled);
//				writer.WriteBoolean(section, XorStr("|FireDelayRepeat"), weapons[i].FireDelayRepeat);
//				writer.WriteFloat(section, XorStr("|FireDelay"), weapons[i].FireDelay);
//				writer.WriteInteger(section, XorStr("|StartBullet"), w.StartBullet);
//				writer.WriteInteger(section, XorStr("|EndBullet"), w.EndBullet);
//				writer.WriteInteger(section, XorStr("|RcsX"), w.RcsX);
//				writer.WriteInteger(section, XorStr("|RcsY"), w.RcsY);
//
//				writer.WriteBoolean(section, XorStr("|pSilent"), w.pSilent);
//				writer.WriteInteger(section, XorStr("|pSilentBullet"), w.pSilentBullet);
//				writer.WriteInteger(section, XorStr("|pSilentHitchance"), w.pSilentHitchance);
//				writer.WriteFloat(section, XorStr("|pSilentFov"), w.pSilentFov);
//				writer.WriteFloat(section, XorStr("|pSilentSmooth"), w.pSilentSmooth);
//			}
//
//			writer.WriteBoolean(section, XorStr("|ChangerEnabled"), w.ChangerEnabled);
//			writer.WriteInteger(section, XorStr("|ChangerSkin"), w.ChangerSkin);
//			writer.WriteString(section, XorStr("|ChangerName"), w.ChangerName);
//			writer.WriteInteger(section, XorStr("|ChangerStatTrak"), w.ChangerStatTrak);
//			writer.WriteInteger(section, XorStr("|ChangerSeed"), w.ChangerSeed);
//			writer.WriteFloat(section, XorStr("|ChangerWear"), w.ChangerWear);
//		}*/
//	}
//}