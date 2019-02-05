#include "Framework.h"
#include "BoxCollider.h"
#include "./Boundings/BBox_OBB.h"


BoxCollider::BoxCollider(IGameObject* object)
	: Collider(object)
{
	CollisionController::Get()->RegisterCollider(this);
	Initialize();
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Initialize()
{
	// debugLine 데이터 입력 - 충돌처리와는 관련 없음..
	vector<D3DXVECTOR3> points;

	D3DXVECTOR3 min = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	//D3DXVECTOR3 max = position + scale * 0.5f;
	D3DXVECTOR3 width = D3DXVECTOR3(1.0f, 0, 0);
	D3DXVECTOR3 height = D3DXVECTOR3(0, 1.0f, 0);
	D3DXVECTOR3 depth = D3DXVECTOR3(0, 0, 1.0f);

	//bottom
	points.push_back(min);
	points.push_back(min + depth);
	points.push_back(min + depth + width);
	points.push_back(min + width);
		 
	//top
	points.push_back(min + height);
	points.push_back(min + height + depth);
	points.push_back(min + height + depth + width);
	points.push_back(min + height + width);

	debugingLine = new BBox_OBB(points.data());

}

void BoxCollider::Render()
{


	vector<D3DXVECTOR3> points;
	D3DXVECTOR3 width = D3DXVECTOR3(1.0f, 0, 0);
	D3DXVECTOR3 height = D3DXVECTOR3(0, 1.0f, 0);
	D3DXVECTOR3 depth = D3DXVECTOR3(0, 0, 1.0f);

	//bottom
	points.push_back(center - width*0.5f);
	points.push_back(min + depth);
	points.push_back(min + depth + width);
	points.push_back(min + width);

	//top
	points.push_back(min + height);
	points.push_back(min + height + depth);
	points.push_back(min + height + depth + width);
	points.push_back(min + height + width);

	Collider::Render();
	debugingLine->RenderLine(world);

	

	
}

void BoxCollider::UpdateBoundary()
{
	// 공간 변환
	/*for (auto point : points)
		D3DXVec3TransformCoord(&point, &point, &world);*/

}
