////////////////////////////////////////////////////////////////////////////////
// Filename: userinterfaceclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textclass.h"
#include "minimapclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: UserInterfaceClass
////////////////////////////////////////////////////////////////////////////////
class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass&);
	~UserInterfaceClass();

	bool Initialize(D3DClass*, int, int,char*minimappath,char* pointpath);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int, float, float, float, float, float, float,float,int);
	bool Render(D3DClass*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX,int ,int);

	bool UpdateRenderCounts(ID3D11DeviceContext*, int, int, int);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, float, float, float, float, float, float,float,int);

private:
	FontClass* m_Font1;
	TextClass *m_FpsString, *m_VideoStrings, *m_PositionStrings;
	int m_previousFps;
	int m_previousPosition[8];
	TextClass* m_RenderCountStrings;
	MiniMapClass* m_MiniMap;
	BitmapClass* m_aspeed;
	BitmapClass* m_mspeed;
	BitmapClass* m_ui[4] = { 0 };
};

#endif