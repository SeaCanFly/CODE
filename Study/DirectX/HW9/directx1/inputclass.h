#pragma once
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <dinput.h>
class InputClass
{
private:
	//bool m_keys[256];
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	unsigned char m_keyboardState[256];

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
	
public:	
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_mouseLastState;
	InputClass();
	InputClass(const InputClass&);
	//void Initialize();
	//void KeyDown(unsigned int);
	//void KeyUp(unsigned int);
	//bool IsKeyDown(unsigned int);
	bool IsAPressed();
	bool IsDPressed();
	bool IsWPressed();
	bool IsSPressed();
	bool IsQPressed();
	bool IsEPressed();
	bool IsUpPressed();
	bool IsDownPressed();
	bool IsRightPressed();
	bool IsLeftPressed();
	~InputClass();
	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();
	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);
};
#endif // !_INPUTCLASS_H_
