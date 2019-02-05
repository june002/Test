#pragma once
#include "framework.h"
#include "../Draw/ILine.h"
#include "../Draw/DebugLine.h"

struct BBox_OBB : public ILine
{
	BBox_OBB(D3DXVECTOR3* pointArr, int size = 8)
	{
		assert(size == 8);
		for (int i = 0; i < size; i++)
			points[i] = pointArr[i];

		line = new DebugLine();
	}
	
	void RenderLine(D3DXMATRIX& world)
	{
		

		line->Draw(world, this);
		line->Render();
	}


	void GetLine(D3DXMATRIX & world, vector<D3DXVECTOR3>& lines)
	{
		D3DXVECTOR3 temp[8];

		for (int i = 0; i < 8; i++)
			D3DXVec3TransformCoord(&temp[i], &points[i], &world);

		//bottom
		lines.push_back(temp[0]);
		lines.push_back(temp[1]);
		lines.push_back(temp[1]);
		lines.push_back(temp[2]);
		lines.push_back(temp[2]);
		lines.push_back(temp[3]);
		lines.push_back(temp[3]);
		lines.push_back(temp[0]);

		//top
		lines.push_back(temp[4]);
		lines.push_back(temp[5]);
		lines.push_back(temp[5]);
		lines.push_back(temp[6]);
		lines.push_back(temp[6]);
		lines.push_back(temp[7]);
		lines.push_back(temp[7]);
		lines.push_back(temp[4]);

		//middle
		lines.push_back(temp[0]);
		lines.push_back(temp[4]);
		lines.push_back(temp[1]);
		lines.push_back(temp[5]);
		lines.push_back(temp[2]);
		lines.push_back(temp[6]);
		lines.push_back(temp[3]);
		lines.push_back(temp[7]);
	}



	D3DXVECTOR3 points[8];
	DebugLine* line;
	// ILine을(를) 통해 상속됨
};