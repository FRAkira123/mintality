#pragma once
typedef void(*LPSEARCHFUNC)(LPCTSTR lpszFileName);

BOOL SearchFiles(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders = FALSE)
{
	LPTSTR part;
	char tmp[MAX_PATH];
	char name[MAX_PATH];

	HANDLE hSearch = NULL;
	WIN32_FIND_DATA wfd;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

	if (bInnerFolders)
	{
		if (GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
		strcpy(name, part);
		strcpy(part, "*.*");
		wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
		if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
			do
			{
				if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
					continue;

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					char next[MAX_PATH];
					if (GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
					strcpy(part, wfd.cFileName);
					strcat(next, "\\");
					strcat(next, name);

					SearchFiles(next, lpSearchFunc, TRUE);
				}
			} while (FindNextFile(hSearch, &wfd));
			FindClose(hSearch);
	}

	if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
		return TRUE;
	do
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			char file[MAX_PATH];
			if (GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
			strcpy(part, wfd.cFileName);

			lpSearchFunc(wfd.cFileName);
		}
	while (FindNextFile(hSearch, &wfd));
	FindClose(hSearch);
	return TRUE;
}


namespace Settings
{
#define ENCRYPTION_KEY 0xA67D7
	string IniFile = "";
	size_t IniFileLen = 0;

	void IniFileED()
	{
		for (size_t i = 0; i < IniFileLen; i++) {
			IniFile[i] ^= ENCRYPTION_KEY;
		}
	}

	void InitPath(const char* szPath)
	{
		IniFile = szPath;
		IniFileLen = IniFile.size();
		IniFileED();
	}

	int LoadCvar(char* szSection, char* szKey, int DefaultValue)
	{
		IniFileED();
		char IntValue[16] = { 0 };
		GetPrivateProfileStringA(szSection, szKey, to_string(DefaultValue).c_str(), IntValue, sizeof(IntValue), IniFile.c_str());
		IniFileED();
		return atoi(IntValue);
	}

	string LoadCvar(char* szSection, char* szKey, string DefaultValue)
	{
		IniFileED();
		char cTempString[16] = { 0 };
		GetPrivateProfileStringA(szSection, szKey, DefaultValue.c_str(), cTempString, sizeof(cTempString), IniFile.c_str());
		IniFileED();
		return string(cTempString);
	}

	float LoadCvar(char* szSection, char* szKey, float DefaultValue)
	{
		IniFileED();
		char FloatValue[16] = { 0 };
		GetPrivateProfileStringA(szSection, szKey, to_string(DefaultValue).c_str(), FloatValue, sizeof(FloatValue), IniFile.c_str());
		IniFileED();
		return (float)atof(FloatValue);
	}

	void SaveCvar(char* szSection, char* szKey, int Value)
	{
		string IntValue = to_string(Value);
		IniFileED();
		WritePrivateProfileStringA(szSection, szKey, IntValue.c_str(), IniFile.c_str());
		IniFileED();
	}

	void SaveCvar(char* szSection, char* szKey, float Value)
	{
		string FloatValue = to_string(Value);
		IniFileED();
		WritePrivateProfileStringA(szSection, szKey, FloatValue.c_str(), IniFile.c_str());
		IniFileED();
	}

	void SaveCvar(char* szSection, char* szKey, string Value)
	{
		IniFileED();
		WritePrivateProfileStringA(szSection, szKey, Value.c_str(), IniFile.c_str());
		IniFileED();
	}


	void LoadSettings(string szIniFile)
	{
		InitPath(szIniFile.c_str());
		Vars.VisualMenu.WeaponESP1 = Settings::LoadCvar("Visual", "|WeaponESPon", Vars.VisualMenu.WeaponESP1);
		Vars.VisualMenu.Armor1 = Settings::LoadCvar("Visual", "|Armoron", Vars.VisualMenu.Armor1);
		Vars.VisualMenu.Health1 = Settings::LoadCvar("Visual", "|Healthon", Vars.VisualMenu.Health1);
		Vars.VisualMenu.boxed = Settings::LoadCvar("Visual", "|boxedon", Vars.VisualMenu.boxed);
		Vars.VisualMenu.Player2DBox = Settings::LoadCvar("Visual", "|Player2DBox", Vars.VisualMenu.Player2DBox);
		Vars.VisualMenu.Player3DBox = Settings::LoadCvar("Visual", "|Player3DBox", Vars.VisualMenu.Player3DBox);
		Vars.VisualMenu.HitMarks = Settings::LoadCvar("Visual", "|HitMarks", Vars.VisualMenu.HitMarks);
		Vars.VisualMenu.InfoDamge = Settings::LoadCvar("Visual", "|InfoDamge", Vars.VisualMenu.InfoDamge);
		Vars.VisualMenu.ESPLine = Settings::LoadCvar("Visual", "|ESPLine", Vars.VisualMenu.ESPLine);
		Vars.VisualMenu.Head = Settings::LoadCvar("Visual", "|Head", Vars.VisualMenu.Head);
		Vars.VisualMenu.ArmorDraw = Settings::LoadCvar("Visual", "|ArmorDraw", Vars.VisualMenu.ArmorDraw);
		Vars.VisualMenu.HealthDraw = Settings::LoadCvar("Visual", "|HealthDraw", Vars.VisualMenu.HealthDraw);
		Vars.VisualMenu.ESPNickName = Settings::LoadCvar("Visual", "|ESPNickName", Vars.VisualMenu.ESPNickName);
		Vars.VisualMenu.ESPDistance = Settings::LoadCvar("Visual", "|ESPDistance", Vars.VisualMenu.ESPDistance);
		Vars.VisualMenu.ESPSkelet = Settings::LoadCvar("Visual", "|ESPSkelet", Vars.VisualMenu.ESPSkelet);
		Vars.VisualMenu.HPBar = Settings::LoadCvar("Visual", "|HPBar", Vars.VisualMenu.HPBar);
		Vars.VisualMenu.ArmorBar = Settings::LoadCvar("Visual", "|ArmorBar", Vars.VisualMenu.ArmorBar);
		Vars.VisualMenu.ESPWeapon = Settings::LoadCvar("Visual", "|ESPWeapon", Vars.VisualMenu.ESPWeapon);
		Vars.VisualMenu.DropWeapon = Settings::LoadCvar("Visual", "|DropWeapon", Vars.VisualMenu.DropWeapon);
		Vars.VisualMenu.Weapon2DBox = Settings::LoadCvar("Visual", "|Weapon2DBox", Vars.VisualMenu.Weapon2DBox);
		Vars.VisualMenu.Weapon3DBox = Settings::LoadCvar("Visual", "|Weapon3DBox", Vars.VisualMenu.Weapon3DBox);
		Vars.Visuals.Glows.c4 = Settings::LoadCvar("Visual", "|GlowsC4", Vars.Visuals.Glows.c4);
		Vars.Visuals.Glows.player = Settings::LoadCvar("Visual", "|GlowPlayer", Vars.Visuals.Glows.player);
		Vars.Visuals.Glows.ourPlayers = Settings::LoadCvar("Visual", "|GlowourPlayers", Vars.Visuals.Glows.ourPlayers);
		Vars.Visuals.Glows.weapon = Settings::LoadCvar("Visual", "|Gloweapon", Vars.Visuals.Glows.weapon);
		
		Vars.Visuals.Chams.Enabled = Settings::LoadCvar("Visual", "|ChamsEnable", Vars.Visuals.Chams.Enabled);
		Vars.Visuals.Chams.XQZ = Settings::LoadCvar("Visual", "|ChamsVisAll", Vars.Visuals.Chams.XQZ);
		Vars.Visuals.Filter.Enemies = Settings::LoadCvar("Visual", "|Enemies1", Vars.Visuals.Filter.Enemies);
		Vars.Visuals.Filter.Friendlies = Settings::LoadCvar("Visual", "|Friendlies1", Vars.Visuals.Filter.Friendlies);
		Vars.Visuals.Filter.Localplayer = Settings::LoadCvar("Visual", "|Localplayer1", Vars.Visuals.Filter.Localplayer);
		Vars.Visuals.Filter.Weapons = Settings::LoadCvar("Visual", "|Weapons1", Vars.Visuals.Filter.Weapons);
		Vars.Visuals.Filter.Decoy = Settings::LoadCvar("Visual", "|Decoy1", Vars.Visuals.Filter.Decoy);
		Vars.Visuals.Filter.C4 = Settings::LoadCvar("Visual", "|1C4", Vars.Visuals.Filter.C4);
		




		Vars.VisualMenu.BulletTrace =	Settings::LoadCvar("Visual", "|BulletTrace", Vars.VisualMenu.BulletTrace);
		Vars.VisualMenu.IsFlashed =	Settings::LoadCvar("Visual", "|IsFlashed", Vars.VisualMenu.IsFlashed);
		Vars.VisualMenu.ESPHitBox = Settings::LoadCvar("Visual", "|ESPHitBox", Vars.VisualMenu.ESPHitBox);
		Vars.VisualMenu.ESPLastPlace = Settings::LoadCvar("Visual", "|ESPLastPlace", Vars.VisualMenu.ESPLastPlace);
		Vars.VisualMenu.CircleEsp =	Settings::LoadCvar("Visual", "|CircleEsp", Vars.VisualMenu.CircleEsp);

		//Legit_Aim
		Vars.Legitbot.pSilent = Settings::LoadCvar("AimBot", "|pSilent", Vars.Legitbot.pSilent);
		Vars.Legitbot.Aimbot.Enabled = Settings::LoadCvar("AimBot", "|LegitbotEnable", Vars.Legitbot.Aimbot.Enabled);
		Vars.Legitbot.Aimbot.AlwaysOn = Settings::LoadCvar("AimBot", "|AlwaysOn", Vars.Legitbot.Aimbot.AlwaysOn);
		Vars.Legitbot.Aimbot.OnKey = Settings::LoadCvar("AimBot", "|OnKey", Vars.Legitbot.Aimbot.OnKey);

		Vars.Legitbot.CHKSmoke = Settings::LoadCvar("AimBot", "|CHKSmoke", Vars.Legitbot.CHKSmoke);

		Vars.Menu.AllWeapSettings = Settings::LoadCvar("AimBot", "|AllWeapSettings", Vars.Menu.AllWeapSettings);
		AV.Enable = Settings::LoadCvar("AimBot", "|AWEnable", AV.Enable);
		AV.Smooth = Settings::LoadCvar("AimBot", "|AWSmooth", AV.Smooth);

		AV.Automatic.HitBoxAim = Settings::LoadCvar("AimBot", "|AutomaticHitBoxAim", AV.Automatic.HitBoxAim);
		AV.Automatic.Fov = Settings::LoadCvar("AimBot", "|AutomaticFov", AV.Automatic.Fov);
		AV.Automatic.Smooth = Settings::LoadCvar("AimBot", "|AutomaticSmooth", AV.Automatic.Smooth);

		AV.Sniper.HitBoxAim = Settings::LoadCvar("AimBot", "|SniperHitBoxAim", AV.Sniper.HitBoxAim);
		AV.Sniper.Fov = Settings::LoadCvar("AimBot", "|SniperFov", AV.Sniper.Fov);
		AV.Sniper.Smooth = Settings::LoadCvar("AimBot", "|SniperSmooth", AV.Sniper.Smooth);

		AV.Shotgun.HitBoxAim = Settings::LoadCvar("AimBot", "|ShotgunHitBoxAim", AV.Shotgun.HitBoxAim);
		AV.Shotgun.Fov = Settings::LoadCvar("AimBot", "|ShotgunFov", AV.Shotgun.Fov);
		AV.Shotgun.Smooth = Settings::LoadCvar("AimBot", "|ShotgunSmooth", AV.Shotgun.Smooth);

		AV.Pistol.HitBoxAim = Settings::LoadCvar("AimBot", "|PistolHitBoxAim", AV.Pistol.HitBoxAim);
		AV.Pistol.Fov = Settings::LoadCvar("AimBot", "|PistolFov", AV.Pistol.Fov);
		AV.Pistol.Smooth = Settings::LoadCvar("AimBot", "|PistolSmooth", AV.Pistol.Smooth);

		AV.HitBox = Settings::LoadCvar("AimBot", "|AWHitBox", AV.HitBox);
		Vars.Legitbot.FOV = Settings::LoadCvar("AimBot", "|LegitbotFOV", Vars.Legitbot.FOV);
		Vars.Misc.RCS = Settings::LoadCvar("AimBot", "|RCS", Vars.Misc.RCS);
		Vars.Misc.RCSWork = Settings::LoadCvar("AimBot", "|RCSWork", Vars.Misc.RCSWork);
		Vars.Legitbot.Triggerbot.Enabled = Settings::LoadCvar("AimBot", "|Triggerbot", Vars.Legitbot.Triggerbot.Enabled);
		Vars.Legitbot.Triggerbot.AutoFire = Settings::LoadCvar("AimBot", "|AutoFire", Vars.Legitbot.Triggerbot.AutoFire);
//		TriggersInt = Settings::LoadCvar("AimBot", "|TriggersInt", TriggersInt);
		Vars.Legitbot.Triggerbot.FrFr = Settings::LoadCvar("AimBot", "|FriendlyFire", Vars.Legitbot.Triggerbot.FrFr);

		//Misc
		Vars.Misc.ChangeNick = Settings::LoadCvar("AimBot", "|ChangeNick", Vars.Misc.ChangeNick);
		Vars.Misc.ChatSpam = Settings::LoadCvar("AimBot", "|ChatSpam", Vars.Misc.ChatSpam);
		Vars.Misc.SpamTime = Settings::LoadCvar("AimBot", "|SpamTime", Vars.Misc.SpamTime);
		Vars.Visuals.Removals.Flash = Settings::LoadCvar("AimBot", "|Flash", Vars.Visuals.Removals.Flash);
		Vars.Visuals.Removals.AlphaFlash = Settings::LoadCvar("AimBot", "|AlphaFlash", Vars.Visuals.Removals.AlphaFlash);
		Vars.Misc.AutoPistol = Settings::LoadCvar("AimBot", "|AutoPistol", Vars.Misc.AutoPistol);
		Vars.Misc.Bhop = Settings::LoadCvar("AimBot", "|Bhop", Vars.Misc.Bhop);
		Vars.Misc.AutoStrafe = Settings::LoadCvar("AimBot", "|AutoStrafe", Vars.Misc.AutoStrafe);

		/////
		Vars.g_iChamsCTV[0]  = Settings::LoadCvar("Visual", "|g_iChamsCTV_R", Vars.g_iChamsCTV[0]);
		Vars.g_iChamsCTV[1]  = Settings::LoadCvar("Visual", "|g_iChamsCTV_G", Vars.g_iChamsCTV[1]);
		Vars.g_iChamsCTV[2] = Settings::LoadCvar("Visual", "|g_iChamsCTV_B", Vars.g_iChamsCTV[2]);

	}

	void SaveSettings(string szIniFile)
	{
		InitPath(szIniFile.c_str());

		//Visual
		Settings::SaveCvar("Visual", "|WeaponESPon", Vars.VisualMenu.WeaponESP1);
		Settings::SaveCvar("Visual", "|Armoron", Vars.VisualMenu.Armor1);
		Settings::SaveCvar("Visual", "|Healthon", Vars.VisualMenu.Health1);
		Settings::SaveCvar("Visual", "|boxedon", Vars.VisualMenu.boxed);
		Settings::SaveCvar("Visual", "|Player2DBox", Vars.VisualMenu.Player2DBox);
		Settings::SaveCvar("Visual", "|Player3DBox", Vars.VisualMenu.Player3DBox);
		Settings::SaveCvar("Visual", "|HitMarks", Vars.VisualMenu.HitMarks);
		Settings::SaveCvar("Visual", "|InfoDamge", Vars.VisualMenu.InfoDamge);
		Settings::SaveCvar("Visual", "|ESPLine", Vars.VisualMenu.ESPLine);
		Settings::SaveCvar("Visual", "|Head", Vars.VisualMenu.Head);
		Settings::SaveCvar("Visual", "|ArmorDraw", Vars.VisualMenu.ArmorDraw);
		Settings::SaveCvar("Visual", "|HealthDraw", Vars.VisualMenu.HealthDraw);
		Settings::SaveCvar("Visual", "|ESPNickName", Vars.VisualMenu.ESPNickName);
		Settings::SaveCvar("Visual", "|ESPDistance", Vars.VisualMenu.ESPDistance);
		Settings::SaveCvar("Visual", "|ESPSkelet", Vars.VisualMenu.ESPSkelet);
		Settings::SaveCvar("Visual", "|HPBar", Vars.VisualMenu.HPBar);
		Settings::SaveCvar("Visual", "|ArmorBar", Vars.VisualMenu.ArmorBar);
		Settings::SaveCvar("Visual", "|ESPWeapon", Vars.VisualMenu.ESPWeapon);
		Settings::SaveCvar("Visual", "|DropWeapon", Vars.VisualMenu.DropWeapon);
		Settings::SaveCvar("Visual", "|Weapon2DBox", Vars.VisualMenu.Weapon2DBox);
		Settings::SaveCvar("Visual", "|Weapon3DBox", Vars.VisualMenu.Weapon3DBox);
		Settings::SaveCvar("Visual", "|GlowsC4", Vars.Visuals.Glows.c4);
		Settings::SaveCvar("Visual", "|GlowPlayer", Vars.Visuals.Glows.player);
		Settings::SaveCvar("Visual", "|GlowourPlayers", Vars.Visuals.Glows.ourPlayers);
		Settings::SaveCvar("Visual", "|Gloweapon", Vars.Visuals.Glows.weapon);

		Settings::SaveCvar("Visual", "|ChamsEnable", Vars.Visuals.Chams.Enabled);
		Settings::SaveCvar("Visual", "|ChamsVisAll", Vars.Visuals.Chams.XQZ);
		Settings::SaveCvar("Visual", "|Enemies1", Vars.Visuals.Filter.Enemies);
		Settings::SaveCvar("Visual", "|Friendlies1", Vars.Visuals.Filter.Friendlies);
		Settings::SaveCvar("Visual", "|Localplayer1", Vars.Visuals.Filter.Localplayer);
		Settings::SaveCvar("Visual", "|Weapons1", Vars.Visuals.Filter.Weapons);
		Settings::SaveCvar("Visual", "|Decoy1", Vars.Visuals.Filter.Decoy);
		Settings::SaveCvar("Visual", "|1C4", Vars.Visuals.Filter.C4);
		

		///////
		Settings::SaveCvar("Visual", "|g_iChamsCTV_R", Vars.g_iChamsCTV[0]);
		Settings::SaveCvar("Visual", "|g_iChamsCTV_G", Vars.g_iChamsCTV[1]);
		Settings::SaveCvar("Visual", "|g_iChamsCTV_B", Vars.g_iChamsCTV[2]);
		///////


		Settings::SaveCvar("Visual", "|DropWeapon", Vars.VisualMenu.Radar);
		Settings::SaveCvar("Visual", "|Weapon2DBox", Vars.VisualMenu.ShowPitch);
		Settings::SaveCvar("Visual", "|Weapon3DBox", Vars.VisualMenu.ShowYaw);
		Settings::SaveCvar("Visual", "|DropWeapon", Vars.VisualMenu.BombTimer);	 

		Settings::SaveCvar("Visual", "|BulletTrace", Vars.VisualMenu.BulletTrace);
		Settings::SaveCvar("Visual", "|IsFlashed", Vars.VisualMenu.IsFlashed);
		Settings::SaveCvar("Visual", "|ESPHitBox", Vars.VisualMenu.ESPHitBox);
		Settings::SaveCvar("Visual", "|ESPLastPlace", Vars.VisualMenu.ESPLastPlace);
		Settings::SaveCvar("Visual", "|CircleEsp", Vars.VisualMenu.CircleEsp);

		
		//Legit_Aim

		Settings::SaveCvar("AimBot", "|pSilent", Vars.Legitbot.pSilent);
		Settings::SaveCvar("AimBot", "|LegitbotEnable", Vars.Legitbot.Aimbot.Enabled);
		Settings::SaveCvar("AimBot", "|AlwaysOn", Vars.Legitbot.Aimbot.AlwaysOn);
		Settings::SaveCvar("AimBot", "|OnKey", Vars.Legitbot.Aimbot.OnKey);
		Settings::SaveCvar("AimBot", "|CHKSmoke", Vars.Legitbot.CHKSmoke);



		Settings::SaveCvar("AimBot", "|AllWeapSettings", Vars.Menu.AllWeapSettings);
		Settings::SaveCvar("AimBot", "|AWEnable", AV.Enable);
		Settings::SaveCvar("AimBot", "|AWSmooth", AV.Smooth);

		Settings::SaveCvar("AimBot", "|AutomaticHitBoxAim", AV.Automatic.HitBoxAim);
		Settings::SaveCvar("AimBot", "|AutomaticFov", AV.Automatic.Fov);
		Settings::SaveCvar("AimBot", "|AutomaticSmooth", AV.Automatic.Smooth);

		Settings::SaveCvar("AimBot", "|SniperHitBoxAim", AV.Sniper.HitBoxAim);
		Settings::SaveCvar("AimBot", "|SniperFov", AV.Sniper.Fov);
		Settings::SaveCvar("AimBot", "|SniperSmooth", AV.Sniper.Smooth);

		Settings::SaveCvar("AimBot", "|ShotgunHitBoxAim", AV.Shotgun.HitBoxAim);
		Settings::SaveCvar("AimBot", "|ShotgunFov", AV.Shotgun.Fov);
		Settings::SaveCvar("AimBot", "|ShotgunSmooth", AV.Shotgun.Smooth);

		Settings::SaveCvar("AimBot", "|PistolHitBoxAim", AV.Pistol.HitBoxAim);
		Settings::SaveCvar("AimBot", "|PistolFov", AV.Pistol.Fov);
		Settings::SaveCvar("AimBot", "|PistolSmooth", AV.Pistol.Smooth);

		Settings::SaveCvar("AimBot", "|AWHitBox", AV.HitBox);
		Settings::SaveCvar("AimBot", "|LegitbotFOV", Vars.Legitbot.FOV);
		Settings::SaveCvar("AimBot", "|RCS", Vars.Misc.RCS);
		Settings::SaveCvar("AimBot", "|RCSWork", Vars.Misc.RCSWork);
		Settings::SaveCvar("AimBot", "|Triggerbot", Vars.Legitbot.Triggerbot.Enabled);
		Settings::SaveCvar("AimBot", "|AutoFire", Vars.Legitbot.Triggerbot.AutoFire);
	//	Settings::SaveCvar("AimBot", "|TriggersInt", TriggersInt);
		Settings::SaveCvar("AimBot", "|FriendlyFire", Vars.Legitbot.Triggerbot.FrFr);

		//Misc
		Settings::SaveCvar("AimBot", "|ChangeNick", Vars.Misc.ChangeNick);
		Settings::SaveCvar("AimBot", "|Nick", buf);
		Settings::SaveCvar("AimBot", "|ChatSpam", Vars.Misc.ChatSpam);
		Settings::SaveCvar("AimBot", "|SpamTime", Vars.Misc.SpamTime);
		Settings::SaveCvar("AimBot", "|Flash", Vars.Visuals.Removals.Flash);
		Settings::SaveCvar("AimBot", "|AlphaFlash", Vars.Visuals.Removals.AlphaFlash);
		Settings::SaveCvar("AimBot", "|AutoPistol", Vars.Misc.AutoPistol);
		Settings::SaveCvar("AimBot", "|Bhop", Vars.Misc.Bhop);
		Settings::SaveCvar("AimBot", "|AutoStrafe", Vars.Misc.AutoStrafe);





	}


}