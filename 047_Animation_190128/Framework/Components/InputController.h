#pragma once

enum KeyType
{
	NONE = 0,
	POSITIVE,
	NEGATIVE
};

class InputController
{
	enum MouseType : DWORD
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT = 1,
		WHEELMOVE_X = 2,
		WHEELMOVE_Y = 3,
	};

public:
	static InputController* Get();

	static void Create();
	static void Delete();

	// � Ű�� ���� �� ������ �߰� + ������Ʈ ��� - Static
	// ����Ű�� ��� ó�� ���� ����غ��� 
	// Ű����� ���콺�� - �Լ� overloading���� �ذ�����
	void AddControlKey(wstring name, DWORD key1, KeyType feature1, DWORD key2 = NULL, KeyType feature2 = KeyType::NONE, float sensitivity = 3.0f);
	void AddContorlButton(wstring name, MouseType mouseKey, float sensitivity = 0.5f);

	float GetAxis(wstring name);
	bool GetButton(wstring name);
	bool GetKey(wstring name);


private:
	InputController();
	~InputController();

	static InputController* instance;
	void Initialize();
	
	typedef pair<DWORD, float> key;
	typedef array<key,2> KeyList;
	typedef unordered_map<wstring, KeyList> KeyMap;
	KeyMap Keys;

	typedef pair<MouseType, float> button;
	typedef unordered_map<wstring, button> MouseButtonMap;
	MouseButtonMap Buttons;

	enum InputType
	{
		Key = 0,
		Mouse
	};
	unordered_map<wstring, InputType> InputList;
};
