#pragma once

#define M_RADPI 57.295779513082f

enum GameFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),

	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE1 = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_LOOKSPIN = (1 << 25),

};

enum GameContents
{
	CONTENTS_EMPTY = 0,		// No contents
	CONTENTS_SOLID = 0x1,		// an eye is never valid in a solid
	CONTENTS_WINDOW = 0x2,	// translucent, but not watery (glass)
	CONTENTS_AUX = 0x4,
	CONTENTS_GRATE = 0x8,		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
	CONTENTS_SLIME = 0x10,
	CONTENTS_WATER = 0x20,
	CONTENTS_BLOCKLOS = 0x40,	// block AI line of sight
	CONTENTS_OPAQUE = 0x80,	// things that cannot be seen through (may be non-solid though)

	CONTENTS_TESTFOGVOLUME = 0x100,
	CONTENTS_UNUSED = 0x200,

	// unused 
	// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
	// if not visible, then grab from the bottom.
	// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)

	CONTENTS_BLOCKLIGHT = 0x400,

	CONTENTS_TEAM1 = 0x800,	// per team contents used to differentiate collisions 
	CONTENTS_TEAM2 = 0x1000,	// between players and objects on different teams

								// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW

	CONTENTS_IGNORE_NODRAW_OPAQUE = 0x2000,

								// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)

	CONTENTS_MOVEABLE = 0x4000,

								// remaining contents are non-visible, and don't eat brushes

	CONTENTS_AREAPORTAL = 0x8000,

	CONTENTS_PLAYERCLIP = 0x10000,
	CONTENTS_MONSTERCLIP = 0x20000,

								// currents can be added to any other contents, and may be mixed
	CONTENTS_CURRENT_0 = 0x40000,
	CONTENTS_CURRENT_90 = 0x80000,
	CONTENTS_CURRENT_180 = 0x100000,
	CONTENTS_CURRENT_270 = 0x200000,
	CONTENTS_CURRENT_UP = 0x400000,
	CONTENTS_CURRENT_DOWN = 0x800000,

	CONTENTS_ORIGIN = 0x1000000,	// removed before bsping an entity

	CONTENTS_MONSTER = 0x2000000,	// should never be on a brush, only in game
	CONTENTS_DEBRIS = 0x4000000,
	CONTENTS_DETAIL = 0x8000000,// brushes to be added after vis leafs
	CONTENTS_TRANSLUCENT = 0x10000000,	// auto set if any surface has trans
	CONTENTS_LADDER = 0x20000000,

	CONTENTS_HITBOX = 0x40000000,	// use accurate hitboxes on trace
};

enum  SurfaceFlag
{
	// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
	SURF_LIGHT = 0x0001,		// value will hold the light strength
	SURF_SKY2D = 0x0002,		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
	SURF_SKY = 0x0004,	// don't draw, but add to skybox
	SURF_WARP = 0x0008,	// turbulent water warp
	SURF_TRANS = 0x0010,
	SURF_NOPORTAL = 0x0020,	// the surface can not have a portal placed on it
	SURF_TRIGGER = 0x0040,	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
	SURF_NODRAW = 0x0080,	// don't bother referencing the texture

	SURF_HINT = 0x0100,	// make a primary bsp splitter

	SURF_SKIP = 0x0200,// completely ignore, allowing non-closed brushes
	SURF_NOLIGHT = 0x0400,// Don't calculate light
	SURF_BUMPLIGHT = 0x0800,	// calculate three lightmaps for the surface for bumpmapping
	SURF_NOSHADOWS = 0x1000,	// Don't receive shadows 
	SURF_NODECALS = 0x2000,// Don't receive decals
	SURF_NOPAINT = SURF_NODECALS,	// the surface can not have paint placed on it 
	SURF_NOCHOP = 0x4000,// Don't subdivide patches on this surface 

	SURF_HITBOX = 0x8000,	// surface is part of a hitbox
};

#define MAXSTUDIOSKINS		32		// total textures
#define MAXSTUDIOBONES		128		// total bones actually used
#define MAXSTUDIOFLEXDESC	1024	// maximum number of low level flexes (actual morph targets)
#define MAXSTUDIOFLEXCTRL	96		// maximum number of flexcontrollers (input sliders)
#define MAXSTUDIOPOSEPARAM	24
#define MAXSTUDIOBONECTRLS	4
#define MAXSTUDIOANIMBLOCKS 256

#define BONE_CALCULATE_MASK			0x1F
#define BONE_PHYSICALLY_SIMULATED	0x01	// bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL		0x02	// procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL		0x04	// bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE	0x08	// bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER	0x10	// bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800	
#define BONE_USED_BY_VERTEX_LOD2	0x00001000  
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8

#define BONE_TYPE_MASK				0x00F00000
#define BONE_FIXED_ALIGNMENT		0x00100000	// bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS		0x00200000	// Vector48
#define BONE_HAS_SAVEFRAME_ROT64	0x00400000	// Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32	0x00800000	// Quaternion32

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

#define TEXTURE_GROUP_LIGHTMAP						XorStr("Lightmaps")
#define TEXTURE_GROUP_WORLD							XorStr("World textures")
#define TEXTURE_GROUP_MODEL							XorStr("Model textures")
#define TEXTURE_GROUP_VGUI							XorStr("VGUI textures")
#define TEXTURE_GROUP_PARTICLE						XorStr("Particle textures")
#define TEXTURE_GROUP_DECAL							XorStr("Decal textures")
#define TEXTURE_GROUP_SKYBOX						XorStr("SkyBox textures")
#define TEXTURE_GROUP_CLIENT_EFFECTS				XorStr("ClientEffect textures")
#define TEXTURE_GROUP_OTHER							XorStr("Other textures")
#define TEXTURE_GROUP_PRECACHED						XorStr("Precached")	// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						XorStr("CubeMap textures")
#define TEXTURE_GROUP_RENDER_TARGET					XorStr("RenderTargets")
#define TEXTURE_GROUP_UNACCOUNTED					XorStr("Unaccounted textures")	// Textures that weren't assigned a texture group.
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			XorStr("Static Indices")
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		XorStr("Displacement Verts")
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	XorStr("Lighting Verts")
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	XorStr("World Verts")
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	XorStr("Model Verts")
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	XorStr("Other Verts")
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			XorStr("Dynamic Indices")
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			XorStr("Dynamic Verts")
#define TEXTURE_GROUP_DEPTH_BUFFER					XorStr("DepthBuffer")
#define TEXTURE_GROUP_VIEW_MODEL					XorStr("ViewModel")
#define TEXTURE_GROUP_PIXEL_SHADERS					XorStr("Pixel Shaders")
#define TEXTURE_GROUP_VERTEX_SHADERS				XorStr("Vertex Shaders")
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			XorStr("RenderTarget Surfaces")
#define TEXTURE_GROUP_MORPH_TARGETS					XorStr("Morph Targets")


#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE
#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

// hyi jopa wh aim
// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)


#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)


#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)



