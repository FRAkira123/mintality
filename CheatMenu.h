#pragma once

typedef HRESULT(WINAPI* Reset_t)(IDirect3DDevice9* m_pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
Reset_t oReset = nullptr;

typedef HRESULT(WINAPI* Present_t)(IDirect3DDevice9 * m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
Present_t oPresent = nullptr;


bool Create = false;

Variables Vars;
AimVariables AV;

extern VTHookManager* Direct9Hook;

int WScreen = 0, HScreen = 0;
#include "cConfiguration.h"
#include "CFG.h"


bool test_targets = false;
int target_type = 0;
int min_max = 0;


string BaseDir = "";
string LogFile = "";
string GuiFile = "";
string IniFile = "";

vector<string> ConfigList;

void ReadConfigs(LPCTSTR lpszFileName)
{
	if (!strstr(lpszFileName, "gui.ini"))
		ConfigList.push_back(lpszFileName);
	
}

void RefreshConfigs()
{
	ConfigList.clear();
	string ConfigDir = BaseDir + "\\*.ini";
	SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
}

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	IMGUI_API bool ComboBoxArray(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	

	IMGUI_API  bool TabLabels(int numTabs, const char** tabLabels, int& selectedIndex, const char** tabLabelTooltips, bool autoLayout, int *pOptionalHoveredIndex)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		style.ItemSpacing.x = 1;
		style.ItemSpacing.y = 1;

		if (numTabs > 0 && (selectedIndex < 0 || selectedIndex >= numTabs)) selectedIndex = 0;
		if (pOptionalHoveredIndex) *pOptionalHoveredIndex = -1;

		const float btnOffset = 3.f*style.FramePadding.x;
		const float sameLineOffset = 3.f*style.ItemSpacing.x;
		const float uniqueLineOffset = 3.f*style.WindowPadding.x;

		float windowWidth = 0.f, sumX = 0.f;
		if (autoLayout) windowWidth = ImGui::GetWindowWidth() - uniqueLineOffset;

		bool selection_changed = false;
		for (int i = 0; i < numTabs; i++)
		{
			if (i == selectedIndex)
			{
				style.Colors[ImGuiCol_Button] = colorActive;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorActive;
			}
			else
			{
				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
			}

			ImGui::PushID(i);

			if (!autoLayout) { if (i > 0) ImGui::SameLine(); 
			}
			else if (sumX > 0.f) 
			{
				sumX += sameLineOffset;
				sumX += ImGui::CalcTextSize(tabLabels[i]).x + btnOffset;
				if (sumX > windowWidth) sumX = 0.f;
				else ImGui::SameLine();
			}

			if (ImGui::Button(tabLabels[i], ImVec2(110, 30))) { selection_changed = (selectedIndex != i); selectedIndex = i; }
			if (autoLayout && sumX == 0.f) {
				sumX = ImGui::GetItemRectSize().x;
			}
			if (pOptionalHoveredIndex) {
				if (ImGui::IsItemHovered()) {
					*pOptionalHoveredIndex = i;
					if (tabLabelTooltips && tabLabelTooltips[i] && strlen(tabLabelTooltips[i]) > 0)  ImGui::SetTooltip("%s", tabLabelTooltips[i]);
				}
			}
			else if (tabLabelTooltips && tabLabelTooltips[i] && ImGui::IsItemHovered() && strlen(tabLabelTooltips[i]) > 0) ImGui::SetTooltip("%s", tabLabelTooltips[i]);
			ImGui::PopID();
		}

		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}
}



vector<int> GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	auto pPlayer = pClientEntList->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		auto pObserverTarget = pClientEntList->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < 64; PlayerIndex++)
	{
		auto pCheckPlayer = pClientEntList->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		auto pObserverTarget = pClientEntList->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}




