#pragma once

	void NVA(Vector &angle)
	{

		while (angle.Y <= -180) angle.Y += 360;
		while (angle.Y > 180) angle.Y -= 360;
		while (angle.X< -89) angle.X = -89;
		while (angle.X > 89) angle.X = 89;


		if (angle.X > 89.0) angle.X = 89;
		if (angle.X < -89.0)angle.X = -89;
		if (angle.Y < -180)  angle.Y = -179.999;
		if (angle.Y > 180)  angle.Y = 179.999;

		angle.Z = 0;
	}


	void SmoothAimAngles(Vector MyViewAngles, Vector AimAngles, Vector &OutAngles, float Smoothing) 
	{
		VectorSubtract(AimAngles, MyViewAngles, OutAngles);

		NVA(OutAngles);

		OutAngles.X = OutAngles.X / Smoothing + MyViewAngles.X;
		OutAngles.Y = OutAngles.Y / Smoothing + MyViewAngles.Y;

		NVA(OutAngles);
	}


	void Norma(Vector &vIn, Vector &vOut)
	{
		float flLen = vIn.Length();
		if (flLen == 0) {
			vOut.Init(0, 0, 1);
			return;
		}
		flLen = 1 / flLen;
		vOut.Init(vIn.X * flLen, vIn.Y* flLen, vIn.Z * flLen);
	}


	void CA(Vector src, Vector dst, Vector &angles)
	{
		Vector delta = src - dst;
		double hyp = delta.Length2D(); //delta.Length
		angles.Y = (atan(delta.Y / delta.X) * 57.295779513082f);
		angles.X = (atan(delta.Z / hyp) * 57.295779513082f);
		angles.Z = 0.00;

		if (delta.X >= 0.0)
			angles.Y += 180.0f;
	}


	DWORD WINAPI InitRandomBone(HANDLE h_Thread)
	{
		while (true)
		{
			AV.RandomBone = GetRandom(0, 7);
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
		}
		return 0;
	}

	
	bool EntityIsValid(int i)
	{
		auto* pEntity = pClientEntList->GetClientEntity(i);

		if (!pEntity)
			return false;

		if (pEntity->IsDormant())
			return false;

		if (pEntity->GetHealth() <= 0)
			return false;

		if (!pEntity->GetAlive())
			return false;

		if (pEntity->HasGunGameImmunity())
			return false;

		if (pEntity == Global::LocalPlayer)
			return false;


		return true;
	}




CBaseCombatWeapon* IClientEntity::GetWeapon()
{
	auto hActiveWeapon = *(DWORD*)((DWORD)this + Engine::Dynamic::Weapon::m_hActiveWeapon);
	return (CBaseCombatWeapon*)pClientEntList->GetClientEntityFromHandle(hActiveWeapon);
}

int CBaseCombatWeapon::GetWeaponID()
{
	typedef int(__thiscall* GetWeaponIDFn)(void*);
	return call_vfunc<GetWeaponIDFn>(this, 458)(this);
}

float& CBaseCombatWeapon::GetNextPrimaryAttack()
{
	return *(float*)((DWORD)this + Engine::Dynamic::Weapon::m_flNextPrimaryAttack);
}

float& CBaseCombatWeapon::GetAccuracyPenalty()
{
	return *(float*)((DWORD)this + Engine::Dynamic::Weapon::m_fAccuracyPenalty);
}

int& CBaseCombatWeapon::GetXUIDLow()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_OriginalOwnerXuidLow);
}

int& CBaseCombatWeapon::GetXUIDHigh()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_OriginalOwnerXuidHigh);
}

int& CBaseCombatWeapon::GetEntityQuality()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_iEntityQuality);
}

int& CBaseCombatWeapon::GetAccountID()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_iAccountID);
}

int& CBaseCombatWeapon::GetItemIDHigh()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_iItemIDHigh);
}

int& CBaseCombatWeapon::GetItemDefinitionIndex()
{
	return *(int*)((DWORD)this + (DWORD)DynNetVars::m_iItemDefinitionIndex);
}

int& CBaseCombatWeapon::GetFallbackPaintKit()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_nFallbackPaintKit);
}

int& CBaseCombatWeapon::GetFallbackStatTrak()
{
	return *(int*)((DWORD)this + Engine::Dynamic::Weapon::m_nFallbackStatTrak);
}

