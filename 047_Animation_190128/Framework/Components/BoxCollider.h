#pragma once
#include "Components/Collider.h"

// obb
class BoxCollider : public Collider
{
public:
	friend class CollisionController;

public:
	BoxCollider(class IGameObject* object);
	~BoxCollider();

	virtual void Initialize() override;
	virtual void Render() override;

	//BBox_OBB* GetDebug() { return debugingLine; }
private:
	virtual void UpdateBoundary() override;

	// normal구하는 함수
	//void Get


private:
	//D3DXVECTOR3 axis[3];
	struct BBox_OBB* debugingLine;
	D3DXVECTOR3 center;
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
	D3DXVECTOR3 rad;

	// Collider을(를) 통해 상속됨
	

};