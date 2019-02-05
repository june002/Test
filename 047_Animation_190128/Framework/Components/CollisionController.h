#pragma once

class CollisionController
{
public:
	static CollisionController* Get();

	static void Create();
	static void Delete();

	void RegisterCollider(class BoxCollider* box);
	void RegisterCollider(class SphereCollider* sphere);

	bool DetectCollision();

private:
	bool DetectCollision(class BoxCollider* boxA, class BoxCollider* boxB);
	bool DetecCollisioin(class BoxCollider* boxA, class SphereCollider* sphereB);
	void RemoveCollider();


private:
	CollisionController();
	~CollisionController();

	static CollisionController* instance;

private:
	typedef vector<class BoxCollider*>  BoxColliders;
	BoxColliders boxList;

	typedef vector<class SphereCollider*> SphereColliders;
	SphereColliders SphereList;


};