float& CBaseCombatWeapon::GetFallbackWear()
{
	return *(float*)((DWORD)this + Engine::Dynamic::Weapon::m_flFallbackWear);
}


bool CBaseCombatWeapon::IsEmpty()
{
	int clip = *(int*)((DWORD)this + 0x00003204 /*offsets.m_iClip1*/);
	return clip == 0;
}

bool CBaseCombatWeapon::IsReloading()
{
	return *(bool*)((DWORD)this + 0x3235);
}

void CBaseCombatWeapon::UpdateAccuracyPenalty()
{
	call_vfunc<void(__thiscall*)(void*)>(this, 471)(this);

}

float CBaseCombatWeapon::GetWeaponCone()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return call_vfunc<OriginalFn>(this, 478)(this);
}

float CBaseCombatWeapon::GetWeaponSpread()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return call_vfunc<OriginalFn>(this, 485)(this);
}

WeaponType CBaseCombatWeapon::GetWeaponType()
{
	auto WeaponID = this->GetItemDefinitionIndex();

	if (WeaponID == WEAPON_XM1014 || WeaponID == WEAPON_NOVA || WeaponID == WEAPON_SAWEDOFF || WeaponID == WEAPON_MAG7)
		return WeaponType::Shotgun;

	if (WeaponID == WEAPON_P2000
		|| WeaponID == WEAPON_USPS
		|| WeaponID == WEAPON_GLOCK
		|| WeaponID == WEAPON_DUALS
		|| WeaponID == WEAPON_P250
		|| WeaponID == WEAPON_CZ75
		|| WeaponID == WEAPON_P2000
		|| WeaponID == WEAPON_FIVE7
		|| WeaponID == WEAPON_TEC9
		|| WeaponID == WEAPON_DEAGLE
		|| WeaponID == WEAPON_R8REVOLVER)
		return WeaponType::Pistol;

	if (WeaponID == WEAPON_M249
		|| WeaponID == WEAPON_NEGEV
		|| WeaponID == WEAPON_MAC10
		|| WeaponID == WEAPON_MP9
		|| WeaponID == WEAPON_MP7
		|| WeaponID == WEAPON_UMP45
		|| WeaponID == WEAPON_P90
		|| WeaponID == WEAPON_BIZON
		|| WeaponID == WEAPON_FAMAS
		|| WeaponID == WEAPON_GALIL
		|| WeaponID == WEAPON_M4A1
		|| WeaponID == WEAPON_M4A1S
		|| WeaponID == WEAPON_AUG
		|| WeaponID == WEAPON_SG553
		|| WeaponID == WEAPON_AK47)
		return WeaponType::Automatic;

	if (WeaponID == WEAPON_SSG08
		|| WeaponID == WEAPON_AWP
		|| WeaponID == WEAPON_SCAR20
		|| WeaponID == WEAPON_G3SG1)
		return WeaponType::Sniper;

	if (WeaponID == WEAPON_FLASHBANG
		|| WeaponID == WEAPON_HEGRENADE
		|| WeaponID == WEAPON_DECOY
		|| WeaponID == WEAPON_SMOKEGRENADE
		|| WeaponID == WEAPON_MOLOTOV
		|| WeaponID == WEAPON_INCGRENADE)
		return WeaponType::Grenade;

	if (WeaponID == WEAPON_KNIFEGG
		|| WeaponID == WEAPON_KNIFE_T
		|| WeaponID == WEAPON_KNIFE_CT
		|| WeaponID == WEAPON_KNIFE_BAYONET
		|| WeaponID == WEAPON_KNIFE_FLIP
		|| WeaponID == WEAPON_KNIFE_GUT
		|| WeaponID == WEAPON_KNIFE_KARAMBIT
		|| WeaponID == WEAPON_KNIFE_M9BAYONET
		|| WeaponID == WEAPON_KNIFE_HUNTSMAN
		|| WeaponID == WEAPON_KNIFE_FALCHION
		|| WeaponID == WEAPON_KNIFE_BUTTERFLY)
		return WeaponType::Knife;
	
	if (WeaponID == WEAPON_C4)
		return WeaponType::Bomb;
}


