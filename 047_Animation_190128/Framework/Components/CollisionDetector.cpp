#include "framework.h"
#include "CollisionDetector.h"
#include "ICollision.h"
#include "../Boundings/BPlane.h"
#include "../Boundings/BBox.h"
#include "../Boundings/BSphere.h"

CollisionDetector::ObjectList CollisionDetector::objects;

CollisionDetector::CollisionDetector()
{
	line = new DebugLine();
}

CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::Register(class ICollision* object, OBJECT_TYPE Otype, BOUNDING_TYPE Btype, VISIBLE_ONOFF visible)
{
	if (object == nullptr) return;

	ILine* bounding;
	switch (Btype)
	{
	case BOUNDING_TYPE::BOX_AABB:
	case BOUNDING_TYPE::BOX_OBB:
		bounding = new BBox();
		break;

	case BOUNDING_TYPE::SPHERE:
		bounding = new BSphere();
		break;

	case BOUNDING_TYPE::PLANE:
		bounding = new BDisk();
	}

	UINT collisionCode = 0x00000000;
	collisionCode = Otype | Btype | visible;

	objects.push_back(make_pair(make_pair(object, bounding), collisionCode));
}

void CollisionDetector::Remove()
{
	objectIter iter = objects.begin();
	for (iter; iter != objects.end(); )
	{
		if (iter->first.first->GetRemove())
		{
			//SAFE_DELETE(iter->first.first);
			iter = objects.erase(iter);
			//cout << "삭제" << endl;
		}

		else
			++iter;
	}

	//cout << "objectSize: " << objects.size() << endl;
}

void CollisionDetector::Update()
{
	for (auto& object : objects)
	{
		if (!object.first.first) continue;
		object.first.first->UpdateBoundary(object.first.second);
		//object.first.second & 0x00000000
	}

	CollisionDetect();

	Remove();
}

void CollisionDetector::Render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		bool check = (bool)(objects[i].second & 0x000000FF);
		if (!check) continue;
		string box = "box " + to_string(i);
		ImGui::Checkbox(box.c_str(), &check);
		objects[i].second |= 0x00000000 | (UINT)check;


		D3DXMATRIX W;
		D3DXMatrixIdentity(&W);
		ILine* temp = reinterpret_cast<ILine*>(objects[i].first.second);
		//temp->SetVisible(check);
		line->Draw(W, temp);
		line->Render();
		
	}

	ImGui::SameLine();

}

void CollisionDetector::CollisionDetect()
{
	for (int i = 0; i < objects.size()-1; i++)
	{
		UINT objType_0 = objects[i].second & 0x00FF0000;
		UINT bndType_0 = objects[i].second & 0x0000FF00;

		bool Collision = false;
		for (int j = i + 1; j < objects.size(); j++)
		{
			UINT objType_1 = objects[j].second & 0x00FF0000;
			if (objType_0 == objType_1) continue;

			UINT bndType_1 = objects[j].second & 0x0000FF00;

			
			if (bndType_0 == BOUNDING_TYPE::BOX_AABB)
			{
				if (bndType_1 == BOUNDING_TYPE::BOX_AABB)
					Collision = AABB_AABB(objects[i].first.second, objects[j].first.second);

				else if (bndType_1 == BOUNDING_TYPE::BOX_OBB)
					Collision = AABB_OBB(objects[i].first.second, objects[j].first.second);

				else if (bndType_1 == BOUNDING_TYPE::SPHERE)
				{
					BBox* First     = reinterpret_cast<BBox*>(objects[i].first.second);
					BSphere* Second = reinterpret_cast<BSphere*>(objects[j].first.second);
					Collision = BOX_SPHERE(First, Second);
				}
			}
			else if (bndType_0 == BOUNDING_TYPE::BOX_OBB)
			{
				if (bndType_1 == BOUNDING_TYPE::BOX_AABB)
					Collision = AABB_OBB(objects[j].first.second, objects[i].first.second);

				else if (bndType_1 == BOUNDING_TYPE::BOX_OBB)
					Collision = OBB_OBB(objects[i].first.second, objects[j].first.second);

				else if (bndType_1 == BOUNDING_TYPE::SPHERE)
				{
					BBox* First = reinterpret_cast<BBox*>(objects[i].first.second);
					BSphere* Second = reinterpret_cast<BSphere*>(objects[j].first.second);
					Collision = BOX_SPHERE(First, Second);
				}
			}
			else if (bndType_0 == BOUNDING_TYPE::SPHERE)
			{
				if (bndType_1 == BOUNDING_TYPE::BOX_AABB)
				{
					BBox* First = reinterpret_cast<BBox*>(objects[j].first.second);
					BSphere* Second = reinterpret_cast<BSphere*>(objects[i].first.second);
					Collision = BOX_SPHERE(First, Second);
				}
				else if (bndType_1 == BOUNDING_TYPE::BOX_OBB)
				{
					BBox* First = reinterpret_cast<BBox*>(objects[j].first.second);
					BSphere* Second = reinterpret_cast<BSphere*>(objects[i].first.second);
					Collision = BOX_SPHERE(First, Second);
				}
				else if (bndType_1 == BOUNDING_TYPE::SPHERE)
					Collision = SPHERE_SPHERE(objects[i].first.second, objects[j].first.second);
			}

			if (Collision)
			{
				objects[i].first.first->PostCollision();
				objects[j].first.first->PostCollision();
			}
		}
	}
}

bool CollisionDetector::AABB_AABB(void* first, void* second)
{
	BBox* First = reinterpret_cast<BBox*>(first);
	BBox* Second = reinterpret_cast<BBox*>(second);







	return false;
}

bool CollisionDetector::AABB_OBB(void* aabb, void* obb)
{
	BBox* AABB = reinterpret_cast<BBox*>(aabb);
	BBox* OBB = reinterpret_cast<BBox*>(obb);

	return false;
}

bool CollisionDetector::OBB_OBB(void * first, void * second)
{
	return false;
}

bool CollisionDetector::BOX_SPHERE(BBox* first, BSphere* second)
{
	vector<pair<array<D3DXVECTOR3,3>, D3DXVECTOR3>> normals;
	//first->SetBoxNormals(normals);

	D3DXVECTOR3 rayPos = second->Center;
	for (auto& normal : normals)
	{
		float U, V, Dist;
		
		bool interSect = D3DXIntersectTri(&normal.first[0], &normal.first[1], &normal.first[2], &rayPos, &(-normal.second), &U, &V, &Dist);

		if (interSect)
		{			
			if (Dist <= second->Radius)
			{
				//cout << "충돌" << endl;
				return true;

			}
		}
	}
	return false;
}

bool CollisionDetector::SPHERE_SPHERE(void * first, void * second)
{
	return false;
}

