#pragma once

class GameRender
{
public:
	GameRender();
	virtual ~GameRender();

	void World(D3DXMATRIX* mat);
	void World(D3DXMATRIX& mat);

	void Position(float x, float y, float z);
	void Position(D3DXVECTOR3& vec);
	void Position(D3DXVECTOR3* vec);

	void Scale(float x, float y, float z);
	void Scale(D3DXVECTOR3& vec);
	void Scale(D3DXVECTOR3* vec);

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	void Rotation(D3DXVECTOR3* vec);

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	void RotationDegree(D3DXVECTOR3* vec);

	void Forward(D3DXVECTOR3* vec);
	void Up(D3DXVECTOR3* vec);
	void Right(D3DXVECTOR3* vec);

	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	bool GetUpdateWorld() { return bUpdateWorld; }
	void SetUpdateWorld(bool update) { bUpdateWorld = update; }

	virtual void UpdateWorld();

protected:
	D3DXMATRIX world;

	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;

	D3DXVECTOR3 forward;
	D3DXVECTOR3 up;
	D3DXVECTOR3 right;
	// �߰�
	bool bUpdateWorld;
};