int	CBaseCombatWeapon::Clip1()
{
	return *(int*)((DWORD)this + (DWORD)DynNetVars::m_iClip1);
}
bool CBaseCombatWeapon::IsValid()
{
	WeaponType t = GetWeaponType();

	if (t != WeaponType::Knife && t != WeaponType::Grenade && t != WeaponType::Bomb)
	{
		if (Clip1() > 0)
			return true;
	}
	return false;
}


void VectorAngles(const Vector& forward, Vector &angles)
{
	if (forward.Y == 0.0f && forward.X == 0.0f)
	{
		angles[0] = (forward.Z > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles.Y = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward.Z, forward.Length2D()) * -180 / M_PI;
		angles.Y = atan2(forward.Y, forward[0]) * 180 / M_PI;

		if (angles.Y> 90) angles.Y -= 180;
		else if (angles.Y < 90) angles.Y += 180;
		else if (angles.Y == 90) angles.Y = 0;
	}

	angles[2] = 0.0f;
}


Vector CalcAngle(Vector src, Vector dst)
{
	Vector angles = {0, 0, 0,};
	Vector delta = src - dst;
	VectorAngles(delta, angles);
	delta.Normalize();
	return angles;
}

class CLegitBot
{
public:
	void Run(IClientEntity* LocalPlayer);
private:
	int FindTarget(IClientEntity * pLocalPlayer, CUserCmd * pCmd);
};

CLegitBot *LegitBot = new CLegitBot();


float GetFov(Vector& viewAngle,Vector& aimAngle)
{
	Vector delta = aimAngle - viewAngle;
	delta.Normalized();
	return sqrtf(powf(delta.X, 2.0f) + powf(delta.Y, 2.0f));
}

int ClosestBone(IClientEntity *Entity, CUserCmd* cmd)
{
	/*	if (Vars.Legitbot.Hitbox == 0)
			return (int)CSGOHitboxID::Neck;
		else if (Vars.Legitbot.Hitbox == 1)
			return (int)CSGOHitboxID::Chest;
		else if (Vars.Legitbot.Hitbox == 2)
			return (int)CSGOHitboxID::Head;
		else if (Vars.Legitbot.Hitbox == 3)
			return AV.RandomBone;*/
	/*else if (Vars.Legitbot.Hitbox == 4)
	{*/
		float BestDist = 360.f;
		int aimbone;

		matrix3x4_t matrix[128];

		if (!Entity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, pEngine->GetLastTimeStamp()))
			return -1;

		auto pStudioModel = pModelInfo->GetStudioModel(Entity->GetModel());
		if (!pStudioModel)
			return -1;

		auto set = pStudioModel->pHitboxSet(Entity->GetHitboxSet());
		if (!set)
			return -1;

		for (int i = 0; i < set->numhitboxes; i++)
		{
			if (i == (int)CSGOHitboxID::RightThigh || i == (int)CSGOHitboxID::LeftThigh || i == (int)CSGOHitboxID::LeftFoot
				|| i == (int)CSGOHitboxID::RightShin || i == (int)CSGOHitboxID::LeftShin || i == (int)CSGOHitboxID::RightFoot
				|| i == (int)CSGOHitboxID::RightHand || i == (int)CSGOHitboxID::LeftHand || i == (int)CSGOHitboxID::RightUpperArm
				|| i == (int)CSGOHitboxID::RightLowerArm || i == (int)CSGOHitboxID::LeftUpperArm || i == (int)CSGOHitboxID::LeftLowerArm)
				continue;

			auto hitbox = set->pHitbox(i);

			if (!hitbox)
				continue;


			auto thisdist = GetFov(cmd->viewangles, CalcAngle(Global::LocalPlayer->GetEyePos(), Renderer::GetInstance()->GetHitboxPosition(Entity, hitbox->bone)));

			if (BestDist > thisdist)
			{
				BestDist = thisdist;
				aimbone = hitbox->bone;
				continue;
			}
		}
		return aimbone;
	//}
	
	

}
enum target_sort_type : int {
	by_hp = 0,      // ∆изнь
	by_distance = 1,    // ƒистанци€
	by_cross_hair = 2 ,  // ѕрицел
};
enum target_len : int {
	target_min = 0, //ћинимальна€ (к ближнему)
	target_max = 1,     //ћаксимальна€ (к дальнему)
};
struct target_player
{
	int index = -1;      //јйди игрока
	float distance = 0.f; //ƒистаци€ от себ€ к игроку
	int hp = 0;       //жизнь игрока
	float Angle = 0.f;    //дистанци€ кросхаира, от центра экрана к игроку

