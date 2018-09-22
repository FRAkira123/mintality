#pragma once


typedef PVOID pvoid;
using Emitsound_fn = void(__stdcall*)(pvoid&, int, int, const char*, unsigned int, const char*, float, float, int, int, int, const Vector*, const Vector*, void*, bool, float, int);
Emitsound_fn oEmitsound = nullptr;


namespace Sound
{
	struct clog
	{
		clog(Vector o, int t)
		{
			origin = o;
			time = t;
		}

		Vector origin;
		int time;
	};

	extern  std::deque< clog > log;

	extern void Add(clog player_log);
	extern void Draw();
};

void __stdcall Emitsound_Hook(void*& filter, int ent_id, int channel, const char *soundentry, unsigned int soundentryhash, const char *sample, float volume, float attenuation, int seed, int flags, int pitch, const Vector *origin, const Vector *direction, pvoid utlvecorigins, bool updatepositions, float soundtime, int speakerentity)
{
	oEmitsound(filter, ent_id, channel, soundentry, soundentryhash, sample, volume, attenuation, seed, flags, pitch, origin, direction, utlvecorigins, updatepositions, soundtime, speakerentity);

	auto player = pClientEntList->GetClientEntity(ent_id);

	if (!Global::LocalPlayer || !player || player == Global::LocalPlayer || (player->GetTeamNum() == Global::LocalPlayer->GetTeamNum() && !Vars.Visuals.Filter.Friendlies))
		return;

	if (channel == 4)
	{
		if (strstr(sample, "footsteps"))
		{
		/*	float delta = abs((*origin - Global::LocalPlayer->GetOrigin()).Length());
			if (delta > Vars.Visuals.SoundEspDist)
				return;*/

			Sound::clog player_log(*origin, pGlobals->curtime + 1);
			Sound::Add(player_log);
		}
	}
}




typedef void(__stdcall* PlaySoundFn)(ISurface*, const char* filename);
PlaySoundFn oPlaySound = nullptr;



void __stdcall OnPlaysound(const char* pszSoundName)
{
//	oPlaySound(pSurface, pszSoundName);
//
//
//	if (strcmp(pszSoundName, "!UI/competitive_accept_beep.wav") != 0)
//	{
//
//		typedef void(*IsReadyCallBackFn)();
//		IsReadyCallBackFn IsReadyCallBack = nullptr;
//
//
//		if (!IsReadyCallBack)
//			IsReadyCallBack = (IsReadyCallBackFn)(FindPatternWithoutMask("client.dll", "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE"));
//		else
//			IsReadyCallBack();
//	}
//
////	if (strcmp(pszSoundName, "!UI/competitive_accept_beep.wav") != 0)
////		return;
//
//
//
}