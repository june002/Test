#pragma once
#include "Components/Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(class IGameObject* object);
	~SphereCollider();

	virtual void Initialize() override;
	virtual void Render() override;

private:
	struct BSphere bounding;

};
