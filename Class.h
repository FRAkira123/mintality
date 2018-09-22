#pragma once


template <typename fdata>
fdata GetType(DWORD address)
{
	return *(fdata*)(address);
}

template <typename fdata>
void SetValueUnsafe(DWORD address, fdata data)
{
	*(fdata*)(address) = data;
}


class IBaseClientDLL;
class IVEngineClient;
class IPanel;

class IClientEntityList;
class ISurface;
class IVModelInfo;
class CGlobalVarsBase;
class IEngineTrace;
class CInput;
class IMaterialSystem;
class IVModelRender;
class IGameMovement;
class IPredicIPredictiontion;
class IVEfx;
typedef ULONG HFont;
class IVPhysicsDebugOverlay;
class RecvTable;
class RecvProp;
class ICollideable;
class IHandleEntity;
class CBaseHandle;
class IClientNetworkable;
class IClientEntity;
class IClientThinkable;
class IClientUnknown;
class IClientNetworkable;
class IClientMode;
class WeaponInfo_t;
class CHudTexture;
class IClientModeShared;
class ConVar;
struct model_t;
class CModelInfo;
class C_CSGameRules;
class IAppSystem;
typedef struct InputContextHandle_t__ *InputContextHandle_t;
struct client_textmessage_t;
class SurfInfo;
class IMaterial;
class IMaterialVar;
class CSentence;
class CAudioSource;
struct AudioState_t;
class ISpatialQuery;
class CPhysCollide;
class IAchievementMgr;
class INetChannelInfo;
class ISPSharedMemory;
class CGamestatsData;
class KeyValues;
class CSteamAPIContext;
struct Frustum_t;
struct vcollide_t;
struct model_t;
class QAngle;
class CGameTrace;
struct cplane_t;
typedef CGameTrace trace_t;
struct studiohdr_t;
struct virtualmodel_t;
typedef unsigned char byte;
struct virtualterrainparams_t;
class CPhysCollide;
typedef unsigned short MDLHandle_t;
class CUtlBuffer;
class IClientRenderable;
class Quaternion;
struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
struct mstudiobodyparts_t;
struct mstudiotexture_t;
class IVDebugOverlay;

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

typedef void*	(*CreateClientClassFn)(int entnum, int serialNum);
typedef void*	(*CreateEventFn)();


typedef unsigned int VPANEL;
typedef void(*pfnDemoCustomDataCallback)(unsigned char *pData, size_t iSize);

namespace Engine
{
	namespace Dynamic
	{
		extern void					Initialize();
		namespace Entity
		{
			extern DWORD_PTR
				m_iHealth,
				m_iTeamNum,
				m_nTickBase,
				m_lifeState,
				m_ArmorValue,
				m_bHasHelmet,
				m_Local,
				m_vecOrigin,
				m_vecViewOffset,
				m_vecVelocity,
				m_aimPunchAngle,
				m_viewPunchAngle,
				m_angEyeAngles,
				m_fFlags,
				m_hActiveWeapon,
				m_bIsDefusing,
				m_flC4Blow,
				m_nHitboxSet,
				m_iShotsFired,
				m_bIsBroken,
				m_rgflCoordinateFrame,
				m_CollisionGroup,
				m_Collision,
				m_vecMins,
				m_vecMaxs,
				m_Move,
				m_flFlashDuration,
				m_bSpottedByMask,
				m_iCrossHairID,
				m_bIsValveDS,
				m_GunGameImmunity,
				m_bIsScoped,
				m_flLowerBodyYawTarget;

		}

		namespace Weapon
		{
			extern DWORD_PTR		m_iClip1,
				m_flNextPrimaryAttack,
				m_fAccuracyPenalty,
				m_iItemDefinitionIndex,
				m_OriginalOwnerXuidLow,
				m_OriginalOwnerXuidHigh,
				m_nFallbackSeed,
				m_nFallbackPaintKit,
				m_flFallbackWear,
				m_iItemIDHigh,
				m_nFallbackStatTrak,
				m_hMyWeapons,
				m_AttributeManager,
				m_Item,
				m_iAccountID,
				m_iEntityQuality,
				m_szCustomName,
				m_hActiveWeapon;


		}
	}
}
namespace DynNetVars
{
	extern DWORD m_iHealth;
	extern DWORD dwCompRanks;
	extern DWORD dwCompWins;
	extern DWORD m_iBulletsFired;
	extern DWORD m_iTeamNum;
	extern DWORD m_bGunGameImmunity;
	extern DWORD m_lifeState;
	extern DWORD m_fFlags;
	extern DWORD m_Local;
	extern DWORD m_nTickBase;
	extern DWORD m_nForceBone;
	extern DWORD m_nModelIndex;
	extern DWORD m_viewPunchAngle;
	extern DWORD m_aimPunchAngle;
	extern DWORD m_vecOrigin;
	extern DWORD m_vecViewOffset;
	extern DWORD m_vecVelocity;
	extern DWORD m_szLastPlaceName;
	extern DWORD m_flNextPrimaryAttack;
	extern DWORD m_hActiveWeapon;
	extern DWORD m_fAccuracyPenalty;
	extern DWORD m_Collision;
	extern DWORD m_iWeaponID;
	extern DWORD m_nHitboxSet;
	extern DWORD m_bHasHelmet;
	extern DWORD m_ArmorValue;
	extern DWORD m_CollisionGroup;
	extern DWORD m_iClass;
	extern DWORD m_bIsBroken;
	extern DWORD m_angEyeAngles;
	extern DWORD m_hOwnerEntity;
	extern DWORD m_flC4Blow;
	extern DWORD m_flFlashDuration;
	extern DWORD m_flLowerBodyYawTarget;
	extern DWORD m_angEyeAnglesX;
	extern DWORD m_angEyeAnglesY;
	extern DWORD m_bIsScoped;
	extern DWORD deadflag;
	extern DWORD ViewModelIndex;
	extern DWORD WorldModelIndex;
	extern DWORD m_nFallbackPaintKit;
	extern DWORD m_nFallbackSeed;
	extern DWORD m_flFallbackWear;
	extern DWORD m_nFallbackStatTrak;
	extern DWORD m_AttributeManager;
	extern DWORD m_Item;
	extern DWORD m_iEntityLevel;
	extern DWORD m_iItemIDHigh;
	extern DWORD m_iItemIDLow;
	extern DWORD m_iAccountID;
	extern DWORD m_iEntityQuality;
	extern DWORD m_OriginalOwnerXuidLow;
	extern DWORD m_OriginalOwnerXuidHigh;
	extern DWORD m_iItemDefinitionIndex;
	extern DWORD m_iClip1;
	extern DWORD m_iClip2;
	extern DWORD m_bNadePinPulled;
	extern DWORD m_fNadeThrowTime;
	extern DWORD m_flPostponeFireReadyTime;
	extern DWORD m_bReloadVisuallyComplete;
	extern DWORD m_hObserverTarget;
	extern DWORD m_flFlashMaxAlpha;
	extern DWORD m_vecMins, m_vecMaxs, m_rgflCoordinateFrame,m_CrossId, m_iObserverMode;
	//end of offsets & netvars
}

struct Vertex_t
{
	Vertex_t() {}
	Vertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0)) {
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0)) {
		m_Position = pos;
		m_TexCoord = coord;
	}

	Vector2D m_Position;
	Vector2D m_TexCoord;
};
enum class FontFeature
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6,
};


#define MAX_SPLITSCREEN_CLIENT_BITS 2
#define MAX_SPLITSCREEN_CLIENTS	( 1 << MAX_SPLITSCREEN_CLIENT_BITS ) // 4
enum
{
	MAX_JOYSTICKS = MAX_SPLITSCREEN_CLIENTS,
	MOUSE_BUTTON_COUNT = 5,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

	// Joystick
	JOYSTICK_FIRST = MOUSE_LAST + 1,

	JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
	JOYSTICK_LAST_BUTTON = JOYSTICK_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_MAX_BUTTON_COUNT - 1),
	JOYSTICK_FIRST_POV_BUTTON,
	JOYSTICK_LAST_POV_BUTTON = JOYSTICK_POV_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_POV_BUTTON_COUNT - 1),
	JOYSTICK_FIRST_AXIS_BUTTON,
	JOYSTICK_LAST_AXIS_BUTTON = JOYSTICK_AXIS_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_AXIS_BUTTON_COUNT - 1),

	JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

	BUTTON_CODE_LAST,
	BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

	// Helpers for XBox 360
	KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON,	// POV buttons
	KEY_XBUTTON_RIGHT,
	KEY_XBUTTON_DOWN,
	KEY_XBUTTON_LEFT,

	KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON,		// Buttons
	KEY_XBUTTON_B,
	KEY_XBUTTON_X,
	KEY_XBUTTON_Y,
	KEY_XBUTTON_LEFT_SHOULDER,
	KEY_XBUTTON_RIGHT_SHOULDER,
	KEY_XBUTTON_BACK,
	KEY_XBUTTON_START,
	KEY_XBUTTON_STICK1,
	KEY_XBUTTON_STICK2,
	KEY_XBUTTON_INACTIVE_START,

	KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON,	// XAXIS POSITIVE
	KEY_XSTICK1_LEFT,							// XAXIS NEGATIVE
	KEY_XSTICK1_DOWN,							// YAXIS POSITIVE
	KEY_XSTICK1_UP,								// YAXIS NEGATIVE
	KEY_XBUTTON_LTRIGGER,						// ZAXIS POSITIVE
	KEY_XBUTTON_RTRIGGER,						// ZAXIS NEGATIVE
	KEY_XSTICK2_RIGHT,							// UAXIS POSITIVE
	KEY_XSTICK2_LEFT,							// UAXIS NEGATIVE
	KEY_XSTICK2_DOWN,							// VAXIS POSITIVE
	KEY_XSTICK2_UP,								// VAXIS NEGATIVE
};



enum class FontDrawType
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

enum class FontFlags {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct IntRect
{
	int x0;
	int y0;
	int w;
	int h;
};

template <typename Fn> __forceinline Fn call_vfunc(void* pClassBase, int nFunctionIndex)
{
	return (Fn)((PDWORD)*(PDWORD*)pClassBase)[nFunctionIndex];
}
enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};
#pragma once
class Color
{
public:
	// constructors
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int r, int g, int b)
	{
		SetColor(r, g, b, 0);
	}
	Color(int r, int g, int b, int a)
	{
		SetColor(r, g, b, a);
	}
	void SetColor(int r, int g, int b, int a = 0)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void GetColor(int &r, int &g, int &b, int &a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int *)this) = color32;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	int GetRawColor() const
	{
		return *((int *)this);
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	int GetD3DColor() const
	{
		return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
	}



	static Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}


	static Color Red() { return Color(255, 0, 0); }
	static Color Green() { return Color(0, 255, 0); }
	static Color Blue() { return Color(0, 0, 255); }
	static Color LightBlue() { return Color(100, 100, 255); }
	static Color Grey() { return Color(100, 100, 100, 190); }
	static Color DarkGrey() { return Color(45, 45, 45); }
	static Color Black() { return Color(0, 0, 0); }
	static Color White() { return Color(255, 255, 255); }
	static Color Purple() { return Color(220, 0, 220); }
	static Color WhiteBlack() { return Color(50, 50, 50, 175); }
	static Color WhiteOrange() { return Color(221, 143, 64, 175); }
	static Color Orange() { return Color(221, 112, 12, 190); }
	static Color WhiteGrey() { return Color(133, 133, 133, 175); }
	static Color WhiteGrey2() { return Color(155, 155, 155); }
	static Color GreyGroupBox() { return Color(75, 75, 75); }

private:
	unsigned char _color[4];
};


#define  Assert( _exp )										((void)0)

//-----------------------------------------------------------------------------
// Flags for GetVertexFormat
//-----------------------------------------------------------------------------
enum VertexFormatFlags_t
{
	// Indicates an uninitialized VertexFormat_t value
	VERTEX_FORMAT_INVALID = 0xFFFFFFFF,

	VERTEX_POSITION = 0x0001,
	VERTEX_NORMAL = 0x0002,
	VERTEX_COLOR = 0x0004,
	VERTEX_SPECULAR = 0x0008,

	VERTEX_TANGENT_S = 0x0010,
	VERTEX_TANGENT_T = 0x0020,
	VERTEX_TANGENT_SPACE = VERTEX_TANGENT_S | VERTEX_TANGENT_T,

	// Indicates we're using wrinkle
	VERTEX_WRINKLE = 0x0040,

	// Indicates we're using bone indices
	VERTEX_BONE_INDEX = 0x0080,

	// Indicates this expects a color stream on stream 1
	VERTEX_COLOR_STREAM_1 = 0x0100,

	// Indicates this format shouldn't be bloated to cache align it
	// (only used for VertexUsage)
	VERTEX_FORMAT_USE_EXACT_FORMAT = 0x0200,

	// Indicates that compressed vertex elements are to be used (see also VertexCompressionType_t)
	VERTEX_FORMAT_COMPRESSED = 0x400,

	// Position or normal (if present) should be 4D not 3D
	VERTEX_FORMAT_PAD_POS_NORM = 0x800,

	// Update this if you add or remove bits...
	VERTEX_LAST_BIT = 11,

	VERTEX_BONE_WEIGHT_BIT = VERTEX_LAST_BIT + 1,
	USER_DATA_SIZE_BIT = VERTEX_LAST_BIT + 4,
	TEX_COORD_SIZE_BIT = VERTEX_LAST_BIT + 7,

	VERTEX_BONE_WEIGHT_MASK = (0x7 << VERTEX_BONE_WEIGHT_BIT),
	USER_DATA_SIZE_MASK = (0x7 << USER_DATA_SIZE_BIT),

	VERTEX_FORMAT_FIELD_MASK = 0x0FF,

	// If everything is off, it's an unknown vertex format
	VERTEX_FORMAT_UNKNOWN = 0,
};

//-----------------------------------------------------------------------------
// Macros for construction..
//-----------------------------------------------------------------------------
#define VERTEX_BONEWEIGHT( _n )				((_n) << VERTEX_BONE_WEIGHT_BIT)
#define VERTEX_USERDATA_SIZE( _n )			((_n) << USER_DATA_SIZE_BIT)
#define VERTEX_TEXCOORD_MASK( _coord )		(( 0x7ULL ) << ( TEX_COORD_SIZE_BIT + 3 * (_coord) ))

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;

typedef uint64 VertexFormat_t;

inline VertexFormat_t VERTEX_TEXCOORD_SIZE(int nIndex, int nNumCoords)
{
	uint64 n64 = nNumCoords;
	uint64 nShift = TEX_COORD_SIZE_BIT + (3 * nIndex);
	return n64 << nShift;
}

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,	// NOTE: D3D9 does not have this format
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,

	IMAGE_FORMAT_NULL,			// Dummy format which takes no video memory

								// Compressed normal map formats
								IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
								IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

								IMAGE_FORMAT_RGBA1010102,	// 10 bit-per component render targets
								IMAGE_FORMAT_BGRA1010102,
								IMAGE_FORMAT_R16F,			// 16 bit FP format

															// Depth-stencil texture formats
															IMAGE_FORMAT_D16,
															IMAGE_FORMAT_D15S1,
															IMAGE_FORMAT_D32,
															IMAGE_FORMAT_D24S8,
															IMAGE_FORMAT_LINEAR_D24S8,
															IMAGE_FORMAT_D24X8,
															IMAGE_FORMAT_D24X4S4,
															IMAGE_FORMAT_D24FS8,
															IMAGE_FORMAT_D16_SHADOW,	// Specific formats for shadow mapping
															IMAGE_FORMAT_D24X8_SHADOW,	// Specific formats for shadow mapping

																						// supporting these specific formats as non-tiled for procedural cpu access (360-specific)
																						IMAGE_FORMAT_LINEAR_BGRX8888,
																						IMAGE_FORMAT_LINEAR_RGBA8888,
																						IMAGE_FORMAT_LINEAR_ABGR8888,
																						IMAGE_FORMAT_LINEAR_ARGB8888,
																						IMAGE_FORMAT_LINEAR_BGRA8888,
																						IMAGE_FORMAT_LINEAR_RGB888,
																						IMAGE_FORMAT_LINEAR_BGR888,
																						IMAGE_FORMAT_LINEAR_BGRX5551,
																						IMAGE_FORMAT_LINEAR_I8,
																						IMAGE_FORMAT_LINEAR_RGBA16161616,

																						IMAGE_FORMAT_LE_BGRX8888,
																						IMAGE_FORMAT_LE_BGRA8888,

																						NUM_IMAGE_FORMATS
};


//-----------------------------------------------------------------------------
// Gets at various vertex format info...
//-----------------------------------------------------------------------------
inline int VertexFlags(VertexFormat_t vertexFormat)
{
	return static_cast<int> (vertexFormat & ((1 << (VERTEX_LAST_BIT + 1)) - 1));
}

inline int NumBoneWeights(VertexFormat_t vertexFormat)
{
	return static_cast<int> ((vertexFormat >> VERTEX_BONE_WEIGHT_BIT) & 0x7);
}

inline int UserDataSize(VertexFormat_t vertexFormat)
{
	return static_cast<int> ((vertexFormat >> USER_DATA_SIZE_BIT) & 0x7);
}

inline int TexCoordSize(int nTexCoordIndex, VertexFormat_t vertexFormat)
{
	return static_cast<int> ((vertexFormat >> (TEX_COORD_SIZE_BIT + 3 * nTexCoordIndex)) & 0x7);
}


//-----------------------------------------------------------------------------
// VertexElement_t (enumerates all usable vertex elements)
//-----------------------------------------------------------------------------
// FIXME: unify this with VertexFormat_t (i.e. construct the lower bits of VertexFormat_t with "1 << (VertexElement_t)element")
enum VertexElement_t
{
	VERTEX_ELEMENT_NONE = -1,

