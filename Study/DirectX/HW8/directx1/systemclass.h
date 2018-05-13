#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include"inputclass.h"
#include"graphicsclass.h"
class SystemClass
{
private:
	LPCWSTR	 m_applicationName;
	HINSTANCE m_hinstance;
	HWND	m_hwnd;
	InputClass* m_input;
	GraphicsClass* m_graphics;
	//function:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

public:
	SystemClass();
	SystemClass(const SystemClass&);
	bool Initialize();
	void Run();
	void Shutdown();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	~SystemClass();
};
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* applicationHandle = 0;
#endif // !_SYSTEMCLASS_H_
