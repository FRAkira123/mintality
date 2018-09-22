#pragma once




#define M_PI 3.14159265358979323846f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define ANG_CLIP( ang )		if( ang > 180.0f ) { ang -= 360.0f; } else if( ang <- 180.0f ) { ang += 360.0f; }
#define	GENTITYNUM_BITS		10
#define	MAX_GENTITIES		( 1 << GENTITYNUM_BITS )
#define CHECK_VALID( _v ) 0
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

struct Vector2D
{
public:
	float x, y;

	Vector2D() {}
	Vector2D(float x_, float y_) { x = x_; y = y_; }
};

typedef float vec_t;

struct Vector
{
	float X = 0, Y = 0, Z = 0;


	vec_t Dot(const Vector& vOther) const;
	float Dots(const Vector& vOther) const;

	Vector()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}

	Vector(float _X, float _Y, float _Z)
	{
		this->X = _X;
		this->Y = _Y;
		this->Z = _Z;
	}

	inline vec_t& operator[](int i)
	{
		return ((vec_t*)this)[i];
	}

	inline vec_t operator[](int i) const
	{
		return ((vec_t*)this)[i];
	}

	Vector operator+ (const Vector &A)
	{
		return Vector(this->X + A.X, this->Y + A.Y, this->Z + A.Z);
	}

	Vector operator+ (const float A)
	{
		return Vector(this->X + A, this->Y + A, this->Z + A);
	}

	Vector operator+= (const Vector &A)
	{
		this->X += A.X;
		this->Y += A.Y;
		this->Z += A.Z;
		return *this;
	}

	Vector operator+= (const float A)
	{
		this->X += A;
		this->Y += A;
		this->Z += A;
		return *this;
	}

	Vector operator- (const Vector &A)
	{
		return Vector(this->X - A.X, this->Y - A.Y, this->Z - A.Z);
	}

	Vector operator- (const float A)
	{
		return Vector(this->X - A, this->Y - A, this->Z - A);
	}

	Vector operator-= (const Vector &A)
	{
		this->X -= A.X;
		this->Y -= A.Y;
		this->Z -= A.Z;
		return *this;
	}

	Vector operator-= (const float A)
	{
		this->X -= A;
		this->Y -= A;
		this->Z -= A;
		return *this;
	}

	Vector operator* (const Vector &A)
	{
		return Vector(this->X * A.X, this->Y * A.Y, this->Z * A.Z);
	}

	Vector operator* (const float A)
	{
		return Vector(this->X * A, this->Y * A, this->Z * A);
	}

	Vector operator*= (const Vector &A)
	{
		this->X *= A.X;
		this->Y *= A.Y;
		this->Z *= A.Z;
		return *this;
	}

	Vector operator*= (const float A)
	{
		this->X *= A;
		this->Y *= A;
		this->Z *= A;
		return *this;
	}

	Vector operator/ (const Vector &A)
	{
		return Vector(this->X / A.X, this->Y / A.Y, this->Z / A.Z);
	}

	Vector operator/ (const float A)
	{
		return Vector(this->X / A, this->Y / A, this->Z / A);
	}

	Vector operator/= (const Vector &A)
	{
		this->X /= A.X;
		this->Y /= A.Y;
		this->Z /= A.Z;
		return *this;
	}

	Vector operator/= (const float A)
	{
		this->X /= A;
		this->Y /= A;
		this->Z /= A;
		return *this;
	}

	bool operator== (const Vector &A)
	{
		if (this->X == A.X
			&& this->Y == A.Y
			&& this->Z == A.Z)
			return true;

		return false;
	}

	bool operator!= (const Vector &A)
	{
		if (this->X != A.X
			|| this->Y != A.Y
			|| this->Z != A.Z)
			return true;

		return false;
	}

	bool IsValid()
	{
		return *this != Vector(0, 0, 0);
	}

	float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (this->X*this->X + this->Y*this->Y + this->Z*this->Z);
	}

	inline vec_t* Vector::Base()
	{
		return (vec_t*)this;
	}

	inline void Zero()
	{
		X = Y = Z = 0.0f;
	}


	inline vec_t VectorLength(const Vector& v)
	{
		return (vec_t)sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
	}


	inline float Vector::Length(void) const
	{
		CHECK_VALID(*this);

		float root = 0.0f;

		float sqsr = X*X + Y*Y + Z*Z;

		__asm sqrtss xmm0, sqsr
		__asm movss root, xmm0

		return root;
	}

	inline Vector Normalize()
	{
		if (this->Y > 180 || this->Y < -180)
		{
			auto AngleY = this->Y / 360;
			if (AngleY < 0)
				AngleY = -AngleY;

			AngleY = round(AngleY);

			if (this->Y < 0)
				this->Y += 360 * AngleY;
			else
				this->Y -= 360 * AngleY;
		}

		if (this->X > 89 || this->X < -89)
		{
			auto AngleX = this->X / 360;
			if (AngleX < 0)
				AngleX = -AngleX;

			AngleX = round(AngleX);

			if (this->X < 0)
				this->X += 360 * AngleX;
			else
				this->X -= 360 * AngleX;
		}

		this->Z = 0;

		return *this;
	}

	inline Vector Vector::Clamp()
	{
		if (this->Y > 180.f || this->Y < -180.f)
		{
			if (this->Y > 180)
				this->Y = 180.f;
			else
				this->Y = -180.f;
		}
		if (this->X > 89.f || this->X < -89.f)
		{
			if (this->X > 89.f)
				this->X = 89.f;
			else
				this->X = -89.f;
		}
		this->Z = 0.f;
		return  *this;
	}

	float Difference(Vector angDestination)
	{
		bool bX180 = false;
		bool bY180 = false;

		float XDiff = _Normalize(this->X - angDestination.X);
		float YDiff = _Normalize(this->Y - angDestination.Y);

		bX180 = 180 > XDiff;
		bY180 = 180 > YDiff;

		if (!bX180)
			XDiff -= 360;

		if (!bY180)
			YDiff -= 360;

		if (0 > XDiff)
			XDiff = (XDiff - XDiff) - XDiff;

		if (0 > YDiff)
			YDiff = (YDiff - YDiff) - YDiff;

		float Diff = YDiff + XDiff;

		return Diff;
	}


	float Dist(const Vector &vOther) const
	{
		Vector delta;

		delta.X = X - vOther.X;
		delta.Y = Y - vOther.Y;
		delta.Z = Z - vOther.Z;

		return delta.Length();
	}


	bool IsZero() const
	{
		return (X > -0.01f && X < 0.01f
			&&	Y > -0.01f && Y < 0.01f
			&&	Z > -0.01f && Z < 0.01f);
	}

	void SinCos(const float &r, float &s, float &c)
	{
		s = sin(r);
		c = cos(r);
	}


	void Rotate2D(const float &f)
	{
		float _x, _y;

		float s, c;

		SinCos(DEG2RAD(f), s, c);

		_x = X;
		_y = Y;

		X = (_x * c) - (_y * s);
		Y = (_x * s) + (_y * c);
	}

	void Init(float _x = 0, float _y = 0, float _z = 0)
	{
		this->X = _x;
		this->Y = _y;
		this->Z = _z;
	}

	inline vec_t* Vector::Base2()
	{
		return (vec_t*)this;
	}

	Vector Normalized()
	{
		if (this->X != this->X)
			this->X = 0;
		if (this->Y != this->Y)
			this->Y = 0;
		if (this->Z != this->Z)
			this->Z = 0;

		if (this->X > 89.f)
			this->X = 89.f;
		if (this->X < -89.f)
			this->X = -89.f;

		while (this->Y > 180)
			this->Y -= 360;
		while (this->Y <= -180)
			this->Y += 360;

		if (this->Y > 180.f)
			this->Y = 180.f;
		if (this->Y < -180.f)
			this->Y = -180.f;

		this->Z = 0;

		return *this;
	}

	inline vec_t Length2D(void) const
	{
		return (vec_t)::sqrtf(X * X + Y * Y);
	}