	// Deliberately explicitly numbered so it's a pain in the ass to change, so you read this:
	// #!#!#NOTE#!#!# update GetVertexElementSize, VertexElementToDeclType and
	//                CVBAllocTracker (elementTable) when you update this!
	VERTEX_ELEMENT_POSITION = 0,
	VERTEX_ELEMENT_POSITION4D = 1,
	VERTEX_ELEMENT_NORMAL = 2,
	VERTEX_ELEMENT_NORMAL4D = 3,
	VERTEX_ELEMENT_COLOR = 4,
	VERTEX_ELEMENT_SPECULAR = 5,
	VERTEX_ELEMENT_TANGENT_S = 6,
	VERTEX_ELEMENT_TANGENT_T = 7,
	VERTEX_ELEMENT_WRINKLE = 8,
	VERTEX_ELEMENT_BONEINDEX = 9,
	VERTEX_ELEMENT_BONEWEIGHTS1 = 10,
	VERTEX_ELEMENT_BONEWEIGHTS2 = 11,
	VERTEX_ELEMENT_BONEWEIGHTS3 = 12,
	VERTEX_ELEMENT_BONEWEIGHTS4 = 13,
	VERTEX_ELEMENT_USERDATA1 = 14,
	VERTEX_ELEMENT_USERDATA2 = 15,
	VERTEX_ELEMENT_USERDATA3 = 16,
	VERTEX_ELEMENT_USERDATA4 = 17,
	VERTEX_ELEMENT_TEXCOORD1D_0 = 18,
	VERTEX_ELEMENT_TEXCOORD1D_1 = 19,
	VERTEX_ELEMENT_TEXCOORD1D_2 = 20,
	VERTEX_ELEMENT_TEXCOORD1D_3 = 21,
	VERTEX_ELEMENT_TEXCOORD1D_4 = 22,
	VERTEX_ELEMENT_TEXCOORD1D_5 = 23,
	VERTEX_ELEMENT_TEXCOORD1D_6 = 24,
	VERTEX_ELEMENT_TEXCOORD1D_7 = 25,
	VERTEX_ELEMENT_TEXCOORD2D_0 = 26,
	VERTEX_ELEMENT_TEXCOORD2D_1 = 27,
	VERTEX_ELEMENT_TEXCOORD2D_2 = 28,
	VERTEX_ELEMENT_TEXCOORD2D_3 = 29,
	VERTEX_ELEMENT_TEXCOORD2D_4 = 30,
	VERTEX_ELEMENT_TEXCOORD2D_5 = 31,
	VERTEX_ELEMENT_TEXCOORD2D_6 = 32,
	VERTEX_ELEMENT_TEXCOORD2D_7 = 33,
	VERTEX_ELEMENT_TEXCOORD3D_0 = 34,
	VERTEX_ELEMENT_TEXCOORD3D_1 = 35,
	VERTEX_ELEMENT_TEXCOORD3D_2 = 36,
	VERTEX_ELEMENT_TEXCOORD3D_3 = 37,
	VERTEX_ELEMENT_TEXCOORD3D_4 = 38,
	VERTEX_ELEMENT_TEXCOORD3D_5 = 39,
	VERTEX_ELEMENT_TEXCOORD3D_6 = 40,
	VERTEX_ELEMENT_TEXCOORD3D_7 = 41,
	VERTEX_ELEMENT_TEXCOORD4D_0 = 42,
	VERTEX_ELEMENT_TEXCOORD4D_1 = 43,
	VERTEX_ELEMENT_TEXCOORD4D_2 = 44,
	VERTEX_ELEMENT_TEXCOORD4D_3 = 45,
	VERTEX_ELEMENT_TEXCOORD4D_4 = 46,
	VERTEX_ELEMENT_TEXCOORD4D_5 = 47,
	VERTEX_ELEMENT_TEXCOORD4D_6 = 48,
	VERTEX_ELEMENT_TEXCOORD4D_7 = 49,

	VERTEX_ELEMENT_NUMELEMENTS = 50
};

inline void Detect_VertexElement_t_Changes(VertexElement_t element) // GREPs for VertexElement_t will hit this
{
	// Make it harder for someone to change VertexElement_t without noticing that dependent code
	// (GetVertexElementSize, VertexElementToDeclType, CVBAllocTracker) needs updating
	Assert(VERTEX_ELEMENT_NUMELEMENTS == 50);
	switch (element)
	{
	case VERTEX_ELEMENT_POSITION:		Assert(VERTEX_ELEMENT_POSITION == 0); break;
	case VERTEX_ELEMENT_POSITION4D:		Assert(VERTEX_ELEMENT_POSITION4D == 1); break;
	case VERTEX_ELEMENT_NORMAL:			Assert(VERTEX_ELEMENT_NORMAL == 2); break;
	case VERTEX_ELEMENT_NORMAL4D:		Assert(VERTEX_ELEMENT_NORMAL4D == 3); break;
	case VERTEX_ELEMENT_COLOR:			Assert(VERTEX_ELEMENT_COLOR == 4); break;
	case VERTEX_ELEMENT_SPECULAR:		Assert(VERTEX_ELEMENT_SPECULAR == 5); break;
	case VERTEX_ELEMENT_TANGENT_S:		Assert(VERTEX_ELEMENT_TANGENT_S == 6); break;
	case VERTEX_ELEMENT_TANGENT_T:		Assert(VERTEX_ELEMENT_TANGENT_T == 7); break;
	case VERTEX_ELEMENT_WRINKLE:		Assert(VERTEX_ELEMENT_WRINKLE == 8); break;
	case VERTEX_ELEMENT_BONEINDEX:		Assert(VERTEX_ELEMENT_BONEINDEX == 9); break;
	case VERTEX_ELEMENT_BONEWEIGHTS1:	Assert(VERTEX_ELEMENT_BONEWEIGHTS1 == 10); break;
	case VERTEX_ELEMENT_BONEWEIGHTS2:	Assert(VERTEX_ELEMENT_BONEWEIGHTS2 == 11); break;
	case VERTEX_ELEMENT_BONEWEIGHTS3:	Assert(VERTEX_ELEMENT_BONEWEIGHTS3 == 12); break;
	case VERTEX_ELEMENT_BONEWEIGHTS4:	Assert(VERTEX_ELEMENT_BONEWEIGHTS4 == 13); break;
	case VERTEX_ELEMENT_USERDATA1:		Assert(VERTEX_ELEMENT_USERDATA1 == 14); break;
	case VERTEX_ELEMENT_USERDATA2:		Assert(VERTEX_ELEMENT_USERDATA2 == 15); break;
	case VERTEX_ELEMENT_USERDATA3:		Assert(VERTEX_ELEMENT_USERDATA3 == 16); break;
	case VERTEX_ELEMENT_USERDATA4:		Assert(VERTEX_ELEMENT_USERDATA4 == 17); break;
	case VERTEX_ELEMENT_TEXCOORD1D_0:	Assert(VERTEX_ELEMENT_TEXCOORD1D_0 == 18); break;
	case VERTEX_ELEMENT_TEXCOORD1D_1:	Assert(VERTEX_ELEMENT_TEXCOORD1D_1 == 19); break;
	case VERTEX_ELEMENT_TEXCOORD1D_2:	Assert(VERTEX_ELEMENT_TEXCOORD1D_2 == 20); break;
	case VERTEX_ELEMENT_TEXCOORD1D_3:	Assert(VERTEX_ELEMENT_TEXCOORD1D_3 == 21); break;
	case VERTEX_ELEMENT_TEXCOORD1D_4:	Assert(VERTEX_ELEMENT_TEXCOORD1D_4 == 22); break;
	case VERTEX_ELEMENT_TEXCOORD1D_5:	Assert(VERTEX_ELEMENT_TEXCOORD1D_5 == 23); break;
	case VERTEX_ELEMENT_TEXCOORD1D_6:	Assert(VERTEX_ELEMENT_TEXCOORD1D_6 == 24); break;
	case VERTEX_ELEMENT_TEXCOORD1D_7:	Assert(VERTEX_ELEMENT_TEXCOORD1D_7 == 25); break;
	case VERTEX_ELEMENT_TEXCOORD2D_0:	Assert(VERTEX_ELEMENT_TEXCOORD2D_0 == 26); break;
	case VERTEX_ELEMENT_TEXCOORD2D_1:	Assert(VERTEX_ELEMENT_TEXCOORD2D_1 == 27); break;
	case VERTEX_ELEMENT_TEXCOORD2D_2:	Assert(VERTEX_ELEMENT_TEXCOORD2D_2 == 28); break;
	case VERTEX_ELEMENT_TEXCOORD2D_3:	Assert(VERTEX_ELEMENT_TEXCOORD2D_3 == 29); break;
	case VERTEX_ELEMENT_TEXCOORD2D_4:	Assert(VERTEX_ELEMENT_TEXCOORD2D_4 == 30); break;
	case VERTEX_ELEMENT_TEXCOORD2D_5:	Assert(VERTEX_ELEMENT_TEXCOORD2D_5 == 31); break;
	case VERTEX_ELEMENT_TEXCOORD2D_6:	Assert(VERTEX_ELEMENT_TEXCOORD2D_6 == 32); break;
	case VERTEX_ELEMENT_TEXCOORD2D_7:	Assert(VERTEX_ELEMENT_TEXCOORD2D_7 == 33); break;
	case VERTEX_ELEMENT_TEXCOORD3D_0:	Assert(VERTEX_ELEMENT_TEXCOORD3D_0 == 34); break;
	case VERTEX_ELEMENT_TEXCOORD3D_1:	Assert(VERTEX_ELEMENT_TEXCOORD3D_1 == 35); break;
	case VERTEX_ELEMENT_TEXCOORD3D_2:	Assert(VERTEX_ELEMENT_TEXCOORD3D_2 == 36); break;
	case VERTEX_ELEMENT_TEXCOORD3D_3:	Assert(VERTEX_ELEMENT_TEXCOORD3D_3 == 37); break;
	case VERTEX_ELEMENT_TEXCOORD3D_4:	Assert(VERTEX_ELEMENT_TEXCOORD3D_4 == 38); break;
	case VERTEX_ELEMENT_TEXCOORD3D_5:	Assert(VERTEX_ELEMENT_TEXCOORD3D_5 == 39); break;
	case VERTEX_ELEMENT_TEXCOORD3D_6:	Assert(VERTEX_ELEMENT_TEXCOORD3D_6 == 40); break;
	case VERTEX_ELEMENT_TEXCOORD3D_7:	Assert(VERTEX_ELEMENT_TEXCOORD3D_7 == 41); break;
	case VERTEX_ELEMENT_TEXCOORD4D_0:	Assert(VERTEX_ELEMENT_TEXCOORD4D_0 == 42); break;
	case VERTEX_ELEMENT_TEXCOORD4D_1:	Assert(VERTEX_ELEMENT_TEXCOORD4D_1 == 43); break;
	case VERTEX_ELEMENT_TEXCOORD4D_2:	Assert(VERTEX_ELEMENT_TEXCOORD4D_2 == 44); break;
	case VERTEX_ELEMENT_TEXCOORD4D_3:	Assert(VERTEX_ELEMENT_TEXCOORD4D_3 == 45); break;
	case VERTEX_ELEMENT_TEXCOORD4D_4:	Assert(VERTEX_ELEMENT_TEXCOORD4D_4 == 46); break;
	case VERTEX_ELEMENT_TEXCOORD4D_5:	Assert(VERTEX_ELEMENT_TEXCOORD4D_5 == 47); break;
	case VERTEX_ELEMENT_TEXCOORD4D_6:	Assert(VERTEX_ELEMENT_TEXCOORD4D_6 == 48); break;
	case VERTEX_ELEMENT_TEXCOORD4D_7:	Assert(VERTEX_ELEMENT_TEXCOORD4D_7 == 49); break;
	default:
		Assert(0); // Invalid input or VertexElement_t has definitely changed
		break;
	}
}

// We're testing 2 normal compression methods
// One compressed normals+tangents into a SHORT2 each (8 bytes total)
// The other compresses them together, into a single UBYTE4 (4 bytes total)
// FIXME: pick one or the other, compare lighting quality in important cases
#define COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2	0
#define COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4	1
//#define COMPRESSED_NORMALS_TYPE						COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2
#define COMPRESSED_NORMALS_TYPE						COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4


//-----------------------------------------------------------------------------
// Shader state flags can be read from the FLAGS materialvar
// Also can be read or written to with the Set/GetMaterialVarFlags() call
// Also make sure you add/remove a string associated with each flag below to CShaderSystem::ShaderStateString in ShaderSystem.cpp
//-----------------------------------------------------------------------------
enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	//	MATERIAL_VAR_UNUSED					  = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
										   //	MATERIAL_VAR_UNUSED					  = (1 << 18),
										   MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
										   MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
										   MATERIAL_VAR_TRANSLUCENT = (1 << 21),
										   MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
										   MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
										   MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
										   MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
										   MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
										   MATERIAL_VAR_HALFLAMBERT = (1 << 27),
										   MATERIAL_VAR_WIREFRAME = (1 << 28),
										   MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
										   MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
										   MATERIAL_VAR_VERTEXFOG = (1 << 31),

										   // NOTE: Only add flags here that either should be read from
										   // .vmts or can be set directly from client code. Other, internal
										   // flags should to into the flag enum in IMaterialInternal.h
};


//-----------------------------------------------------------------------------
// Internal flags not accessible from outside the material system. Stored in Flags2
//-----------------------------------------------------------------------------
enum MaterialVarFlags2_t
{
	// NOTE: These are for $flags2!!!!!
	//	UNUSED											= (1 << 0),

	MATERIAL_VAR2_LIGHTING_UNLIT = 0,
	MATERIAL_VAR2_LIGHTING_VERTEX_LIT = (1 << 1),
	MATERIAL_VAR2_LIGHTING_LIGHTMAP = (1 << 2),
	MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP = (1 << 3),
	MATERIAL_VAR2_LIGHTING_MASK =
	(MATERIAL_VAR2_LIGHTING_VERTEX_LIT |
		MATERIAL_VAR2_LIGHTING_LIGHTMAP |
		MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP),

	// FIXME: Should this be a part of the above lighting enums?
	MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL = (1 << 4),
	MATERIAL_VAR2_USES_ENV_CUBEMAP = (1 << 5),
	MATERIAL_VAR2_NEEDS_TANGENT_SPACES = (1 << 6),
	MATERIAL_VAR2_NEEDS_SOFTWARE_LIGHTING = (1 << 7),
	// GR - HDR path puts lightmap alpha in separate texture...
	MATERIAL_VAR2_BLEND_WITH_LIGHTMAP_ALPHA = (1 << 8),
	MATERIAL_VAR2_NEEDS_BAKED_LIGHTING_SNAPSHOTS = (1 << 9),
	MATERIAL_VAR2_USE_FLASHLIGHT = (1 << 10),
	MATERIAL_VAR2_USE_FIXED_FUNCTION_BAKED_LIGHTING = (1 << 11),
	MATERIAL_VAR2_NEEDS_FIXED_FUNCTION_FLASHLIGHT = (1 << 12),
	MATERIAL_VAR2_USE_EDITOR = (1 << 13),
	MATERIAL_VAR2_NEEDS_POWER_OF_TWO_FRAME_BUFFER_TEXTURE = (1 << 14),
	MATERIAL_VAR2_NEEDS_FULL_FRAME_BUFFER_TEXTURE = (1 << 15),
	MATERIAL_VAR2_IS_SPRITECARD = (1 << 16),
	MATERIAL_VAR2_USES_VERTEXID = (1 << 17),
	MATERIAL_VAR2_SUPPORTS_HW_SKINNING = (1 << 18),
	MATERIAL_VAR2_SUPPORTS_FLASHLIGHT = (1 << 19),
	MATERIAL_VAR2_USE_GBUFFER0 = (1 << 20),
	MATERIAL_VAR2_USE_GBUFFER1 = (1 << 21),
	MATERIAL_VAR2_SELFILLUMMASK = (1 << 22),
	MATERIAL_VAR2_SUPPORTS_TESSELLATION = (1 << 23)
};


#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};
//-----------------------------------------------------------------------------
// Preview image return values
//-----------------------------------------------------------------------------
enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};
struct model_t
{
	char        name[255];
};

struct FileHandle_t;
class KeyValues
{
public:
	//	By default, the KeyValues class uses a string table for the key names that is
	//	limited to 4MB. The game will exit in error if this space is exhausted. In
	//	general this is preferable for game code for performance and memory fragmentation
	//	reasons.
	//
	//	If this is not acceptable, you can use this call to switch to a table that can grow
	//	arbitrarily. This call must be made before any KeyValues objects are allocated or it
	//	will result in undefined behavior. If you use the growable string table, you cannot
	//	share KeyValues pointers directly with any other module. You can serialize them across
	//	module boundaries. These limitations are acceptable in the Steam backend code 
	//	this option was written for, but may not be in other situations. Make sure to
	//	understand the implications before using this.
	static void SetUseGrowableStringTable(bool bUseGrowableTable);

	KeyValues(const char *setName) {}

	//
	// AutoDelete class to automatically free the keyvalues.
	// Simply construct it with the keyvalues you allocated and it will free them when falls out of scope.
	// When you decide that keyvalues shouldn't be deleted call Assign(NULL) on it.
	// If you constructed AutoDelete(NULL) you can later assign the keyvalues to be deleted with Assign(pKeyValues).
	// You can also pass temporary KeyValues object as an argument to a function by wrapping it into KeyValues::AutoDelete
	// instance:   call_my_function( KeyValues::AutoDelete( new KeyValues( "test" ) ) )
	//
	class AutoDelete
	{
	public:
		explicit inline AutoDelete(KeyValues *pKeyValues) : m_pKeyValues(pKeyValues) {}
		explicit inline AutoDelete(const char *pchKVName) : m_pKeyValues(new KeyValues(pchKVName)) {}
		inline ~AutoDelete(void) { if (m_pKeyValues) m_pKeyValues->deleteThis(); }
		inline void Assign(KeyValues *pKeyValues) { m_pKeyValues = pKeyValues; }
		KeyValues *operator->() { return m_pKeyValues; }
		operator KeyValues *() { return m_pKeyValues; }
	private:
		AutoDelete(AutoDelete const &x); // forbid
		AutoDelete & operator= (AutoDelete const &x); // forbid
		KeyValues *m_pKeyValues;
	};

