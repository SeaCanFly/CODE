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
	
	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void Render();
	void GetViewMatrix(D3DXMATRIX&);
	D3DXVECTOR3 camLookat, camDefaultLookat;	
	D3DXMATRIX m_viewMatrix;
	D3DXVECTOR3 m_position;
	D3DXMATRIX rotationMatrix;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float ws, ad,qe;
	float yaw, pitch, roll;
	D3DXVECTOR3 camForward,DefaultForward;
	D3DXVECTOR3 camRight,DefaultRight;
	D3DXVECTOR3 camUpward, DefaultUpward;
private:
	//float m_positionX, m_positionY, m_positionZ;



};
#endif