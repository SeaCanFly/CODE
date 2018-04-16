#pragma once
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
#include "d3dclass.h"


const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
class GraphicsClass
{
private:
	D3DClass* m_D3D;
	//function
	bool Render();
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	
};
#endif // !_GRAPHICSCLASS_H_
