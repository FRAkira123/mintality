#pragma once

//struct Vec3
//{
//	float X;
//	float Y;
//	float Z;
//};
struct cplane_t
{
	Vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};

struct csurface_t
{
	const char*             name;
	short                   surfaceProps;
	unsigned short          flags;
};

class CBaseTrace
{
public:
	Vector                  startpos;
	Vector                  endpos;
	cplane_t                plane;
	float                   fraction;
	int                     contents;
	unsigned short          dispFlags;
	bool                    allsolid;
	bool                    startsolid;
};

class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                     GetEntityIndex() const;
	bool                    DidHit() const;

public:
	float                   fractionleftsolid;
	csurface_t              surface;
	int                     hitgroup;
	short                   physicsbone;
	unsigned short          worldSurfaceIndex;
	IClientEntity*            m_pEnt;
	int                     hitbox;


	inline bool IsVisible() const
	{
		return fraction > 0.97f;
	}

	CGameTrace() { }

private:
	CGameTrace(const CGameTrace& vOther);
};

inline bool CGameTrace::DidHit(VOID) const
{
	return fraction < 1.0f || allsolid || startsolid;
}

typedef CGameTrace trace_t;

enum class TraceType
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(IClientEntity *pEntity, int contentsMask) = 0;
	//    virtual DWORD     GetTraceType() const = 0;
	virtual TraceType GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(IClientEntity* pHandleEntity, int contentsMask)
	{
		return !(pHandleEntity == pSkip);
	}

	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}

	void* pSkip;
};



//===============
typedef float vec_t;
class  VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z)
	{

	}

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:

	VectorAligned(const VectorAligned& vOther);
	VectorAligned(const Vector &vOther);

#else
public:
	explicit VectorAligned(const Vector &vOther)
	{

	}

	VectorAligned& operator=(const Vector &vOther)
	{

		X = vOther.X; Y = vOther.Y; Z = vOther.Z;
		return *this;
	}

#endif
	float w;
};

struct Ray_t
{
	VectorAligned        m_Start;
	VectorAligned        m_Delta;
	VectorAligned        m_StartOffset;
	VectorAligned        m_Extents;

	const matrix3x4_t*    m_WorldAxisTransform;

	bool                m_IsRay;
	bool                m_IsSwept;

	Ray_t(void)
		: m_WorldAxisTransform(0)
	{

	}


	void Init(const Vector& start, const Vector& end)
	{

		m_Delta.X = end.X - start.X;
		m_Delta.Y = end.Y - start.Y;
		m_Delta.Z = end.Z - start.Z;

		m_IsSwept = ((m_Delta.X*m_Delta.X + m_Delta.Y*m_Delta.Y + m_Delta.Z*m_Delta.Z) != 0);

		m_Extents.X = 0.0f; m_Extents.Y = 0.0f; m_Extents.Z = 0.0f;

		m_WorldAxisTransform = 0;

		m_IsRay = true;

		m_StartOffset.X = 0.0f; m_StartOffset.Y = 0.0f; m_StartOffset.Z = 0.0f;

		m_Start.X = start.X; m_Start.Y = start.Y; m_Start.Z = start.Z;
	}
};
//------- 2014.9.12
template< typename Function > Function CallVirtualFunction(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}
class IEngineTrace
{
public:

	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall* vTraceRay)(PVOID, const Ray_t&, unsigned int, CTraceFilter*, trace_t*);
		CallVirtualFunction< vTraceRay >(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}

	int	GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IClientEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* fnGetPointContents)(void*, const Vector&, int, IClientEntity**);
		return CallVirtualFunction<fnGetPointContents>(this, 0)(this, vecAbsPosition, contentsMask, ppEntity);
	}

	void EdgeTraceRay(Ray_t &ray, CTraceFilter &filt, CGameTrace &trace, bool wall = false)
	{
		typedef void(__thiscall *OrigFn)(void *, Ray_t &, unsigned int, CTraceFilter &, CGameTrace &);
		CallVirtualFunction<OrigFn>(this, 5)(this, ray, wall ? 0x200400B : 0x46004003, filt, trace);				// 0x46004003 0x4600400B
	}

};
