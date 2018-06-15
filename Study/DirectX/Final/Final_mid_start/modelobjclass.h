
#ifndef _MODELOBJCLASS_H_
#define _MODELOBJCLASS_H_
#pragma once
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
//#include "textureclass.h"
#include"OBJ_Loader.h"
using namespace objl;
class ModelObjClass
{
public:
	ModelObjClass();
	ModelObjClass(const ModelObjClass&);
	~ModelObjClass();
	bool Initialize(TextureManagerClass*,ID3D11Device*,ID3D11DeviceContext*, char*,char* textureFilename=nullptr);
	void Shutdown();
	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);
	void SetTransform(int t_type,float px, float py,float pz,float dx,float dy,float dz,float rx,float ry,float rz,float sx,float sy,float sz);
	Loader* loader;
private:
	bool InitializeBuffers(ID3D11Device*,Mesh*);
public:
	float t;
	int type;
	char path[512] = { 0 };
	float m_positionX, m_positionY, m_positionZ;
	float m_dx, m_dy, m_dz;
	float m_rx, m_ry, m_rz;
	float m_sx, m_sy, m_sz;
};
#endif