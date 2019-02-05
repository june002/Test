#include "framework.h"
#include <array>
#include "InputController.h"

InputController* InputController::instance = nullptr;

InputController * InputController::Get()
{
	assert(instance != nullptr);

	return instance;
}

void InputController::Create()
{
	assert(instance == nullptr);
	instance = new InputController();
	instance->Initialize();
}

void InputController::Delete()
{
	SAFE_DELETE(instance);
}

void InputController::AddControlKey(wstring name, DWORD key1, KeyType feature1, DWORD key2, KeyType feature2, float sensitivity)
{
	KeyList list;
	ZeroMemory(&list, list.size()* sizeof(key));
	float amount = 0.0f;

	if (feature1 == KeyType::NONE) amount = 0.0f;
	else if (feature1 == KeyType::POSITIVE) amount = sensitivity;
	else amount = -sensitivity;
	
	list[0] =  make_pair(key1, amount);

	if (key2 != NULL)
	{
		if (feature2 == KeyType::NONE) amount = 0.0f;
		else if (feature2 == KeyType::POSITIVE) amount = sensitivity;
		else amount = -sensitivity;
		
		list[1] = make_pair(key2, amount);
	}
	
	Keys[name] = list;

	// 비트 연산으로 개선하기
	InputList[name] = InputType::Key;
}

void InputController::AddContorlButton(wstring name, MouseType mouseKey, float sensitivity)
{
	float amount = sensitivity;

	if (mouseKey == MouseType::WHEELMOVE_X || mouseKey == MouseType::WHEELMOVE_Y)
		amount = 0.0f;

	Buttons[name] = make_pair(mouseKey, amount);

	InputList[name] = InputType::Mouse;
}

float InputController::GetAxis(wstring name)
{

	InputType type = InputList[name];

	//if (type == NULL) return 0.0f;
	if (type == InputType::Key)
	{
		for (auto key : Keys[name])
		{
			if (Keyboard::Get()->Press(key.first) == false) continue;
			//OutputDebugString(L"")
			return key.second;
		}

		return 0.0f;
	}
	else if (type == InputType::Mouse)
	{
		if (Buttons[name].first == MouseType::BUTTON_LEFT ||
			Buttons[name].first == MouseType::BUTTON_RIGHT)
		{
			if (Mouse::Get()->Down(Buttons[name].first))
				return Buttons[name].second;
		}
		else
		{
			D3DXVECTOR3 wheelMove = Mouse::Get()->GetMoveValue();

			if (Buttons[name].first == MouseType::WHEELMOVE_X)
				return wheelMove.x;
			else
				return wheelMove.y;
		}
	}

	return 0.0f;
}

bool InputController::GetButton(wstring name)
{
	if (Mouse::Get()->Down(Buttons[name].first)) return true;

	return false;
}

bool InputController::GetKey(wstring name)
{
	for (auto key : Keys[name])
	{
		if (Keyboard::Get()->Press(key.first))
			return true;
	}

	return false;
}

InputController::InputController()
{
	
}

InputController::~InputController()
{
}

void InputController::Initialize()
{
	// 기본키 추가
	AddControlKey(L"Horizontal", 'A', KeyType::NEGATIVE, 'D', KeyType::POSITIVE);
	AddControlKey(L"Vertical", 'S', KeyType::NEGATIVE, 'W', KeyType::POSITIVE);
	AddControlKey(L"Walk", VK_LCONTROL, KeyType::NONE);
	AddControlKey(L"Run", VK_LSHIFT, KeyType::NONE);
	AddControlKey(L"Rotate", 'R', KeyType::NONE);


	// 마우스 추가
	AddContorlButton(L"Fire1", MouseType::BUTTON_LEFT);
	AddContorlButton(L"Aim", MouseType::BUTTON_RIGHT);
	AddContorlButton(L"MouseX", MouseType::WHEELMOVE_X);
	AddContorlButton(L"MouseY", MouseType::WHEELMOVE_Y);



}
