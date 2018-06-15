////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ZONECLASS1_H_
#define _ZONECLASS1_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "texturemanagerclass.h"
#include "timerclass.h"
#include "userinterfaceclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "positionclass.h"
#include "frustumclass.h"
#include "skydomeclass.h"
#include "terrainclass1.h"
#include "modelobjclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ZoneClass
////////////////////////////////////////////////////////////////////////////////
class ZoneClass1
{
public:
	ZoneClass1();
	ZoneClass1(const ZoneClass1&);
	~ZoneClass1();

	bool Initialize(TextureManagerClass*,D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, TextureManagerClass*, float, int);
	
private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*, TextureManagerClass*,float frametime);
	static unsigned long __stdcall initobj1(void* p);
private:
	TextureManagerClass* tm;
	D3DClass* D3D;
	CRITICAL_SECTION cr;
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	LightClass* m_Light;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;
	SkyDomeClass* m_SkyDome;
	TerrainClass1* m_Terrain;
	ModelObjClass* m_obj[100] = { 0 };
	bool m_displayUI, m_wireFrame, m_cellLines, m_heightLocked;int objnumber;
	int screenW, screenH;
	bool lock;
};

#endif