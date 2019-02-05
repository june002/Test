#include "stdafx.h"
#include "TestAnimator.h"
#include "Fbx/FbxLoader.h"
#include "Components/Player.h"
#include "Components/Zombie.h"


void TestAnimator::Initialize()
{
	FbxLoader* loader = NULL;
	vector<wstring> clipList;

	/*loader = new FbxLoader
	(
	Assets + L"Zombie/Mesh.fbx",
	Models + L"Zombie/", L"warZombie"
	);

	loader->ExportMaterial();
	loader->ExportMesh();
	loader->ExportAnimation(0);

	loader->GetClipList(&clipList);
	SAFE_DELETE(loader);*/

	/*loader = new FbxLoader
	(
		Assets + L"Swat/death.fbx",
		Models + L"Swat/", L"death"
	);
	loader->ExportAnimation(0);
	SAFE_DELETE(loader);*/


	
	/*loader = new FbxLoader
	(
		Assets + L"Weapon/rifle_.fbx",
		Models + L"Weapon/", L"rifle_"
	);
	loader->ExportMaterial();
	loader->ExportMesh();
	SAFE_DELETE(loader);*/

	/*loader = new FbxLoader
	(
		Assets + L"Swat/walk_forward.fbx",
		Models + L"Swat/", L"walk_forward"
	);
	loader->ExportAnimation(0);

	loader = new FbxLoader
	(
		Assets + L"Swat/walk_left.fbx",
		Models + L"Swat/", L"walk_left"
	);
	loader->ExportAnimation(0);

	loader = new FbxLoader
	(
		Assets + L"Swat/walk_right.fbx",
		Models + L"Swat/", L"walk_right"
	);
	loader->ExportAnimation(0);

	loader = new FbxLoader
	(
		Assets + L"Swat/walk_backward.fbx",
		Models + L"Swat/", L"walk_backward"
	);
	loader->ExportAnimation(0);

	loader = new FbxLoader
	(
		Assets + L"Swat/run_forward.fbx",
		Models + L"Swat/", L"run_forward"
	);
	loader->ExportAnimation(0);

	loader = new FbxLoader
	(
		Assets + L"Swat/run_backward.fbx",
		Models + L"Swat/", L"run_backward"
	);
	loader->ExportAnimation(0);*/

	SAFE_DELETE(loader);

	swat = new Player();
	zombie = new Zombie();

}

void TestAnimator::Ready()
{
	swat->Ready();
	swat->GetAnimator()->Position(-5.0f, 0.0f, -5.0f);
	zombie->Ready();
	//zombie->GetAnimator()->Position(5.0f, 0.0f, 5.0f);

}

void TestAnimator::Destroy()
{

}

void TestAnimator::Update()
{
	test = CollisionController::Get()->DetectCollision();

	swat->Update();
	//rifle->UpdateWorld();
	//rifle->update
	zombie->Update();

}

void TestAnimator::PreRender()
{

}

void TestAnimator::Render()
{
	swat->Render();
	zombie->Render();


	ImGui::Checkbox("collision", &test);
}