	// Quick setup constructors
	KeyValues(const char *setName, const char *firstKey, const char *firstValue);
	KeyValues(const char *setName, const char *firstKey, const wchar_t *firstValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue);
	KeyValues(const char *setName, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue, const char *secondKey, int secondValue);

	// Section name
	const char *GetName() const;
	void SetName(const char *setName);

	// gets the name as a unique int
	int GetNameSymbol() const { return m_iKeyName; }

	// File access. Set UsesEscapeSequences true, if resource file/buffer uses Escape Sequences (eg \n, \t)
	void UsesEscapeSequences(bool state); // default false
	void UsesConditionals(bool state); // default true
	bool LoadFromFile(void *filesystem, const char *resourceName, const char *pathID = NULL);
	bool SaveToFile(void *filesystem, const char *resourceName, const char *pathID = NULL, bool sortKeys = false, bool bAllowEmptyString = false);

	// Read from a buffer...  Note that the buffer must be null terminated
	bool LoadFromBuffer(char const *resourceName, const char *pBuffer, void* pFileSystem = NULL, const char *pPathID = NULL);

	// Read from a utlbuffer...
	bool LoadFromBuffer(char const *resourceName, void*buf, void* pFileSystem = NULL, const char *pPathID = NULL);

	// Find a keyValue, create it if it is not found.
	// Set bCreate to true to create the key if it doesn't already exist (which ensures a valid pointer will be returned)
	KeyValues *FindKey(const char *keyName, bool bCreate = false);
	KeyValues *FindKey(int keySymbol) const;
	KeyValues *CreateNewKey();		// creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
	void AddSubKey(KeyValues *pSubkey);	// Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
	void RemoveSubKey(KeyValues *subKey);	// removes a subkey from the list, DOES NOT DELETE IT

											// Key iteration.
											//
											// NOTE: GetFirstSubKey/GetNextKey will iterate keys AND values. Use the functions 
											// below if you want to iterate over just the keys or just the values.
											//
	KeyValues *GetFirstSubKey() { return m_pSub; }	// returns the first subkey in the list
	KeyValues *GetNextKey() { return m_pPeer; }		// returns the next subkey
	void SetNextKey(KeyValues * pDat);
	KeyValues *FindLastSubKey();	// returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

									//
									// These functions can be used to treat it like a true key/values tree instead of 
									// confusing values with keys.
									//
									// So if you wanted to iterate all subkeys, then all values, it would look like this:
									//     for ( KeyValues *pKey = pRoot->GetFirstTrueSubKey(); pKey; pKey = pKey->GetNextTrueSubKey() )
									//     {
									//		   Msg( "Key name: %s\n", pKey->GetName() );
									//     }
									//     for ( KeyValues *pValue = pRoot->GetFirstValue(); pKey; pKey = pKey->GetNextValue() )
									//     {
									//         Msg( "Int value: %d\n", pValue->GetInt() );  // Assuming pValue->GetDataType() == TYPE_INT...
									//     }
	KeyValues* GetFirstTrueSubKey();
	KeyValues* GetNextTrueSubKey();

	KeyValues* GetFirstValue();	// When you get a value back, you can use GetX and pass in NULL to get the value.
	KeyValues* GetNextValue();


	// Data access
	int   GetInt(const char *keyName = NULL, int defaultValue = 0);
	uint64 GetUint64(const char *keyName = NULL, uint64 defaultValue = 0);
	float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f);
	const char *GetString(const char *keyName = NULL, const char *defaultValue = "");
	const wchar_t *GetWString(const char *keyName = NULL, const wchar_t *defaultValue = L"");
	void *GetPtr(const char *keyName = NULL, void *defaultValue = (void*)0);
	bool GetBool(const char *keyName = NULL, bool defaultValue = false);
	Color GetColor(const char *keyName = NULL /* default value is all black */);
	bool  IsEmpty(const char *keyName = NULL);

	// Data access
	int   GetInt(int keySymbol, int defaultValue = 0);
	float GetFloat(int keySymbol, float defaultValue = 0.0f);
	const char *GetString(int keySymbol, const char *defaultValue = "");
	const wchar_t *GetWString(int keySymbol, const wchar_t *defaultValue = L"");
	void *GetPtr(int keySymbol, void *defaultValue = (void*)0);
	Color GetColor(int keySymbol /* default value is all black */);
	bool  IsEmpty(int keySymbol);

	// Key writing
	void SetWString(const char *keyName, const wchar_t *value);
	void SetString(const char *keyName, const char *value);
	void SetInt(const char *keyName, int value);
	void SetUint64(const char *keyName, uint64 value);
	void SetFloat(const char *keyName, float value);
	void SetPtr(const char *keyName, void *value);
	void SetColor(const char *keyName, Color value);
	void SetBool(const char *keyName, bool value) { SetInt(keyName, value ? 1 : 0); }

	// Adds a chain... if we don't find stuff in this keyvalue, we'll look
	// in the one we're chained to.
	void ChainKeyValue(KeyValues* pChain);

	void RecursiveSaveToFile(void* buf, int indentLevel, bool sortKeys = false, bool bAllowEmptyString = false);

	bool WriteAsBinary(void*buffer);
	bool ReadAsBinary(void*buffer, int nStackDepth = 0);

	// Allocate & create a new copy of the keys
	KeyValues *MakeCopy(void) const;

	// Make a new copy of all subkeys, add them all to the passed-in keyvalues
	void CopySubkeys(KeyValues *pParent) const;

	// Clear out all subkeys, and the current value
	void Clear(void);

	// Data type
	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};
	types_t GetDataType(const char *keyName = NULL);

	// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
	void deleteThis();

	void SetStringValue(char const *strValue);

	// unpack a key values list into a structure
	void UnpackIntoStructure(struct KeyValuesUnpackStructure const *pUnpackTable, void *pDest, size_t DestSizeInBytes);

	// Process conditional keys for widescreen support.
	bool ProcessResolutionKeys(const char *pResString);

	// Dump keyvalues recursively into a dump context
	bool Dump(class IKeyValuesDumpContext *pDump, int nIndentLevel = 0);

	// Merge in another KeyValues, keeping "our" settings
	void RecursiveMergeKeyValues(KeyValues *baseKV);

private:
	KeyValues(KeyValues&);	// prevent copy constructor being used

							// prevent delete being called except through deleteThis()
	~KeyValues();

	KeyValues* CreateKey(const char *keyName);

	/// Create a child key, given that we know which child is currently the last child.
	/// This avoids the O(N^2) behaviour when adding children in sequence to KV,
	/// when CreateKey() wil have to re-locate the end of the list each time.  This happens,
	/// for example, every time we load any KV file whatsoever.
	KeyValues* CreateKeyUsingKnownLastChild(const char *keyName, KeyValues *pLastChild);
	void AddSubkeyUsingKnownLastChild(KeyValues *pSubKey, KeyValues *pLastChild);

	void RecursiveCopyKeyValues(KeyValues& src);
	void RemoveEverything();
	//	void RecursiveSaveToFile( IBaseFileSystem *filesystem, void*buffer, int indentLevel );
	//	void WriteConvertedString( void*buffer, const char *pszString );

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void RecursiveSaveToFile(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void SaveKeyToFile(KeyValues *dat, void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void WriteConvertedString(void *filesystem, FileHandle_t f, void *pBuf, const char *pszString);

	void RecursiveLoadFromBuffer(char const *resourceName, void*buf);

	// For handling #include "filename"
	void AppendIncludedKeys(void* includedKeys);
	void ParseIncludedKeys(char const *resourceName, const char *filetoinclude,
		void* pFileSystem, const char *pPathID, void* includedKeys);

	// For handling #base "filename"
	void MergeBaseKeys(void* baseKeys);

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void InternalWrite(void *filesystem, FileHandle_t f, void *pBuf, const void *pData, int len);

	void Init();
	const char * ReadToken(void*buf, bool &wasQuoted, bool &wasConditional);
	void WriteIndents(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel);

	void FreeAllocatedValue();
	void AllocateValueBlock(int size);

	int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

					// These are needed out of the union because the API returns string pointers
	char *m_sValue;
	wchar_t *m_wsValue;

	// we don't delete these
	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char	   m_iDataType;
	char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
	char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
	char	   unused[1];

	KeyValues *m_pPeer;	// pointer to next key in list
	KeyValues *m_pSub;	// pointer to Start of a new sub key list
	KeyValues *m_pChain;// Search here if it's not in our list

private:
	// Statics to implement the optional growable string table
	// Function pointers that will determine which mode we are in
	static int(*s_pfGetSymbolForString)(const char *name, bool bCreate);
	static const char *(*s_pfGetStringForSymbol)(int symbol);
	static void *s_pGrowableStringTable;

public:
	// Functions that invoke the default behavior
	static int GetSymbolForStringClassic(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolClassic(int symbol);

	// Functions that use the growable string table
	static int GetSymbolForStringGrowable(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolGrowable(int symbol);

	// Functions to get external access to whichever of the above functions we're going to call.
	static int CallGetSymbolForString(const char *name, bool bCreate = true) { return s_pfGetSymbolForString(name, bCreate); }
	static const char *CallGetStringForSymbol(int symbol) { return s_pfGetStringForSymbol(symbol); }
};


typedef unsigned short ModelInstanceHandle_t;

struct ModelRenderInfo_t
{
	Vector origin;
	Vector angles;
	char pad[0x4];
	void *pRenderable;
	const model_t *pModel;
	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};
class IMaterial
{
public:
	// Get the name of the material.  This is a full path to 
	// the vmt file starting from "hl2/materials" (or equivalent) without
	// a file extension.
	virtual const char *	GetName() const = 0;
	virtual const char *	GetTextureGroupName() const = 0;

	// Get the preferred size/bitDepth of a preview image of a material.
	// This is the sort of image that you would use for a thumbnail view
	// of a material, or in WorldCraft until it uses materials to render.
	// separate this for the tools maybe
	virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0;

	// Get a preview image at the specified width/height and bitDepth.
	// Will do resampling if necessary.(not yet!!! :) )
	// Will do color format conversion. (works now.)
	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	// 
	virtual int				GetMappingWidth() = 0;
	virtual int				GetMappingHeight() = 0;

	virtual int				GetNumAnimationFrames() = 0;

	// For material subrects (material pages).  Offset(u,v) and scale(u,v) are normalized to texture.
	virtual bool			InMaterialPage(void) = 0;
	virtual	void			GetMaterialOffset(float *pOffset) = 0;
	virtual void			GetMaterialScale(float *pScale) = 0;
	virtual IMaterial		*GetMaterialPage(void) = 0;

	// find a vmt variable.
	// This is how game code affects how a material is rendered.
	// The game code must know about the params that are used by
	// the shader for the material that it is trying to affect.
	virtual IMaterialVar *	FindVar(const char *varName, bool *found, bool complain = true) = 0;

	// The user never allocates or deallocates materials.  Reference counting is
	// used instead.  Garbage collection is done upon a call to 
	// IMaterialSystem::UncacheUnusedMaterials.
	virtual void			IncrementReferenceCount(void) = 0;
	virtual void			DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	// Each material is assigned a number that groups it with like materials
	// for sorting in the application.
	virtual int 			GetEnumerationID(void) const = 0;

	virtual void			GetLowResColorSample(float s, float t, float *color) const = 0;

	// This computes the state snapshots for this material
	virtual void			RecomputeStateSnapshots() = 0;

	// Are we translucent?
	virtual bool			IsTranslucent() = 0;

	// Are we alphatested?
	virtual bool			IsAlphaTested() = 0;

	// Are we vertex lit?
	virtual bool			IsVertexLit() = 0;

	// Gets the vertex format
	virtual VertexFormat_t	GetVertexFormat() const = 0;

	// returns true if this material uses a material proxy
	virtual bool			HasProxy(void) const = 0;

	virtual bool			UsesEnvCubemap(void) = 0;

	virtual bool			NeedsTangentSpace(void) = 0;

	virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;

	// returns true if the shader doesn't do skinning itself and requires
	// the data that is sent to it to be preskinned.
	virtual bool			NeedsSoftwareSkinning(void) = 0;

	// Apply constant color or alpha modulation
	virtual void			AlphaModulate(float alpha) = 0;
	virtual void			ColorModulate(float r, float g, float b) = 0;

	// Material Var flags...
	virtual void			SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool			GetMaterialVarFlag(MaterialVarFlags_t flag) = 0;

	// Gets material reflectivity
	virtual void			GetReflectivity(Vector& reflect) = 0;

	// Gets material property flags
	virtual bool			GetPropertyFlag(MaterialPropertyTypes_t type) = 0;

	// Is the material visible from both sides?
	virtual bool			IsTwoSided() = 0;

	// Sets the shader associated with the material
	virtual void			SetShader(const char *pShaderName) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetNumPasses(void) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetTextureMemoryBytes(void) = 0;

	// Meant to be used with materials created using CreateMaterial
	// It updates the materials to reflect the current values stored in the material vars
	virtual void			Refresh() = 0;

	// GR - returns true is material uses lightmap alpha for blending
	virtual bool			NeedsLightmapBlendAlpha(void) = 0;

	// returns true if the shader doesn't do lighting itself and requires
	// the data that is sent to it to be prelighted
	virtual bool			NeedsSoftwareLighting(void) = 0;

	// Gets at the shader parameters
	virtual int				ShaderParamCount() const = 0;
	virtual IMaterialVar	**GetShaderParams(void) = 0;

	// Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
	// the material can't be found.
	virtual bool			IsErrorMaterial() const = 0;

	virtual void			Unused() = 0;

	// Gets the current alpha modulation
	virtual float			GetAlphaModulation() = 0;
	virtual void			GetColorModulation(float *r, float *g, float *b) = 0;

	// Is this translucent given a particular alpha modulation?
	virtual bool			IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;

	// fast find that stores the index of the found var in the string table in local cache
	virtual IMaterialVar *	FindVarFast(char const *pVarName, unsigned int *pToken) = 0;

	// Sets new VMT shader parameters for the material
	virtual void			SetShaderAndParams(void *pKeyValues) = 0;
	virtual const char *	GetShaderName() const = 0;

	virtual void			DeleteIfUnreferenced() = 0;

	virtual bool			IsSpriteCard() = 0;

	virtual void			CallBindProxy(void *proxyData) = 0;

	virtual void			RefreshPreservingMaterialVars() = 0;

	virtual bool			WasReloadedFromWhitelist() = 0;

	virtual bool			SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;

	virtual int				GetReferenceCount() const = 0;
};
#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_POINTER_HANDLE(StudioDecalHandle_t);
struct studioloddata_t
{
	// not needed - this is really the same as studiohwdata_t.m_NumStudioMeshes
	//int					m_NumMeshes; 
	void* m_pMeshData; // there are studiohwdata_t.m_NumStudioMeshes of these.
	float m_SwitchPoint;
	// one of these for each lod since we can switch to simpler materials on lower lods.
	int numMaterials;
	IMaterial** ppMaterials; /* will have studiohdr_t.numtextures elements allocated */
							 // hack - this needs to go away.
	int* pMaterialFlags; /* will have studiohdr_t.numtextures elements allocated */

						 // For decals on hardware morphing, we must actually do hardware skinning
						 // For this to work, we have to hope that the total # of bones used by
						 // hw flexed verts is < than the max possible for the dx level we're running under
	int* m_pHWMorphDecalBoneRemap;
	int m_nDecalBoneCount;
};

struct studiohwdata_t
{
	int m_RootLOD; // calced and clamped, nonzero for lod culling
	int m_NumLODs;
	studioloddata_t* m_pLODs;
	int m_NumStudioMeshes;

	inline float LODMetric(float unitSphereSize) const
	{
		return (unitSphereSize != 0.0f) ? (100.0f / unitSphereSize) : 0.0f;
	}

	inline int GetLODForMetric(float lodMetric) const
	{
		if (!m_NumLODs)
			return 0;

		// shadow lod is specified on the last lod with a negative switch
		// never consider shadow lod as viable candidate
		int numLODs = (m_pLODs[m_NumLODs - 1].m_SwitchPoint < 0.0f) ? m_NumLODs - 1 : m_NumLODs;

		for (int i = m_RootLOD; i < numLODs - 1; i++)
		{
			if (m_pLODs[i + 1].m_SwitchPoint > lodMetric)
				return i;
		}

		return numLODs - 1;
	}
};

struct DrawModelState_t
{
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	IClientRenderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	StudioDecalHandle_t m_decals;
	int m_drawFlags;
	int m_lod;
};

class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class IWorldRenderList : public IRefCounted
{
};
class IMatRenderContext : public IRefCounted
{
};
enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_WHATEVER
};

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial *mat)
	{
		typedef void(__thiscall *OrigFn)(void *, IMaterial *, int, int);
		call_vfunc<OrigFn>(this, 1)(this, mat, 0, 0);
	}

	void DrawModelExecute(void* ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		typedef void(__thiscall* OriginalFn)(void*, void* ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
		return call_vfunc<OriginalFn>(this, 21)(this, ctx, state, pInfo, pCustomBoneToWorld);
	}
};

typedef unsigned short MaterialHandle_t;
class IMaterialSystem
{
public:
	IMaterial* CreateMaterial(bool flat, bool ignorez, bool wireframed);
	IMaterial* FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL);

	MaterialHandle_t FirstMaterial()
	{
		typedef MaterialHandle_t(__thiscall* FirstMaterialFn)(void*);
		return call_vfunc<FirstMaterialFn>(this, 86)(this);
	}

	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		typedef MaterialHandle_t(__thiscall* NextMaterialFn)(void*, MaterialHandle_t);
		return call_vfunc<NextMaterialFn>(this, 87)(this, h);
	}

	MaterialHandle_t InvalidMaterial()
	{
		typedef MaterialHandle_t(__thiscall* InvalidMaterialFn)(void*);
		return call_vfunc<InvalidMaterialFn>(this, 88)(this);
	}

	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		typedef IMaterial*(__thiscall* GetMaterialFn)(void*, MaterialHandle_t);
		return call_vfunc<GetMaterialFn>(this, 89)(this, h);
	}

	//IMaterial* FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL);
};







