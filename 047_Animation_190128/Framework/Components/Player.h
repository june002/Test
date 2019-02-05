#pragma once

class Player : public IGameObject
{
public:
	// 생성자 수정 필요
	Player();
	~Player();

	void Ready();
	void Update() override;
	void Render() override;

	void Hitted();
	void SetClipState();

private:

	//GameAnimator* character;
	class BoxCollider* collider_Character;

	GameModel* rifle;
	//MeshCube* rifle;
	


	D3DXVECTOR3 rot1;
	enum State : UINT
	{
		Idle = 0,
		Walk= 1,
		Run = 2,
		//Aim = 3,
		Death = 3
	};

private:
	State clipState;
	const float rotSpeed = 5.0f;
	const float walkSpeed = 1.5f;
	const float runSpeed = 5.0f;

};
