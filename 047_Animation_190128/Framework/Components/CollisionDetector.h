#pragma once

enum OBJECT_TYPE : UINT
{
	PLAYER = 0x00010000,
	ENEMY  = 0x00020000
};
enum BOUNDING_TYPE : UINT
{
	BOX_AABB = 0x00000100,
	BOX_OBB  = 0x00000200,
	SPHERE   = 0x00000300,
	PLANE    = 0x00000400
};
enum VISIBLE_ONOFF : UINT
{
	ON  = 0x00000001,
	OFF = 0x00000000
};


class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();


public:
	static void Register(class ICollision* object, OBJECT_TYPE Otype, BOUNDING_TYPE Btype, VISIBLE_ONOFF visible = ON);
	void Remove();
	void Update();
	void Render();

private:
	void CollisionDetect();
	bool AABB_AABB(void* first, void* second);
	bool AABB_OBB(void* aabb, void* obb);
	bool OBB_OBB(void* first, void* second);
	bool BOX_SPHERE(BBox* first, BSphere* second);
	bool SPHERE_SPHERE(void* first, void* second);


public:
	typedef vector<pair<pair<class ICollision*, void*>, UINT>> ObjectList;
	typedef vector<pair<pair<class ICollision*, void*>, UINT>>::iterator objectIter;
	static ObjectList objects;

private:
	class DebugLine* line;
};