private:
	float _Normalize(float angAngle)
	{
		return (float)(fmod(angAngle + 180, 360) - 180);
	}
};

inline vec_t VectorNormalizes(Vector& v)
{
	vec_t l = v.Length();

	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.X = v.Y = 0.0f; v.Z = 1.0f;
	}

	return l;
}

FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b)
{
	return (a.X * b.X + a.Y * b.Y + a.Z * b.Z);
}

inline vec_t Vector::Dot(const Vector& vOther) const
{
	return DotProduct(*this, vOther);
}

inline float Vector::Dots(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.X*vOther.X + a.Y*vOther.Y + a.Z*vOther.Z);
}

inline vec_t VectorLength(const Vector& v)
{
	return (vec_t)sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	c.X = a.X - b.X;
	c.Y = a.Y - b.Y;
	c.Z = a.Z - b.Z;
}
struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.X; m_flMatVal[0][1] = yAxis.X; m_flMatVal[0][2] = zAxis.X; m_flMatVal[0][3] = vecOrigin.X;
		m_flMatVal[1][0] = xAxis.Y; m_flMatVal[1][1] = yAxis.Y; m_flMatVal[1][2] = zAxis.Y; m_flMatVal[1][3] = vecOrigin.Y;
		m_flMatVal[2][0] = xAxis.Z; m_flMatVal[2][1] = yAxis.Z; m_flMatVal[2][2] = zAxis.Z; m_flMatVal[2][3] = vecOrigin.Z;
	}

	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}
	float *operator[](int i)
	{
		return m_flMatVal[i];
	}
	const float *operator[](int i) const
	{
		return m_flMatVal[i];
	}
	float *Base()
	{
		return &m_flMatVal[0][0];
	}
	const float *Base() const
	{
		return &m_flMatVal[0][0];
	}

	float m_flMatVal[3][4];
};

struct VMatrix
{
	float m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};



