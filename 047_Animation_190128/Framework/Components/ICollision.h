#pragma once

class ICollision
{
public:	
	virtual void UpdateBoundary(void* bound) = 0;
	virtual void PostCollision() = 0;

	bool GetRemove() { return isRemove; }
	void Remove() { isRemove = true; }
public:
	bool isRemove;
	//ILine* bounding;
};
