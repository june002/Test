#pragma once
#include "Framework.h"

class IGameObject
{
public:
	/*IGameObject();
	~IGameObject();*/

	virtual void Ready() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	wstring GetTag() { return tag; }
	void SetTag(wstring tag) { this->tag = tag; }

	class GameAnimator* GetAnimator() { return character; }
	class GameModel* GetModel() { return model; }

protected:
	wstring tag;
	GameAnimator* character;
	GameModel* model;

};
