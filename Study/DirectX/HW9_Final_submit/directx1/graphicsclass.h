
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
#include "textclass.h"
#include "textureshaderclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "timerclass.h"
#include "inputclass.h"
#include "positionclass.h"
#include "minimapclass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED =true;
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
	bool Initialize(HINSTANCE,int, int, HWND);
	void Shutdown();
	//bool Frame(float rotX, float rotY, float rotZ,float ws,float ad,float qe,float frametime);
	//bool Frame(int, int);
	//bool Render();
	bool Frame();
private:
	//bool Render(float);
	bool HandleInput(float);
	bool RenderGraphics(float rotation);

private:
	MiniMapClass* m_MiniMap;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;
	InputClass* m_Input;
	PositionClass* m_Position;
	
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model, *m_SphereModel,*m_Pyramid;
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_textureShader;
	LightClass* m_Light;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	TextClass* m_Text;
	int objnumber;
	unsigned int polynumber;
	int m_width, m_height;
	ModelObjClass* obj[10] = { nullptr };
};
#endif
