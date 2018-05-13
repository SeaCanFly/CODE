#include "systemclass.h"
extern int key;
bool SystemClass::Frame()
{
	bool result;
//	int mouseX, mouseY;
	float  rotX, rotY, rotZ,ws,ad,qe;
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();
	/*if (m_input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	if (m_input->IsKeyDown(VK_NUMPAD0))
	{
		key = 0;
	}
	if (m_input->IsKeyDown(VK_NUMPAD1))
	{
		key = 1;
	}*/
	result = m_input->Frame();
	if (!result)
	{
		return false;
	}
	//m_input->GetMouseLocation(mouseX, mouseY);
	/*result = m_graphics->Frame(mouseX, mouseY);
	if (!result)
	{
		return false;
	}*/
	// Do the frame processing for the graphics object.
	result = m_graphics->Frame(m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime());
	if (!result)
	{
		return false;
	}
	// Finally render the graphics to the screen.
	//result = m_graphics->Render();
	//if (!result)
	//{
	//	return false;
	//}
	// Do the frame input processing.
	if(m_input->IsEscapePressed() == true)
	{
		return false;
	}
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Get the view point position/rotation.
	
	m_Position->GetMove(ws, ad,qe);
	m_Position->GetRotation(rotX, rotY, rotZ);
	result = m_graphics->Frame(rotX, rotY, rotZ,ws,ad,qe,m_Timer->GetTime());
	if (!result)
	{
		return false;
	}
	return true;

}
bool SystemClass::HandleInput(float frameTime)
{
	bool keyDown;
	
	//float speed = 10.0f * frameTime;
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);
	//mouse
	if ((m_input->m_mouseState.lX != m_input->m_mouseLastState.lX) || (m_input->m_mouseState.lY != m_input->m_mouseLastState.lY))
	{
		m_Position->m_rotationY += m_input->m_mouseLastState.lX * 0.1f;

		m_Position->m_rotationX += m_input->m_mouseState.lY * 0.1f;

		m_input->m_mouseLastState = m_input->m_mouseState;
	}
	
	
		keyDown = m_input->IsLeftPressed();
		m_Position->TurnLeft(keyDown);

		keyDown = m_input->IsRightPressed();
		m_Position->TurnRight(keyDown);

		keyDown = m_input->IsUpPressed();
		m_Position->LookUpward(keyDown);

		keyDown = m_input->IsDownPressed();
		m_Position->LookDownward(keyDown);
	
	// Handle the input.
	if(m_input->IsAPressed())
	m_Position->MoveLeft();

	if(m_input->IsDPressed())
	m_Position->MoveRight();

	if(m_input->IsWPressed())
	m_Position->MoveForward();

	if(m_input->IsSPressed())
	m_Position->MoveBackward();

	if(m_input->IsQPressed())
	m_Position->MoveUpward();

	if(m_input->IsEPressed())
	m_Position->MoveDownward();

	

	return true;
}
void SystemClass::InitializeWindows(int & screenWidth, int & screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	applicationHandle = this;
	m_hinstance = GetModuleHandle(0);
	m_applicationName = L"Engine";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(0, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, 0, 0, m_hinstance, 0);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(false);
	return;
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(0, 0);
	}
	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = nullptr;
	applicationHandle = nullptr;
	return;
}

SystemClass::SystemClass()
{
	m_input = 0;
	m_graphics = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
}

SystemClass::SystemClass(const SystemClass & other)
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;
	screenHeight = 0;
	screenWidth = 0;
	InitializeWindows(screenWidth, screenHeight);
	m_input = new InputClass;
	if (!m_input)
	{
		return false;
	}
	// Initialize the input object.
	result = m_input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}
	m_graphics=new GraphicsClass;
	if (!m_graphics)
	{
		return false;
	}
	result = m_graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}
	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}
	// Initialize the fps object.
	m_Fps->Initialize();
	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}
	// Initialize the cpu object.
	m_Cpu->Initialize();
	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}
	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(0.0f, 2.0f, -10.0f);

	return true;
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;
	ZeroMemory(&msg, sizeof(MSG));
	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
		if (m_input->IsEscapePressed() == true)
		{
			done = true;
		}
	}
	return;
}

void SystemClass::Shutdown()
{
	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
	// Release the input object.
	if (m_input)
	{
		m_input->Shutdown();
		delete m_input;
		m_input = 0;
	}
	if (m_graphics)
	{
		m_graphics->Shutdown();
		delete m_graphics;
		m_graphics = nullptr;
	}
	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}
	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}
	//if (m_input)
	//{
	//	delete m_input;
	//	m_input = nullptr;
	//}
	ShutdownWindows();
	return;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	/*switch (umsg)
	{
	case WM_KEYDOWN:
	{
		m_input->KeyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP:
	{
		m_input->KeyUp((unsigned int)wparam);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}*/
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

SystemClass::~SystemClass()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return applicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}
