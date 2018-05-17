
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
#pragma once
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "modelobjclass.h"
#include "bitmapclass.h"
#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED =false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float rotX, float rotY, float rotZ,float ws,float ad,float qe,float frametime);
	//bool Frame(int, int);
	//bool Render();
	bool GraphicsClass::Frame(int fps, int cpu, float frameTime);
private:
	bool Render(float);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model, *m_SphereModel,*m_Pyramid;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ModelObjClass* m_tank,*m_phone,*m_plane,*m_house;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;
	int objnumber;
	unsigned long polynumber;
	int m_width, m_height;
	ModelObjClass* obj[10] = { nullptr };
};
#endif
