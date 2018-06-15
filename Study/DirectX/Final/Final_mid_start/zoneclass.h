////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_


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
#include "terrainclass.h"
#include "modelobjclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: ZoneClass
////////////////////////////////////////////////////////////////////////////////
class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(TextureManagerClass*,D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, TextureManagerClass*, float, int);
	
private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*, TextureManagerClass*,float);
	static unsigned long __stdcall create(void* p);
	static unsigned long __stdcall initobj(void* p);
private:
	CRITICAL_SECTION cr_se;
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	LightClass* m_Light;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;
	SkyDomeClass* m_SkyDome;
	TerrainClass* m_Terrain;
	ModelObjClass* m_obj[100] = { 0 };
	TextureManagerClass* tm;
	D3DClass* D3D;
	bool m_displayUI, m_wireFrame, m_cellLines, m_heightLocked;
	int objnumber,screenW,screenH,getcount;
	float speed;
	bool lock,rlock;
	float posX, posY, posZ, rotY;
		ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
	int direction;
	int init_state;
};

#endif