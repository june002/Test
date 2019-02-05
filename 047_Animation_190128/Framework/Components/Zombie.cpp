#include "Framework.h"
#include "Zombie.h"
#include "BoxCollider.h"


Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::Ready()
{
	character = new GameAnimator
	(
		Shaders + L"046_Model.fx",
		Models + L"Zombie/warZombie.material",
		Models + L"Zombie/warZombie.mesh"
	);
	//character->AddClip(Models + L"Zombie/idle.animation");
	character->AddClip(Models + L"Zombie/attack.animation");
	character->AddClip(Models + L"Zombie/Walk.animation");
	character->Ready();
	character->Scale(0.02f, 0.02f, 0.02f);
	character->Rotation(0.0f, (float)D3DX_PI*-0.5, 0.0f);

	// colliders
	collider_Body = new BoxCollider(this);
	collider_Body->Position(D3DXVECTOR3(-8.1f, 90.0f, -24.5f));
	collider_Body->Scale(D3DXVECTOR3(78.6f, 181.9f, 68.0f));
	collider_Body->SetTag(L"Enemy");

	collider_LeftHand = new BoxCollider(this);
	collider_LeftHand->Position(D3DXVECTOR3(73.77f, 139.344f, -24.590f));
	collider_LeftHand->Scale(D3DXVECTOR3(39.35f, 34.450f, 34.45f));
	collider_LeftHand->SetTag(L"Enemy");

	collider_RightHand = new BoxCollider(this);
	collider_RightHand->Position(D3DXVECTOR3(-90.164f, 122.951f, -5.0f));
	collider_RightHand->Scale(D3DXVECTOR3(34.4f, 29.517f, 29.517f));
	collider_RightHand->SetTag(L"Enemy");


}

void Zombie::Update()
{
	character->Update();

	D3DXMATRIX w0, w1;
	character->World(&w0);

	//collider_body
	{
		collider_Body->SetParentWorld(w0);
	}
	//collider_rightHand , LeftHand
	{
		int boneIndex = character->GetModel()->BoneByName(L"RightHand")->Index();
		w1 = character->GetRenderTransform(boneIndex);
		collider_RightHand->SetParentWorld(w1*w0);
	}
	{
		int boneIndex = character->GetModel()->BoneByName(L"LeftHand")->Index();
		w1 = character->GetRenderTransform(boneIndex);
		collider_LeftHand->SetParentWorld(w1*w0);
	}

}

void Zombie::Render()
{
	character->Render();
	collider_Body->Render();
	collider_RightHand->Render();
	collider_LeftHand->Render();
}

void Zombie::SetClipState()
{
}
