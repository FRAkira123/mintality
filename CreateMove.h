#pragma once


using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
CreateMoveFn oCreateMove;

class CreateMoveFunc 
{
public:
	virtual ~CreateMoveFunc() = 0 {}
	virtual void BunnyHop(IClientEntity* pLocal, CUserCmd* pCmd) = 0;
	virtual void AutoStrafe(IClientEntity* LocalPlayer, CUserCmd* pCmd) = 0;
	virtual void AutoPistol(CBaseCombatWeapon* pWeapon, CUserCmd* pCmd) = 0;
	virtual void ChangeName(const char* name) = 0;
	virtual void LegitStrafe(IClientEntity* LocalPlayer, CUserCmd *pCmd) = 0;
	virtual void Spamer(const char* message, float TimeSpam) = 0;
	virtual void RCS(IClientEntity* mPlayer, IVEngineClient* pEngineClient, float &add) = 0;
	virtual void ClantagChanger(IClientEntity* mPlayer, char* text) = 0;
	virtual void SetClanTag(const char* tag, const char* name) = 0;
};

class PlayerCreateMove : public CreateMoveFunc 
{
public:

	enum MoveType_t
	{
		MOVETYPE_NONE = 0,
		MOVETYPE_ISOMETRIC,
		MOVETYPE_WALK,
		MOVETYPE_STEP,
		MOVETYPE_FLY,
		MOVETYPE_FLYGRAVITY,
		MOVETYPE_VPHYSICS,
		MOVETYPE_PUSH,
		MOVETYPE_NOCLIP,
		MOVETYPE_LADDER,
		MOVETYPE_OBSERVER,
		MOVETYPE_CUSTOM,
		MOVETYPE_LAST = MOVETYPE_CUSTOM,
		MOVETYPE_MAX_BITS = 4
	};

	template<class T, class U>
	T Clamp(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}

	float NormalizeFloat(float result)
	{
		while (result > 180.0f)
			result -= 360.0f;

		while (result < -180.0f)
			result += 360.0f;

		return result;
	}

	void BunnyHop(IClientEntity* pLocal, CUserCmd* pCmd) override
	{
		static bool bLastJumped = false;
		static bool bShouldFake = false;

		if (!bLastJumped && bShouldFake)
		{
			bShouldFake = false;
			pCmd->buttons |= IN_JUMP;
		}
		else if (pCmd->buttons & IN_JUMP)
		{
			if (pLocal->GetFlags() & FL_ONGROUND)
			{
				bLastJumped = true;
				bShouldFake = true;
			}
			else
			{
				pCmd->buttons &= ~IN_JUMP;
				bLastJumped = false;
			}
		}
		else
		{
			bLastJumped = false;
			bShouldFake = false;
		}
	}

