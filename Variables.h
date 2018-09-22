#pragma once
bool  PressedKeys[256] = {};


#define VK_E 0x45
#define VK_C 0x43
#define VK_V 0x56

int Vibor1 = -1;
const char* AimKey[10] = { "LKM", "PKM", "CTRL", "SHIFT", "E", "C", "V", "Mouse5", "Mouse6","CapsLock" };
DWORD dwKey[10] = { VK_LBUTTON, VK_RBUTTON, VK_LCONTROL, VK_SHIFT, VK_E, VK_C, VK_V, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL };

int Vibor2 = -1;
DWORD dwKey2[10] = { VK_LBUTTON, VK_RBUTTON, VK_LCONTROL, VK_SHIFT, VK_E, VK_C, VK_V, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL };
const char* TriggKey[10] = { "LKM", "PKM", "CTRL", "SHIFT", "E", "C", "V", "Mouse5", "Mouse6","CapsLock" };

static char buf[135] = "XXX                                                                                                            \r";
static char buf9[135] = "vk.com/cXX                                                                                                       \r";
static char buf10[135] = "XX                                                                                                         \r";
static char buf2[64] = "XX | Private project";
static char buf3[64] = "XX ";
static char buf4[64] = "vk.com/XX | XX";
static char buf8[135] = "                                                                                                                              \r ";
static char buf5[64] = " ";
static char buf6[64] = " ";
static char buf7[64] = " ";

struct Variables
{
	Variables()
	{

	}
	bool m_radarIsActive = false;
	bool SpectatorList = false;
	bool updateinfo = false;



	//Chams
	float g_iChamsTV[4] = { 0.968f, 0.705f, 0.078f, 1.0f };
	float g_iChamsCTH[4] = { 0.247f, 0.282f, 0.803f, 1.0f };
	float g_iChamsTH[4] = { 0.941f, 0.117f, 0.137f, 1.0f };
	float g_iChamsCTV[4] = { 0.125f, 0.705f, 0.223f, 1.0f };
	float g_iChamsLV[4] = { 0.125f, 0.705f, 0.223f, 1.0f };
	float g_iChamsLH[4] = { 0.125f, 0.705f, 0.223f, 1.0f };


