#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

#include "../header/Angel.h"

#define	TEXTUREPOOL_MAX 100

typedef struct structTextureElement {
	GLuint  uiTextureID;
	char   *TextureName;
	int		iTexWidth;
	int		iTexHeight;
} TextureElement;

class TexturePool
{
	int _iNumTextures;
	TextureElement _Pool[TEXTUREPOOL_MAX];		// �w�]���x�s 100 �i�K��
public:
	static TexturePool* create();		// �إ� TexturePool ������
	static TexturePool *getInstance();	// ���o  TexturePool ������

	void destroyInstance();		// ������o�귽
	GLuint AddTexture(char *texName);
	GLuint GetTextureID(char *texName) {}; // �S����@

protected:
	TexturePool();			// �קK�Q�~��
	~TexturePool();
	void initDefault() {};
	static TexturePool* _pTexturePool;
};

#endif