	target_player(int _index, float _distance, int _hp, float _angle) : index(_index), distance(_distance), hp(_hp), Angle(_angle) {  }
};

float getHypotenuseFromCenter(Vector Point)
{
	float PositionX = 0;
	float PositionY = 0;
	float ScreenCenterX, ScreenCenterY;
	Vector Screen = {0,0,0};

	static int width = 0, height = 0;
	pEngine->GetScreenSize(width, height);
	ScreenCenterX = width / 2;
	ScreenCenterY = height / 2;

	if (WorldToScreen(Point, Screen) == FALSE) {
		return 9999.0f;
	}

	PositionX = Screen.X > ScreenCenterX ? Screen.X - ScreenCenterX : ScreenCenterX - Screen.X;
	PositionY = Screen.Y > ScreenCenterY ? Screen.Y - ScreenCenterY : ScreenCenterY - Screen.Y;

	return sqrt(PositionX * PositionX + PositionY * PositionY);
}




int FindTargetByPriority(IClientEntity* g_pLocalPlayer, CUserCmd* g_pCmd, target_sort_type flSortType, target_len min_max_len)
{
	int target = -1;

	if (g_pLocalPlayer->IsValid() == true
		|| !g_pLocalPlayer->GetWeapon()->IsReloading()
		|| !g_pLocalPlayer->GetWeapon()->IsEmpty()
		|| g_pLocalPlayer->GetWeapon()->GetWeaponType() != WeaponType::Knife
		|| g_pLocalPlayer->GetWeapon()->GetWeaponType() != WeaponType::Grenade
		|| g_pLocalPlayer->GetWeapon()->GetWeaponType() != WeaponType::Bomb
		)
	{
		std::vector<target_player> g_PlayerList;

		for (int index = 0; index < pClientEntList->GetHighestEntityIndex(); index++) {

			auto pEntityPlayer = pClientEntList->GetClientEntity(index);

			if (EntityIsValid(index) == false)
				continue;

			if (!Vars.Legitbot.Aimbot.FriendlyFire && pEntityPlayer->GetTeamNum() == g_pLocalPlayer->GetTeamNum())
				continue;
			else
				if ((Vars.Legitbot.Aimbot.FriendlyFire && pEntityPlayer->GetTeamNum() != g_pLocalPlayer->GetTeamNum()) && pEntityPlayer->GetTeamNum() == g_pLocalPlayer->GetTeamNum())
					continue;

			if (!pEntityPlayer->IsVisible(ClosestBone(pEntityPlayer, g_pCmd)))
				continue;

			//ѕолучаем дистанцию
			float distance = Renderer::GetInstance()->Distance(g_pLocalPlayer->GetOrigin(), pEntityPlayer->GetOrigin());
			//ѕолучаем хп
			int hp = pEntityPlayer->GetHealth();
			//получаем угол от цели до центра экрана
			float AngleLength = getHypotenuseFromCenter(pEntityPlayer->GetOrigin());
			//заносим в список смертников)
			g_PlayerList.push_back(target_player(index, distance, hp, AngleLength));
		}
		//если возможные цели есть:
		if (g_PlayerList.size() > 0)
		{
			//сортируем
			switch (flSortType)
			{
				//если тип сортировки по прицелу
			case target_sort_type::by_cross_hair:
				std::sort(g_PlayerList.begin(), g_PlayerList.end(), [](const target_player a, const target_player b) { return a.Angle < b.Angle; });
				break;
				//если тип сортировки по дистанции
			case target_sort_type::by_distance:
				std::sort(g_PlayerList.begin(), g_PlayerList.end(), [](const target_player a, const target_player b) { return a.distance < b.distance; });
				break;
				//тип сортировки по хп
			case target_sort_type::by_hp:
				std::sort(g_PlayerList.begin(), g_PlayerList.end(), [](const target_player a, const target_player b) { return a.hp < b.hp; });
				break;

			}
			//далее выбираем цель из сортированного списка.
			switch (min_max_len)
			{
				//если нужно минимальное. самый ближний по: дистанции/прицелу, или с самым меньшим хп
			case target_len::target_min:
				target = g_PlayerList.front().index; //айди игрока - наша цель дл€ аима
				break;
				//если нужно максимальное. самый дальний по дистанции/прицелу, или с самым большим хп.
			case target_len::target_max:
				target = g_PlayerList.back().index; //айди игрока - наша цель дл€ аима
				break;
			}
		}

		//очищаем список сортировки так как у нас уже есть айди цели.
		g_PlayerList.clear();
	}
	//возвращаем результат.
	return target;
}


