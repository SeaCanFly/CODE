////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "zoneclass1.h"

extern int scene;
ZoneClass1::ZoneClass1()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_SkyDome = 0;
	m_Terrain = 0;
	InitializeCriticalSection(&cr);
	lock = 1;
	objnumber = 0;
}


ZoneClass1::ZoneClass1(const ZoneClass1& other)
{
}


ZoneClass1::~ZoneClass1()
{
	DeleteCriticalSection(&cr);
}


bool ZoneClass1::Initialize(TextureManagerClass* TextureManager,D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;
	screenW = screenWidth;
	screenH = screenHeight;
	tm = TextureManager;
	D3D = Direct3D;
	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if(!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth,"Engine/data/minimap/minimap1.tga","Engine/data/minimap/point.tga");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(50.0f);
	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(512.5f, 10.0f, 10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if(!m_Frustum)
	{
		return false;
	}

	// Initialize the frustum object.
	m_Frustum->Initialize(screenDepth);

	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if(!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(Direct3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new TerrainClass1;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "Engine/data/setup1.txt");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}
	printf("m_Terrain Initialize done\n");
	
	ifstream fobj("Engine/data/obj_manager1.txt");
	if (!fobj.is_open())return false;
	string curline;
	objnumber = 0;
	while (getline(fobj,curline))
	{
		if (curline == "")continue;
		m_obj[objnumber] = new ModelObjClass;
		if (!m_obj[objnumber])return false;
		result = m_obj[objnumber]->Initialize(TextureManager, Direct3D->GetDevice(),Direct3D->GetDeviceContext(), const_cast<char*>(curline.c_str()));
		if (!result)
		{
			//MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
			cout << curline << " load failed\n" << endl;
			return false;
		}
		cout << curline << " load successed\n" << endl;
		float x, y, z,dx,dy,dz,rx,ry,rz,sx,sy,sz,t;
		getline(fobj, curline);
		sscanf(curline.c_str(), "%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f",&t, &x, &y, &z,&dx,&dy,&dz,&rx,&ry,&rz,&sx,&sy,&sz);
		printf("[%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f]\n",t, x, y, z,dx,dy,dz,rx,ry,rz,sx,sy,sz);
		m_obj[objnumber]->SetTransform(t,x, y, z, dx, dy, dz, rx, ry, rz,sx,sy,sz);
		objnumber++;
	}
	// Set the UI to display by default.
	m_displayUI = true;

	// Set wire frame rendering initially to disabled.
	m_wireFrame = false;

	// Set the rendering of cell lines initially to disabled.
	m_cellLines = false;

	// Set the user locked to the terrain height for movement.
	m_heightLocked = true;

	return true;
}

//unsigned long __stdcall ZoneClass1::initobj1(void* p)
//{
//	ZoneClass1* cs = (ZoneClass1*)p;
//	printf("objfile1 loading...\n");
//	ifstream fobj1("Engine/data/obj_manager1.txt");
//	if (!fobj1.is_open())
//	{
//		printf("objfile1 open failed\n");
//		return -1;
//	}
//	string curline;
//	bool result;
//	while (getline(fobj1, curline))
//	{
//		//EnterCriticalSection(&cs->cr);
//		cs->m_obj[cs->objnumber] = new ModelObjClass();
//		if (!cs->m_obj[cs->objnumber])return false;
//		result = cs->m_obj[cs->objnumber]->Initialize(cs->tm, cs->D3D->GetDevice(), cs->D3D->GetDeviceContext(), const_cast<char*>(curline.c_str()));
//		if (!result)
//		{
//			cout << curline << " load failed\n" << endl;
//			return -1;
//		}
//		cout << curline << " load successed\n" << endl;
//		float x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz;
//		int t;
//		getline(fobj1, curline);
//		sscanf(curline.c_str(), "%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f", &t, &x, &y, &z, &dx, &dy, &dz, &rx, &ry, &rz, &sx, &sy, &sz);
//		printf("[%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f]\n", t, x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz);
//		cs->m_obj[cs->objnumber]->SetTransform(t, x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz);
//		cs->objnumber++;
//		//LeaveCriticalSection(&cs->cr);
//	}
//	fobj1.close();
//	cs->lock = 1;
//	printf("objflie1 load done\n");
//}
void ZoneClass1::Shutdown()
{
		for (int i = 0; i < objnumber; i++)
	{
		if (m_obj[i])
		{
			m_obj[i]->Shutdown();
			delete m_obj[i];
			m_obj[i] = 0;
		}
	}
	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the sky dome object.
	if(m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the frustum object.
	if(m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if(m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}


bool ZoneClass1::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager, 
					  float frameTime, int fps)
{
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;


	// Do the frame input processing.
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ,1.0f,1);
	if(!result)
	{
		return false;
	}

	// Do the terrain frame processing.
	m_Terrain->Frame();

	// If the height is locked to the terrain then position the camera on top of it.
	if(m_heightLocked)
	{
		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_Terrain->GetHeightAtPosition(posX, posZ, height);
		if(foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by one meter.
			m_Position->SetPosition(posX, height + 1.0f, posZ);
			m_Camera->SetPosition(posX, height + 1.0f, posZ);
		}
	}

	// Render the graphics.
	result = Render(Direct3D, ShaderManager, TextureManager,frameTime);
	if(!result)
	{
		return false;
	}

	return true;
}


void ZoneClass1::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->MoveForward(keyDown,1.0f);

	keyDown = Input->IsDownPressed();
	m_Position->MoveBackward(keyDown,1.0f);

	keyDown = Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	/*if (Input->IsLPressed())
	{
		if (lock == 1)
		{
			lock = 0;
			void* init_obj;
			init_obj = CreateThread(0, 0, initobj1, (void*)this, 0, 0);
			CloseHandle(init_obj);
		}
	}*/
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	if((600<=(int)posX)&&(607>=(int)posX)&&(9==(int)posY)&& (385==(int)posZ))
	{
		printf("Go to scene 0\n");
		scene = 0;
	}
	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if(Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if(Input->IsF2Toggled())
	{
		m_wireFrame = !m_wireFrame;
	}

	// Determine if we should render the lines around each terrain cell.
	if(Input->IsF3Toggled())
	{
		m_cellLines = !m_cellLines;
	}

	// Determine if we should be locked to the terrain height when we move around or not.
	if(Input->IsF4Toggled())
	{
		m_heightLocked = !m_heightLocked;
	}

	return;
}


bool ZoneClass1::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager,float frametime)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	int i;
	static float rotation = 0.0f;
	static float t = 0.0f;
	t += frametime;
	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f*frametime;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);
	
	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();
	
	// Construct the frustum.
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Turn off back face culling and turn off the Z buffer.
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderSkyDomeShader(Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, 
												projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	// Turn the Z buffer back and back face culling on.
	Direct3D->TurnZBufferOn();
	Direct3D->TurnOnCulling();
	
	// Turn on wire frame rendering of the terrain if needed.
	if(m_wireFrame)
	{
		Direct3D->EnableWireframe();
	}

	// Render the terrain cells (and cell lines if needed).
	for(i=0; i<m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDeviceContext(), i, m_Frustum);
		if(result)
		{
			// Render the cell buffers using the hgih quality terrain shader.
			result = ShaderManager->RenderTerrainShader1(Direct3D->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix,
														projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
														TextureManager->GetTexture(2), TextureManager->GetTexture(3),
														m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if(!result)
			{
				return false;
			}

			// If needed then render the bounding box around this terrain cell using the color shader. 
			if(m_cellLines)
			{
				m_Terrain->RenderCellLines(Direct3D->GetDeviceContext(), i);
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellLinesIndexCount(i), worldMatrix, 
												 viewMatrix, projectionMatrix);
				if(!result)
				{
					return false;
				}
			}
		}
	}
	
	// Turn off wire frame rendering of the terrain if it was on.
	if(m_wireFrame)
	{
		Direct3D->DisableWireframe();  
	}
	XMMATRIX mo,ro, so;
	for (int i = 0; i < objnumber; i++)
	{
		if (m_obj[i] != nullptr)
		{
			m_Camera->GetViewMatrix(viewMatrix);
			float x = m_obj[i]->m_positionX + (m_obj[i]->m_dx);
			float y = m_obj[i]->m_positionY + (m_obj[i]->m_dy);
			float z = m_obj[i]->m_positionZ + (m_obj[i]->m_dz);
			m_obj[i]->SetPosition(x, y, z);
			mo = XMMatrixTranslation(x, y, z);
			ro = XMMatrixRotationRollPitchYaw(m_obj[i]->m_rx*rotation, m_obj[i]->m_ry*rotation, m_obj[i]->m_rz*rotation);
			so = XMMatrixScaling(m_obj[i]->m_sx, m_obj[i]->m_sy, m_obj[i]->m_sz);
			worldMatrix =so*ro*mo;
			for (int j = 0; j < (int)m_obj[i]->loader->LoadedMeshes.size(); j++)
			{
				m_obj[i]->loader->LoadedMeshes[j].Render(Direct3D->GetDeviceContext());
				XMFLOAT4 ka = XMFLOAT4(m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ka.X, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ka.Y, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ka.Z, 1.0f);
				XMFLOAT4 kd = XMFLOAT4(m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Kd.X, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Kd.Y, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Kd.Z, 1.0f);
				XMFLOAT4 ks = XMFLOAT4(m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ks.X, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ks.Y, m_obj[i]->loader->LoadedMeshes[j].MeshMaterial.Ks.Z, 1.0f);
				if (m_obj[i]->loader->LoadedMeshes[j].m_textureCount != -1)
				{
					result = ShaderManager->Light(Direct3D->GetDeviceContext(), m_obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
						viewMatrix, projectionMatrix, TextureManager->GetTexture(m_obj[i]->loader->LoadedMeshes[j].m_textureCount), 
						m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
						m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			
					if (!result)
					{
						printf("render obj error(!=-1)\n");
						return false;
					}
				}
				else
				{
					printf("no texture\n");
					result = ShaderManager->Light(Direct3D->GetDeviceContext(), m_obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
						viewMatrix, projectionMatrix, TextureManager->GetTexture(4),
						m_Light->GetDirection(), ka,kd, m_Camera->GetPosition(),
						ks, m_Light->GetSpecularPower());
					/*result = ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
						viewMatrix, projectionMatrix);*/
			
				if (!result)
				{
					printf("render obj error(=-1)\n");
				return false;
				}
				}
			}
			Direct3D->GetWorldMatrix(worldMatrix);
		}
	}
	// Update the render counts in the UI.
	result = m_UserInterface->UpdateRenderCounts(Direct3D->GetDeviceContext(), m_Terrain->GetRenderCount(), m_Terrain->GetCellsDrawn(), 
												 m_Terrain->GetCellsCulled());
	if(!result)
	{
		return false;
	}

	// Render the user interface.
	if(m_displayUI)
	{
		result = m_UserInterface->Render(Direct3D, ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix,screenW,screenH);
		if(!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}