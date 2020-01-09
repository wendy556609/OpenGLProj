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
	TextureElement _Pool[TEXTUREPOOL_MAX];		// 預設能儲存 100 張貼圖
public:
	static TexturePool* create();		// 建立 TexturePool 的實體
	static TexturePool *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();		// 釋放取得資源
	GLuint AddTexture(char *texName);
	GLuint GetTextureID(char *texName) {}; // 沒有實作

protected:
	TexturePool();			// 避免被誤用
	~TexturePool();
	void initDefault() {};
	static TexturePool* _pTexturePool;
};

#endif