float GetFovs(Vector& viewAngle, Vector& aimAngle)
{
	Vector delta = aimAngle - viewAngle;
	delta.Normalized();
	return sqrtf(powf(delta.X, 2.0f) + powf(delta.Y, 2.0f));
}

int CLegitBot::FindTarget(IClientEntity* pLocalPlayer, CUserCmd* pCmd)
{
	float flMax = 8192.f;
	int iBestTarget = -1;

	if (!pLocalPlayer || !pCmd)
		return -1;

		for (int i = 0; i < pClientEntList->GetHighestEntityIndex(); i++)
		{
			auto pEntityPlayer = pClientEntList->GetClientEntity(i);

			if (EntityIsValid(i) == false)
				continue;

			if (AV.Enable)
			{
				if (!IsVisible(pEntityPlayer))
					continue;

				Vector Calcs  = { 0,0,0 }, 
					   OldAng = { 0,0,0 };

				pEngine->GetViewAngles(OldAng);
				CA(pLocalPlayer->GetEyePos(), pEntityPlayer->GetEyePos(), Calcs);
				AIMVar.m_bestfov = GetFovs(OldAng, Calcs);

			}
			else
			{
				if (!pEntityPlayer->IsVisible(ClosestBone(pEntityPlayer, pCmd)))
					continue;

				AIMVar.m_bestfov = GetFov(pCmd->viewangles, CalcAngle(pLocalPlayer->GetEyePos(), Renderer::GetInstance()->GetHitboxPosition(pEntityPlayer, ClosestBone(pEntityPlayer, pCmd))));
			}
				
			
			if (!Vars.Legitbot.Aimbot.FriendlyFire && pEntityPlayer->GetTeamNum() == pLocalPlayer->GetTeamNum())
				continue;
			else
				if ((Vars.Legitbot.Aimbot.FriendlyFire && pEntityPlayer->GetTeamNum() != pLocalPlayer->GetTeamNum()) && pEntityPlayer->GetTeamNum() == pLocalPlayer->GetTeamNum())
					continue;


			if (AIMVar.m_bestfov < flMax)
			{
				flMax = AIMVar.m_bestfov;
				iBestTarget = i;
			}	
	
		}

	return iBestTarget;
}


bool LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos)
{
	typedef bool(__cdecl* _LineGoesThroughSmoke) (Vector, Vector);

	static _LineGoesThroughSmoke LineGoesThroughSmokeFn = nullptr;
	static bool SearchFunction = false;

	if (!SearchFunction)
	{
		DWORD dwFunctionAddress = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));

		if (dwFunctionAddress)
		{
			LineGoesThroughSmokeFn = (_LineGoesThroughSmoke)dwFunctionAddress;
			SearchFunction = true;
		}
	}

	if (LineGoesThroughSmokeFn && SearchFunction)
		return LineGoesThroughSmokeFn(vStartPos, vEndPos);

	return false;
}




