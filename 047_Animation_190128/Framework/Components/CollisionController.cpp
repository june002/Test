#include "Framework.h"
#include "CollisionController.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "./Draw/DebugLine.h"

CollisionController* CollisionController::instance = nullptr;

CollisionController * CollisionController::Get()
{
	assert(instance != nullptr);
	return instance;
}

void CollisionController::Create()
{
	assert(instance == nullptr);
	instance = new CollisionController();
}

void CollisionController::Delete()
{
	SAFE_DELETE(instance);
}

void CollisionController::RegisterCollider(BoxCollider * box)
{
	boxList.push_back(box);
}

void CollisionController::RegisterCollider(SphereCollider * sphere)
{
	SphereList.push_back(sphere);
}

bool CollisionController::DetectCollision()
{
	//box_box
	for (int i = 0; i < boxList.size(); i++)
	{
		for (int j = i + 1; j <= boxList.size() - 1; j++)
		{
			return DetectCollision(boxList[i], boxList[j]);
		}
	}

	// box_sphere
	// sphere_sphere
	// thread..
}

bool CollisionController::DetectCollision(BoxCollider * boxA, BoxCollider * boxB)
{
	// box_a
	D3DXMATRIX frame_A = boxA->World();
	D3DXVECTOR3 center_A = D3DXVECTOR3(frame_A._41, frame_A._42, frame_A._43);
	D3DXVECTOR3 test;
	D3DXVec3TransformCoord(&test, &D3DXVECTOR3(0,0,0), &frame_A);
	//D3DXVECTOR3 eA = D3DXVECTOR3(frame_A._11, frame_A._22, frame_A._33) * 0.5f;
	D3DXVECTOR3 eA;
	/*eA.x = fabsf(frame_A._11 * boxA->Scale().x);
	eA.y = fabsf(frame_A._22 * boxA->Scale().y);
	eA.z = fabsf(frame_A._33 * boxA->Scale().z);*/

	D3DXVECTOR3 axis_A[3];
	axis_A[0] = D3DXVECTOR3(frame_A._11, frame_A._12, frame_A._13);
	axis_A[1] = D3DXVECTOR3(frame_A._21, frame_A._22, frame_A._23);
	axis_A[2] = D3DXVECTOR3(frame_A._31, frame_A._32, frame_A._33);

	for(int i = 0; i < 3; i++)
		D3DXVec3Normalize(&axis_A[i], &axis_A[i]);

	eA[0] = D3DXVec3Dot(&axis_A[0], &D3DXVECTOR3(frame_A._11, frame_A._12, frame_A._13)) * 0.5f;
	eA[1] = D3DXVec3Dot(&axis_A[1], &D3DXVECTOR3(frame_A._21, frame_A._22, frame_A._23)) * 0.5f;
	eA[2] = D3DXVec3Dot(&axis_A[2], &D3DXVECTOR3(frame_A._31, frame_A._32, frame_A._33)) * 0.5f;





	// box_b
	D3DXMATRIX frame_B = boxB->World();
	D3DXVECTOR3 center_B = D3DXVECTOR3(frame_B._41, frame_B._42, frame_B._43);;
	//D3DXVec3TransformCoord(&center_B, &D3DXVECTOR3(0, 0, 0), &frame_B);
	//D3DXVECTOR3 eB = D3DXVECTOR3(frame_B._11, frame_B._22, frame_B._33)* 0.5f;
	D3DXVECTOR3 eB;
	/*eB.x = fabsf(frame_B._11 * boxB->Scale().x);
	eB.y = fabsf(frame_B._22 * boxB->Scale().y);
	eB.z = fabsf(frame_B._33 * boxB->Scale().z);*/


	D3DXVECTOR3 axis_B[3];
	axis_B[0] = D3DXVECTOR3(frame_B._11, frame_B._12, frame_B._13);
	axis_B[1] = D3DXVECTOR3(frame_B._21, frame_B._22, frame_B._23);
	axis_B[2] = D3DXVECTOR3(frame_B._31, frame_B._32, frame_B._33);

	for (int i = 0; i < 3; i++)
		D3DXVec3Normalize(&axis_B[i], &axis_B[i]);

	eB[0] = D3DXVec3Dot(&axis_B[0], &D3DXVECTOR3(frame_B._11, frame_B._12, frame_B._13)) * 0.5f;
	eB[1] = D3DXVec3Dot(&axis_B[1], &D3DXVECTOR3(frame_B._21, frame_B._22, frame_B._23)) * 0.5f;
	eB[2] = D3DXVec3Dot(&axis_B[2], &D3DXVECTOR3(frame_B._31, frame_B._32, frame_B._33)) * 0.5f;


	// boxA 중심에서 boxB중심까지 벡터를 boxA 프레임으로 변환
	// T의 각 성분의 크기는 boxA의 축에 투영한 길이와 같음
	D3DXVECTOR3 T = center_B - center_A;
	//D3DXVec3TransformNormal(&T, &T, &frame_A);
	T.x = D3DXVec3Dot(&T, &axis_A[0]);
	T.y = D3DXVec3Dot(&T, &axis_A[1]);
	T.z = D3DXVec3Dot(&T, &axis_A[2]);

	// R, AbsR
	/*D3DXMATRIX inv;
	D3DXMatrixInverse(&inv, NULL, &frame_B);
	D3DXMATRIX RfromBToA = inv * frame_A;*/

	float RfromBToA[3][3];
	float AbsR[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			RfromBToA[i][j] = D3DXVec3Dot(&axis_A[i], &axis_B[j]);
			AbsR[i][j] = fabsf(RfromBToA[i][j]) + FLT_EPSILON;
		}
	}

	// 투영된 거리 interval radii and distance between centers
	float rA, rB;

	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++)
	{
		rA = eA[i];
		rB = eB[0] * AbsR[i][0] + eB[1] * AbsR[i][1] + eB[2] * AbsR[i][2];
		// T는 A의 공간으로 변환된 상태이므로
		// T의 각 성분의 크기는 boxA의 축에 투영한 길이와 같음
		if (fabsf(T[i]) > rA + rB) return false;
	}

	//Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++)
	{
		rA = eA[0] * AbsR[0][i] + eA[1] * AbsR[1][i] + eA[2] * AbsR[2][i];
		rB = eB[i];
		// rfrombtoa를 역으로 곱해주는 효과
		// boxB의 축으로 투영 하는 것이므로 inv를 곱해주는 것과 같은 효과..
		if (fabsf(T[0] * RfromBToA[0][i] + T[1] * RfromBToA[1][i]) + T[2] * RfromBToA[2][i])
			return false;
	}

	//Test axis L = A0 x B0
	rA = eA[1] * AbsR[2][0] + eA[2] * AbsR[1][0];
	rB = eB[1] * AbsR[0][2] + eB[2] * AbsR[0][1];
	if (fabsf(T[2] * RfromBToA[1][0] - T[1] * RfromBToA[2][0] > rA + rB)) return false;

	//Test axis L = A0 x B1
	rA = eA[1] * AbsR[2][1] + eA[2] * AbsR[1][1];
	rB = eB[0] * AbsR[0][2] + eB[2] * AbsR[0][0];
	if (fabsf(T[2] * RfromBToA[1][1] - T[1] * RfromBToA[2][1] > rA + rB)) return false;

	//Test axis L = A0 x B2
	rA = eA[1] * AbsR[2][2] + eA[2] * AbsR[1][2];
	rB = eB[0] * AbsR[0][1] + eB[1] * AbsR[0][0];
	if (fabsf(T[2] * RfromBToA[1][2] - T[1] * RfromBToA[2][2] > rA + rB)) return false;

	//Test axis L = A1 x B0
	rA = eA[0] * AbsR[2][0] + eA[2] * AbsR[0][0];
	rB = eB[1] * AbsR[1][2] + eB[2] * AbsR[1][1];
	if (fabsf(T[0] * RfromBToA[2][0] - T[2] * RfromBToA[0][0] > rA + rB)) return false;
	
	//Test axis L = A1 x B1
	rA = eA[0] * AbsR[2][1] + eA[2] * AbsR[0][1];
	rB = eB[0] * AbsR[1][2] + eB[2] * AbsR[1][0];
	if (fabsf(T[0] * RfromBToA[2][1] - T[2] * RfromBToA[0][1] > rA + rB)) return false;

	//Test axis L = A1 x B2
	rA = eA[0] * AbsR[2][2] + eA[2] * AbsR[0][2];
	rB = eB[0] * AbsR[1][1] + eB[1] * AbsR[1][0];
	if (fabsf(T[0] * RfromBToA[2][2] - T[2] * RfromBToA[0][2] > rA + rB)) return false;

	//Test axis L = A2 x B0
	rA = eA[0] * AbsR[1][0] + eA[1] * AbsR[0][0];
	rB = eB[1] * AbsR[2][2] + eB[2] * AbsR[2][1];
	if (fabsf(T[1] * RfromBToA[0][0] - T[0] * RfromBToA[1][0] > rA + rB)) return false;

	//Test axis L = A2 x B1
	rA = eA[0] * AbsR[1][1] + eA[1] * AbsR[0][1];
	rB = eB[0] * AbsR[2][2] + eB[2] * AbsR[2][0];
	if (fabsf(T[1] * RfromBToA[0][1] - T[0] * RfromBToA[1][1] > rA + rB)) return false;

	//Test axis L = A2 x B2
	rA = eA[0] * AbsR[1][2] + eA[1] * AbsR[0][2];
	rB = eB[0] * AbsR[2][1] + eB[1] * AbsR[2][0];
	if (fabsf(T[1] * RfromBToA[0][2] - T[0] * RfromBToA[1][2] > rA + rB)) return false;

	boxA->SetCollider(boxB);
	boxA->SetCollision(true);
	
	boxB->SetCollider(boxA);
	boxB->SetCollision(true);

	return true;


}

bool CollisionController::DetecCollisioin(BoxCollider * boxA, SphereCollider * sphereB)
{

	return false;
}

void CollisionController::RemoveCollider()
{
	/*for (auto box : boxList)
	{
		if(box->GetRemove())
			
	}*/


}

//void CollisionController::DetectCollision()
//{
//	for (auto box : boxList)
//	{
//
//	}
//
//	for (auto sphere : SphereList)
//	{
//
//	}
//
//	for (auto box : boxList)
//	{
//		for (auto spehre : SphereList)
//		{
//
//		}
//	}
//
//}


CollisionController::CollisionController()
{
}

CollisionController::~CollisionController()
{
}
