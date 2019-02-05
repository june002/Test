#pragma once
#include "GameRender.h"



class GameAnimator : public GameModel
{
public:
	GameAnimator(wstring shaderFile, wstring matFile, wstring meshFile);
	~GameAnimator();

	void AddClip(wstring clipFile);

	virtual void Update();
	virtual void Render();

	void SetCurrentClip(UINT index) { currentClip = index; }
	UINT GetCurrentClip() { return currentClip; }

private:
	void UpdateWorld() override;
	void UpdateTransforms() override;

private:
	UINT currentClip;
	int currentKeyframe;
	int nextKeyframe;

	float frameTime;
	float frameFactor;

	vector<class ModelClip *> clips;

	
};