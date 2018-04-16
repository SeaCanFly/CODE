#include "graphicsclass.h"
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_SphereModel = 0;
	m_Pyramid = 0;
	m_LightShader = 0;
	m_Light = 0;
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
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "Engine/data/2.txt", L"Engine/data/seafloor.dds");
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
	m_Light->SetDiffuseColor(0.7f, 0.4f, 0.3f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
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
	rotation += (float)D3DX_PI * 0.02f;
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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,ro,mo;
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

	D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);
	//D3DXMatrixRotationZ(&worldMatrix, rotation);
	m_Pyramid->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Pyramid->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_Pyramid->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
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
		viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

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
		viewMatrix, projectionMatrix, m_SphereModel->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	// Present the rendered scene to the screen.
		if (!result)
	{
		return false;
	}	

	

	m_D3D->EndScene();
	return true;
}