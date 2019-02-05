#pragma once
class Math
{
public:
	static const float PI;

	static float Modulo(float val1, float val2);

	static float ToRadian(float degree);
	static float ToDegree(float radian);

	static int Random(int r1, int r2);
	static float Random(float r1, float r2);

	static float Clamp(float value, float min, float max);

	//Ãß°¡
	static D3DXVECTOR3 GetRotationFromMat(D3DXMATRIX mat, D3DXVECTOR3 scale);
};