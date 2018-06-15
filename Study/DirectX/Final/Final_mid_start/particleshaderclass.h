////////////////////////////////////////////////////////////////////////////////
// Filename: particleshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLESHADERCLASS_H_
#define _PARTICLESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>
using namespace std;
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: ParticleShaderClass
////////////////////////////////////////////////////////////////////////////////
class ParticleShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ParticleShaderClass();
	ParticleShaderClass(const ParticleShaderClass&);
	~ParticleShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
};

#endif