struct VisibleFogVolumeInfo_t
{
	int		m_nVisibleFogVolume;
	int		m_nVisibleFogVolumeLeaf;
	bool	m_bEyeInFogVolume;
	float	m_flDistanceToWater;
	float	m_flWaterHeight;
	IMaterial *m_pFogVolumeMaterial;
};

typedef unsigned short LeafIndex_t;
enum
{
	INVALID_LEAF_INDEX = (LeafIndex_t)~0
};

struct WorldListLeafData_t
{
	LeafIndex_t	leafIndex;	// 16 bits
	int16	waterData;
	uint16 	firstTranslucentSurface;	// engine-internal list index
	uint16	translucentSurfaceCount;	// count of translucent surfaces+disps
};

struct WorldListInfo_t
{
	int		m_ViewFogVolume;
	int		m_LeafCount;
	bool	m_bHasWater;
	WorldListLeafData_t	*m_pLeafDataList;
};

struct VisOverrideData_t
{
	Vector		m_vecVisOrigin;					// The point to to use as the viewpoint for area portal backface cull checks.
	float		m_fDistToAreaPortalTolerance;	// The distance from an area portal before using the full screen as the viewable portion.
};

struct BrushVertex_t
{
	Vector		m_Pos;
	Vector		m_Normal;
	Vector		m_TangentS;
	Vector		m_TangentT;
	Vector2D	m_TexCoord;
	Vector2D	m_LightmapCoord;

private:
	BrushVertex_t(const BrushVertex_t& src);
};

class IBrushSurface
{
public:
	// Computes texture coordinates + lightmap coordinates given a world position
	virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
	virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;

	// Gets the vertex data for this surface
	virtual int  GetVertexCount() const = 0;
	virtual void GetVertexData(BrushVertex_t* pVerts) = 0;

	// Gets at the material properties for this surface
	virtual IMaterial* GetMaterial() = 0;
};

class IBrushRenderer
{
public:
	// Draws the surface; returns true if decals should be rendered on this surface
	virtual bool RenderBrushModelSurface(IClientEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
};

class IVRenderView
{
public:

	// Draw normal brush model.
	// If pMaterialOverride is non-null, then all the faces of the bmodel will
	// set this material rather than their regular material.
	virtual void			DrawBrushModel(IClientEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool sort) = 0;

	// Draw brush model that has no origin/angles change ( uses identity transform )
	// FIXME, Material proxy IClientEntity *baseentity is unused right now, use DrawBrushModel for brushes with
	//  proxies for now.
	virtual void			DrawIdentityBrushModel(IWorldRenderList *pList, model_t *model) = 0;

	// Mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
	virtual void			TouchLight(struct dlight_t *light) = 0;
	// Draw 3D Overlays
	virtual void			Draw3DDebugOverlays(void) = 0;
	// Sets global blending fraction
	virtual void			SetBlend(float blend) = 0;
	virtual float			GetBlend(void) = 0;

	// Sets global color modulation
	virtual void			SetColorModulation(float const* blend) = 0;
	virtual void			GetColorModulation(float* blend) = 0;

	// Wrap entire scene drawing
	virtual void			SceneBegin(void) = 0;
	virtual void			SceneEnd(void) = 0;

	// Gets the fog volume for a particular point
	virtual void			GetVisibleFogVolume(const Vector& eyePoint, VisibleFogVolumeInfo_t *pInfo) = 0;

	// Wraps world drawing
	// If iForceViewLeaf is not -1, then it uses the specified leaf as your starting area for setting up area portal culling.
	// This is used by water since your reflected view origin is often in solid space, but we still want to treat it as though
	// the first portal we're looking out of is a water portal, so our view effectively originates under the water.
	virtual IWorldRenderList * CreateWorldList() = 0;

	virtual void			BuildWorldLists(IWorldRenderList *pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float *pReflectionWaterHeight = NULL) = 0;
	virtual void			DrawWorldLists(IWorldRenderList *pList, unsigned long flags, float waterZAdjust) = 0;
	virtual int				GetNumIndicesForWorldLists(IWorldRenderList *pList, unsigned long nFlags) = 0;

	// Optimization for top view
	virtual void			DrawTopView(bool enable) = 0;
	virtual void			TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;

	// Draw lights
	virtual void			DrawLights(void) = 0;
	// FIXME:  This function is a stub, doesn't do anything in the engine right now
	virtual void			DrawMaskEntities(void) = 0;

	// Draw surfaces with alpha, don't call in shadow depth pass
	virtual void			DrawTranslucentSurfaces(IWorldRenderList *pList, int *pSortList, int sortCount, unsigned long flags) = 0;

	// Draw Particles ( just draws the linefine for debugging map leaks )
	virtual void			DrawLineFile(void) = 0;
	// Draw lightmaps
	virtual void			DrawLightmaps(IWorldRenderList *pList, int pageId) = 0;
	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;

	// Return true if any of these leaves are visible in the current PVS.
	virtual bool			AreAnyLeavesVisible(int *leafList, int nLeaves) = 0;

	virtual	void			VguiPaint(void) = 0;
	// Sets up view fade parameters
	virtual void			ViewDrawFade(byte *color, IMaterial *pMaterial) = 0;
	// Sets up the projection matrix for the specified field of view
	virtual void			OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	// Determine lighting at specified position
	virtual Color		GetLightAtPoint(Vector& pos) = 0;
	// Whose eyes are we looking through?
	virtual int				GetViewEntity(void) = 0;
	virtual bool			IsViewEntity(int entindex) = 0;
	// Get engine field of view setting
	virtual float			GetFieldOfView(void) = 0;
	// 1 == ducking, 0 == not
	virtual unsigned char	**GetAreaBits(void) = 0;

	// Set up fog for a particular leaf
	virtual void			SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;

	// Installs a brush surface draw override method, null means use normal renderer
	virtual void			InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;

	// Draw brush model shadow
	virtual void			DrawBrushModelShadow(IClientRenderable *pRenderable) = 0;

	// Does the leaf contain translucent surfaces?
	virtual	bool			LeafContainsTranslucentSurfaces(IWorldRenderList *pList, int sortIndex, unsigned long flags) = 0;

	virtual bool			DoesBoxIntersectWaterVolume(const Vector &mins, const Vector &maxs, int leafWaterDataID) = 0;

	virtual void			SetAreaState(unsigned char chAreaBits[MAX_AREA_STATE_BYTES], unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;

	// See i
	virtual void			VGui_Paint(int mode) = 0;
};


class player_info_t
{
//public:
//	char           pad_0x0000[0x10]; //0x0000
//									 //	char           szName[32]; //0x0010 
//	char           szName[128];
//	char           pad_0x0030[0x64]; //0x0030
//	char           szSteamID[20]; //0x0094 SteamID on text format (STEAM_X:Y:Z)
//	char           pad_0x00A8[0x10]; //0x00A8
//	unsigned long  iSteamID; //0x00B8 
//	char           unknown2[0x14C];

private:
	DWORD __pad0[2];
public:
	int m_nXuidLow;
	int m_nXuidHigh;
	char szName[128];
	int m_nUserID;
	char m_szSteamID[33];
	UINT m_nSteam3ID;
	char m_szFriendsName[128];
	bool m_bIsFakePlayer;
	bool m_bIsHLTV;
	DWORD m_dwCustomFiles[4];
	BYTE m_FilesDownloaded;
private:
	int __pad1;
};

class ClientClass
{
public:
	CreateClientClassFn*      m_pCreateFn;
	CreateEventFn*            m_pCreateEventFn;
	char*		              m_pName;
	RecvTable*			      m_pTable;
	ClientClass*	          m_pNext;
	int				          m_nID;
};

class CGlobalVarsBase
{
public:
	float				realtime;
	int					framecount;
	float				absoluteframetime;
	float				absoluteframestarttimestddev;
	float				curtime;
	float				frametime;
	int					maxClients;
	int					tickcount;
	float				interval_per_tick;
	float				interpolation_amount;
	int					simTicksThisFrame;
	int					network_protocol;
	void*				pSaveData;
private:
	bool				m_bClient;
public:
	bool				m_bRemoteClient;
private:
	int					nTimestampNetworkingBase;
	int					nTimestampRandomizeWindow;
};


CGlobalVarsBase*		pGlobals = nullptr;



class CViewSetup;
class CEngineSprite;

#define FFADE_IN			0x0001		// Just here so we don't pass 0 into the function
#define FFADE_OUT			0x0002		// Fade out (not in)
#define FFADE_MODULATE		0x0004		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0008		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE			0x0010		// Purges all other fades, replacing them with this one

#define SCREENFADE_FRACBITS		9		// which leaves 16-this for the integer part
// This structure is sent over the net to describe a screen fade event
struct ScreenFade_t
{
	unsigned short 	duration;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration
	unsigned short 	holdTime;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	byte			r, g, b, a;		// fade to color ( max alpha )
};

enum ClientFrameStage_t2
{
	FRAME_UNDEFINED2 = -1,			// (haven't run any frames yet)
	FRAME_START2,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START2,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START2,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END2,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END2,

	// We're about to start rendering the scene
	FRAME_RENDER_START2,
	// We've finished rendering the scene.
	FRAME_RENDER_END2
};

typedef int qboolean;
struct bf_write;
struct bf_read;

struct vrect_t
{
	int				x, y, width, height;
	vrect_t			*pnext;
};
class IBaseClientDLL
{
public:
	virtual int				Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase *pGlobals) = 0;
	virtual int				Disconnect(void) = 0;
	virtual int				Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase *pGlobals) = 0;
	virtual void			PostInit() = 0;
	virtual void			Shutdown(void) = 0;
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	virtual void			LevelInitPostEntity() = 0;
	virtual void			LevelShutdown(void) = 0;
	virtual ClientClass		*GetAllClasses(void) = 0;
	virtual int				HudVidInit(void) = 0;
	virtual void			HudProcessInput(bool bActive) = 0;
	virtual void			HudUpdate(bool bActive) = 0;
	virtual void			HudReset(void) = 0;
	virtual void			HudText(const char * message) = 0;
	virtual void			ShouldDrawDropdownConsole(void) = 0;
	virtual void			IN_ActivateMouse(void) = 0;
	virtual void			IN_DeactivateMouse(void) = 0;
	virtual void			IN_Accumulate(void) = 0;
	virtual void			IN_ClearStates(void) = 0;
	virtual bool			IN_IsKeyDown(const char *name, bool& isdown) = 0;
	virtual int				IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;
	virtual void			CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool			WriteUsercmdDeltaToBuffer(int nSlot, bf_write *buf, int from, int to, bool isnewcommand) = 0;
	virtual void			EncodeUserCmdToBuffer(int nSlot, bf_write& buf, int slot) = 0;
	virtual void			DecodeUserCmdFromBuffer(int nSlot, bf_read& buf, int slot) = 0;
	virtual void			View_Render(vrect_t *rect) = 0;
	virtual void			RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;
	virtual void			View_Fade(ScreenFade_t *pSF) = 0;
	virtual void			SetCrosshairAngle(const QAngle& angle) = 0;
	virtual void			InitSprite(CEngineSprite *pSprite, const char *loadname) = 0;
	virtual void			ShutdownSprite(CEngineSprite *pSprite) = 0;
	virtual int				GetSpriteSize(void) const = 0;
	virtual void			VoiceStatus(int entindex, int iSsSlot, qboolean bTalking) = 0;
	virtual int				PlayerAudible(int audible) = 0;
	virtual void			InstallStringTableCallback(char const *tableName) = 0;
	virtual void			FrameStageNotify(ClientFrameStage_t2 curStage) = 0;
	virtual bool			DispatchUserMessage(int msg_type, int unk1, int unk2, bf_read &msg_data) = 0;
};

