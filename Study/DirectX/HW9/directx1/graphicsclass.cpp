#include "graphicsclass.h"
extern int key;
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_SphereModel = 0;
	m_Pyramid = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_tank = 0;
	m_phone = 0;
	m_plane = 0;
	m_house = 0;
	m_Bitmap = 0;
	m_Text = 0;
	polynumber = 0;
	objnumber = 0;
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
{
}
bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
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
	// Set the position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
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
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
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
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
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
		//obj[objnumber]->SetPosition(-5.0f+objnumber*2.0f, 2.0f, 10.0f);
		objnumber++;
	}
	
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}
	//// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "Engine/data/2.txt", L"Engine/data/0.dds");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//m_SphereModel = new ModelClass;
	//if (!m_SphereModel)return false;
	//result = m_SphereModel->Initialize(m_D3D->GetDevice(), "Engine/data/sphere.txt", L"Engine/data/t1.dds");
	//m_SphereModel->SetPosition(2.0f, 2.0f, 2.0f);

	//m_Pyramid = new ModelClass;
	//if (!m_Pyramid)return false;
	//result = m_Pyramid->Initialize(m_D3D->GetDevice(), "Engine/data/1.txt", L"Engine/data/1.dds");

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


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,L"Engine/data/back.jpg", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
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
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
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
	if (m_tank)
	{
		m_tank->Shutdown();
		delete m_tank;
		m_tank = 0;
	}
	if (m_house)
	{
		m_house->Shutdown();
		delete m_house;
		m_house = 0;
	}
	if (m_phone)
	{
		m_phone->Shutdown();
		delete m_phone;
		m_phone = 0;
	}
	if (m_plane)
	{
		m_plane->Shutdown();
		delete m_plane;
		m_plane = 0;
	}
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	if (m_SphereModel)
	{
		m_SphereModel->Shutdown();
		delete m_SphereModel;
		m_SphereModel = 0;
	}
	if (m_Pyramid)
	{
		m_Pyramid->Shutdown();
		delete m_Pyramid;
		m_Pyramid = 0;
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
bool GraphicsClass::Frame(float rotX, float rotY, float rotZ,float ws,float ad,float qe,float frametime)
{
	bool result;
	static float rotation = 0.0f;
	//m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetMove(ws, ad,qe);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI *0.001f*frametime;
	//rotation += rotation*frametime;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	result = Render(rotation);
		if (!result)
		{
			return false;
		}
	return true;
}
bool GraphicsClass::Render(float rotation)
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

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}
	// Render the bitmap with the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
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
	bool flag = 0;
	if (!polynumber)flag = 1;
//	if (key == 1)
	{
		for (int i = 0; i < objnumber; i++)
		{
			if (obj[i]!=nullptr)
			{
				m_Camera->GetViewMatrix(viewMatrix);
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
					if(flag)polynumber += (unsigned long)(obj[i]->loader->LoadedIndices.max_size())/3;
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
	}
	//if (key == 0)
	//{

	//


	//	m_D3D->GetWorldMatrix(worldMatrix);
	//	D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);
	//	//D3DXMatrixRotationZ(&worldMatrix, rotation);
	//	m_Pyramid->Render(m_D3D->GetDeviceContext());
	//	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Pyramid->GetIndexCount(), worldMatrix,
	//		viewMatrix, projectionMatrix, m_Pyramid->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//	// Present the rendered scene to the screen.
	//	if (!result)
	//	{
	//		return false;
	//	}
	//	m_D3D->GetWorldMatrix(worldMatrix);
	//	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//	D3DXMatrixRotationY(&worldMatrix, rotation);
	//	//D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);
	//	//D3DXMatrixRotationX(&worldMatrix, rotation);
	//	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//	m_Model->Render(m_D3D->GetDeviceContext());
	//	// Render the model using the light shader.
	//	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
	//		viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	//	if (!result)
	//	{
	//		return false;
	//	}
	//	// Reset the world matrix.
	//	m_D3D->GetWorldMatrix(worldMatrix);
	//	// Setup the translation matrix for the sphere model.
	//	m_SphereModel->GetPosition(posX, posY, posZ);
	//	D3DXMatrixTranslation(&mo, posX, posY, posZ);
	//	//m_D3D->GetWorldMatrix(worldMatrix);
	//	D3DXMatrixRotationX(&ro, rotation);
	//	D3DXMatrixMultiply(&worldMatrix, &mo, &ro);
	//	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//	m_SphereModel->Render(m_D3D->GetDeviceContext());
	//	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix,
	//		viewMatrix, projectionMatrix, m_SphereModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//	// Present the rendered scene to the screen.
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}


	m_D3D->EndScene();
	return true;
}