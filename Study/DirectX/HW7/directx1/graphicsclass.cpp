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
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
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
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
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
	// Create the model object.
	m_tank = new ModelObjClass;
	if (!m_tank)return false;
	result=m_tank->Initialize(m_D3D->GetDevice(), "Engine/data/tank.obj");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
		return false;
	}

	m_phone = new ModelObjClass;
	if (!m_phone)return false;
	result=m_phone->Initialize(m_D3D->GetDevice(), "Engine/data/ea.obj");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
		return false;
	}

	m_house = new ModelObjClass;
	if (!m_house)return false;
	result=m_house->Initialize(m_D3D->GetDevice(), "Engine/data/house.obj");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
		return false;
	}

	m_plane = new ModelObjClass;
	if (!m_plane)return false;
	result = m_plane->Initialize(m_D3D->GetDevice(), "Engine/data/plane.obj",L"Engine/data/A6M_ZERO_D.bmp");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the OBJ", L"Error", MB_OK);
		return false;
	}

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "Engine/data/2.txt", L"Engine/data/0.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_SphereModel = new ModelClass;
	if (!m_SphereModel)return false;
	result = m_SphereModel->Initialize(m_D3D->GetDevice(), "Engine/data/sphere.txt", L"Engine/data/t1.dds");
	m_SphereModel->SetPosition(2.0f, 2.0f, 2.0f);

	m_Pyramid = new ModelClass;
	if (!m_Pyramid)return false;
	result = m_Pyramid->Initialize(m_D3D->GetDevice(), "Engine/data/1.txt", L"Engine/data/1.dds");

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
	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetDirection(1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(50.0f);
	return true;
}
void GraphicsClass::Shutdown()
{
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
	if (m_tank)
	{
		m_tank->Shutdown();
		delete m_tank;
		m_tank = 0;
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
bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	// Render the graphics scene.
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
	if (key == 1)
	{
		//m_Camera->SetPosition(0.0f, 0.0f, -50.0f);
		//m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetWorldMatrix(worldMatrix);
		posX = 0.0f;
		posY = -1.0f;
		posZ = -3.0f;
		D3DXMatrixTranslation(&mo, posX, posY, posZ);
		D3DXMatrixRotationY(&ro, rotation);
		D3DXMatrixScaling(&so, 0.05f, 0.05f, 0.05f);
		worldMatrix = so*mo*ro;;
		for (int i = 0; i < (int)m_tank->loader->LoadedMeshes.size(); i++)
		{
			m_tank->loader->LoadedMeshes[i].Render(m_D3D->GetDeviceContext());
			objl::Mesh curMesh = m_tank->loader->LoadedMeshes[i];
		
			/*D3DXVECTOR4 ka = D3DXVECTOR4(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1.0f);
			D3DXVECTOR4 kd = D3DXVECTOR4(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1.0f);
			D3DXVECTOR4 ks = D3DXVECTOR4(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1.0f);*/
			if (curMesh.m_dtexture != nullptr)
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, curMesh.m_dtexture, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}
			else
			{
				result = m_LightShader->ObjRender(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}

		}

		m_D3D->GetWorldMatrix(worldMatrix);
		posX = 3.0f;
		posY = 1.0f;
		posZ = -1.0f;
		D3DXMatrixTranslation(&mo, posX, posY, posZ);
		D3DXMatrixRotationY(&ro, -rotation);
		D3DXMatrixScaling(&so, 0.2f, 0.2f, 0.2f);
		worldMatrix = so*mo*ro;
		for (int i = 0; i < (int)m_plane->loader->LoadedMeshes.size(); i++)
		{
			m_plane->loader->LoadedMeshes[i].Render(m_D3D->GetDeviceContext());
			objl::Mesh M = m_plane->loader->LoadedMeshes[i];
		/*	D3DXVECTOR4 ka = D3DXVECTOR4(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1.0f);
			D3DXVECTOR4 kd = D3DXVECTOR4(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1.0f);
			D3DXVECTOR4 ks = D3DXVECTOR4(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1.0f);*/
			if (M.m_dtexture != nullptr)
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), M.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, M.m_dtexture, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}
			else
			{
				result = m_LightShader->ObjRender(m_D3D->GetDeviceContext(), M.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}

		}
	
		m_D3D->GetWorldMatrix(worldMatrix);
		posX = -5.0f;
		posY = -5.0f;
		posZ = 10.0f;
		D3DXMatrixTranslation(&mo, posX, posY, posZ);
		D3DXMatrixRotationY(&ro, rotation);
		D3DXMatrixScaling(&so, 0.5f, 0.5f, 0.5f);
		worldMatrix = so*ro*mo;
		for (int i = 0; i < (int)m_house->loader->LoadedMeshes.size(); i++)
		{
			m_house->loader->LoadedMeshes[i].Render(m_D3D->GetDeviceContext());
			objl::Mesh curMesh = m_house->loader->LoadedMeshes[i];
			/*D3DXVECTOR4 ka = D3DXVECTOR4(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1.0f);
			D3DXVECTOR4 kd = D3DXVECTOR4(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1.0f);
			D3DXVECTOR4 ks = D3DXVECTOR4(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1.0f);*/
			if (curMesh.m_dtexture != nullptr)
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, curMesh.m_dtexture, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}
			else
			{
				result = m_LightShader->ObjRender(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}

		}

		m_D3D->GetWorldMatrix(worldMatrix);
		posX = 2.0f;
		posY = 2.0f;
		posZ = 2.0f;
		D3DXMatrixTranslation(&mo, posX, posY, posZ);
		D3DXMatrixRotationYawPitchRoll(&ro, rotation-60.0f, rotation, rotation);
		D3DXMatrixScaling(&so, 1.0f, 1.0f, 1.0f);
		worldMatrix = so*ro*mo;
		for (int i = 0; i < (int)m_phone->loader->LoadedMeshes.size(); i++)
		{
			m_phone->loader->LoadedMeshes[i].Render(m_D3D->GetDeviceContext());
			objl::Mesh curMesh = m_phone->loader->LoadedMeshes[i];
			/*D3DXVECTOR4 ka = D3DXVECTOR4(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1.0f);
			D3DXVECTOR4 kd = D3DXVECTOR4(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1.0f);
			D3DXVECTOR4 ks = D3DXVECTOR4(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1.0f);*/
			if (curMesh.m_dtexture != nullptr)
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, curMesh.m_dtexture, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}
			else
			{
				result = m_LightShader->ObjRender(m_D3D->GetDeviceContext(), curMesh.m_indexCount, worldMatrix,
					viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result)
				{
					return false;
				}
			}

		}
	}
	if (key == 0)
	{

	


		m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);
		//D3DXMatrixRotationZ(&worldMatrix, rotation);
		m_Pyramid->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Pyramid->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Pyramid->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		// Present the rendered scene to the screen.
		if (!result)
		{
			return false;
		}
		m_D3D->GetWorldMatrix(worldMatrix);
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, rotation);
		//D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);
		//D3DXMatrixRotationX(&worldMatrix, rotation);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Model->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
		// Setup the translation matrix for the sphere model.
		m_SphereModel->GetPosition(posX, posY, posZ);
		D3DXMatrixTranslation(&mo, posX, posY, posZ);
		//m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixRotationX(&ro, rotation);
		D3DXMatrixMultiply(&worldMatrix, &mo, &ro);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_SphereModel->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_SphereModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		// Present the rendered scene to the screen.
		if (!result)
		{
			return false;
		}
	}
	

	m_D3D->EndScene();
	return true;
}