class IVEngineClient
{
public:
	virtual int                   GetIntersectingSurfaces(const model_t *model, const Vector &vCenter, const float radius, const bool bOnlyVisibleSurfaces, SurfInfo *pInfos, const int nMaxInfos) = 0;
	virtual Vector                GetLightForPoint(const Vector &pos, bool bClamp) = 0;
	virtual IMaterial*            TraceLineMaterialAndLighting(const Vector &start, const Vector &end, Vector &diffuseLightColor, Vector& baseColor) = 0;
	virtual const char*           ParseFile(const char *data, char *token, int maxlen) = 0;
	virtual bool                  CopyFile(const char *source, const char *destination) = 0;
	virtual void                  GetScreenSize(int& width, int& height) = 0;
	virtual void                  ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
	virtual void                  ClientCmd(const char *szCmdString) = 0;
	virtual bool                  GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int                   GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t* TextMessageGet(const char *pName) = 0; // 10
	virtual bool                  Con_IsVisible(void) = 0;
	virtual int                   GetLocalPlayer(void) = 0;
	virtual const model_t*        LoadModel(const char *pName, bool bProp = false) = 0;
	virtual float                 GetLastTimeStamp(void) = 0;
	virtual CSentence*            GetSentence(CAudioSource *pAudioSource) = 0; // 15
	virtual float                 GetSentenceLength(CAudioSource *pAudioSource) = 0;
	virtual bool                  IsStreaming(CAudioSource *pAudioSource) const = 0;
	virtual void                  GetViewAngles(Vector& va) = 0;
	virtual void                  SetViewAngles(Vector& va) = 0;
	virtual int                   GetMaxClients(void) = 0; // 20
	virtual   const char*         Key_LookupBinding(const char *pBinding) = 0;
	virtual const char*           Key_BindingForKey(int &code) = 0;
	virtual void                  Key_SetBinding(int, char const*) = 0;
	virtual void                  StartKeyTrapMode(void) = 0;
	virtual bool                  CheckDoneKeyTrapping(int &code) = 0;
	virtual bool                  IsInGame(void) = 0;
	virtual bool                  IsConnected(void) = 0;
	virtual bool                  IsDrawingLoadingImage(void) = 0;
	virtual void                  HideLoadingPlaque(void) = 0;
	virtual void                  Con_NPrintf(int pos, const char *fmt, ...) = 0; // 30
	virtual void                  Con_NXPrintf(const struct con_nprint_s *info, const char *fmt, ...) = 0;
	virtual int                   IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;
	virtual int                   IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;
	virtual bool                  CullBox(const Vector& mins, const Vector& maxs) = 0;
	virtual void                  Sound_ExtraUpdate(void) = 0;
	virtual const char*           GetGameDirectory(void) = 0;
	virtual const VMatrix&        WorldToScreenMatrix() = 0;
	virtual const VMatrix&        WorldToViewMatrix() = 0;
	virtual int                   GameLumpVersion(int lumpId) const = 0;
	virtual int                   GameLumpSize(int lumpId) const = 0; // 40
	virtual bool                  LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int                   LevelLeafCount() const = 0;
	virtual ISpatialQuery*        GetBSPTreeQuery() = 0;
	virtual void                  LinearToGamma(float* linear, float* gamma) = 0;
	virtual float                 LightStyleValue(int style) = 0; // 45
	virtual void                  ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;
	virtual void                  GetAmbientLightColor(Vector& color) = 0;
	virtual int                   GetDXSupportLevel() = 0;
	virtual bool                  SupportsHDR() = 0;
	virtual void                  Mat_Stub(IMaterialSystem *pMatSys) = 0; // 50
	virtual void                  GetChapterName(char *pchBuff, int iMaxLength) = 0;
	virtual char const*           GetLevelName(void) = 0;
	virtual char const*           GetLevelNameShort(void) = 0;
	virtual char const*           GetMapGroupName(void) = 0;
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
	virtual void                  SetVoiceCasterID(unsigned int someint) = 0; // 56
	virtual void                  EngineStats_BeginFrame(void) = 0;
	virtual void                  EngineStats_EndFrame(void) = 0;
	virtual void                  FireEvents() = 0;
	virtual int                   GetLeavesArea(unsigned short *pLeaves, int nLeaves) = 0;
	virtual bool                  DoesBoxTouchAreaFrustum(const Vector &mins, const Vector &maxs, int iArea) = 0; // 60
	virtual int                   GetFrustumList(Frustum_t **pList, int listMax) = 0;
	virtual bool                  ShouldUseAreaFrustum(int i) = 0;
	virtual void                  SetAudioState(const AudioState_t& state) = 0;
	virtual int                   SentenceGroupPick(int groupIndex, char *name, int nameBufLen) = 0;
	virtual int                   SentenceGroupPickSequential(int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int                   SentenceIndexFromName(const char *pSentenceName) = 0;
	virtual const char*           SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int                   SentenceGroupIndexFromName(const char *pGroupName) = 0;
	virtual const char*           SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float                 SentenceLength(int sentenceIndex) = 0;
	virtual void                  ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector *pBoxColors = NULL) = 0;
	virtual void                  ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool                  IsOccluded(const Vector &vecAbsMins, const Vector &vecAbsMaxs) = 0; // 74
	virtual int                   GetOcclusionViewId(void) = 0;
	virtual void*                 SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void                  SaveFreeMemory(void *pSaveMem) = 0;
	virtual INetChannelInfo*      GetNetChannelInfo(void) = 0;
	virtual void                  DebugDrawPhysCollide(const CPhysCollide *pCollide, IMaterial *pMaterial, const matrix3x4_t& transform, const Color &color) = 0; //79
	virtual void                  CheckPoint(const char *pName) = 0; // 80
	virtual void                  DrawPortals() = 0;
	virtual bool                  IsPlayingDemo(void) = 0;
	virtual bool                  IsRecordingDemo(void) = 0;
	virtual bool                  IsPlayingTimeDemo(void) = 0;
	virtual int                   GetDemoRecordingTick(void) = 0;
	virtual int                   GetDemoPlaybackTick(void) = 0;
	virtual int                   GetDemoPlaybackStartTick(void) = 0;
	virtual float                 GetDemoPlaybackTimeScale(void) = 0;
	virtual int                   GetDemoPlaybackTotalTicks(void) = 0;
	virtual bool                  IsPaused(void) = 0; // 90
	virtual float                 GetTimescale(void) const = 0;
	virtual bool                  IsTakingScreenshot(void) = 0;
	virtual bool                  IsHLTV(void) = 0;
	virtual bool                  IsLevelMainMenuBackground(void) = 0;
	virtual void                  GetMainMenuBackgroundName(char *dest, int destlen) = 0;
	virtual void                  SetOcclusionParameters(const int /*OcclusionParams_t*/ &params) = 0; // 96
	virtual void                  GetUILanguage(char *dest, int destlen) = 0;
	virtual int                   IsSkyboxVisibleFromPoint(const Vector &vecPoint) = 0;
	virtual const char*           GetMapEntitiesString() = 0;
	virtual bool                  IsInEditMode(void) = 0; // 100
	virtual float                 GetScreenAspectRatio(int viewportWidth, int viewportHeight) = 0;
	virtual bool                  REMOVED_SteamRefreshLogin(const char *password, bool isSecure) = 0; // 100
	virtual bool                  REMOVED_SteamProcessCall(bool & finished) = 0;
	virtual unsigned int          GetEngineBuildNumber() = 0; // engines build
	virtual const char *          GetProductVersionString() = 0; // mods version number (steam.inf)
	virtual void                  GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool                  IsHammerRunning() const = 0;
	virtual void                  ExecuteClientCmd(const char *szCmdString) = 0; //108
	virtual bool                  MapHasHDRLighting(void) = 0;
	virtual bool                  MapHasLightMapAlphaData(void) = 0;
	virtual int                   GetAppID() = 0;
	virtual Vector                GetLightForPointFast(const Vector &pos, bool bClamp) = 0;
	virtual void                  ClientCmd_Unrestricted1(char  const*, int, bool);
	virtual void                  ClientCmd_Unrestricted(const char *szCmdString) = 0; // 114
	virtual void                  SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void                  SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void                  SetOverlayBindProxy(int iOverlayID, void *pBindProxy) = 0;
	virtual bool                  CopyFrameBufferToMaterial(const char *pMaterialName) = 0;
	virtual void                  ReadConfiguration(const int iController, const bool readDefault) = 0;
	virtual void                  SetAchievementMgr(IAchievementMgr *pAchievementMgr) = 0;
	virtual IAchievementMgr*      GetAchievementMgr() = 0;
	virtual bool                  MapLoadFailed(void) = 0;
	virtual void                  SetMapLoadFailed(bool bState) = 0;
	virtual bool                  IsLowViolence() = 0;
	virtual const char*           GetMostRecentSaveGame(void) = 0;
	virtual void                  SetMostRecentSaveGame(const char *lpszFilename) = 0;
	virtual void                  StartXboxExitingProcess() = 0;
	virtual bool                  IsSaveInProgress() = 0;
	virtual bool                  IsAutoSaveDangerousInProgress(void) = 0;
	virtual unsigned int          OnStorageDeviceAttached(int iController) = 0;
	virtual void                  OnStorageDeviceDetached(int iController) = 0;
	virtual char* const           GetSaveDirName(void) = 0;
	virtual void                  WriteScreenshot(const char *pFilename) = 0;
	virtual void                  ResetDemoInterpolation(void) = 0;
	virtual int                   GetActiveSplitScreenPlayerSlot() = 0;
	virtual int                   SetActiveSplitScreenPlayerSlot(int slot) = 0;
	virtual bool                  SetLocalPlayerIsResolvable(char const *pchContext, int nLine, bool bResolvable) = 0;
	virtual bool                  IsLocalPlayerResolvable() = 0;
	virtual int                   GetSplitScreenPlayer(int nSlot) = 0;
	virtual bool                  IsSplitScreenActive() = 0;
	virtual bool                  IsValidSplitScreenSlot(int nSlot) = 0;
	virtual int                   FirstValidSplitScreenSlot() = 0; // -1 == invalid
	virtual int                   NextValidSplitScreenSlot(int nPreviousSlot) = 0; // -1 == invalid
	virtual ISPSharedMemory*      GetSinglePlayerSharedMemorySpace(const char *szName, int ent_num = (1 << 11)) = 0;
	virtual void                  ComputeLightingCube(const Vector& pt, bool bClamp, Vector *pBoxColors) = 0;
	virtual void                  RegisterDemoCustomDataCallback(const char* szCallbackSaveID, pfnDemoCustomDataCallback pCallback) = 0;
	virtual void                  RecordDemoCustomData(pfnDemoCustomDataCallback pCallback, const void *pData, size_t iDataLength) = 0;
	virtual void                  SetPitchScale(float flPitchScale) = 0;
	virtual float                 GetPitchScale(void) = 0;
	virtual bool                  LoadFilmmaker() = 0;
	virtual void                  UnloadFilmmaker() = 0;
	virtual void                  SetLeafFlag(int nLeafIndex, int nFlagBits) = 0;
	virtual void                  RecalculateBSPLeafFlags(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomNew(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomChanged(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomSkyAbove(void) = 0;
	virtual float                 DSPGetCurrentDASRoomSkyPercent(void) = 0;
	virtual void                  SetMixGroupOfCurrentMixer(const char *szgroupname, const char *szparam, float val, int setMixerType) = 0;
	virtual int                   GetMixLayerIndex(const char *szmixlayername) = 0;
	virtual void                  SetMixLayerLevel(int index, float level) = 0;
	virtual int                   GetMixGroupIndex(char  const* groupname) = 0;
	virtual void                  SetMixLayerTriggerFactor(int i1, int i2, float fl) = 0;
	virtual void                  SetMixLayerTriggerFactor(char  const* char1, char  const* char2, float fl) = 0;
	virtual bool                  IsCreatingReslist() = 0;
	virtual bool                  IsCreatingXboxReslist() = 0;
	virtual void                  SetTimescale(float flTimescale) = 0;
	virtual void                  SetGamestatsData(CGamestatsData *pGamestatsData) = 0;
	virtual CGamestatsData*       GetGamestatsData() = 0;
	virtual void                  GetMouseDelta(int &dx, int &dy, bool b) = 0; // unknown
	virtual   const char*         Key_LookupBindingEx(const char *pBinding, int iUserId = -1, int iStartCount = 0, int iAllowJoystick = -1) = 0;
	virtual int                   Key_CodeForBinding(char  const*, int, int, int) = 0;
	virtual void                  UpdateDAndELights(void) = 0;
	virtual int                   GetBugSubmissionCount() const = 0;
	virtual void                  ClearBugSubmissionCount() = 0;
	virtual bool                  DoesLevelContainWater() const = 0;
	virtual float                 GetServerSimulationFrameTime() const = 0;
	virtual void                  SolidMoved(class IClientEntity *pSolidEnt, class ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin, bool accurateBboxTriggerChecks) = 0;
	virtual void                  TriggerMoved(class IClientEntity *pTriggerEnt, bool accurateBboxTriggerChecks) = 0;
	virtual void                  ComputeLeavesConnected(const Vector &vecOrigin, int nCount, const int *pLeafIndices, bool *pIsConnected) = 0;
	virtual bool                  IsInCommentaryMode(void) = 0;
	virtual void                  SetBlurFade(float amount) = 0;
	virtual bool                  IsTransitioningToLoad() = 0;
	virtual void                  SearchPathsChangedAfterInstall() = 0;
	virtual void                  ConfigureSystemLevel(int nCPULevel, int nGPULevel) = 0;
	virtual void                  SetConnectionPassword(char const *pchCurrentPW) = 0;
	virtual CSteamAPIContext*     GetSteamAPIContext() = 0;
	virtual void                  SubmitStatRecord(char const *szMapName, unsigned int uiBlobVersion, unsigned int uiBlobSize, const void *pvBlob) = 0;
	virtual void                  ServerCmdKeyValues(KeyValues *pKeyValues) = 0; // 203
	virtual void                  SpherePaintSurface(const model_t* model, const Vector& location, unsigned char chr, float fl1, float fl2) = 0;
	virtual bool                  HasPaintmap(void) = 0;
	virtual void                  EnablePaintmapRender() = 0;
	//virtual void                TracePaintSurface( const model_t *model, const Vector& position, float radius, CUtlVector<Color>& surfColors ) = 0;
	virtual void                  SphereTracePaintSurface(const model_t* model, const Vector& position, const Vector &vec2, float radius, /*CUtlVector<unsigned char, CUtlMemory<unsigned char, int>>*/ int& utilVecShit) = 0;
	virtual void                  RemoveAllPaint() = 0;
	virtual void                  PaintAllSurfaces(unsigned char uchr) = 0;
	virtual void                  RemovePaint(const model_t* model) = 0;
	virtual bool                  IsActiveApp() = 0;
	virtual bool                  IsClientLocalToActiveServer() = 0;
	virtual void                  TickProgressBar() = 0;
	virtual InputContextHandle_t  GetInputContext(int /*EngineInputContextId_t*/ id) = 0;
	virtual void                  GetStartupImage(char* filename, int size) = 0;
	virtual bool                  IsUsingLocalNetworkBackdoor(void) = 0;
	virtual void                  SaveGame(const char*, bool, char*, int, char*, int) = 0;
	virtual void                  GetGenericMemoryStats(/* GenericMemoryStat_t */ void **) = 0;
	virtual bool                  GameHasShutdownAndFlushedMemory(void) = 0;
	virtual int                   GetLastAcknowledgedCommand(void) = 0;
	virtual void                  FinishContainerWrites(int i) = 0;
	virtual void                  FinishAsyncSave(void) = 0;
	virtual int                   GetServerTick(void) = 0;
	virtual const char*           GetModDirectory(void) = 0;
	virtual bool                  AudioLanguageChanged(void) = 0;
	virtual bool                  IsAutoSaveInProgress(void) = 0;
	virtual void                  StartLoadingScreenForCommand(const char* command) = 0;
	virtual void                  StartLoadingScreenForKeyValues(KeyValues* values) = 0;
	virtual void                  SOSSetOpvarFloat(const char*, float) = 0;
	virtual void                  SOSGetOpvarFloat(const char*, float &) = 0;
	virtual bool                  IsSubscribedMap(const char*, bool) = 0;
	virtual bool                  IsFeaturedMap(const char*, bool) = 0;
	virtual void                  GetDemoPlaybackParameters(void) = 0;
	virtual int                   GetClientVersion(void) = 0;
	virtual bool                  IsDemoSkipping(void) = 0;
	virtual void                  SetDemoImportantEventData(const KeyValues* values) = 0;
	virtual void                  ClearEvents(void) = 0;
	virtual int                   GetSafeZoneXMin(void) = 0;
	virtual bool                  IsVoiceRecording(void) = 0;
	virtual void                  ForceVoiceRecordOn(void) = 0;
	virtual bool                  IsReplay(void) = 0;
};

class IAppSystem
{
public:
	virtual bool                            Connect(CreateInterfaceFn factory) = 0;                                  // 0
	virtual void                            Disconnect() = 0;                                                          // 1
	virtual void*                           QueryInterface(const char *pInterfaceName) = 0;                          // 2
	virtual int /*InitReturnVal_t*/         Init() = 0;                                                                // 3
	virtual void                            Shutdown() = 0;                                                            // 4
	virtual const void* /*AppSystemInfo_t*/ GetDependencies() = 0;                                                     // 5
	virtual int /*AppSystemTier_t*/         GetTier() = 0;                                                             // 6
	virtual void                            Reconnect(CreateInterfaceFn factory, const char *pInterfaceName) = 0;    // 7
	virtual void                            UnkFunc() = 0;                                                             // 8
};
class ISurface : public IAppSystem
{
public:
	// frame
	virtual void        RunFrame() = 0;
	virtual VPANEL      GetEmbeddedPanel() = 0;
	virtual void        SetEmbeddedPanel(VPANEL pPanel) = 0;
	virtual void        PushMakeCurrent(VPANEL panel, bool useInsets) = 0;
	virtual void        PopMakeCurrent(VPANEL panel) = 0;
	virtual void        DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void        DrawSetColor(Color col) = 0;
	virtual void        DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void        DrawFilledRectArray(IntRect *pRects, int numRects) = 0;
	virtual void        DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;
	virtual void        DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void        DrawPolyLine(int *px, int *py, int numPoints) = 0;
	virtual void        DrawSetApparentDepth(float f) = 0;
	virtual void        DrawClearApparentDepth(void) = 0;
	virtual void        DrawSetTextFont(HFont font) = 0;
	virtual void        DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void        DrawSetTextColor(Color col) = 0;
	virtual void        DrawSetTextPos(int x, int y) = 0;
	virtual void        DrawGetTextPos(int& x, int& y) = 0;
	virtual void        DrawPrintText(const wchar_t *text, int textLen, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) = 0;
	virtual void        DrawUnicodeChar(wchar_t wch, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) = 0;
	virtual void        DrawFlushText() = 0;
	virtual void*       CreateHTMLWindow(void *events, VPANEL context) = 0;
	virtual void        PaintHTMLWindow(void *htmlwin) = 0;
	virtual void        DeleteHTMLWindow(void *htmlwin) = 0;
	virtual int         DrawGetTextureId(char const *filename) = 0;
	virtual bool        DrawGetTextureFile(int id, char *filename, int maxlen) = 0;
	virtual void        DrawSetTextureFile(int id, const char *filename, int hardwareFilter, bool forceReload) = 0;
	virtual void        DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall) = 0;
	virtual void        DrawSetTexture(int id) = 0;
	virtual void        DeleteTextureByID(int id) = 0;
	virtual void        DrawGetTextureSize(int id, int &wide, int &tall) = 0;
	virtual void        DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool        IsTextureIDValid(int id) = 0;
	virtual int         CreateNewTextureID(bool procedural = false) = 0;
	virtual void        GetScreenSize(int &wide, int &tall) = 0;
	virtual void        SetAsTopMost(VPANEL panel, bool state) = 0;
	virtual void        BringToFront(VPANEL panel) = 0;
	virtual void        SetForegroundWindow(VPANEL panel) = 0;
	virtual void        SetPanelVisible(VPANEL panel, bool state) = 0;
	virtual void        SetMinimized(VPANEL panel, bool state) = 0;
	virtual bool        IsMinimized(VPANEL panel) = 0;
	virtual void        FlashWindow(VPANEL panel, bool state) = 0;
	virtual void        SetTitle(VPANEL panel, const wchar_t *title) = 0;
	virtual void        SetAsToolBar(VPANEL panel, bool state) = 0;
	virtual void        CreatePopup(VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void        SwapBuffers(VPANEL panel) = 0;
	virtual void        Invalidate(VPANEL panel) = 0;
	virtual void        SetCursor(unsigned long cursor) = 0;
	virtual bool        IsCursorVisible() = 0;
	virtual void        ApplyChanges() = 0;
	virtual bool        IsWithin(int x, int y) = 0;
	virtual bool        HasFocus() = 0;
	virtual bool        SupportsFeature(int /*SurfaceFeature_t*/ feature) = 0;
	virtual void        RestrictPaintToSinglePanel(VPANEL panel, bool bForceAllowNonModalSurface = false) = 0;
	virtual void        SetModalPanel(VPANEL) = 0;
	virtual VPANEL      GetModalPanel() = 0;
	virtual void        UnlockCursor() = 0;
	virtual void        LockCursor() = 0;
	virtual void        SetTranslateExtendedKeys(bool state) = 0;
	virtual VPANEL      GetTopmostPopup() = 0;
	virtual void        SetTopLevelFocus(VPANEL panel) = 0;
	virtual HFont       CreateFont() = 0;
	virtual bool        SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;
	virtual bool        AddCustomFontFile(const char *fontFileName) = 0;
	virtual int         GetFontTall(HFont font) = 0;
	virtual int         GetFontAscent(HFont font, wchar_t wch) = 0;
	virtual bool        IsFontAdditive(HFont font) = 0;
	virtual void        GetCharABCwide(HFont font, int ch, int &a, int &b, int &c) = 0;
	virtual int         GetCharacterWidth(HFont font, int ch) = 0;
	virtual void        GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall) = 0;
	virtual VPANEL      GetNotifyPanel() = 0;
	virtual void        SetNotifyIcon(VPANEL context, ULONG icon, VPANEL panelToReceiveMessages, const char *text) = 0;
	virtual void        PlaySound(const char *fileName) = 0;
	virtual int         GetPopupCount() = 0;
	virtual VPANEL      GetPopup(int index) = 0;
	virtual bool        ShouldPaintChildPanel(VPANEL childPanel) = 0;
	virtual bool        RecreateContext(VPANEL panel) = 0;
	virtual void        AddPanel(VPANEL panel) = 0;
	virtual void        ReleasePanel(VPANEL panel) = 0;
	virtual void        MovePopupToFront(VPANEL panel) = 0;
	virtual void        MovePopupToBack(VPANEL panel) = 0;
	virtual void        SolveTraverse(VPANEL panel, bool forceApplySchemeSettings = false) = 0;
	virtual void        PaintTraverse(VPANEL panel) = 0;
	virtual void        EnableMouseCapture(VPANEL panel, bool state) = 0;
	virtual void        GetWorkspaceBounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void        GetAbsoluteWindowBounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void        GetProportionalBase(int &width, int &height) = 0;
	virtual void        CalculateMouseVisible() = 0;
	virtual bool        NeedKBInput() = 0;
	virtual bool        HasCursorPosFunctions() = 0;
	virtual void        SurfaceGetCursorPos(int &x, int &y) = 0;
	virtual void        SurfaceSetCursorPos(int x, int y) = 0;
	virtual void        DrawTexturedLine(const Vertex_t &a, const Vertex_t &b) = 0;
	virtual void        DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void        DrawTexturedPolyLine(const Vertex_t *p, int n) = 0;
	virtual void        DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void        DrawTexturedPolygon(int n, Vertex_t *pVertice, bool bClipVertices = true) = 0;

	HFont Create_Font()
	{
		typedef HFont(__thiscall* OriginalFn)(void*);
		return call_vfunc<OriginalFn>(this, 71)(this);
	}


};
class IClientNetworkable
{
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass*	GetClientClass() = 0;/// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
	virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			OnDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PreDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual void			unknown();
	virtual bool			IsDormant(void) = 0;
	virtual int				GetIndex(void) const = 0;
	virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;

};

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8;


class IClientRenderable
{
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual Vector const&              GetRenderOrigin(void) = 0;
	virtual Vector const&              GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       Unused(void) const {}
	virtual ClientShadowHandle_t       GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&      RenderHandle() = 0;
	virtual model_t*                   GetModel() const = 0;
	virtual int                        DrawModel(int flags, const int /*RenderableInstance_t*/ &instance) = 0;
	virtual int                        GetBody() = 0;
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void* /*IPVSNotify*/       GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector &mins, Vector &maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool                       GetShadowCastDistance(float *pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector *pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int /*ShadowType_t*/       ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t      GetModelInstance() = 0;
	virtual const matrix3x4_t&         RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char *pAttachmentName) = 0;
	virtual   bool                     GetAttachment(int number, Vector &origin, Vector &angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
};


class ICollideable
{
public:
	virtual void pad0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
};

class CBaseHandle;
class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};


class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual IClientEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};
class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};

class IVDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(*oScreenPosition)(void*, const Vector&, Vector&);
		return call_vfunc<oScreenPosition>(this, 11)(this, vIn, vOut);
	}
};

class WeaponInfo_t
{
public:
	char _0x0000[4];
	BYTE m_bParsedScript; //0x0004 
	BYTE m_bLoadedHudElements; //0x0005 
	BYTE m_szClassName; //0x0006 
	char _0x0007[1961];
	__int32 m_iAmmoType; //0x07B0 
	char _0x07B4[12];
	CHudTexture* m_pHudTexture_WeaponSilenced; //0x07C0 
	CHudTexture* m_pHudTexture_Weapon; //0x07C4 
	CHudTexture* m_pHudTexture_Ammo; //0x07C8 
	char _0x07CC[4];
	CHudTexture* m_pHudTexture_Crosshair; //0x07D0 
	char _0x07D4[20];
	__int32 m_iWeaponType; //0x07E8 
	__int32 m_iTeam; //0x07EC 
	__int32 m_iWeaponId; //0x07F0 
	BYTE m_bFullAuto; //0x07F4 
	char _0x07F5[3];
	float m_flHeatPerShot; //0x07F8 
	__int32 m_iWeaponPrice; //0x07FC 
	float m_flArmorRatio; //0x0800 
	float m_flMaxPlayerSpeed; //0x0804 
	float m_flMaxPlayerSpeedAlt; //0x0808 
	__int32 m_iCrosshairMinDistance; //0x080C 
	__int32 m_iCrosshairDeltaDistance; //0x0810 
	float m_flPenetration; //0x0814 
	__int32 m_iDamage; //0x0818 
	float m_flRange; //0x081C 
	float m_flRangeModifier; //0x0820 
	__int32 m_iBullets; //0x0824 
	float m_flCycleTime; //0x0828 
	float m_flCycleTimeAlt; //0x082C 
	char _0x0830[416];
	float m_flSpread; //0x09D0 
	float m_flSpreadAlt; //0x09D4 
	float m_flInaccuracyCrouch; //0x09D8 
	float m_flInaccuracyCrouchAlt; //0x09DC 
	float m_flInaccuracyStand; //0x09E0 
	float m_flInaccuracyStandAlt; //0x09E4 
	float m_flInaccuracyJump; //0x09E8 
	float m_flInaccuracyJumpAlt; //0x09EC 
	float m_flInaccuracyLand; //0x09F0 
	float m_flInaccuracyLandAlt; //0x09F4 
	float m_flInaccuracyLadder; //0x09F8 
	float m_flInaccuracyLadderAlt; //0x09FC 
	float m_flInaccuracyFire; //0x0A00 
	float m_flInaccuracyFireAlt; //0x0A04 
	float m_flInaccuracyMove; //0x0A08 
	float m_flInaccuracyMoveAlt; //0x0A0C 
	float m_flRecoveryTimeStand; //0x0A10 
	float m_flRecoveryTimeCrouch; //0x0A14 
	float m_flInaccuracyReload; //0x0A18 
	float m_flInaccuracyAltSwitch; //0x0A1C 
	float m_flRecoilAngle; //0x0A20 
	float m_flRecoilAngleAlt; //0x0A24 
	float m_flRecoilAngleVariance; //0x0A28 
	float m_flRecoilAngleVarianceAlt; //0x0A2C 
	float m_flRecoilMagnitude; //0x0A30 
	float m_flRecoilMagnitudeAlt; //0x0A34 
	float m_flRecoilMagnitudeVariance; //0x0A38 
	float m_flRecoilMagnitudeVarianceAlt; //0x0A3C 
	__int32 m_iRecoilSeed; //0x0A40 
	float m_flFlinchVelocityModifierLarge; //0x0A44 
	float m_flFlinchVelocityModifierSmall; //0x0A48 
	float m_flTimeToIdle; //0x0A4C 
	float m_flIdleInterval; //0x0A50                      // 0x0828
};

class CHudTexture
{
public:
	char type[64]; //0x0000
	char subtype[64]; //0x0040
	char unknowndata00[2]; //0x0080
	char charinFont; //0x0082
	char unknowndata01[1]; //0x0083
};//Size=0x00AC
class CSWeaponInfo //vorher
{
public:
	char _0x0000[2048];
	__int32 m_IsFullAuto; //0x0800 
	char _0x0804[52];
	__int32 weapon_type; //0x0838 
	__int32 weapon_team; //0x083C 
	__int32 weapon_id; //0x0840 
	char _0x0844[4];
	float heat_ps; //0x0848 
	__int32 price; //0x084C 
	float m_flArmorRatio; //0x0850
	float player_speed; //0x0854 
	float player_speed_alt; //0x0858  
	__int32 crosshair_min_distance; //0x085C 
	__int32 crosshair_delta; //0x0860 
	float m_flPenetration; //0x0864 
	__int32 m_iDamage; //0x0868 
	float m_flRange; //0x086C 
	float m_flRangeModifier; //0x0870 
	__int32 bullets; //0x0874 
	float cycle_time; //0x0878 
	float cycle_time_alt; //0x087C 
	char _0x0880[416];
	float spread; //0x0A20 
	float spread_alt; //0x0A24 
};
class CCSWeaponInfo_t
{
public:
	void* vTable; //0x0000
	BYTE N0309F389; //0x0004
	BYTE N030AC4C1; //0x0005
	char name_class[93]; //0x0006
	char printname[80]; //0x00
	char viewmodel[80]; //0x00A6
	char playermodel[80]; //0x00F6
	char bullettype[32]; //0x0146
	char anim_prefix[58]; //0x0166
	char N03122066[32]; //0x01A0
	char contentpack[32]; //0x01C0
	char unknowndata00[128]; //0x01E0
	char name_real[32]; //0x0260
	char unknowndata01[1184]; //0x0280
	CHudTexture* hudTexture_silenced; //0x0720
	CHudTexture* hudTexture; //0x0724
	CHudTexture* hudTexture_ammo; //0x0728
	char unknowndata02[4]; //0x072C
	CHudTexture* hudTexture_crosshair_01; //0x0730
	CHudTexture* hudTexture_crosshair_02; //0x0734
	CHudTexture* hudTexture_crosshair_03; //0x0738
	CHudTexture* hudTexture_crosshair_04; //0x073C
	char unknowndata03[8]; //0x0740
	__int32 WeaponType; //0x0748
	__int32 Team; //0x074C
	__int32 WeaponID; //0x0750
	BYTE FullAuto; //0x0754
	char unknowndata04[7]; //0x0755
	__int32 WeaponPrice; //0x075C
	float WeaponArmorRatio; //0x0760
	float MaxPlayerSpeed; //0x0764
	float MaxPlayerSpeedAlt; //0x0768
	__int32 CrosshairMinDistance; //0x076C
	__int32 CrosshairDeltaDistance; //0x0770
	float flPenetrationPower; //0x0774
	__int32 iDamage; //0x0778
	float flRange; //0x077C
	float flRangeModifier; //0x0780
	__int32 iBullets; //0x0784
	float CycleTime; //0x0788

};//Size=0x078C

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif


enum ItemDefinitionIndex_t
{
	ITEM_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_P2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE_T = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_CT = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_R8REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9BAYONET = 508,
	WEAPON_KNIFE_HUNTSMAN = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BUTTERFLY = 515,


};


class CCSWeaponInfo
{
public:
	char pad_0x0000[4]; // 0x0000
	char* consoleName; // 0x0004
	char pad_0008[12]; // 0x0008
	int iMaxClip1; // 0x0014
	int iMaxClip2; // 0x0018
	int iDefaultClip1; // 0x001C
	int iDefaultClip2; // 0x0020
	char pad_0024[8]; // 0x0024
	char* szWorldModel; // 0x002C
	char* szViewModel; // 0x0030
	char* szDroppedModel; // 0x0034
	char pad_0038[4]; // 0x0038
	char* N0000023E; // 0x003C
	char pad_0040[56]; // 0x0040
	char* szEmptySound; // 0x0078
	char pad_007C[4]; // 0x007C
	char* szBulletType; // 0x0080
	char pad_0084[4]; // 0x0084
	char* szHudName; // 0x0088
	char* szWeaponName; // 0x008C
	char pad_0090[56]; // 0x0090
	int WeaponType; // 0x00C8
	int iWeaponPrice; // 0x00CC
	int iKillAward; // 0x00D0
	char* szAnimationPrefix; // 0x00D4
	float flCycleTime; // 0x00D8
	float flCycleTimeAlt; // 0x00DC
	float flTimeToIdle; // 0x00E0
	float flIdleInterval; // 0x00E4
	bool bFullAuto; // 0x00E8
	char pad_0x00E5[3]; // 0x00E9
	int iDamage; // 0x00EC
	float m_flRange; // 0x081C
	float m_flRangeModifier; //0x0820 
	float flArmorRatio; // 0x00F0
	int iBullets; // 0x00F4
	float flPenetration; // 0x00F8
	float flFlinchVelocityModifierLarge; // 0x00FC
	float flFlinchVelocityModifierSmall; // 0x0100
	float flRange; // 0x0104
	float flRangeModifier; // 0x0108
	float flThrowVelocity; // 0x010C
	char pad_0x010C[12]; // 0x0110
	bool bHasSilencer; // 0x011C
	char pad_0x0119[3]; // 0x011D
	char* pSilencerModel; // 0x0120
	int iCrosshairMinDistance; // 0x0124
	int iCrosshairDeltaDistance;// 0x0128 - iTeam?
	float flMaxPlayerSpeed; // 0x012C
	float flMaxPlayerSpeedAlt; // 0x0130
	float flSpread; // 0x0134
	float flSpreadAlt; // 0x0138
	float flInaccuracyCrouch; // 0x013C
	float flInaccuracyCrouchAlt; // 0x0140
	float flInaccuracyStand; // 0x0144
	float flInaccuracyStandAlt; // 0x0148
	float flInaccuracyJumpInitial;// 0x014C
	float flInaccuracyJump; // 0x0150
	float flInaccuracyJumpAlt; // 0x0154
	float flInaccuracyLand; // 0x0158
	float flInaccuracyLandAlt; // 0x015C
	float flInaccuracyLadder; // 0x0160
	float flInaccuracyLadderAlt; // 0x0164
	float flInaccuracyFire; // 0x0168
	float flInaccuracyFireAlt; // 0x016C
	float flInaccuracyMove; // 0x0170
	float flInaccuracyMoveAlt; // 0x0174
	float flInaccuracyReload; // 0x0178
	int iRecoilSeed; // 0x017C
	float flRecoilAngle; // 0x0180
	float flRecoilAngleAlt; // 0x0184
	float flRecoilAngleVariance; // 0x0188
	float flRecoilAngleVarianceAlt; // 0x018C
	float flRecoilMagnitude; // 0x0190
	float flRecoilMagnitudeAlt; // 0x0194
	float flRecoilMagnitudeVariance; // 0x0198
	float flRecoilMagnitudeVarianceAlt; // 0x019C
	float flRecoveryTimeCrouch; // 0x01A0
	float flRecoveryTimeStand; // 0x01A4
	float flRecoveryTimeCrouchFinal; // 0x01A8
	float flRecoveryTimeStandFinal; // 0x01AC
	int iRecoveryTransitionStartBullet;// 0x01B0 
	int iRecoveryTransitionEndBullet; // 0x01B4
	bool bUnzoomAfterShot; // 0x01B8
	bool bHideViewModelZoomed; // 0x01B9
	char pad_0x01B5[2]; // 0x01BA
	char iZoomLevels[3]; // 0x01BC
	int iZoomFOV[2]; // 0x01C0
	float fZoomTime[3]; // 0x01C4
	char* szWeaponClass; // 0x01D4
	float flAddonScale; // 0x01D8
	char pad_0x01DC[4]; // 0x01DC
	char* szEjectBrassEffect; // 0x01E0
	char* szTracerEffect; // 0x01E4
	int iTracerFrequency; // 0x01E8
	int iTracerFrequencyAlt; // 0x01EC
	char* szMuzzleFlashEffect_1stPerson; // 0x01F0
	char pad_0x01F4[4]; // 0x01F4
	char* szMuzzleFlashEffect_3rdPerson; // 0x01F8
	char pad_0x01FC[4]; // 0x01FC
	char* szMuzzleSmokeEffect; // 0x0200
	float flHeatPerShot; // 0x0204
	char* szZoomInSound; // 0x0208
	char* szZoomOutSound; // 0x020C
	float flInaccuracyPitchShift; // 0x0210
	float flInaccuracySoundThreshold; // 0x0214
	float flBotAudibleRange; // 0x0218
	BYTE pad_0x0218[8]; // 0x0220
	char* pWrongTeamMsg; // 0x0224
	bool bHasBurstMode; // 0x0228
	BYTE pad_0x0225[3]; // 0x0229
	bool bIsRevolver; // 0x022C
	bool bCannotShootUnderwater; // 0x0230
	char m_pszName[32];
	char* m_szWeaponName; //0x0004
	char pad_0x0008[0x8]; //0x0008
	ItemDefinitionIndex_t* m_pItemDefinition; //0x0010
	int m_iMaxClip1; //0x0014
	char pad_0x0018[0xC]; //0x0018
	int m_iMaxAmmo; //0x0024
	char pad_0x0028[0x4]; //0x0028
	char* m_szWorldModel; //0x002C
	char* m_szViewModel; //0x0030
	char* m_szDroppedModel; //0x0034
	char pad_0x0038[0x4]; //0x0038
	char* N0000054E; //0x003C
	char pad_0x0040[0x38]; //0x0040
	char* N0000055D; //0x0078
	char pad_0x007C[0x4]; //0x007C
	char* m_szAmmoType; //0x0080
	char pad_0x0084[0x4]; //0x0084
	char* m_szLocalizedName; //0x0088
	char pad_0x008C[0x3C]; //0x008C
	int m_eWeaponType; //0x00C8
	int m_iPrice; //0x00CC
	char pad_0x00D0[0x4]; //0x00D0
	char* m_szAnimationPrefix; //0x00D4
	char pad_0x00D8[0x14]; //0x00D8
	int m_iDamage; //0x00EC
	float m_fArmorRatio; //0x00F0
	char pad_0x00F4[0x4]; //0x00F4
	float m_fPenetration; //0x00F8
	char pad_0x00FC[0x8]; //0x00FC
	float m_fRange; //0x0104
	float m_fRangeModifier; //0x0108
	unsigned char m_bHasSilencer; //0x011C
	char pad_0x011D[0x10B]; //0x011D
	unsigned char m_bHasBurstmode; //0x0228
	unsigned char m_bIsRevolver; //0x0229
	char pad_0x022A[0x1BE]; //0x022A
};

enum WeaponType : byte
{
	Shotgun,
	Pistol,
	Automatic,
	Sniper,
	Grenade,
	Knife,
	Bomb
};

class CBaseCombatWeapon
{
public:
	char			__pad[0x64];
	int				index;
	int			    GetWeaponID();
	float&			GetNextPrimaryAttack();
	float&			GetAccuracyPenalty();
	int&			GetXUIDLow();
	int&			GetXUIDHigh();
	int&			GetEntityQuality();
	int&			GetAccountID();
	int&			GetItemIDHigh();
	int&			GetItemDefinitionIndex();
	int&			GetFallbackPaintKit();
	int&			GetFallbackStatTrak();
	float&			GetFallbackWear();
	bool			IsEmpty();
	bool			IsReloading();
	void			UpdateAccuracyPenalty();
	float			GetWeaponSpread();
	float			GetWeaponCone();


