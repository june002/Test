#pragma once

// 템플릿 클래스
// MonoBehavior
// 지금은 GameModel(GameAnimator) + Mesh만 가능하도록
class Collider
{
public:
	Collider(class IGameObject* object);
	~Collider();

	virtual void Initialize() = 0;
	void Update();
	virtual void Render();

	void SetParentWorld(D3DXMATRIX mat); 

	void World(D3DXMATRIX mat) { world = mat; }
	D3DXMATRIX World() { return world; }
	D3DXVECTOR3 Position() { return position; }
	D3DXVECTOR3 Rotation() { return rotation; }
	D3DXVECTOR3 Scale() { return scale; }

	void Position(D3DXVECTOR3& pos); 
	void Rotation(D3DXVECTOR3& rot); 
	void Scale(D3DXVECTOR3& scl); 

	IGameObject* GetGameObject() { return object; }
	bool OnCollision(class Collider* col);

	void SetCollider(Collider* col) { collider = col; }

	wstring GetTag() { return tag; }
	void SetTag(wstring t) { tag = t; }

	bool GetActive() { return bActive; }
	void SetActive(bool active) { bActive = active; }

	bool GetRemove() { return bRemove; }
	void SetRemove(bool remove) { bRemove = remove; }

	bool GetVisible() { return bVisible; }
	void SetVisible(bool visible) { bVisible = visible; }

	bool GetCollision() { return bCollision; }
	void SetCollision(bool collision) { bCollision = collision; }

	void SetUpdateWorld(bool update) { bUpdateWorld = update; }

private:
	virtual void UpdateBoundary();
	void UpdateWorld();

protected:
	bool bRemove;
	bool bVisible;
	bool bActive;

	bool bCollision;

	class IGameObject* object;
	Collider* collider;
	// 모델 자체 인지 .. 모델에 속한 bone인지..
	//UINT parentIndex;
	wstring tag;
	

protected:
	D3DXMATRIX parentWorld;
	D3DXMATRIX world;

	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	bool bUpdateWorld;
};
