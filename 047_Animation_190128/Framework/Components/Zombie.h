#pragma once

class Zombie : public IGameObject
{
public:
	Zombie();
	~Zombie();

	void Ready();
	void Update() override;
	void Render() override;

	void SetClipState();
private:
	//class GameAnimator* character;
	class BoxCollider* collider_RightHand;
	class BoxCollider* collider_LeftHand;
	class BoxCollider* collider_Body;

	enum State : UINT
	{
		Idle = 0,
		Walk = 1,
		Run = 2,
		Aim = 3
	};

private:
	//State clipState;
	const float walkSpeed = 10.0f;
	const float runSpeed = 20.0f;
};