	CCSWeaponInfo* GetWpnData()
	{
		typedef CCSWeaponInfo*(__thiscall* GetWeaponDataFn)(void*);
		return call_vfunc< GetWeaponDataFn >(this, 446)(this);
	}

	const char* GetName()
	{
		typedef  const char* (__thiscall* GetNameFn)(void*);
		return call_vfunc<GetNameFn>(this, 378)(this);
	}


	bool IsValid();
	int	Clip1();

	WeaponType GetWeaponType();

};


class IClientEntityList
{
public:

	virtual void Function0() = 0;
	virtual void Function1() = 0;
	virtual void Function2() = 0;

	virtual IClientEntity *		GetClientEntity(int entnum);
	virtual IClientEntity *		GetClientEntityFromHandle(DWORD hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void);

};

// m_lifeState values
#define	LIFE_ALIVE				0 // alive
#define	LIFE_DYING				1 // playing death animation or still falling off of a ledge waiting to hit ground
#define	LIFE_DEAD				2 // dead. lying still.
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

enum class ObserverMode_t : int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM = 1,
	OBS_MODE_FREEZECAM = 2,
	OBS_MODE_FIXED = 3,
	OBS_MODE_IN_EYE = 4,
	OBS_MODE_CHASE = 5,
	OBS_MODE_ROAMING = 6
};

class __declspec (novtable)IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void			Release(void) = 0;
	virtual void			blahblahpad(void) = 0;
	virtual const Vector&	GetAbsAngles(void) const = 0;

	CBaseCombatWeapon* GetWeapon();

	bool IsDead()
	{
		BYTE LifeState = *(PBYTE)((DWORD)this + DynNetVars::m_lifeState);
		return (LifeState != LIFE_ALIVE);
	}

	DWORD GetObserverTarget()
	{
		return *reinterpret_cast<DWORD*>((DWORD)this + (DWORD)DynNetVars::m_hObserverTarget);
	}

	ObserverMode_t GetObserverMode()
	{
		return *(ObserverMode_t*)((DWORD)this + (DWORD)DynNetVars::m_iObserverMode);
	}

	bool IsEnemy();

	Vector& GetAbsOrigin()
	{
		typedef Vector&(__thiscall* fn)(void*);
		return call_vfunc<fn>(this, 10)(this);
	}

	Vector GetAbsOrigin2()
	{
		__asm
		{
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
			CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	Vector GetOrigin()
	{
		if (!this)
			return Vector(0,0,0);

		return *(Vector*)((uintptr_t)(DWORD)this + (DWORD)DynNetVars::m_vecOrigin);
	}
	int GetTeamNum()
	{
		return *(int*)((DWORD)this + (DWORD)DynNetVars::m_iTeamNum);
	}
	int GetFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x100);
	}

	Vector* GetEyeAnglesPointer()
	{


		return reinterpret_cast<Vector*>((DWORD)this + (DWORD)0xAA08);
	}

	Vector m_vecPunch()
	{
		if (!this)
			return Vector(0, 0, 0);

		return *reinterpret_cast<Vector*>((DWORD)this + /*(DWORD)0x301C*/ (DWORD)DynNetVars::m_aimPunchAngle);
	}

	float GetLowerBodyYawTarget()
	{
		return *reinterpret_cast<float*>((DWORD)this + (DWORD)DynNetVars::m_flLowerBodyYawTarget);
	}

	Vector GetPunch()
	{
		if (!this)
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + (DWORD)DynNetVars::m_aimPunchAngle);
	}


	void getRenderBounds(Vector& mins, Vector& maxs)
	{
		typedef void(__thiscall* original)(void*, Vector&, Vector&);
		call_vfunc<original>((void*)(this + 0x4), 17)((void*)(this + 0x4), mins, maxs);
	}

	bool IsPlayer()
	{
		if (!this || this == nullptr)
			return false;

		if (this->IsDormant())
			return false;

		if (this->GetTeamNum() == 0)
			return false;

		if (this->GetHealth() <= 0)
			return false;

		if (this->HasGunGameImmunity())
			return false;

		return true;
	}

	Vector aim_punch()
	{
		if (!this)
			return Vector(0, 0, 0);
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)DynNetVars::m_aimPunchAngle);
	}

	Vector view_punch()
	{
		if (!this)
			return Vector(0, 0, 0);
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)DynNetVars::m_viewPunchAngle);
	}

	bool GetAlive()
	{
		return (bool)(*(int*)((DWORD)this + (DWORD)DynNetVars::m_lifeState) == 0);
	}

	int GetHealth()
	{
		if (!this)
			return 0;

		return  *reinterpret_cast< int* >((DWORD)this + (DWORD)DynNetVars::m_iHealth);
	}

	int GetArmor()
	{
		if (!this)
			return 0;

		return  *reinterpret_cast< int* >((DWORD)this + (DWORD)DynNetVars::m_ArmorValue);
	}

	void NoFlash(float alpha)
	{
		*(float*)((DWORD)this + (DWORD)DynNetVars::m_flFlashMaxAlpha) = alpha;
	}

	int GetMoveType()
	{
		return *(int*)((DWORD)this + 0x258);
	}


	bool SpottedByMask()
	{
	//	return  *reinterpret_cast< bool* >((DWORD)this + (DWORD)Engine::Dynamic::Entity::m_bSpottedByMask);
	}

	Vector GetEyeAngles()
	{
		if (!this)
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + /*(DWORD)0xB24C*/(DWORD)DynNetVars::m_angEyeAngles);
	}

	bool IsDormant()
	{
		return  *reinterpret_cast< bool* >((DWORD)this + (DWORD)0xE9);
	}

	int GetCrossId()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0xB2A4);
	}

	bool SpottedBy()
	{
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0x939);
	}

	const char *GetLastPlace()
	{
		return reinterpret_cast<const char*>((DWORD)this + (DWORD)DynNetVars::m_szLastPlaceName);
	}


	float GetFlashDuration()
	{
		return *(float*)((DWORD)this + (DWORD)DynNetVars::m_flFlashDuration);
	}

	bool IsFlashed()
	{
		return GetFlashDuration() > 0 ? true : false;
	}

	float GetBombTimer()
	{
		float bombTime = *(float*)((DWORD)this + (DWORD)DynNetVars::m_flC4Blow);
		float returnValue = bombTime -pGlobals->curtime;
		return (returnValue < 0) ? 0.f : returnValue;

	}

	int GetMoney(void)
	{
		return *(int*)((DWORD)this + 0x0000A9F8);
	}


	Vector GetEyess()
	{
		if (!this)
			return Vector(0, 0, 0);
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x104);
	}

	Vector GetEyePos(void)
	{
		if (!this)
			return Vector(0, 0, 0);
		return  this->GetOrigin() + this->GetEyess();
	}


	int GetTickBase()
	{
		return *(int*)((DWORD)this + (DWORD)DynNetVars::m_nTickBase);
	}

	ULONG GetOwnerHandle(void)
	{
		return *(ULONG*)((DWORD)this + (DWORD)DynNetVars::m_hOwnerEntity);
	}

	BYTE GetLifeState()
	{
		return *(BYTE*)((DWORD)this + (DWORD)DynNetVars::m_lifeState);
	}
	bool IsValid()
	{
		bool bValid = (GetLifeState() == 0 && GetHealth() > 0 && !IsDormant()) ? true : false;
		return bValid;
	}
	int	Clips()
	{
		return *(int*)((DWORD)this + (DWORD)DynNetVars::m_iClip1);
	}


	int GetHitboxSet()
	{
		return *(int*)((DWORD)this + (DWORD)0x09FC);
	}

	ICollideable* GetCollideable()
	{
		return (ICollideable*)((uintptr_t)this + (DWORD)DynNetVars::m_Collision);
	}

	bool HasHelmet()
	{
		return *(bool*)((DWORD)this + (DWORD)DynNetVars::m_bHasHelmet);
	}

	bool HasGunGameImmunity()
	{
		return *(bool*)((DWORD)this + (DWORD)DynNetVars::m_bGunGameImmunity);
	}

	bool IsScoped()
	{
		return *(bool*)((DWORD)this + (DWORD)DynNetVars::m_bIsScoped);
	}

	Vector GetVelocity()
	{
		if (!this)
			return Vector(0, 0, 0);
		return *(Vector*)((DWORD)this + (DWORD)DynNetVars::m_vecVelocity);
	}



	Vector GetBonePosition(int iBone)
	{
		if (!this)
			return Vector(0, 0, 0);

		matrix3x4_t boneMatrixes[128];
		if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
		{
			matrix3x4_t boneMatrix = boneMatrixes[iBone];
			return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
		}
		else return Vector(0, 0, 0);
	}


	int GetShotsFired(void)
	{
		return *(int*)((DWORD)this + (DWORD)DynNetVars::m_iBulletsFired);
	}

	bool IsVisible(int bone);
	player_info_t GetPlayerInfo();
	std::string GetName()
	{
		string name = GetPlayerInfo().szName;
		std::size_t found = name.find("\n");
		while (found != std::string::npos)
		{
			name.replace(found, found + 2, "");
			found = name.find("\n");
		}
		return name;
	}

};







class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char *(__thiscall* oGetName)(PVOID, unsigned int);
		return call_vfunc< oGetName >(this, 36)(this, vguiPanel);
	}
};


struct surfacephysicsparams_t
{
	float    friction;
	float    elasticity;
	float    density;
	float    thickness;
	float    dampening;
};

struct surfaceaudioparams_t
{
	float    reflectivity;             // like elasticity, but how much sound should be reflected by this surface
	float    hardnessFactor;           // like elasticity, but only affects impact sound choices
	float    roughnessFactor;          // like friction, but only affects scrape sound choices   
	float    roughThreshold;           // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float    hardThreshold;            // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float    hardVelocityThreshold;    // collision velocity > this causes "hard" impacts, < this causes "soft" impacts   
	float    highPitchOcclusion;       //a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
	float    midPitchOcclusion;
	float    lowPitchOcclusion;
};

struct surfacesoundnames_t
{
	unsigned short    walkStepLeft;
	unsigned short    walkStepRight;
	unsigned short	  runStepLeft;
	unsigned short	  runStepRight;
	unsigned short    impactSoft;
	unsigned short    impactHard;
	unsigned short    scrapeSmooth;
	unsigned short    scrapeRough;
	unsigned short    bulletImpact;
	unsigned short    rolling;
	unsigned short    breakSound;
	unsigned short    strainSound;
};

struct surfacegameprops_t
{
public:
	float maxSpeedFactor;
	float jumpFactor;
	float flPenetrationModifier;
	float flDamageModifier;
	unsigned short material;
	byte climbable;
	char pad00[0x4];

};

struct surfacedata_t
{
	surfacephysicsparams_t    physics;
	surfaceaudioparams_t    audio;
	surfacesoundnames_t        sounds;
	surfacegameprops_t        game;
};


class IPhysicsSurfaceProps
{
public:

	surfacedata_t	*GetSurfaceData(int surfaceDataIndex)
	{
		typedef surfacedata_t*(__thiscall* fnGetSurfaceData)(void*, int);
		return call_vfunc<fnGetSurfaceData>(this, 5)(this, surfaceDataIndex);
	}
};

class CUserCmd
{
public:

public:
	virtual ~CUserCmd() { };
	int		command_number;
	int		tick_count;
	Vector	viewangles;
	Vector	aimdirection;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	byte    impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousedx;
	short	mousedy;
	bool	hasbeenpredicted;
	char	pad_0x4C[0x18];
};

class CVerifiedUserCmd
{
public:
	CUserCmd        m_cmd;
	CRC32_t         m_crc;
};

class CInput
{
public:

	CUserCmd* GetUserCmd(int sequence_number)
	{
		return &m_pCommands[sequence_number % 150];
	}

	CVerifiedUserCmd* GetVerifiedUserCmd(int sequence_number)
	{
		return &m_pVerifiedCommands[sequence_number % 150];
	}

	void*               pvftable;                     //0x00
	bool                m_fTrackIRAvailable;          //0x04
	bool                m_fMouseInitialized;          //0x05
	bool                m_fMouseActive;               //0x06
	bool                m_fJoystickAdvancedInit;      //0x07
	char                pad_0x08[0x2C];               //0x08
	void*               m_pKeys;                      //0x34
	char                pad_0x38[0x64];               //0x38
	bool                m_fCameraInterceptingMouse;   //0x9C
	bool                m_fCameraInThirdPerson;       //0x9D
	bool                m_fCameraMovingWithMouse;     //0x9E
	Vector             m_vecCameraOffset;            //0xA0
	bool                m_fCameraDistanceMove;        //0xAC
	int                 m_nCameraOldX;                //0xB0
	int                 m_nCameraOldY;                //0xB4
	int                 m_nCameraX;                   //0xB8
	int                 m_nCameraY;                   //0xBC
	bool                m_CameraIsOrthographic;       //0xC0
	Vector              m_angPreviousViewAngles;      //0xC4
	Vector              m_angPreviousViewAnglesTilt;  //0xD0
	float               m_flLastForwardMove;          //0xDC
	int                 m_nClearInputState;           //0xE0
	char                pad_0xE4[0x8];                //0xE4
	CUserCmd*           m_pCommands;                  //0xEC
	CVerifiedUserCmd*   m_pVerifiedCommands;          //0xF0
};



class CViewSetup
{
public:
	int			x, x_old;
	int			y, y_old;
	int			width, width_old;
	int			height, height_old;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix;
	matrix3x4_t	m_matCustomViewMatrix;
	char		pad_0x68[0x48];
	float		fov;
	float		fovViewmodel;
	Vector		origin;
	Vector		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	float		m_flAspectRatio;
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	int			m_nMotionBlurMode;
	float		m_flShutterTime;
	Vector		m_vShutterOpenPosition;
	Vector		m_shutterOpenAngles;
	Vector		m_vShutterClosePosition;
	Vector		m_shutterCloseAngles;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	int			m_EdgeBlur;
};

class IInputSystem
{
public:
	void EnableInput(bool bEnable)
	{
		typedef void(__thiscall* OriginalFn)(void*, bool);
		return call_vfunc<OriginalFn>(this, 11)(this, bEnable);
	}

	void ResetInputState()
	{
		typedef void(__thiscall* OriginalFn)(void*);
		return call_vfunc<OriginalFn>(this, 39)(this);
	}

	bool IsButtonDown(ButtonCode_t code)
	{
		typedef bool(__thiscall* OriginalFn)(void*, ButtonCode_t);
		return call_vfunc<OriginalFn>(this, 15)(this, code);
	}

	void GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall* OriginalFn)(void*, int*, int*);
		return call_vfunc<OriginalFn>(this, 56)(this, m_pX, m_pY);
	}

	ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
	{
		typedef ButtonCode_t(__thiscall* OriginalFn)(void*, int);
		return call_vfunc<OriginalFn>(this, 44)(this, nVirtualKey);
	}
	int ButtonCodeToVirtualKey(ButtonCode_t code)
	{
		typedef int(__thiscall* OriginalFn)(void*, ButtonCode_t);
		return call_vfunc<OriginalFn>(this, 45)(this, code);
	}
};


class ConVar
{
public:
	void ConVar::SetValue(const char* value)
	{
		typedef void(__thiscall* OriginalFn)(void*, const char*);
		return call_vfunc<OriginalFn>(this, 14)(this, value);
	}

	void ConVar::SetValue(float value)
	{
		typedef void(__thiscall* OriginalFn)(void*, float);
		return call_vfunc<OriginalFn>(this, 15)(this, value);
	}

	void ConVar::SetValue(int value)
	{
		typedef void(__thiscall* OriginalFn)(void*, int);
		return call_vfunc<OriginalFn>(this, 16)(this, value);
	}

	void ConVar::SetValue(Color value)
	{
		typedef void(__thiscall* OriginalFn)(void*, Color);
		return call_vfunc<OriginalFn>(this, 17)(this, value);
	}

	char* ConVar::GetName()
	{
		typedef char*(__thiscall* OriginalFn)(void*);
		return call_vfunc<OriginalFn>(this, 5)(this);
	}

	char* ConVar::GetDefault()
	{
		return pszDefaultValue;
	}

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 

	void RegisterConCommand(ConVar *pCvar)
	{
		typedef void(__thiscall* OriginalFn)(void*, ConVar*);
		return call_vfunc<OriginalFn>(this, 1)(this, pCvar);
	}

	ConVar* FindVar(const char *var_name)
	{
		typedef ConVar*(__thiscall* OriginalFn)(void*, const char*);
		return call_vfunc<OriginalFn>(this, 15)(this, var_name);
	}

};//Size=0x0048

struct mstudiobbox_t
{
	int     bone;
	int     group;
	Vector	bbmin;
	Vector  bbmax;
	int     szhitboxnameindex;
	int		pad[3];
	float	radius;
	int		pad2[4];

	char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((char*)this) + szhitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int						sznameindex;
	inline char* const		pszName(void) const { return ((char*)this) + sznameindex; }
	int						numhitboxes;
	int						hitboxindex;
	inline mstudiobbox_t*	pHitbox(int i) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
	int		 			parent;
	int					bonecontroller[6];

	Vector				pos;
	float				quat[4];
	Vector				rot;
	Vector				posscale;
	Vector				rotscale;

	matrix3x4_t			poseToBone;
	float				qAlignment[4];
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((BYTE *)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
	int					contents;		// See BSPFlags.h for the contents flags

	int					unused[8];		// remove as appropriate
};

struct studiohdr_t
{
	int					id;
	int					version;

	int					checksum;

	char				name[64];
	int					length;


	Vector				eyeposition;

	Vector				illumposition;

	Vector				hull_min;
	Vector				hull_max;

	Vector				view_bbmin;
	Vector				view_bbmax;

	int					flags;

	int					numbones;
	int					boneindex;

	inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((BYTE *)this) + boneindex) + i; };

	int						numbonecontrollers;
	int						bonecontrollerindex;

	int						numhitboxsets;
	int						hitboxsetindex;

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((BYTE*)this) + hitboxsetindex) + i;
	}

	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);

		if (!s)
			return NULL;

		return s->pHitbox(i);
	}

	inline int iHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);

		if (!s)
			return 0;

		return s->numhitboxes;
	}


	int					numlocalanim;
	int					localanimindex;

	int					numlocalseq;
	int					localseqindex;

	mutable int			activitylistversion;
	mutable int			eventsindexed;

	int					numtextures;
	int					textureindex;

	int					numcdtextures;
	int					cdtextureindex;

	int					numskinref;
	int					numskinfamilies;
	int					skinindex;

	int					numbodyparts;
	int					bodypartindex;

	int					numlocalattachments;
	int					localattachmentindex;

	int					numlocalnodes;
	int					localnodeindex;
	int					localnodenameindex;

	int					numflexdesc;
	int					flexdescindex;

	int					numflexcontrollers;
	int					flexcontrollerindex;

	int					numflexrules;
	int					flexruleindex;

	int					numikchains;
	int					ikchainindex;

	int					nummouths;
	int					mouthindex;

	int					numlocalposeparameters;
	int					localposeparamindex;

	int					surfacepropindex;

	int					keyvalueindex;
	int					keyvaluesize;


	int					numlocalikautoplaylocks;
	int					localikautoplaylockindex;

	float				mass;
	int					contents;

	int					numincludemodels;
	int					includemodelindex;

	mutable void		*virtualModel;

	int					szanimblocknameindex;
	int					numanimblocks;
	int					animblockindex;

	mutable void		*animblockModel;

	int					bonetablebynameindex;

	void				*pVertexBase;
	void				*pIndexBase;

	BYTE				constdirectionallightdot;

	BYTE				rootLOD;

	BYTE				numAllowedRootLODs;

	BYTE				unused[1];

	int					unused4;

	int					numflexcontrollerui;
	int					flexcontrolleruiindex;
	float				flVertAnimFixedPointScale;
	int					unused3[1];
	int					studiohdr2index;
	int					unused2[1];

};


struct AudioState_t
{
	Vector m_Origin;
	Vector m_Angles;
	bool m_bIsUnderwater;
};

class IRecipientFilter
{
public:
	virtual			~IRecipientFilter() {}

	virtual bool	IsReliable(void) const = 0;
	virtual bool	IsInitMessage(void) const = 0;

	virtual int		GetRecipientCount(void) const = 0;
	virtual int		GetRecipientIndex(int slot) const = 0;
};


template< class T, class A > class CUtlVector;
template< class T, class I > class CUtlMemory;

template< class T, class I = int >
class CUtlMemory { };

template< class T, class A = CUtlMemory<T> >
class CUtlVector { };

enum soundlevel_t
{
	SNDLVL_NONE = 0,

	SNDLVL_20dB = 20,			// rustling leaves
	SNDLVL_25dB = 25,			// whispering
	SNDLVL_30dB = 30,			// library
	SNDLVL_35dB = 35,
	SNDLVL_40dB = 40,
	SNDLVL_45dB = 45,			// refrigerator

	SNDLVL_50dB = 50,	// 3.9	// average home
	SNDLVL_55dB = 55,	// 3.0

	SNDLVL_IDLE = 60,	// 2.0	
	SNDLVL_60dB = 60,	// 2.0	// normal conversation, clothes dryer

	SNDLVL_65dB = 65,	// 1.5	// washing machine, dishwasher
	SNDLVL_STATIC = 66,	// 1.25

	SNDLVL_70dB = 70,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

	SNDLVL_NORM = 75,
	SNDLVL_75dB = 75,	// 0.8	// busy traffic

	SNDLVL_80dB = 80,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
	SNDLVL_TALKING = 80,	// 0.7
	SNDLVL_85dB = 85,	// 0.6	// average factory, electric shaver
	SNDLVL_90dB = 90,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
	SNDLVL_95dB = 95,
	SNDLVL_100dB = 100,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
	SNDLVL_105dB = 105,			// helicopter, power mower
	SNDLVL_110dB = 110,			// snowmobile drvrs seat, inboard motorboat, sandblasting
	SNDLVL_120dB = 120,			// auto horn, propeller aircraft
	SNDLVL_130dB = 130,			// air raid siren

	SNDLVL_GUNFIRE = 140,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
	SNDLVL_140dB = 140,	// 0.2

	SNDLVL_150dB = 150,	// 0.2

	SNDLVL_180dB = 180,			// rocket launching

								// NOTE: Valid soundlevel_t values are 0-255.
								//       256-511 are reserved for sounds using goldsrc compatibility attenuation.
};

#define	PITCH_NORM		100			// non-pitch shifted
#define PITCH_LOW		95			// other values are possible - 0-255, where 255 is very high
#define PITCH_HIGH		120

class IEngineSound
{
public:
	virtual bool PrecacheSound(const char *pSample, bool bPreload = false, bool bIsUISound = false) = 0;
	virtual bool IsSoundPrecached(const char *pSample) = 0;
	virtual void PrefetchSound(const char *pSample) = 0;
	virtual bool IsLoopingSound(const char *pSample) = 0;

	virtual float GetSoundDuration(const char *pSample) = 0;

	virtual int EmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
		float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
		const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual int EmitSound2(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
		float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
		const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual void EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel, int iSentenceIndex,
		float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
		const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual void StopSound(int iEntIndex, int iChannel, const char *pSample, unsigned int nSoundEntryHash) = 0;
};

#pragma endregion


class RadianEuler
{
public:
	inline RadianEuler(void) { }
	inline RadianEuler(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	inline RadianEuler(Quaternion const &q);	// evil auto type promotion!!!
	inline RadianEuler(QAngle const &angles);	// evil auto type promotion!!!

												// Initialization
	inline void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f) { x = ix; y = iy; z = iz; }

	//	conversion to qangle
	QAngle ToQAngle(void) const;
	bool IsValid() const;
	void Invalidate();

	inline float *Base() { return &x; }
	inline const float *Base() const { return &x; }

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	float x, y, z;
};

class Quaternion				// same data-layout as engine's vec4_t,
{								//		which is a float[4]
public:
	inline Quaternion(void) {}
	inline Quaternion(float ix, float iy, float iz, float iw) : x(ix), y(iy), z(iz), w(iw) { }
	inline Quaternion(RadianEuler const &angle);	// evil auto type promotion!!!

	inline void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f, float iw = 0.0f) { x = ix; y = iy; z = iz; w = iw; }

	bool IsValid() const;
	void Invalidate();

	bool operator==(const Quaternion &src) const;
	bool operator!=(const Quaternion &src) const;

	float* Base() { return (float*)this; }
	const float* Base() const { return (float*)this; }

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	float x, y, z, w;
};
enum RenderableTranslucencyType_t
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,	// has both translucent and opaque sub-partsa
};

class CModelInfo
{
public:
	virtual							~CModelInfo(void) { }
	virtual const model_t			*GetModel(int modelindex) const = 0;
	// Returns index of model by name
	virtual int						GetModelIndex(const char *name) const = 0;
	// Returns name of model
	virtual const char				*GetModelName(const model_t *model) const = 0;
	virtual void							UNUSED() {};
	virtual vcollide_t				*GetVCollide(const model_t *model) const = 0;
	virtual vcollide_t				*GetVCollide(int modelindex) const = 0;
	virtual void					GetModelBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual	void					GetModelRenderBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual int						GetModelFrameCount(const model_t *model) const = 0;
	virtual int						GetModelType(const model_t *model) const = 0;
	virtual void					*GetModelExtraData(const model_t *model) = 0;
	virtual bool					ModelHasMaterialProxy(const model_t *model) const = 0;
	virtual bool					IsTranslucent(model_t const* model) const = 0;
	virtual bool					IsTranslucentTwoPass(const model_t *model) const = 0;
	virtual void					Unused0() {};
	virtual RenderableTranslucencyType_t ComputeTranslucencyType(const model_t *model, int nSkin, int nBody) = 0;
	virtual int						GetModelMaterialCount(const model_t* model) const = 0;
	virtual void					GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials) = 0;
	virtual bool					IsModelVertexLit(const model_t *model) const = 0;
	virtual const char				*GetModelKeyValueText(const model_t *model) = 0;
	virtual bool					GetModelKeyValue(const model_t *model, CUtlBuffer &buf) = 0; // supports keyvalue blocks in submodels
	virtual float					GetModelRadius(const model_t *model) = 0;

	virtual const studiohdr_t		*FindModel(const studiohdr_t *pStudioHdr, void **cache, const char *modelname) const = 0;
	virtual const studiohdr_t		*FindModel(void *cache) const = 0;
	virtual	virtualmodel_t			*GetVirtualModel(const studiohdr_t *pStudioHdr) const = 0;
	virtual byte					*GetAnimBlock(const studiohdr_t *pStudioHdr, int iBlock) const = 0;
	virtual bool					HasAnimBlockBeenPreloaded(studiohdr_t const*, int) const = 0;

	// Available on client only!!!
	virtual void					GetModelMaterialColorAndLighting(const model_t *model, Vector const& origin,
		Vector const& angles, trace_t* pTrace,
		Vector& lighting, Vector& matColor) = 0;
	virtual void					GetIlluminationPoint(const model_t *model, IClientRenderable *pRenderable, Vector const& origin,
		Vector const& angles, Vector* pLightingCenter) = 0;

	virtual int						GetModelContents(int modelIndex) const = 0;
	virtual void							UNUSED11() {};
	virtual studiohdr_t				*GetStudioModel(const model_t *mod) = 0;
	virtual int						GetModelSpriteWidth(const model_t *model) const = 0;
	virtual int						GetModelSpriteHeight(const model_t *model) const = 0;

	// Sets/gets a map-specified fade range (client only)
	virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void					GetLevelScreenFadeRange(float *pMinArea, float *pMaxArea) const = 0;

	// Sets/gets a map-specified per-view fade range (client only)
	virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;

	// Computes fade alpha based on distance fade + screen fade (client only)
	virtual unsigned char			ComputeLevelScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char			ComputeViewScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;

	// both client and server
	virtual int						GetAutoplayList(const studiohdr_t *pStudioHdr, unsigned short **pAutoplayList) const = 0;

	// Gets a virtual terrain collision model (creates if necessary)
	// NOTE: This may return NULL if the terrain model cannot be virtualized
	virtual CPhysCollide			*GetCollideForVirtualTerrain(int index) = 0;
	virtual bool					IsUsingFBTexture(const model_t *model, int nSkin, int nBody, void /*IClientRenderable*/ *pClientRenderable) const = 0;
	virtual const model_t			*FindOrLoadModel(const char *name) const = 0;
	virtual MDLHandle_t				GetCacheHandle(const model_t *model) const = 0;
	// Returns planes of non-nodraw brush model surfaces
	virtual int						GetBrushModelPlaneCount(const model_t *model) const = 0;
	virtual void					GetBrushModelPlane(const model_t *model, int nIndex, cplane_t &plane, Vector *pOrigin) const = 0;
	virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual bool					UsesEnvCubemap(const model_t *model) const = 0;
	virtual bool					UsesStaticLighting(const model_t *model) const = 0;
};

class CGlowObjectManager
{
public:
	class GlowObjectDefinition_t
	{
	public:
		void set(Color color)
		{
			m_vGlowColor = Vector(color.r(), color.g(), color.b());
			m_flGlowAlpha = color.a();
			m_bRenderWhenOccluded = true;
			m_bRenderWhenUnoccluded = false;
			m_flBloomAmount = 1.f;
		}

		IClientEntity* getEntity()
		{
			return m_hEntity;
		}

		bool IsEmpty() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

	public:
		IClientEntity*		m_hEntity;
		Vector				m_vGlowColor;
		float				m_flGlowAlpha;

		char				unknown[4];
		float				flUnk;
		float				m_flBloomAmount;
		float				localplayeriszeropoint3;


		bool				m_bRenderWhenOccluded;
		bool				m_bRenderWhenUnoccluded;
		bool				m_bFullBloomRender;
		char				unknown1[1];


		int					m_nFullBloomStencilTestValue;
		int					iUnk;
		int					m_nSplitScreenSlot;
		int					m_nNextFreeSlot;

		// Special values for GlowObjectDefinition_t::m_nNextFreeSlot
		static const int END_OF_FREE_LIST = -1;
		static const int ENTRY_IN_USE = -2;
	};

	GlowObjectDefinition_t* m_GlowObjectDefinitions;
	int		max_size;
	int		pad;
	int		size;
	GlowObjectDefinition_t* m_GlowObjectDefinitions2;
	int		currentObjects;
};

class IClientModeShared
{
public:

};

#define INTERFACEVERSION_PLAYERINFOMANAGER			"PlayerInfoManager002"

class CGlobalVars;
class IPlayerInfo;
class edict_t;
class IPlayerInfoManager
{
public:
	virtual IPlayerInfo *GetPlayerInfo(edict_t *pEdict) = 0;
	virtual CGlobalVarsBase *GetGlobalVars() = 0;
};



class CPlayerInfoManager
{
public:

	virtual IPlayerInfo *GetPlayerInfo(edict_t *pEdict);
	virtual CGlobalVarsBase *GetGlobalVars();

	//CGlobalVarsBase *GetGlobals()
	//{
	//	typedef CGlobalVarsBase*(*GlobalsVar)(void*);
	//	return call_vfunc<GlobalsVar>(this, 1)(this);
	//}

};


class GameEventListener2;
class GameEventManager2;
class GameEvent;

#define EVENT_DEBUG_ID_INIT 0x2A

class GameEvent
{
public:

	virtual ~GameEvent() {};
	virtual const char *getName() const = 0;
	virtual bool  isReliable() const = 0;
	virtual bool  isLocal() const = 0;
	virtual bool  isEmpty(const char *keyName = NULL) = 0;
	virtual bool  getBool(const char *key = NULL, bool def = false) = 0;
	virtual int   getInt(const char *key = NULL, int def = 0) = 0;
	virtual unsigned long long getUInt64(char const *key = NULL, unsigned long long def = 0) = 0;
	virtual float getFloat(const char *key = NULL, float def = 0.0f) = 0;
	virtual const char *getString(const char *key = NULL, const char *def = "") = 0;
	virtual const wchar_t *getWString(char const *key = NULL, const wchar_t *def = L"") = 0;
	virtual void unk0() = 0;
	virtual void setBool(const char *key, bool val) = 0;
	virtual void setInt(const char *key, int val) = 0;
	virtual void setUInt64(const char *key, unsigned long long val) = 0;
	virtual void setFloat(const char *key, float val) = 0;
	virtual void setString(const char *key, const char *val) = 0;
	virtual void setWString(const char *key, const wchar_t *val) = 0;
};

class GameEventManager2
{
public:

	virtual	~GameEventManager2(void) {};

	virtual int LoadEventsFromFile(const char *filename) = 0;
	virtual void Reset() = 0;
	virtual bool AddListener(GameEventListener2 *listener, const char *name, bool bServerSide) = 0;
	virtual bool FindListener(GameEventListener2 *listener, const char *name) = 0;
	virtual void RemoveListener(GameEventListener2 *listener) = 0;
	virtual GameEvent *CreateGameEvent(const char *name, bool bForce = false) = 0;
	virtual bool FireEvent(GameEvent *event, bool bDontBroadcast = false) = 0;
	virtual bool FireEventClientSide(GameEvent *gEvent) = 0;
	virtual GameEvent *DuplicateEvent(GameEvent *gEvent) = 0;
	virtual void FreeEvent(GameEvent *gEvent) = 0;
	virtual bool SerializeEvent(GameEvent *gEvent, bf_write *buf) = 0;
	virtual GameEvent *UnserializeEvent(bf_read *buf) = 0;
};


#pragma region IGameEventManager2

class IGameEvent {
public:
	const char* GetName()
	{
		return call_vfunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return call_vfunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	const char* GetString(const char* szKeyName)
	{
		return call_vfunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue)
	{
		return call_vfunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventManager2
{
public:
	virtual	~IGameEventManager2(void) {};

	virtual void FireGameEvent(GameEvent *gEvent) = 0;
	virtual int  GetEventDebugID(void) = 0;
};

#pragma endregion

class GameEventListener2
{
public:
	virtual ~GameEventListener2(void) {};
	virtual void FireGameEvent(IGameEvent* event) = 0;
	virtual int	 GetEventDebugID(void) = 0;
};



GameEventManager2*     pGameEventManager2 = nullptr;
IEngineSound*		    pSound = nullptr;
IBaseClientDLL*	    pClient = nullptr;
IVEngineClient*		pEngine = nullptr;
IPanel*				pPanel = nullptr;
IClientEntityList*		pClientEntList = nullptr;
ISurface*				pSurface = nullptr;
CPlayerInfoManager*    PlayerInfoManager = nullptr;
IVDebugOverlay*        debugOverlay = nullptr;
IEngineTrace*			pEngineTrace = nullptr;
CInput*	            pInput = nullptr;
IClientMode*           pIClientMode = nullptr;
IInputSystem*          pIInput = nullptr;
IClientModeShared*		ClientMode = nullptr;
IMaterialSystem *      pMatSystem = nullptr;
ConVar*                pCon = nullptr;
CModelInfo            *pModelInfo = nullptr;
IVRenderView*			RenderView = nullptr;
IVModelRender*			ModelRender = nullptr;
IPhysicsSurfaceProps*  PhysProps = nullptr;
 unsigned long	espfont = NULL;

 player_info_t IClientEntity::GetPlayerInfo()
 {
	 player_info_t pinfo;
	 pEngine->GetPlayerInfo(GetIndex(), &pinfo);
	 return pinfo;
 }