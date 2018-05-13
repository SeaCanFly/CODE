#pragma once
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_
//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();
	void SetPosition(float, float, float);
	void SetMove(float, float,float);
	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void Render();
	void GetViewMatrix(D3DXMATRIX&);
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float ws, ad,qe;
	D3DXMATRIX m_viewMatrix;
	D3DXVECTOR3 camForward,DefaultForward;
	D3DXVECTOR3 camRight,DefaultRight;
	D3DXVECTOR3 camUpward, DefaultUpward;
};
#endif