Vector SyncWeapon(IClientEntity* mePlayer, IClientEntity* pEntity)
{
	if (!mePlayer || !pEntity)
		return Vector(0, 0, 0);

	WeaponType t = mePlayer->GetWeapon()->GetWeaponType();

	if (AV.Enable == true && mePlayer->GetWeapon()->IsValid())
	{
		if (t == WeaponType::Automatic)
		{
			AIMVar.m_bestfov = AV.Automatic.Fov;
			AV.SmoothType = AV.Automatic.Smooth;
			switch (AV.Automatic.HitBoxAim)
			{
			default:
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
			case  1:
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
			case  2:
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::LowerChest); break;
			case  3:
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head); break;
			case  4:
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, AV.RandomBone); break;
			case 5: 
				return Renderer::GetInstance()->GetHitboxPosition(pEntity, ClosestBone(pEntity, Global::UserCmd));
			}

		}
		else
			if (t == WeaponType::Pistol)
			{

				AIMVar.m_bestfov = AV.Pistol.Fov;
				AV.SmoothType = AV.Pistol.Smooth;
				switch (AV.Pistol.HitBoxAim)
				{
				default:
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
				case  1:
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
				case  2:
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::LowerChest); break;
				case  3:
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head); break;
				case  4:
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, AV.RandomBone); break;
				case 5: 
					return Renderer::GetInstance()->GetHitboxPosition(pEntity, ClosestBone(pEntity, Global::UserCmd));
				}

			}
			else

				if (t == WeaponType::Sniper)
				{

					AIMVar.m_bestfov = AV.Sniper.Fov;
					AV.SmoothType = AV.Sniper.Smooth;
					switch (AV.Sniper.HitBoxAim)
					{
					default:
						return  Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
					case  1:
						return  Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
					case  2:
						return  Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::LowerChest); break;
					case  3:
						return  Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head); break;
					case  4:
						return  Renderer::GetInstance()->GetHitboxPosition(pEntity, AV.RandomBone); break;
					case 5:
						return Renderer::GetInstance()->GetHitboxPosition(pEntity, ClosestBone(pEntity, Global::UserCmd));
					}

				}

				else
					if (t == WeaponType::Shotgun)
					{

						AIMVar.m_bestfov = AV.Sniper.Fov;
						AV.SmoothType = AV.Sniper.Smooth;
						switch (AV.Shotgun.HitBoxAim)
						{
						default:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
						case  1:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Neck); break;
						case  2:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::LowerChest); break;
						case  3:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head); break;
						case  4:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, AV.RandomBone); break;
						case 5:
							return Renderer::GetInstance()->GetHitboxPosition(pEntity, ClosestBone(pEntity, Global::UserCmd));
						}

					}

	}

}