void OnRenderSpectatorList()
{
	if (Vars.SpectatorList)
	{
		int specs = 0;
		int modes = 0;
		std::string spect = "";
		std::string mode = "";
		int DrawIndex = 1;

		for (int playerId : GetObservervators(pEngine->GetLocalPlayer()))
		{
			if (playerId == pEngine->GetLocalPlayer())
				continue;

			auto pPlayer = pClientEntList->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			player_info_t Pinfo;
			pEngine->GetPlayerInfo(playerId, &Pinfo);

			if (Pinfo.m_bIsFakePlayer)
				continue;

			spect += Pinfo.szName;
			spect += "\n";
			specs++;

			if (spect != "")
			{
				Color PlayerObsColor;
				switch (pPlayer->GetObserverMode())
				{
				case ObserverMode_t::OBS_MODE_IN_EYE:
					mode += ("Perspective");
					PlayerObsColor = Color::White();
					break;
				case ObserverMode_t::OBS_MODE_CHASE:
					mode += ("3rd Person");
					PlayerObsColor = Color::White();
					break;
				case ObserverMode_t::OBS_MODE_ROAMING:
					mode += ("Free look");
					PlayerObsColor = Color::Red();
					break;
				case ObserverMode_t::OBS_MODE_DEATHCAM:
					mode += ("Deathcam");
					PlayerObsColor = Color::Red();
					break;
				case ObserverMode_t::OBS_MODE_FREEZECAM:
					mode += ("Freezecam");
					PlayerObsColor = Color::Red();
					break;
				case ObserverMode_t::OBS_MODE_FIXED:
					mode += ("Fixed");
					PlayerObsColor = Color::Orange();
					break;
				default:
					break;
				}

				mode += "\n";
				modes++;
			}

		}

		if (ImGui::Begin("Spectator List", &Vars.SpectatorList, ImVec2(200, 100), 0.9f, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders))
		{
			if (specs > 0) spect += "\n";
			if (modes > 0) mode += "\n";
			ImVec2 size = ImGui::CalcTextSize(spect.c_str());
			ImGui::Columns(2);

			ImGui::Text("Name");
			ImGui::NextColumn();

			ImGui::Text("Mode");
			ImGui::NextColumn();
			ImGui::Separator();

			ImGui::Text(spect.c_str());
			ImGui::NextColumn();

			ImGui::Text(mode.c_str());
			ImGui::Columns(1);
			DrawIndex++;
		}
		ImGui::End();
	}
}






