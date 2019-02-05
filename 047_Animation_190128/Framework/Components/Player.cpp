#include "Framework.h"
#include "Player.h"
#include "BoxCollider.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Ready()
{
	//character
	character = new GameAnimator
		(Shaders + L"046_Model.fx",
		Models + L"Swat/Swat.material",
		Models + L"Swat/Swat.mesh");

	character->AddClip(Models + L"Swat/idle.animation");
	character->AddClip(Models + L"Swat/walk_forward.animation");
	character->AddClip(Models + L"Swat/run_forward.animation");
	character->AddClip(Models + L"Swat/death.animation");

	character->Ready();

	//character->SetUpdateWorld(true);
	character->Scale(0.02f, 0.02f, 0.02f);
	character->Rotation(0.0f, (float)D3DX_PI, 0.0f);

	// weapon
	/*r_material = new Material(Shaders + L"015_Mesh.fx");
	r_material->SetDiffuseMap(Textures + L"Red.png");
	rifle = new MeshCube(r_material, 0.1f, 0.5f, 2.5f);*/

	//// swat_rightHand
	//int boneIndex = GetModel()->BoneByName(L"swat:RightHand")->Index();
	//D3DXMATRIX world = GetRenderTransform(boneIndex);

	//D3DXMATRIX w = boneTransforms[boneIndex];
	//D3DXMATRIX world;
	//rifle->Matrix(&world);

	

	rifle = new GameModel
	(
	Shaders + L"046_Model.fx",
	Models + L"Weapon/rifle_.material",
	Models + L"Weapon/rifle_.mesh"
	);
	rifle->Ready();
	rifle->SetUpdateWorld(false);

	/*rifle->Rotation(0.0f, (float)D3DX_PI*0.5, 0.0f);
	offset = D3DXVECTOR3(0, 0, 0);
	tempRot = D3DXVECTOR3(0, 0, 0);*/
	//rifle->Position(15.0f, 0.0f, 0.0f);

	//rifle->Scale(0.1f, 0.1f, 0.1f);

	//collider
	collider_Character = new BoxCollider(this);
	{
		collider_Character->Position(D3DXVECTOR3(-5.0f, 90.164f, 0.0f));
		collider_Character->Scale(D3DXVECTOR3(44.0f, 162.0f, 54.16f));
		collider_Character->SetTag(L"Player");

		D3DXMATRIX cworld;
		character->World(&cworld);
		collider_Character->SetParentWorld(cworld);
	}
}

void Player::Update()
{
	SetClipState();
	UINT clip = character->GetCurrentClip();

	float moveSpeed(0.0f);
	if (clip == State::Walk) moveSpeed = walkSpeed;
	else if (clip == State::Run) moveSpeed = runSpeed;

	//rotation
	if (InputController::Get()->GetKey(L"Rotate"))
	{
		float rotationY = InputController::Get()->GetAxis(L"MouseX") * rotSpeed * Time::Delta();
		D3DXVECTOR3 rotation;
		character->Rotation(&rotation);
		rotation.y += rotationY;
		character->Rotation(rotation);
	}

	// move
	{
		D3DXVECTOR3 move(0, 0, 0);
		move.x = InputController::Get()->GetAxis(L"Horizontal");
		move.z = InputController::Get()->GetAxis(L"Vertical");

		D3DXVECTOR3 position, forward, right;
		character->Position(&position);
		character->Forward(&forward);
		character->Right(&right);
		position += (forward * -move.z + right * -move.x) * moveSpeed * Time::Delta();

		character->Position(position);
		character->Update();
	}
	
	// Rifle
	{
		// Rifle의 부모는 swat:RightHand
		int boneIndex = character->GetModel()->BoneByName(L"swat:RightHand")->Index();

		D3DXMATRIX s;
		D3DXMatrixScaling(&s, 80.0f, 80.0f, 80.0f);

		D3DXMATRIX r;
		//D3DXMatrixRotationYawPitchRoll(&r, tempRot.y, tempRot.x, tempRot.z);
		D3DXMatrixRotationYawPitchRoll(&r, 5.047f, 0.103f, 1.545f);

		D3DXMATRIX t;
		//D3DXMatrixTranslation(&p, offset.x, offset.y, offset.z);
		D3DXMatrixTranslation(&t, -83.607f, 221.311f, 63.934f);

		D3DXMATRIX cworld;
		character->World(&cworld);
		//D3DXMATRIX w = character->GetBoneTransform(boneIndex) * cworld;
		D3DXMATRIX w = s*r *t* (character->GetRenderTransform(boneIndex) * cworld);

		rifle->World(w);
		rifle->Update();
	}
	
	//collider
	{
		D3DXMATRIX cworld;
		character->World(&cworld);
		collider_Character->SetParentWorld(cworld);
	}



}

void Player::Render()
{
	character->Render();
	rifle->Render();

	if (collider_Character->GetVisible())
		collider_Character->Render();


	/*D3DXVECTOR3 position, scale, rotation;

	string Label;
	Label = "rot1";
	ImGui::SliderFloat3(Label.c_str(), (float*)rot1, -10.0f, 10.0f);

	Label = "Position";
	ImGui::SliderFloat3(Label.c_str(), (float*)offset, -300.0f, 300.0f);

	Label = "Rotation";
	ImGui::SliderFloat3(Label.c_str(), (float*)tempRot, (float)(-D3DX_PI * 2), (float)(D3DX_PI * 2));*/

	


	



}

void Player::Hitted()
{
	Collider* col;
	if (collider_Character->OnCollision(col) == false) return;

	if (col->GetTag() != collider_Character->GetTag())
		clipState = State::Death;

	character->SetCurrentClip(clipState);

}

void Player::SetClipState()
{
	if (clipState == State::Death) return;

	if (InputController::Get()->GetKey(L"Walk")) clipState = State::Walk;
	else if (InputController::Get()->GetKey(L"Run")) clipState = State::Run;
	else clipState = State::Idle;

	character->SetCurrentClip(clipState);

}
