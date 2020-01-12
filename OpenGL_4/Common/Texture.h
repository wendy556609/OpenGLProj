#ifndef TEXTURE_H
#define TEXTURE_H
#include "../Header/Angel.h"
#include "TexturePool.h"

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

class Texture
{
protected:
	Texture();			// �קK�Q�~��
	~Texture();
	void initDefault() {};
	static Texture* _pTexture;
private:

public:
	GLuint g_uiFTexID[7]; // �T�Ӫ�����O�����P���K��
	GLuint g_uiSphereCubeMap;

	static Texture* create();		// �إ� TexturePool ������
	static Texture *getInstance();	// ���o  TexturePool ������

	void destroyInstance();		// ������o�귽

	void SetTexture();
};

#endif