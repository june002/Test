#include "framework.h"
#include "Math.h"

const float Math::PI = 3.14159265f;

float Math::Modulo(float val1, float val2)
{
	while (val1 - val2 >= 0)
		val1 -= val2;

	return val1;
}

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}

float Math::Random(float r1, float r2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = r2 - r1;
	float val = random * diff;
	
	return r1 + val;
}

float Math::Clamp(float value, float min, float max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}

D3DXVECTOR3 Math::GetRotationFromMat(D3DXMATRIX mat, D3DXVECTOR3 scale)
{
	bool bCheck = false;

	bCheck |= scale.x == 0.0f;
	bCheck |= scale.y == 0.0f;
	bCheck |= scale.z == 0.0f;

	if (bCheck) return D3DXVECTOR3();

	float factorX = 1.0f / scale.x;
	float factorY = 1.0f / scale.y;
	float factorZ = 1.0f / scale.z;

	D3DXMATRIX m;
	m._11 *= factorX; m._12 *= factorX; m._13 *= factorX; m._14 = 0.0f;
	m._21 *= factorY; m._22 *= factorY; m._23 *= factorY; m._24 = 0.0f;
	m._31 *= factorZ; m._32 *= factorZ; m._33 *= factorZ; m._34 = 0.0f;
	m._41 = 0.0f; m._42 = 0.0f; m._43 = 0.0f; m._44 = 1.0f;

	return D3DXVECTOR3
	(
		atan2(m._31, m._33),
		atan2(-m._32, sqrt(pow(m._12, 2) + pow(m._22, 2))),
		atan2(m._12, m._22)
	);
}