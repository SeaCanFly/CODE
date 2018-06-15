////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"

#include<fstream>
#include<stdio.h>
#include<iostream>
#include <string>
using namespace std;
int scene;
ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Timer = 0;
	m_Fps = 0;
	m_ShaderManager = 0;
	m_TextureManager = 0;
	m_Zone = 0;
	m_Zone1 = 0;
	scene = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;


	// Create the input object.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		//MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		printf("Could not initialize the input object");
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture manager object.
	m_TextureManager = new TextureManagerClass;
	if(!m_TextureManager)
	{
		return false;
	}

	// Initialize the texture manager object.
	ifstream ftexture("Engine/data/texture_manager.txt");
	if (!ftexture.is_open())return false;
	string curline;
	int i = 0;
	getline(ftexture, curline);	
	result = m_TextureManager->Initialize(stoi(curline));
	printf("[%d] texture_manager initialize done\n",stoi(curline));
	while (getline(ftexture, curline))
	{
		result=m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(),  const_cast<char*>(curline.c_str()), i);
		
		
		if (!result)
		{
			cout << curline << " load failed" << endl;
			return false;
		}
		cout << curline << " load successed" << endl;
		i++;
	}
	
	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the zone object.
	m_Zone = new ZoneClass;
	if(!m_Zone)
	{
		return false;
	}

	// Initialize the zone object.
	result = m_Zone->Initialize(m_TextureManager, m_Direct3D, hwnd, screenWidth, screenHeight, SCREEN_DEPTH);
	if(!result)
	{
		printf("m_Zone Initialize failed\n");
		return false;
	}
	printf("m_Zone Initialize done\n");
		m_Zone1 = new ZoneClass1;
	if(!m_Zone1)
	{
		return false;
	}

	// Initialize the zone object.
	result = m_Zone1->Initialize(m_TextureManager,m_Direct3D, hwnd, screenWidth, screenHeight, SCREEN_DEPTH);
	if(!result)
	{
		printf("m_Zone1 Initialize failed\n");
		return false;
	}
	printf("m_Zone1 Initialize done\n");
	return true;
}


void ApplicationClass::Shutdown()
{
	if (m_Zone1)
	{
		m_Zone1->Shutdown();
		delete m_Zone1;
		m_Zone1 = 0;
	}
	// Release the zone object.
	if(m_Zone)
	{
		m_Zone->Shutdown();
		delete m_Zone;
		m_Zone = 0;
	}
	
	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the texture manager object.
	if(m_TextureManager)
	{
		m_TextureManager->Shutdown();
		delete m_TextureManager;
		m_TextureManager = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	// Update the system stats.
	m_Fps->Frame();
	m_Timer->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the zone frame processing.
	if (scene == 0)
	{
		result = m_Zone->Frame(m_Direct3D, m_Input, m_ShaderManager, m_TextureManager, m_Timer->GetTime(), m_Fps->GetFps());
		if (!result)
		{
			printf("zone run failed\n");
			return false;
		}
	}
	if (scene == 1)
	{
		result = m_Zone1->Frame(m_Direct3D, m_Input, m_ShaderManager, m_TextureManager, m_Timer->GetTime(), m_Fps->GetFps());
		if (!result)
		{
			printf("zone1 run failed\n");
			return false;
		}
	}
	return result;
}