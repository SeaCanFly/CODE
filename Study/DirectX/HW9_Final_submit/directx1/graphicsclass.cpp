#include "graphicsclass.h"
extern int key;
GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_TerrainShader = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
	m_MiniMap = 0;
	polynumber = 0;
	objnumber = 0;
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
{
}
bool GraphicsClass::Frame()
{
	bool result;
	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();


	// Set the frames per second.
	result = m_Text->SetFps(m_Fps->GetFps(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(m_Fps->GetFps(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetObjNumber(objnumber, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetPolyNumber(polynumber, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetScreenPix(m_width,m_height, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	static float rotation=0.0f;
	rotation += (float)D3DX_PI *0.001f*(m_Timer->GetTime());
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	result = RenderGraphics(rotation);
	if (!result)
	{
		return false;
	}
	return true;
}
//bool GraphicsClass::Frame(int mouseX, int mouseY)
//{
//	bool result;
//	// Set the location of the mouse.
//	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
//	if (!result)
//	{
//		return false;
//	}
//	// Set the position of the camera.
//	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
//	return true;
//}
bool GraphicsClass::Initialize(HINSTANCE hinstance,int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	float cameraX, cameraY, cameraZ;
	int terrainWidth, terrainHeight;
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	m_width = screenWidth;
	m_height = screenHeight;
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
	cameraX = 50.0f;
	cameraY = 2.0f;
	cameraZ = -7.0f;
	m_Camera->SetPosition(cameraX, cameraY, cameraZ);
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

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	
	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	ifstream fobj("obj.txt");
	if (!fobj.is_open())return false;
	string curline;
	objnumber = 0;
	while (getline(fobj,curline))
	{
		obj[objnumber] = new ModelObjClass;
		if (!obj[objnumber])return false;
		result = obj[objnumber]->Initialize(m_D3D->GetDevice(), const_cast<char*>(curline.c_str()));
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
			return false;
		}
		
		objnumber++;
	}
	
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}
	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}
	m_textureShader = new TextureShaderClass();
	result=m_textureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the textureshader.", L"Error", MB_OK);
		return false;
	}
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "Engine/data/heightmap01.bmp", L"Engine/data/dirt01.dds", "Engine/data/colorm01.bmp");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}
	m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);
	// Create the bitmap object.
	m_MiniMap = new MiniMapClass;
	if (!m_MiniMap)
	{
		return false;
	}

	// Initialize the mini map object.
	result = m_MiniMap->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1),
		(float)(terrainHeight - 1));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(0.8f, 0.8f, 0.8f, 0.8f);
	//m_Light->SetDirection(1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(50.0f);
	return true;
}
void GraphicsClass::Shutdown()
{
	// Release the bitmap object.

	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = 0;
	}
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}
	if(m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
	
	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	// Release the model object.
	for (int i = 0; i < objnumber; i++)
	{
		if (obj[i])
		{
			obj[i]->Shutdown();
			delete obj[i];
			obj[i] = nullptr;
		}
	}
	
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}
int flag = 1;
bool GraphicsClass::RenderGraphics(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,ro,mo,so;
	D3DXMATRIX orthoMatrix;
	float posX, posY, posZ;
	bool result;
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_Terrain->Render(m_D3D->GetDeviceContext());
	// Render the terrain using the terrain shader.
	result = m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	//m_D3D->TurnZBufferOn();
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	result = m_MiniMap->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_textureShader);

	if (!result)
	{
		return false;
	}
	
	
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();
	//m_D3D->TurnZBufferOff();
	bool flag = 0;
	if (!polynumber)flag = 1;
//	if (key == 1)
	
		for (int i = 0; i < objnumber; i++)
		{
			if (obj[i]!=nullptr)
			{
				//m_Camera->GetViewMatrix(viewMatrix);
				m_D3D->GetWorldMatrix(worldMatrix);
				posX = -7.0f+i*50.0f;
				posY = 2.0f;
				posZ = 10.0f;
				D3DXMatrixTranslation(&mo, posX, posY, posZ);
				D3DXMatrixRotationY(&ro, rotation);
				D3DXMatrixScaling(&so, 0.5f, 0.5f, 0.5f);
				if (i > 2)D3DXMatrixScaling(&so, 2.0f, 2.0f, 2.0f);
				if (i == 4)D3DXMatrixRotationYawPitchRoll(&ro, rotation, rotation, rotation);
				worldMatrix = so*ro*mo;;
				for (int j = 0; j < (int)obj[i]->loader->LoadedMeshes.size(); j++)
				{
					obj[i]->loader->LoadedMeshes[j].Render(m_D3D->GetDeviceContext());
					if(flag)polynumber += (unsigned int)(obj[i]->loader->LoadedMeshes[j].m_indexCount)/3;
					/*D3DXVECTOR4 ka = D3DXVECTOR4(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1.0f);
					D3DXVECTOR4 kd = D3DXVECTOR4(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1.0f);
					D3DXVECTOR4 ks = D3DXVECTOR4(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1.0f);*/
					if (obj[i]->loader->LoadedMeshes[j].m_dtexture != nullptr)
					{
						result = m_LightShader->Render(m_D3D->GetDeviceContext(), obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
							viewMatrix, projectionMatrix, obj[i]->loader->LoadedMeshes[j].m_dtexture, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
						if (!result)
						{
							return false;
						}
					}
					else
					{
						result = m_LightShader->ObjRender(m_D3D->GetDeviceContext(), obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
							viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
						if (!result)
						{
							return false;
						}
					}

				}
			}
		}
	



	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	

	// Update the location of the camera on the mini map.
	m_MiniMap->PositionUpdate(posX, posZ);

	return true;
}
