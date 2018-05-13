#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include"inputclass.h"
#include"graphicsclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "timerclass.h"
#include "positionclass.h"
class SystemClass
{
private:
	LPCWSTR	 m_applicationName;
	HINSTANCE m_hinstance;
	HWND	m_hwnd;
	InputClass* m_input;
	GraphicsClass* m_graphics;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	//function:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	bool HandleInput(float);
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
