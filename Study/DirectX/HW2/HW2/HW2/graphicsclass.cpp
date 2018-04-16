#pragma once
#include "graphicsclass.h"

bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(255.0f, 255.0f, 0.0f, 1.0f);
	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	return true;
}

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}
GraphicsClass::GraphicsClass(const GraphicsClass & other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,SCREEN_DEPTH, SCREEN_NEAR);
	m_D3D->SaveVideoCardInfo();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}
	return true;
}

void GraphicsClass::Shutdown()
{
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}
