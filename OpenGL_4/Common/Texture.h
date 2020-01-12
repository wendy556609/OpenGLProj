#ifndef TEXTURE_H
#define TEXTURE_H
#include "../Header/Angel.h"
#include "TexturePool.h"

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

class Texture
{
protected:
	Texture();			// 避免被誤用
	~Texture();
	void initDefault() {};
	static Texture* _pTexture;
private:

public:
	GLuint g_uiFTexID[7]; // 三個物件分別給不同的貼圖
	GLuint g_uiSphereCubeMap;

	static Texture* create();		// 建立 TexturePool 的實體
	static Texture *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();		// 釋放取得資源

	void SetTexture();
};

#endif