	float g_fMColor[4] = { 0.21f, 0.43f, 0.56f, 0.7f };
	float g_fBColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };//RGBA color
	float g_fTColor[4] = { 1.f, 1.f, 1.f, 1.f };
	float g_fSColor[4] = { 1.f, 1.f, 1.f, 1.f };

	struct Ragebot_s
	{
		bool 	Enabled = false;
		bool 	AutoFire;
		bool 	Hold;
		int 	HoldKey;
		bool    AlwayOn;
		int 	Filter; // will hold flags for team/enemy/etc.
		bool 	Silent;
		bool	RCS;
		bool 	VisCheck;
		bool 	AutoWall;
		float	AutoWallDmg;
		int 	TargetMethod;
		int		Hitbox;
		float 	FOV = 360.f;
		float 	AimKey = 1;
		bool    FreFir;
		bool 	HitChance;
		float	HitChanceAmt;
		bool 	AutoStop;
		bool 	AutoCrouch;
		bool 	FriendlyFire;
		bool	Aimstep;
		float	AimstepAmount;
		bool	HitScanAll;
		bool	HitScanHitbox;
		bool	UntrustedCheck = true;
		struct
		{
			bool	Enabled;
			int		Pitch;
			int		Yaw;
			bool	AimAtPlayer;
			bool	DetectEdge;
			bool	PSilent;
		} Antiaim;

	} Ragebot;

	struct
	{
		
		bool 	Enabled = false;
		float 	FOV = 360;
		int 	Key = 0;
		bool	OnKey;
		int 	Filter; // will hold flags for team/enemy/etc.
		bool 	RCS = true;
		float 	RCSAmount = 50;
		float	Speed = 1.5f;
		bool 	VisCheck;
		int 	Hitbox;

		bool 	AlwaysOn;
		bool	FriendlyFire;
		bool FreFir = false;

		float Distance = 500.f;
		struct
		{
			bool	Enabled = false;
			bool	AutoFire;
			int		Key;
			bool 	HitChance;
			float	HitChanceAmt;
			bool	Dellay;
			float	DellayAAmt;
			bool FrFr = false;

			struct
			{
				bool Head;
				bool Chest;
				bool Stomach;
				bool Arms;
				bool Legs;
				bool Friendly;
				
			} Filter;
		
		} Triggerbot;


		struct
		{
			bool	Enabled;
			bool	AutoFire;
			int		Key;
			bool 	HitChance;
			float	HitChanceAmt;
			bool	FrendlyFire;
			bool Button;

		} KnifeBot;


		struct
		{
			bool 	Enabled;
			int 	Key;
			bool	OnKey;
			int     group;
			int 	Filter; // will hold flags for team/enemy/etc.
			bool    smart;
			bool 	VisCheck;
			bool 	AlwaysOn;
			bool	FriendlyFire;
			bool	SmokeCheck;
			bool    AutoPistol;
			bool 	kill;
			float 	WE12;
		} Aimbot;


//		bool 	Enabled;
//		bool 	pSilent;
		float RCSAmountX = 100.f;
		float RCSAmountY = 100.f;
//		float	Speed;
//		int 	Hitbox;
//		float	PFOV;
//		float 	FOV;
		bool 	AdaptiveRSC = false;
		bool CHKSmoke = false;
		int 	WE;
		int 	WE2;


		bool fastzoom;
		bool fastzoomswitch;
		int delay;
		bool pSilent = false;


	} Legitbot;

	struct
	{
		bool 	Enabled;
		int 	Box;
		int 	BoxType;
		bool	Skeleton;
		bool	Glow;
		bool	BulletTrace;
		float   BulletTraceLength;
		bool	CrosshairOn;
		int		CrosshairType;
		int		CrosshairStyle;
		float 	TeamColor[3];
		float 	TeamColorWall[3];
		float 	EnemyColor[3];
		bool DropWeap;
		bool ASUS;
		float ASUSFactor;

		float 	EnemyColorWall[3];
		struct
		{
			bool Enemies;
			bool Friendlies;
			bool Weapons;
			bool Decoy;
			bool C4;
			bool Localplayer;
		} Filter;

		struct
		{
			bool	RainbowHands;
			float 	RainbowTime;
			bool	Enabled;
			int 	Mode;
			bool	Wireframe;
			bool	hands;
			bool	XQZ;
			float 	TeamColor[3];
			float 	TeamColorWall[3];
			float  	EnemyColor[3];
			float 	EnemyColorWall[3];
		} Chams;


		struct
		{
			bool 	Name;
			bool 	Health;
			bool 	Weapon;
			bool	Flashed;
		} Info;

		struct
		{
			bool	Hands;
			bool    ColorHand;
			bool	Weapon;
			bool	VisualRecoil;
			bool	Flash;
			float  AlphaFlash = 0.f;
			bool    Smoke;
			bool	Sky;
			int HandsMode;
		} Removals;

		struct
		{
			bool c4 = false,
				player = false,
				weapon = false,
				ourPlayers = false;

		}Glows;


		int		SkyChanger = 0;
		int HandsType;
		int	ViewmodelChangerValue;
		bool AntiSS = false;
		bool NoSmoke;
		bool	RemovalsHands;
		bool	HandChams;
		bool	ChamsWeapon;
		bool	RemovalsVisualRecoil;
		bool	RemovalsFlash;
		bool    RemovalsSmoke;
		bool	RemovalsSky;
		bool Sound = false;
		bool ChamsChip = false;

		int WeaponsType;

	} Visuals;

	struct
	{
		bool 	Lolkekman = false;
		bool	ZapuskChita = false;
		bool 	Bhop = false;
		bool 	AutoStrafe = false;
		bool 	LegitAutoStrafe = false;
		bool	ChatSpam = false;
		bool	ChatSpam12 = false;
		bool	ChangeNick2 = false;
		bool	ChangeNickSite = false;
		bool	ChangClanTag2 = false;
		bool	ChatSpam2 = false;
		bool	NoName = false;
		bool    AutoPistol = false;
		bool    ChangeNick = false;
		bool   	ChangeNickGroup = false;
		float   SpamTime = 5.f;


		int		ChatSpamMode = false;
		bool	Watermark = false;
		bool	Ranks = false;
		bool	AirStuck = false;
		int		AirStuckKey = false;
		bool	AutoAccept = false;
		bool	Namespam = false;
		bool	typeoftop = false;
		bool misc_ptextmenu = false;

		bool RCS = false;
		float RCSWork = 2.f;

		bool FC = false;
		int FOV = 30;

		bool FCV = false;
		int FOVV = 30;
		bool    ChangClanTag = false;

		char* buf;
	} Misc;

	struct
	{

		int     AllTab = 0;
		bool	Opened = true;
		int 	Key;
		bool	Ragebot = false;
		bool	Legitbot = false;
		bool	Visual = false;
		bool    Colors = false;
		bool	Misc = false;
		bool	ColorMenu = false;
		bool    TriggerBot = false;
		bool    GlowMenu = false;
		bool   ChamsMenu = false;
		int		ConfigIndex;
		bool	LoadFaceit = true;
		bool   SettingsmMenu = false;
		bool AllWeapSettings = false;
	} Menu;

	struct
	{
		bool CircleEsp = false,
			Armor1 = false,
			Health1 = false,
			WeaponESP1 = false,
			boxed = false,
			Player2DBox = false,
			Player2DBox2 = false,
			Player3DBox = false,
			HitMarks = false,
			ESPLine = false,
			ESPHeads = false,
			HPBar = false,
			HealthDraw = false,
			ArmorBar = false,
			ArmorDraw = false,
			ESPNickName = false,
			ESPDistance = false,
			ESPLastPlace = false,
			ESPSkelet = false,
			ESPHitBox = false,
			IsFlashed = false,
			BulletTrace = false,
			InfoDamge = false,
			DropWeapon = false,
			ESPWeapon = false,
			BombTimer = false,
			Radar = false,
			Head = false,
			Weapon2DBox = false,
			Weapon3DBox = false,
			ShowPitch = false,
			ShowYaw = false;

			float BulletTraceLength = 50.f;

	}VisualMenu;

	struct
	{
		bool EnableAimBot = false;

	}AimBotMenu;



};



