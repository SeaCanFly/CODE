////////////////////////////////////////////////////////////////////////////////
// Filename: texturemanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREMANAGERCLASS_H_
#define _TEXTUREMANAGERCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureManagerClass
////////////////////////////////////////////////////////////////////////////////
class TextureManagerClass
{
public:
	TextureManagerClass();
	TextureManagerClass(const TextureManagerClass&);
	~TextureManagerClass();

	bool Initialize(int);
	void Shutdown();

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, int);

	ID3D11ShaderResourceView* GetTexture(int);
int m_curCount;
private:
	TextureClass* m_TextureArray;
	
	int m_textureCount;
};

#endif