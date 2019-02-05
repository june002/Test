#include "Framework.h"
#include "SphereCollider.h"
#include "./Boundings/BSphere.h"

SphereCollider::SphereCollider(IGameObject* object)
	: Collider(object)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
}

void SphereCollider::Render()
{
	Collider::Render();

}
