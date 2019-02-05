#include "Framework.h"
#include "Collider.h"
#include "IGameObject.h"

// 부모설정 다시
Collider::Collider(class IGameObject* object)
	: position(0,0,0), rotation(0,0,0), scale(1.0f,1.0f,1.0f)
	, bVisible(true), bActive(true), bRemove(false), bCollision(false),//parentIndex(parentIndex), 
	 bUpdateWorld(true)
	
{
	D3DXMatrixIdentity(&world);

	if (object->GetAnimator() == nullptr)
	{
		
	}

}

Collider::~Collider()
{
}

void Collider::Update()
{
	UpdateBoundary();

	
}

void Collider::Render()
{
	// debugLine -> boxCollider로 
	/*string Label = "Collision";

	ImGui::Checkbox(Label.c_str(), &bCollision);*/

	// imgui collider 조정
	/*string Label;
	Label = "Visible";
	ImGui::Checkbox(Label.c_str(), &bVisible);

	Label = "Position";
	ImGui::SliderFloat3(Label.c_str(), (float*)position, -500.0f, 500.0f);

	Label = "Rad";
	ImGui::SliderFloat3(Label.c_str(), (float*)rad, 0.01f, 300.0f);*/


}

void Collider::SetParentWorld(D3DXMATRIX mat)
{
	parentWorld = mat;
	UpdateWorld();
}

void Collider::Position(D3DXVECTOR3 & pos)
{
	position = pos;
	UpdateWorld();
}

void Collider::Rotation(D3DXVECTOR3 & rot)
{
	rotation = rot;
	UpdateWorld();
}

void Collider::Scale(D3DXVECTOR3 & scl)
{
	scale = scl;
	UpdateWorld();
}

bool Collider::OnCollision(Collider * col)
{
	col = collider;
	return bCollision;
}

void Collider::UpdateBoundary()
{
}

void Collider::UpdateWorld()
{
	if (bUpdateWorld)
	{
		D3DXMATRIX S, R, T;
		D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
		D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		world = S * R * T  * parentWorld;
	}
	
	//world = parentWorld;
}