void CLegitBot::Run(IClientEntity* pLocalPlayer)
{	
	float flRecoilX = Vars.Legitbot.RCSAmountX;
	float flRecoilY = Vars.Legitbot.RCSAmountY;
	int CrossId = pLocalPlayer->GetCrossId();

	if (!Vars.Legitbot.Aimbot.Enabled)
		return;

	if (pLocalPlayer->IsValid() == false
		||pLocalPlayer->GetWeapon()->IsReloading()
		|| pLocalPlayer->GetWeapon()->IsEmpty()
		|| pLocalPlayer->GetWeapon()->GetWeaponType() == WeaponType::Knife
		|| pLocalPlayer->GetWeapon()->GetWeaponType() == WeaponType::Grenade
		|| pLocalPlayer->GetWeapon()->GetWeaponType() == WeaponType::Bomb
		)
		return;


	if (!(Vars.Legitbot.Aimbot.AlwaysOn || (Vars.Legitbot.Aimbot.OnKey &&  GetAsyncKeyState(dwKey[Vars.Legitbot.Aimbot.Key]))))
		return;

	if (test_targets)
	{
		switch (target_type)
		{
		case 0:
			switch (min_max)
			{
			case 0:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_cross_hair, target_len::target_min);
				break;
			case 1:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_cross_hair, target_len::target_max);
				break;
			}
			break;

		case 1:
			switch (min_max)
			{
			case 0:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_distance, target_len::target_min);
				break;
			case 1:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_distance, target_len::target_max);
				break;
			}
			break;
			switch (min_max)
			{
			case 0:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_hp, target_len::target_min);
				break;
			case 1:
				AIMVar.m_ibesttargetlegit = FindTargetByPriority(pLocalPlayer, Global::UserCmd, target_sort_type::by_hp, target_len::target_max);
				break;
			}
		case 2: break;
		}
	}
	else
		if (!test_targets)	
			AIMVar.m_ibesttargetlegit = FindTarget(pLocalPlayer, Global::UserCmd);
	
		
	if (AIMVar.m_ibesttargetlegit == -1)
		return;

	auto pEntityPlayer = pClientEntList->GetClientEntity(AIMVar.m_ibesttargetlegit);

	if (!EntityIsValid(AIMVar.m_ibesttargetlegit))
		return;


	Vector  vecBone = { 0, 0, 0 };
	
	
	if(AV.Enable)
		vecBone = SyncWeapon(pLocalPlayer, pEntityPlayer);
	else
		vecBone = Renderer::GetInstance()->GetHitboxPosition(pEntityPlayer, ClosestBone(pEntityPlayer, Global::UserCmd));

		
	if (vecBone.IsZero())
		return;


	if (Vars.Legitbot.CHKSmoke)
		if (LineGoesThroughSmoke(pLocalPlayer->GetEyePos(), vecBone))
			return;

	auto qAim = CalcAngle(pLocalPlayer->GetEyePos(), vecBone);


	if (GetFov(Global::UserCmd->viewangles, qAim) > AIMVar.m_bestfov)
			return;

	if ((flRecoilX > 1.f || flRecoilY >  1.f) && pLocalPlayer->GetShotsFired() > 2)
	{
		if (pLocalPlayer->aim_punch().Length() > 0.f &&  pLocalPlayer->GetPunch().Length() < 150.f)
		{

			if (flRecoilX > 1)
				qAim.X -= pLocalPlayer->GetPunch().X * (flRecoilX / 50.f);

			if (flRecoilY > 1)
				qAim.Y -= pLocalPlayer->GetPunch().Y * (flRecoilY / 50.f);

		}
	}


	float flSmooth = 10.f;
	
	if (Vars.Legitbot.pSilent && (pLocalPlayer->GetShotsFired() > 0 && pLocalPlayer->GetShotsFired() < 2))
		flSmooth = 0.1f;
	else
		if (Vars.Legitbot.pSilent &&  pLocalPlayer->GetShotsFired() > 1)
		{
			if (AV.Enable && AV.Smooth)
			{
				auto delta = Global::UserCmd->viewangles - qAim;
				flSmooth = AV.SmoothType;
				if (!delta.IsZero())
				{
					delta.Normalized();
					qAim = Global::UserCmd->viewangles - delta / flSmooth;
				}
			}
			else 	
				if (!AV.Enable || !AV.Smooth)
				{
					flSmooth = Vars.Legitbot.Speed;
					if (flSmooth >= 1.f)
					{
						auto delta = Global::UserCmd->viewangles - qAim;
						if (!delta.IsZero())
						{
							delta.Normalized();
							qAim = Global::UserCmd->viewangles - delta / flSmooth;
						}
					}
				}
		}
		else 
			if (AV.Enable && AV.Smooth)
			{
				auto delta = Global::UserCmd->viewangles - qAim;
				flSmooth = AV.SmoothType;
				if (!delta.IsZero())
				{
					delta.Normalized();
					qAim = Global::UserCmd->viewangles - delta / flSmooth;
				}
			}
			else
				if (!AV.Enable || !AV.Smooth )
				{
					flSmooth = Vars.Legitbot.Speed;
					if (flSmooth >= 1.f)
					{
						auto delta = Global::UserCmd->viewangles - qAim;
						if (!delta.IsZero())
						{
							delta.Normalized();
							qAim = Global::UserCmd->viewangles - delta / flSmooth;
						}
					}
				} 
		


	qAim.Normalized();
	qAim.Clamp();

	bool bBulletTime = true;
	if (pLocalPlayer->GetWeapon()->GetNextPrimaryAttack() > pLocalPlayer->GetTickBase() * pGlobals->interval_per_tick)
		bBulletTime = false;

	if (Vars.Legitbot.pSilent &&  pLocalPlayer->GetShotsFired() < 3 )
	{
		if (pLocalPlayer->GetWeapon()->GetNextPrimaryAttack() - ((float)pLocalPlayer->GetTickBase()* pGlobals->interval_per_tick) > 0)
		{	
				if (Global::UserCmd->buttons & IN_ATTACK && bBulletTime)
					Global::SendPacket = false;
				else
					Global::SendPacket = true;
		}

		if (pLocalPlayer->GetShotsFired() > 3)
			Global::SendPacket = true;

		Global::UserCmd->viewangles = qAim;
		
	}
	else 
		if ((pLocalPlayer->GetShotsFired() > 2 && Vars.Legitbot.pSilent) || !Vars.Legitbot.pSilent)
		{

			Global::UserCmd->viewangles = qAim;
			pEngine->SetViewAngles(Global::UserCmd->viewangles);
		}
		

	Global::UserCmd->viewangles.Normalized();
	Global::UserCmd->viewangles.Clamp();


	return;
}