HRESULT WINAPI myPresent(IDirect3DDevice9 * m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	JUNK_CODE_ONE
		if (!m_pDevice)
			return S_OK;

	m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	if (Create == false)
	{
		ImGui_Init(hWnd, m_pDevice);
		Create = true;
	}
	else
	{
		ImGui_NewFrame();
		if (bShowWindow)
		{
			ImGui::Begin(XorStr(" "), &bShowWindow, ImVec2(700, 453), 1.0f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			{
				float SpaceLineOne = 251.f;
				float SpaceLineTwo = 360.f;
				static const char* tabNames[] = { u8"Aim Bot",u8"Visual", u8"Misc", u8"Trigger Bot", u8"Glow Esp", u8"Settings" };
				static const int numTabs = sizeof(tabNames) / sizeof(tabNames[0]);
				static const char* tabTooltips[numTabs] = {};
				static int selectedTab = 1,
					optionalHoveredTab = 2;
				ImGui::TabLabels(numTabs, tabNames, selectedTab, tabTooltips, false, &optionalHoveredTab);
				ImGui::NewLine();
				
				
				switch (selectedTab)
				{
				case 1:
					//visual

					ImGui::Columns(3, NULL, false);
					{
						ImGui::Selectable(XorStr(u8" ESP Box "), &Vars.VisualMenu.boxed);
						if (Vars.VisualMenu.boxed)
						{
							ImGui::Checkbox(XorStr(u8"2D Бокс"), &Vars.VisualMenu.Player2DBox);
							ImGui::Checkbox(XorStr(u8"3D Бокс"), &Vars.VisualMenu.Player3DBox);
							ImGui::Checkbox(XorStr(u8"2D Бокс 2"), &Vars.VisualMenu.Player2DBox2);
						}

						ImGui::Selectable(XorStr(u8" ESP Здоровье  "), &Vars.VisualMenu.Health1);
						if (Vars.VisualMenu.Health1)
						{
							ImGui::Checkbox(XorStr(u8"Здоровье"), &Vars.VisualMenu.HealthDraw);
							ImGui::Checkbox(XorStr(u8"Полоска Здоровья"), &Vars.VisualMenu.HPBar);
						}

						ImGui::Selectable(XorStr(u8" ESP Броня  "), &Vars.VisualMenu.Armor1);
						if (Vars.VisualMenu.Armor1)
						{
							ImGui::Checkbox(XorStr(u8"Броня"), &Vars.VisualMenu.ArmorDraw);
							ImGui::Checkbox(XorStr(u8"Полоска Брони"), &Vars.VisualMenu.ArmorBar);
						}





						ImGui::Selectable(XorStr(u8" ESP Оружие  "), &Vars.VisualMenu.WeaponESP1);
						if (Vars.VisualMenu.WeaponESP1)
						{
							ImGui::Checkbox(XorStr(u8"Оружие в руках"), &Vars.VisualMenu.ESPWeapon);
							ImGui::Checkbox(XorStr(u8"Оружие на полу"), &Vars.VisualMenu.DropWeapon);



							ImGui::Checkbox(XorStr(u8"2D Боксы оружия"), &Vars.VisualMenu.Weapon2DBox);
							ImGui::Checkbox(XorStr(u8"3D Боксы оружия"), &Vars.VisualMenu.Weapon3DBox);
						}


						ImGui::Selectable(XorStr(u8" InfoDamge"), &Vars.VisualMenu.InfoDamge);
						ImGui::Selectable(XorStr(u8" HitMarks"), &Vars.VisualMenu.HitMarks);
						ImGui::Selectable(XorStr(u8" Круги"), &Vars.VisualMenu.CircleEsp);
						ImGui::Selectable(XorStr(u8" Линии"), &Vars.VisualMenu.ESPLine);
						ImGui::Selectable(XorStr(u8" Голова"), &Vars.VisualMenu.Head);
						ImGui::Selectable(XorStr(u8" Ники"), &Vars.VisualMenu.ESPNickName);
						/*ImGui::Checkbox(XorStr(u8"Последнее место"), &Vars.VisualMenu.ESPLastPlace);*/
						ImGui::Selectable(XorStr(u8" Показ Взгляда"), &Vars.VisualMenu.BulletTrace);
						if (Vars.VisualMenu.BulletTrace)
							ImGui::SliderFloat(XorStr(u8" Длина"), &Vars.VisualMenu.BulletTraceLength, 0, 150);
						ImGui::Selectable(XorStr(u8" Дистанция"), &Vars.VisualMenu.ESPDistance);
						ImGui::Selectable(XorStr(u8" Скелет"), &Vars.VisualMenu.ESPSkelet);
						ImGui::Selectable(XorStr(u8" Ослеплен"), &Vars.VisualMenu.IsFlashed);
						ImGui::Selectable(XorStr(u8" Показать Pitch"), &Vars.VisualMenu.ShowPitch);
						ImGui::Selectable(XorStr(u8" Показать Yaw"), &Vars.VisualMenu.ShowYaw);

						ImGui::NextColumn();

						ImGui::Selectable(XorStr(" Chams"), &Vars.Visuals.Chams.Enabled);
						ImGui::Selectable(XorStr(" Visible Hidden"), &Vars.Visuals.Chams.XQZ);
						ImGui::Selectable(XorStr(u8" Показывать Врагов"), &Vars.Visuals.Filter.Enemies);
						ImGui::Selectable(XorStr(u8" Показывать Союзников"), &Vars.Visuals.Filter.Friendlies);

						ImGui::NextColumn();

						ImGui::MyColorEdit3(XorStr(u8"Chams CT Видимые"), Vars.g_iChamsCTV, 1 << 7);
						ImGui::MyColorEdit3(XorStr(u8"Chams CT За стеной"), Vars.g_iChamsCTH, 1 << 7);
						ImGui::MyColorEdit3(XorStr(u8"Chams T Видимые"), Vars.g_iChamsTV, 1 << 7);
						ImGui::MyColorEdit3(XorStr(u8"Chams T За стеной"), Vars.g_iChamsTH, 1 << 7);
						ImGui::MyColorEdit3(XorStr(u8"Player Видимые"), Vars.g_iChamsLV, 1 << 7);
						ImGui::MyColorEdit3(XorStr(u8"Player За стеной"), Vars.g_iChamsLH, 1 << 7);

					}
					break;
				case 0:
					//AimBot
					ImGui::Columns(3, NULL, false);
					{
						ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), (XorStr(u8"Клавиша Аимбота  ")));
						ImGui::Combo(XorStr(u8" "), &Vars.Legitbot.Aimbot.Key, AimKey, ARRAYSIZE(AimKey));
						ImGui::Checkbox(XorStr(u8"Включить AimBot"), &Vars.Legitbot.Aimbot.Enabled);
						ImGui::Checkbox(XorStr(u8"Включить pSilent"), &Vars.Legitbot.pSilent);
						ImGui::Checkbox(XorStr(u8"Всегда включен"), &Vars.Legitbot.Aimbot.AlwaysOn);
						ImGui::Checkbox(XorStr(u8"AimBot на клавишу"), &Vars.Legitbot.Aimbot.OnKey);
						ImGui::Checkbox(XorStr(u8"Проверка Smoke"), &Vars.Legitbot.CHKSmoke);
						ImGui::Checkbox(XorStr(u8"AutoPistol"), &Vars.Misc.AutoPistol);

						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox(XorStr(u8"Огонь по своим"), &Vars.Legitbot.Aimbot.FriendlyFire);
						ImGui::Checkbox(XorStr(u8"Настройка на каждое оружие"), &Vars.Menu.AllWeapSettings);

						if (Vars.Menu.AllWeapSettings)
						{
							ImGui::Checkbox(XorStr(u8"Вкл Fov под каждое"), &AV.Enable);
							ImGui::Checkbox(XorStr(u8"Вкл Smooth под каждое"), &AV.Smooth);
						}

				

						
					}

					ImGui::Columns(4, NULL, false);
					{
						if (Vars.Menu.AllWeapSettings)
						{
							ImGui::Separator();
							ImGui::BulletText(XorStr(u8"Для Автоматических "));
							ImGui::Spacing();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), (XorStr(u8"Кость  ")));
							ImGui::Combo(XorStr(u8"##Кость AU"), &AV.Automatic.HitBoxAim, AutomaticBones, ARRAYSIZE(AutomaticBones));
							ImGui::Text(XorStr(u8"FOV  "));
							ImGui::SliderFloat(XorStr("##FOV AU"), &AV.Automatic.Fov, 1.f, 50.f);
							ImGui::Text(XorStr(u8"Smooth  "));
							ImGui::SliderFloat(XorStr("##Smooth AU"), &AV.Automatic.Smooth, 1.f, 8.f);

							ImGui::NextColumn();
							ImGui::BulletText(XorStr(u8"Для Снайперских "));
							ImGui::Spacing();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), (XorStr(u8"Кость  ")));
							ImGui::Combo(XorStr(u8"##Кость "), &AV.Sniper.HitBoxAim, SniperBones, ARRAYSIZE(SniperBones));
							ImGui::Text(XorStr(u8"FOV   "));
							ImGui::SliderFloat(XorStr(" "), &AV.Sniper.Fov, 1.1f, 45.f);
							ImGui::Text(XorStr(u8"Smooth    "));
							ImGui::SliderFloat(XorStr("  "), &AV.Sniper.Smooth, 1.f, 8.f);


							ImGui::NextColumn();
							ImGui::BulletText(XorStr(u8"Для Дробовиков "));
							ImGui::Spacing();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), (XorStr(u8"Кость     ")));
							ImGui::Combo(XorStr(u8"##Bone"), &AV.Shotgun.HitBoxAim, ShotgunBones, ARRAYSIZE(ShotgunBones));
							ImGui::Text(XorStr(u8"FOV    "));
							ImGui::SliderFloat(XorStr("##FOV SG"), &AV.Shotgun.Fov, 1.1f, 30.f);
							ImGui::Text(XorStr(u8"Smooth        "));
							ImGui::SliderFloat(XorStr("##Smooth SG"), &AV.Shotgun.Smooth, 1.f, 8.f);

							ImGui::NextColumn();
							ImGui::BulletText(XorStr(u8"Для Пистолетов "));
							ImGui::Spacing();
							ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), (XorStr(u8"Кость      ")));
							ImGui::Combo(XorStr(u8"##Кость PS"), &AV.Pistol.HitBoxAim, PistolBones, ARRAYSIZE(PistolBones));
							ImGui::Text(XorStr(u8"FOV        "));
							ImGui::SliderFloat(XorStr("##FOV PS"), &AV.Pistol.Fov, 1.1f, 20.f);
							ImGui::Text(XorStr(u8"Smooth         "));
							ImGui::SliderFloat(XorStr("##Smooth PS"), &AV.Pistol.Smooth, 1.f, 8.f);
						}
					}
					break;
				case 2:
					//Misc
					ImGui::Columns(2, NULL, false);
					{
						ImGui::Checkbox(XorStr(u8"Name Spam [CRYSTYLE]"), &Vars.Misc.ChangeNick);
						ImGui::Checkbox(XorStr(u8"Name Spam [Ссылка Группы]"), &Vars.Misc.ChangeNickGroup);
						ImGui::Checkbox(XorStr(u8"Name Spam [Сайт Чита]"), &Vars.Misc.ChangeNickSite);
						ImGui::Checkbox(XorStr(u8"Name Spam [Нет Ника]"), &Vars.Misc.NoName);

						ImGui::Checkbox(XorStr(u8"Custom Ник"), &Vars.Misc.ChangeNick2);
						if (Vars.Misc.ChangeNick2)
						{
							ImGui::InputText(XorStr(u8" "), buf5, IM_ARRAYSIZE(buf5));
						}


						ImGui::Checkbox(XorStr(u8"Сменить ClanTag на CRYSTYLE"), &Vars.Misc.ChangClanTag);
						ImGui::Checkbox(XorStr(u8"Custom ClanTag"), &Vars.Misc.ChangClanTag2);
						if (Vars.Misc.ChangClanTag2)
						{
							ImGui::InputText(XorStr(u8" "), buf6, IM_ARRAYSIZE(buf6));
						}

						ImGui::Checkbox(XorStr(u8"Чат Спам Сайта"), &Vars.Misc.ChatSpam);
						if (Vars.Misc.ChatSpam)
						{
							ImGui::SliderFloat(XorStr(u8"Интервал Спама"), &Vars.Misc.SpamTime, 1.f, 16.f);
						}

						ImGui::Checkbox(XorStr(u8"Чат Спам Группы ВК"), &Vars.Misc.ChatSpam12);
						if (Vars.Misc.ChatSpam12)
						{
							ImGui::SliderFloat(XorStr(u8"Интервал Спама "), &Vars.Misc.SpamTime, 1.f, 16.f);
						}

						ImGui::Checkbox(XorStr(u8"Custom Чат Спам"), &Vars.Misc.ChatSpam2);
						if (Vars.Misc.ChatSpam2)
						{
							ImGui::InputText(XorStr(u8" "), buf7, IM_ARRAYSIZE(buf7));
							ImGui::SliderFloat(XorStr(u8"Интервал Спама"), &Vars.Misc.SpamTime, 1.f, 16.f);
						}




						ImGui::NextColumn();

						ImGui::Checkbox(XorStr("textmenu"), &Vars.Misc.misc_ptextmenu);
						ImGui::Checkbox(XorStr("Radar"), &Vars.m_radarIsActive);
						ImGui::Checkbox(XorStr("Bunny Hop"), &Vars.Misc.Bhop);
						ImGui::Checkbox(XorStr(u8"SpectatorList"), &Vars.SpectatorList);
						ImGui::Checkbox(XorStr(u8"Лист Обновлений Чита"), &Vars.updateinfo);
						ImGui::Checkbox(XorStr("Auto Strafe"), &Vars.Misc.AutoStrafe);
						ImGui::Checkbox(XorStr("Legit AutoStrave"), &Vars.Misc.LegitAutoStrafe);
						ImGui::Checkbox(XorStr(u8"Ranks"), &Vars.Misc.Ranks);
						ImGui::Checkbox(XorStr("BombTimer"), &Vars.VisualMenu.BombTimer);

						ImGui::Checkbox(XorStr("No Flash"), &Vars.Visuals.Removals.Flash);
						if (Vars.Visuals.Removals.Flash)
							ImGui::SliderFloat(XorStr("No Flash"), &Vars.Visuals.Removals.AlphaFlash, 0.f, 200.f);
						ImGui::Checkbox(XorStr("View Model Fov changer"), &Vars.Misc.FCV);
						if (Vars.Misc.FCV)
							ImGui::SliderInt(XorStr("VM FOV"), &Vars.Misc.FOVV, 0, 120);

						ImGui::Checkbox(XorStr("Fov changer"), &Vars.Misc.FC);
						if (Vars.Misc.FC)
							ImGui::SliderInt(XorStr("FOV"), &Vars.Misc.FOV, 0, 60);
					}
					break;

				case 3:
					//TriggerBot
					ImGui::Checkbox(XorStr(u8"Включить TriggerBot"), &Vars.Legitbot.Triggerbot.Enabled);
					ImGui::Checkbox(XorStr(u8"Автовыстрел"), &Vars.Legitbot.Triggerbot.AutoFire);
					ImGui::Combo(XorStr(u8"Клавиша TriggerBot'a"), &Vibor2, TriggKey, ARRAYSIZE(TriggKey));
					ImGui::Checkbox(XorStr(u8"Огонь По Своим"), &Vars.Legitbot.Triggerbot.FrFr);
					break;
				case 4:
					//Glow & Chams
					ImGui::Columns(2, NULL, false);
					{
						ImGui::Checkbox(XorStr("C4"), &Vars.Visuals.Glows.c4);
						ImGui::Checkbox(XorStr(u8"Игроки"), &Vars.Visuals.Glows.player);
						ImGui::Checkbox(XorStr(u8"Оружие"), &Vars.Visuals.Glows.weapon);
						ImGui::Checkbox(XorStr(u8"Показывать Своих"), &Vars.Visuals.Glows.ourPlayers);
						ImGui::NextColumn();


						

					}
					break;
				case 5:
					//Settings


					static int iConfigSelect = 0;
					static int iMenuSheme = 1;
					static char ConfigName[64] = { 0 };

					ImGui::ComboBoxArray("Select Config", &iConfigSelect, ConfigList);


					if (ImGui::Button("Load Config"))
						Settings::LoadSettings(BaseDir + "\\" + ConfigList[iConfigSelect]);

					ImGui::SameLine();
					if (ImGui::Button("Save Config"))
						Settings::SaveSettings(BaseDir + "\\" + ConfigList[iConfigSelect]);

					ImGui::SameLine();

					if (ImGui::Button("Refresh Config List"))
						RefreshConfigs();


					ImGui::InputText("Config Name", ConfigName, 64);

					if (ImGui::Button("Create and Save new Config"))
					{
						string ConfigFileName = ConfigName;

						if (ConfigFileName.size() < 1)
							ConfigFileName = "settings";


						Settings::SaveSettings(BaseDir + "\\" + ConfigFileName + ".ini");
						RefreshConfigs();
					}

					break;
				}
			}
			ImGui::End();
		}

		if (Vars.m_radarIsActive)
			showRadarHack();

		if (Vars.SpectatorList)
			OnRenderSpectatorList();


		ImGui::Render();
	}
	JUNK_CODE_ONE
	return oPresent(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


HRESULT WINAPI myReset(IDirect3DDevice9* m_pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	JUNK_CODE_ONE

	if (!m_pDevice)
		return S_OK;

	if (!Create)
		return m_pDevice->Reset(pPresentationParameters);

	ImGui_InvalidateDeviceObjects();
	auto hResult = oReset(m_pDevice, pPresentationParameters);
	ImGui_CreateDeviceObjects();
	
	JUNK_CODE_ONE
	return hResult;
}
