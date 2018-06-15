////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "zoneclass.h"

extern int scene;
ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_SkyDome = 0;
	m_Terrain = 0;
	speed = 1.0f;
	lock = 1;
	rlock = 1;
	objnumber = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	InitializeCriticalSection(&cr_se);
	getcount = 1;
	init_state= 0;
	direction = 1;
}


ZoneClass::ZoneClass(const ZoneClass& other)
{
}


ZoneClass::~ZoneClass()
{
	DeleteCriticalSection(&cr_se);
}


bool ZoneClass::Initialize(TextureManagerClass* TextureManager,D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
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
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth,"Engine/data/minimap/minimap.tga","Engine/data/minimap/point.tga");
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

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(Direct3D->GetDevice(),Direct3D->GetDeviceContext(),"Engine/data/textures/star.tga");
	if (!result)
	{
		return false;
	}

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
	m_Position->SetPosition(512.5f, 30.0f, 10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if(!m_Frustum)
	{
		return false;
	}

	// Initialize the frustum object.
	m_Frustum->Initialize(screenDepth);
	printf("m_Frustum Initialize done\n");
	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if(!m_SkyDome)
	{
		printf("m_Terrain Initialize failed\n");
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(Direct3D->GetDevice());
	if(!result)
	{
		printf("m_SkyDome Initialize done\n");
		return false;
	}
	printf("m_SkyDome Initialize done\n");
	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "Engine/data/setup.txt");
	if(!result)
	{
		printf("m_Terrain Initialize failed\n");
		return false;
	}
	printf("m_Terrain Initialize done\n");
	void* init_obj;
	init_obj = CreateThread(0, 0, initobj, (void*)this, 0, 0);
	CloseHandle(init_obj);
	//ifstream fobj("Engine/data/obj_manager.txt");
	//if (!fobj.is_open())return false;
	//string curline;
	//objnumber = 0;
	//while (getline(fobj,curline))
	//{
	//	m_obj[objnumber] = new ModelObjClass;
	//	if (!m_obj[objnumber])return false;
	//	result = m_obj[objnumber]->Initialize(TextureManager, Direct3D->GetDevice(),Direct3D->GetDeviceContext(), const_cast<char*>(curline.c_str()));
	//	if (!result)
	//	{
	//		//MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
	//		cout << curline << " load failed\n" << endl;
	//		return false;
	//	}
	//	cout << curline << " load successed\n" << endl;
	//	float x, y, z,dx,dy,dz,rx,ry,rz,sx,sy,sz;
	//	getline(fobj, curline);
	//	sscanf(curline.c_str(), "%f %f %f/%f %f %f/%f %f %f/%f %f %f", &x, &y, &z,&dx,&dy,&dz,&rx,&ry,&rz,&sx,&sy,&sz);
	//	printf("[%f %f %f/%f %f %f/%f %f %f/%f %f %f]\n", x, y, z,dx,dy,dz,rx,ry,rz,sx,sy,sz);
	//	m_obj[objnumber]->SetTransform(x, y, z, dx, dy, dz, rx, ry, rz,sx,sy,sz);
	//	objnumber++;
	//}

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

unsigned long __stdcall ZoneClass::initobj(void* p)
{
	ZoneClass* cs = (ZoneClass*)p;
	printf("obj loading...\n");
	ifstream fobj("Engine/data/obj_manager.txt");
	if (!fobj.is_open())
	{
		printf("objfile open failed\n");
		return -1;
	}
	string curline;	
	bool result;
	while (getline(fobj, curline))
	{
		if (curline == "")continue;
		EnterCriticalSection(&cs->cr_se);
		cs->m_obj[cs->objnumber] = new ModelObjClass();
		if (!cs->m_obj[cs->objnumber])return false;
		result = cs->m_obj[cs->objnumber]->Initialize(cs->tm, cs->D3D->GetDevice(), cs->D3D->GetDeviceContext(), const_cast<char*>(curline.c_str()));
		if (!result)
		{
			cout << curline << " load failed\n" << endl;
			return -1;
		}
		cout << curline << " load successed\n" << endl;
		float x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz;
		int t;
		getline(fobj, curline);
		sscanf(curline.c_str(), "%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f", &t,&x, &y, &z, &dx, &dy, &dz, &rx, &ry, &rz, &sx, &sy, &sz);
		printf("[%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f]\n",t, x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz);
		cs->m_obj[cs->objnumber]->SetTransform(t,x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz);
		cs->objnumber++;
		LeaveCriticalSection(&cs->cr_se);
	}
	fobj.close();
	cs->init_state = 1;
	printf("objflie load done\n");
}

void ZoneClass::Shutdown()
{
	if(m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if(m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}
	// Release the terrain object.
	for (int i = 0; i < objnumber; i++)
	{
		if (m_obj[i])
		{
			m_obj[i]->Shutdown();
			delete m_obj[i];
			m_obj[i] = 0;
		}
	}
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


bool ZoneClass::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager, 
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
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ,speed,getcount);
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
	// Run the frame processing for the particle system.
	m_ParticleSystem->Frame(frameTime, Direct3D->GetDeviceContext());
	// Render the graphics.
	result = Render(Direct3D, ShaderManager, TextureManager,frameTime);
	if(!result)
	{
		return false;
	}

	return true;
}

unsigned long __stdcall ZoneClass::create(void* p)
{
	ZoneClass* cs = (ZoneClass*)p;
	
	printf("instance...\n");
	bool result;	
	EnterCriticalSection(&cs->cr_se);	
	int t = cs->getcount-1;
	printf("%d select\n", t);
	ifstream fo("Engine/data/obj_manager.txt");
	if (!fo.is_open())
	{
		printf("objfile open failed\n");
		return -1;
	}
	string curline;
	
	while (t)
	{
		getline(fo, curline);
		getline(fo, curline);
		t--;
	}
	getline(fo, curline);

	cs->m_obj[cs->objnumber] = new ModelObjClass;
	if (!cs->m_obj[cs->objnumber])return -1;
	result = cs->m_obj[cs->objnumber]->Initialize(cs->tm, cs->D3D->GetDevice(), cs->D3D->GetDeviceContext(),const_cast<char*>(curline.c_str()));
	if (!result)
	{	
		cout << " load failed\n" << endl;
		return -1;
	}
	float x, y, z, dx, dy, dz, rx, ry, rz, sx, sy, sz;
	int ty;
	getline(fo, curline);
	sscanf(curline.c_str(), "%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f",&ty, &x, &y, &z, &dx, &dy, &dz, &rx, &ry, &rz, &sx, &sy, &sz);
	printf("Create:[%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f]\n",ty, cs->posX, cs->posY, cs->posZ, dx, dy, dz, rx, ry, rz, sx, sy, sz);
	cs->m_obj[cs->objnumber]->SetTransform(ty,cs->posX, cs->posY, cs->posZ, dx, dy, dz, rx, ry, rz, sx, sy, sz);
	cs->objnumber++;
	fo.close();	
	cs->rlock = 1;
	LeaveCriticalSection(&cs->cr_se);
	printf("instance done\n");
}
void ZoneClass::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mx, my;
	
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->MoveForward(keyDown,speed);

	keyDown = Input->IsDownPressed();
	m_Position->MoveBackward(keyDown,speed);

	keyDown = Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	if (Input->Is1Pressed())
	{
		getcount = 1;
	}
	else if (Input->Is2Pressed())
	{
		getcount = 2;
	}
		else if (Input->Is3Pressed())
	{
		getcount = 3;
	}
		else if (Input->Is4Pressed())
	{
		getcount = 4;
	}
		else if (Input->Is5Pressed())
	{
		getcount = 5;
	}
		else if (Input->Is6Pressed())
	{
		getcount = 6;
	}
		else if (Input->Is7Pressed())
	{
		getcount = 7;
	}
		else if (Input->Is8Pressed())
	{
		getcount = 8;
	}
		else if (Input->Is9Pressed())
	{
		getcount = 9;
	}
	if (Input->IsSPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					m_obj[i]->t = 0;
					m_obj[i]->m_dx = 1.0f*direction;
				}
			}
		}
	}
	else if(Input->IsDPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					m_obj[i]->t = 0;
					m_obj[i]->m_dy = 1.0f;
				}
			}
		}
	}
	else if(Input->IsFPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					m_obj[i]->t = 0;
					m_obj[i]->m_dz = 1.0f;
				}
			}
		}
	}
	else if(Input->IsGPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					
					m_obj[i]->m_sx += 0.01f;
					m_obj[i]->m_sy += 0.01f;
					m_obj[i]->m_sz += 0.01f;
				}
			}
		}
	}
	else if(Input->IsHPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
			
					m_obj[i]->m_sx -= 0.01f;
					m_obj[i]->m_sy -= 0.01f;
					m_obj[i]->m_sz -= 0.01f;
				}
			}
		}
	}
	else if (Input->IsTPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					m_obj[i]->t = 0;
					m_obj[i]->m_dx = 0.0f;
					m_obj[i]->m_dy = 0.0f;
					m_obj[i]->m_dz = 0.0f;
					m_obj[i]->m_rx = 0.0f;
					m_obj[i]->m_ry = 0.0f;
					m_obj[i]->m_rz = 0.0f;	
				}
			}
		}	
	}
	else if(Input->IsWPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					if(m_obj[i]->m_dx<0)
						m_obj[i]->m_dx=-m_obj[i]->m_dx;
					if(m_obj[i]->m_dy<0)
						m_obj[i]->m_dy=-m_obj[i]->m_dy;
					if(m_obj[i]->m_dz<0)
						m_obj[i]->m_dz=-m_obj[i]->m_dz;
				}
			}
		}
	}
	else if(Input->IsEPressed())
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (m_obj[i])
			{
				if (m_obj[i]->type == getcount)
				{
					if (m_obj[i]->m_dx>0)
						m_obj[i]->m_dx = -m_obj[i]->m_dx;
					if (m_obj[i]->m_dy>0)
						m_obj[i]->m_dy = -m_obj[i]->m_dy;
					if (m_obj[i]->m_dz>0)
						m_obj[i]->m_dz = -m_obj[i]->m_dz;
				}
			}
		}
	}
	else if(Input->IsRPressed())
	{
		if (lock == 1)
		{
			lock = 0;	
			printf("saving...\n");
			//ofstream fsave;
			//fsave.open("Engine/data/obj_manager.txt",ios::app);
			FILE* fs;
			fs = fopen("Engine/data/obj_manager.txt", "w");
			if (!fs)
			{
				printf("objfile open failed\n");

			}
			for (int i = 0; i < objnumber; i++)
			{

				if (m_obj[i])
				{
						/*fsave << m_obj[i]->path << endl;
						fsave << m_obj[i]->type << ":" << m_obj[i]->m_positionX << " " << m_obj[i]->m_positionY << " " << m_obj[i]->m_positionZ << "/" <<
							m_obj[i]->m_dx << " " << m_obj[i]->m_dy << " " << m_obj[i]->m_dz << "/" <<
							m_obj[i]->m_rx << " " << m_obj[i]->m_ry << " " << m_obj[i]->m_rz << "/" <<
							m_obj[i]->m_sx << " " << m_obj[i]->m_sy << " " << m_obj[i]->m_sz << endl;*/
						//strcat(m_obj[i]->path, "\n");
						fwrite(m_obj[i]->path, sizeof(char), strlen(m_obj[i]->path), fs);
						char temp[1024] = { 0 };
						sprintf(temp, "\n%d:%f %f %f/%f %f %f/%f %f %f/%f %f %f\n",
							m_obj[i]->type, m_obj[i]->m_positionX, m_obj[i]->m_positionY, m_obj[i]->m_positionZ,
							m_obj[i]->m_dx, m_obj[i]->m_dy, m_obj[i]->m_dz,
							m_obj[i]->m_rx, m_obj[i]->m_ry, m_obj[i]->m_rz,
							m_obj[i]->m_sx, m_obj[i]->m_sy, m_obj[i]->m_sz);
						fwrite(temp, sizeof(char), strlen(temp), fs);					
					}
			}
			fclose(fs);
			//fsave.close();		
		}		
		printf("saved\n");
		lock = 1;
	}
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	
	if((702<=(int)posX)&&(705>=(int)posX)&&(11==(int)posY)&& (387==(int)posZ))
	{
		printf("Go to scene 1\n");
		scene = 1;
	}
	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	

	if (keyDown=Input->IsJPressed())
	{
		speed += 1.0f;
		printf("speed:%f\n", speed);
	}
	if(keyDown=Input->IsKPressed())
	{
		speed -= 1.0f;
		printf("speed:%f\n", speed);	
	}
	if (Input->IsRightMouseButtonDown())
	{
		if (rlock)
		{
			rlock = 0;
			void* t;
			this->posX = posX;
			this->posY = posY;
			this->posZ = posZ;
			this->rotY = rotY;
			t = CreateThread(0, 0, create, (void*)this, 0, 0);
			CloseHandle(t);
		}
	}
	if (Input->IsLeftMouseButtonDown())
	{
		Input->GetMouseLocation(mx, my);
		printf("[%d %d]\n", mx, my);
		if (mx > screenW - 154 && mx < screenW)
		{
			if (my < 32 && my>0)
			{
				speed += 1.0f;

			}
			else if (my > 32 && my < 64)
			{
				speed -= 1.0f;
			}
		}
	}
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


bool ZoneClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager,float frametime)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	int i;
	static float rotation = 0.0f;
	
	
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
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix,
														projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
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
	//if (init_state)
	//{
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
				worldMatrix = so*ro*mo;
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
						result = ShaderManager->Light(Direct3D->GetDeviceContext(), m_obj[i]->loader->LoadedMeshes[j].m_indexCount, worldMatrix,
							viewMatrix, projectionMatrix, TextureManager->GetTexture(4),
							m_Light->GetDirection(), ka, kd, m_Camera->GetPosition(),
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
	//}

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

			// Turn on alpha blending.
	Direct3D->EnableAlphaBlending();
	Direct3D->GetWorldMatrix(worldMatrix);
	mo = XMMatrixTranslation(704.0f, 12.0f, 388.0f);

	so = XMMatrixScaling(2.0f, 2.0f, 2.0f);
	worldMatrix = so*mo;
	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(Direct3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(Direct3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					  m_ParticleSystem->GetTexture());
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending.
	Direct3D->DisableAlphaBlending();
	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}