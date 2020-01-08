#pragma once
#include <Windows.h>
#include <math.h>
//https://www.mpgh.net/forum/showthread.php?t=1446167
/*--------------------------------------------------
Library : Lithtech Vector
File	: LTVector.h
----------------------------------------------------*/
struct LTVECTOR3
{
	FLOAT x, y, z;

	LTVECTOR3(FLOAT radius = 0) { this->x = this->y = this->z = radius; }
	LTVECTOR3(FLOAT X, FLOAT Y, FLOAT Z) : x(X), y(Y), z(Z) {}
	~LTVECTOR3() { }

	LTVECTOR3 operator +(LTVECTOR3 X)
	{
		return LTVECTOR3(this->x + X.x, this->y + X.y, this->z + X.z);
	}
	LTVECTOR3 operator -(LTVECTOR3 X)
	{
		return LTVECTOR3(this->x - X.x, this->y - X.y, this->z - X.z);
	}
	LTVECTOR3 operator *(FLOAT X)
	{
		return LTVECTOR3(this->x * X, this->y * X, this->z * X);
	}
	LTVECTOR3 operator /(FLOAT X)
	{
		return LTVECTOR3(this->x / X, this->y / X, this->z / X);
	}

	LTVECTOR3& operator +=(LTVECTOR3 X)
	{
		return LTVECTOR3(this->x + X.x, this->y + X.y, this->z + X.z);
	}
	LTVECTOR3& operator -=(LTVECTOR3 X)
	{
		return LTVECTOR3(this->x - X.x, this->y - X.y, this->z - X.z);
	}
	LTVECTOR3& operator *=(FLOAT X)
	{
		return LTVECTOR3(this->x * X, this->y * X, this->z * X);
	}
	LTVECTOR3& operator /=(FLOAT X)
	{
		return LTVECTOR3(this->x / X, this->y / X, this->z / X);
	}

	FLOAT operator *=(LTVECTOR3 X)
	{
		return (this->x * X.x + this->y * X.y + this->z * X.z);
	}

	BOOL operator ==(LTVECTOR3 X)
	{
		if (this->x == X.x && this->y == X.y && this->z == X.z)
			return true;
		return false;
	}
	BOOL operator !=(LTVECTOR3 X)
	{
		return !(*this == X);
	}

	DOUBLE Distance(LTVECTOR3 X)
	{
		return (DOUBLE)sqrt((this->x - X.x) * (this->x - X.x) + (this->y - X.y) * (this->y - X.y) + (this->z - X.z) * (this->z - X.z));
	}
};

struct LTVECTOR4
{
	FLOAT x, y, z, t;

	LTVECTOR4(FLOAT value = 0) { this->x = this->y = this->z = this->t = value; }
	LTVECTOR4(FLOAT X, FLOAT Y, FLOAT Z, FLOAT T) : x(X), y(Y), z(Z), t(T) {}
	~LTVECTOR4() { }

	LTVECTOR4 operator +(LTVECTOR4 X)
	{
		return LTVECTOR4(this->x + X.x, this->y + X.y, this->z + X.z, this->t + X.t);
	}
	LTVECTOR4 operator -(LTVECTOR4 X)
	{
		return LTVECTOR4(this->x - X.x, this->y - X.y, this->z - X.z, this->t - X.t);
	}
	LTVECTOR4 operator *(FLOAT X)
	{
		return LTVECTOR4(this->x * X, this->y * X, this->z * X, this->t * X);
	}
	LTVECTOR4 operator /(FLOAT X)
	{
		return LTVECTOR4(this->x / X, this->y / X, this->z / X, this->t / X);
	}

	LTVECTOR4& operator +=(LTVECTOR4 X)
	{
		return LTVECTOR4(this->x + X.x, this->y + X.y, this->z + X.z, this->t + X.t);
	}
	LTVECTOR4& operator -=(LTVECTOR4 X)
	{
		return LTVECTOR4(this->x - X.x, this->y - X.y, this->z - X.z, this->t - X.t);
	}
	LTVECTOR4& operator *=(FLOAT X)
	{
		return LTVECTOR4(this->x * X, this->y * X, this->z * X, this->t * X);
	}
	LTVECTOR4& operator /=(FLOAT X)
	{
		return LTVECTOR4(this->x / X, this->y / X, this->z / X, this->t / X);
	}

	BOOL operator ==(LTVECTOR4 X)
	{
		if (this->x == X.x && this->y == X.y && this->z == X.z && this->t == X.t)
			return true;
		return false;
	}
	BOOL operator !=(LTVECTOR4 X)
	{
		return !(*this == X);
	}
};