	void AutoStrafe(IClientEntity* LocalPlayer, CUserCmd* pCmd) override
	{
		if (LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
		static float move = 650.f;
		float s_move = move * 0.5065f;
		if ((LocalPlayer->GetFlags() & FL_ONGROUND)) return;

		pCmd->forwardmove = move * 0.015f;
		pCmd->sidemove += static_cast<float>(((pCmd->tick_count % 2) * 2) - 1) * s_move;

		if (pCmd->mousedx)
			pCmd->sidemove = static_cast<float>(Clamp(pCmd->mousedx, -1, 1)) * s_move;

		static auto strafe = pCmd->viewangles.Y;

		float rt = pCmd->viewangles.Y, rotation;
		rotation = strafe - rt;

		if (rotation < -pGlobals->interval_per_tick)
			pCmd->sidemove = -s_move;

		if (rotation > pGlobals->interval_per_tick)
			pCmd->sidemove = s_move;

		strafe = rt;
	}

	void AutoPistol(CBaseCombatWeapon* pWeapon,CUserCmd* pCmd) override
	{
		WeaponType t = pWeapon->GetWeaponType();
		if (t == WeaponType::Pistol && (GetAsyncKeyState(0x1) & 0x8000))
		{
			static bool WasFiring = false;
			if (pCmd->buttons & IN_ATTACK)
			{
				if (WasFiring)
				{
					pCmd->buttons &= ~IN_ATTACK;
				}
			}
			WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
		}
	}

	void ChangeName(const char* name) override
	{
		ConVar* nameConvar = pCon->FindVar(XorStr("name"));
		*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;
		nameConvar->SetValue(name);
	}

	void LegitStrafe(IClientEntity* LocalPlayer, CUserCmd *pCmd) override
	{
		auto* pLocal = LocalPlayer;
		if (!(pLocal->GetFlags() & FL_ONGROUND))
		{
			pCmd->forwardmove = 0.0f;

			if (pCmd->mousedx < 0)
			{
				pCmd->sidemove = -450.0f;
			}
			else if (pCmd->mousedx > 0)
			{
				pCmd->sidemove = 450.0f;
			}
		}
	}

	void Spamer(const char* message, float TimeSpam) override
	{

		static clock_t start_t = clock();
		double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
		if (timeSoFar < TimeSpam)
			return;

		char buffer[250];
		sprintf_s(buffer, "say \"%s\"", message);
		pEngine->ExecuteClientCmd(buffer);

		start_t = clock();

	}


	Vector OldAngle = { 0 ,0, 0 };
	void RCS(IClientEntity* mPlayer, IVEngineClient* pEngineClient, float &add) override
	{
		if (!mPlayer || !pEngineClient)
			return;


		WeaponType t = mPlayer->GetWeapon()->GetWeaponType();
		if (t == WeaponType::Sniper 
			|| t == WeaponType::Knife 
			|| t == WeaponType::Bomb)
			return;

		Vector ViewAngle = { 0 ,0, 0 },
			ModifiedAngle = { 0 ,0, 0 };

		pEngineClient->GetViewAngles(ViewAngle);
		ViewAngle.Normalize();
		Vector PunchAngle = mPlayer->m_vecPunch();

		ViewAngle.X += OldAngle.X;
		ViewAngle.Y += OldAngle.Y;
		ViewAngle.Z = 0;

		ModifiedAngle.X = ViewAngle.X - PunchAngle.X * add;
		ModifiedAngle.Y = ViewAngle.Y - PunchAngle.Y * add;
		ModifiedAngle.Z = ViewAngle.Z;

		ModifiedAngle.Normalize();

		if (!ModifiedAngle.X && !ModifiedAngle.Y)
			return;

		pEngineClient->SetViewAngles(ModifiedAngle);

		OldAngle.X = PunchAngle.X * add;
		OldAngle.Y = PunchAngle.Y * add;

	}


	void SetClanTag(const char* tag, const char* name) override
	{
		static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>((DWORD)(FindPatternWithoutMask(XorStr("engine.dll"), XorStr("53 56 57 8B DA 8B F9 FF 15"))));
		pSetClanTag(tag, name);
	}


	void ClantagChanger(IClientEntity* mPlayer, char* text) override
	{
		if (!pEngine->IsConnected() || !pEngine->IsInGame())
			return;

		SetClanTag(text, mPlayer->GetName().c_str());

	}
	
};

int crs  = 0;
void Trigger_bot(IClientEntity* pLocalEntity, CUserCmd *pCmd)
{
	int CrossId = pLocalEntity->GetCrossId();
	crs = CrossId;

	

	if ((GetAsyncKeyState(dwKey2[Vibor2]) || Vars.Legitbot.Triggerbot.AutoFire) && Vars.Legitbot.Triggerbot.Enabled)
	{	
		if (CrossId > 0 && CrossId <= 64)
		{
			auto ChoosedPlayer = pClientEntList->GetClientEntity(CrossId);

			if (!EntityIsValid(CrossId))
				return;

			WeaponType t = pLocalEntity->GetWeapon()->GetWeaponType();

			if ((pLocalEntity->IsValid() == false)
				|| pLocalEntity->GetWeapon()->IsReloading()
				|| pLocalEntity->GetWeapon()->IsEmpty()
				|| t == WeaponType::Knife
				|| t == WeaponType::Grenade
				|| t == WeaponType::Bomb
				)

				return;

			if((ChoosedPlayer->GetTeamNum() != pLocalEntity->GetTeamNum()) || (ChoosedPlayer->GetTeamNum() == pLocalEntity->GetTeamNum() && Vars.Legitbot.Triggerbot.FrFr))
				pCmd->buttons |= IN_ATTACK;
		}
		
	}
	
}




PlayerCreateMove *PCM = new PlayerCreateMove();
CreateMoveFunc *CMF = PCM;
bool __stdcall CreateMovesss(float flInputSampleTime, CUserCmd* cmd)
{
	if (pEngine->IsInGame() == false)
		return false;

	JUNK_CODE_ONE

	if (!cmd->command_number || cmd->command_number == 0)
		return false;

	auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (!pLocalEntity)
		return false;

	auto pWeapon = pLocalEntity->GetWeapon();

	if(!pWeapon)
		return false;


	Global::UserCmd = cmd;
	Global::LocalPlayer = pLocalEntity;



	if (pLocalEntity->IsValid())
	{

		Global::MyViewAng = cmd->viewangles;

		if (Vars.Misc.Bhop)
			CMF->BunnyHop(pLocalEntity, cmd);

		if (Vars.Misc.AutoPistol)
			CMF->AutoPistol(pWeapon, cmd);

		if (Vars.Misc.AutoStrafe)
			CMF->AutoStrafe(pLocalEntity, cmd);

		if (Vars.Misc.ChangeNick)
			CMF->ChangeName(buf);

		if (Vars.Misc.ChangClanTag)
			CMF->ClantagChanger(pLocalEntity, buf3);

		if (Vars.Misc.LegitAutoStrafe)
			CMF->LegitStrafe(pLocalEntity, cmd);

		if (Vars.Misc.ChatSpam)
			CMF->Spamer(buf2, Vars.Misc.SpamTime);

		if (Vars.Visuals.Removals.Flash)
			pLocalEntity->NoFlash(Vars.Visuals.Removals.AlphaFlash);


		if (Vars.Misc.RCS && AIMVar.m_ibesttargetlegit < 0)
			CMF->RCS(pLocalEntity, pEngine, Vars.Misc.RCSWork);
		

		LegitBot->Run(pLocalEntity);		
		Trigger_bot(pLocalEntity, cmd);


		DWORD* framePointer;
		__asm mov framePointer, ebp;
		*(bool*)(*framePointer - 0x1C) = Global::SendPacket;

		cmd->viewangles.Clamp();

		JUNK_CODE_ONE
			
			
	}
	


	return false;
}
