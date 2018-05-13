
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
	bool Initialize(ID3D11Device*, char*,WCHAR* textureFilename=nullptr);
	void Shutdown();
	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);
	Loader* loader;
private:
	bool InitializeBuffers(ID3D11Device*,Mesh*);
private:
	float m_positionX, m_positionY, m_positionZ;
};
#endif