struct AimVariables
{
	struct
	{
		float Fov = 1;
		Vector HitBox = { 0,0,0 };
		int HitBoxAim = 0;
		float Smooth = 1.f;
		float distance = 1.f;
	}Automatic;

	struct
	{
		float Fov = 1;
		Vector HitBox = { 0,0,0 };
		int HitBoxAim = 0;
		float Smooth = 1.f;
		float distance = 1.f;
	}Pistol;

	struct
	{
		float Fov = 1;
		Vector HitBox = { 0,0,0 };
		int HitBoxAim = 0;
		float Smooth = 1.f;
		float distance = 1.f;
	}Sniper;


	struct
	{
		float Fov = 1;
		Vector HitBox = { 0,0,0 };
		int HitBoxAim = 0;
		float Smooth = 1.f;
		float distance = 1.f;

	}Shotgun;


	bool Enable = false;
	bool Smooth = false;
	float SmoothType = 1.f;
	int HitBox = 1;
	int RandomBone = 0;
}Av;

extern Variables Vars;
struct
{

	float m_bestfov = Vars.Legitbot.FOV;
	float m_bestdist = Vars.Legitbot.Distance;
	int m_ibesttargetlegit = -1;
	IClientEntity* MyPlayer = nullptr;

	Vector AimDot = { 0,0,0 };

	bool CheckTarget = false;
	int HitBox = 5;

}AIMVar;

const char* Bones[] =
{
	u8"Neck",
	u8"Chest",
	u8"Head",
	u8"Random",
	u8"Near",
};


const char* AutomaticBones[] =
{
	u8"None",
	u8"Neck",
	u8"Chest",
	u8"Head",
	u8"Random",
	u8"Near",
};

const char* PistolBones[] =
{
	u8"None",
	u8"Neck",
	u8"Chest",
	u8"Head",
	u8"Random",
	u8"Near",
};


const char* SniperBones[] =
{
	u8"None",
	u8"Neck",
	u8"Chest",
	u8"Head",
	u8"Random",
	u8"Near",
};

const char* ShotgunBones[] =
{
	u8"None",
	u8"Neck",
	u8"Chest",
	u8"Head",
	u8"Random",
	u8"Near",
};


const char* type_of_target[] =
{
	u8"Fov",
	u8"Distance",
	u8"Health"
};

const char* chamsMode[] =
{
	"Flat",
	"Textured"
};


const char* cWeaponsType[] =
{
	"None",
	"Nothing",
	"Chams",
	"Transparent",
	"Wireframe",
	"Blend",
	"Rainbow",

};
const char* cHandsType[] =
{
	"None",
	"Nothing",
	"Chams",
	"Transparent",
	"rWireframe",
	"Blend",
	"Rainbow",

};

const char* type_of_min_max[] =
{
	u8"Ближний",
	u8"Дальний"
};


const char* type_of_priority[] =
{
	u8"Fov",
	u8"Distance",
	u8"Real Distance",
	u8"Health",
	u8"Distance & FOV",
	u8"Real Distance & FOV",
	u8"Health & FOV",
	u8"Health & Distance"
};

const char* aimBones[] =
{
	"Head",
	"Neck",
	"Neck Lower",
	"Pelvis",
	"Stomach",
	"Chest",
	"LowerChest",
	"UpperChest",
	"Reandom",
	"Nearest",

};