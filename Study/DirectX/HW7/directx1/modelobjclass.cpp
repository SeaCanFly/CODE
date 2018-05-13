#pragma once
#include "modelobjclass.h"
#include "stringtowchar.h"
ModelObjClass::ModelObjClass()
{
	//m_Texture = 0;

}
ModelObjClass::ModelObjClass(const ModelObjClass& other)
{
}
ModelObjClass::~ModelObjClass()
{
	if(loader)
	delete loader;
	loader = 0;
}
bool ModelObjClass::Initialize(ID3D11Device* device, char* modelFilename,WCHAR* textureFilename)
{
	bool result;
	// Load in the model data,
	loader = new Loader;
	result=loader->LoadFile(modelFilename);
	if (!result)return false;
	for (int i = 0; i < (int)loader->LoadedMeshes.size(); i++)
	{
		loader->LoadedMeshes[i].m_vertexCount = loader->LoadedMeshes[i].Vertices.size();
		loader->LoadedMeshes[i].m_indexCount = loader->LoadedMeshes[i].Indices.size();
		InitializeBuffers(device, &(loader->LoadedMeshes[i]));
	}
	for (int i = 0; i < loader->LoadedMeshes.size(); i++)
	{
		if (loader->LoadedMeshes[i].MeshMaterial.map_Ka != "")
		{
			WCHAR* dtexture = stringToWchar(loader->LoadedMeshes[i].MeshMaterial.map_Ka);
			result = loader->LoadedMeshes[i].LoadTexture(device, dtexture);
			if (!result)
			{
				return false;
			}
		}
		else
		{
			result = loader->LoadedMeshes[i].LoadTexture(device, textureFilename);
			if (!result)
			{
				return false;
			}
		}
	}
	return true;
}
void ModelObjClass::Shutdown()
{
	for (int i = 0; i < (int)loader->LoadedMeshes.size(); i++)
	{
		
		loader->LoadedMeshes[i].Shutdown();
	}

	return;
}
bool ModelObjClass::InitializeBuffers(ID3D11Device* device,Mesh* curMesh)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
	// Create the vertex array.
	vertices = new VertexType[curMesh->m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[curMesh->m_indexCount];
	if (!indices)
	{
		return false;
	}
	// Load the vertex array and index array with data.
	for (i = 0; i < curMesh->m_vertexCount; i++)
	{

		vertices[i].position = D3DXVECTOR3(curMesh->Vertices[i].Position.X, curMesh->Vertices[i].Position.Y, curMesh->Vertices[i].Position.Z);
		vertices[i].texture = D3DXVECTOR2(curMesh->Vertices[i].TextureCoordinate.X,curMesh->Vertices[i].TextureCoordinate.Y);
		vertices[i].normal = D3DXVECTOR3(curMesh->Vertices[i].Normal.X,curMesh->Vertices[i].Normal.Y,curMesh->Vertices[i].Normal.Z);
	}
	for (i = 0; i < curMesh->m_indexCount; i++)
	{
		indices[i] = curMesh->Indices[i];
	}
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (curMesh->m_vertexCount);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(curMesh->m_vertexBuffer));
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (curMesh->m_indexCount);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(curMesh->m_indexBuffer));
	if (FAILED(result))
	{
		return false;
	}
	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
	return true;
}


void ModelObjClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}
void ModelObjClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}