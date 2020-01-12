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
	GLuint babyWall, babyFloor,	cotWood;

	static Texture* create();		// 建立 TexturePool 的實體
	static Texture *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();		// 釋放取得資源


	void SetTexture() {
		auto texturepool = TexturePool::create();
		g_uiFTexID[0] = texturepool->AddTexture("texture/checker.png");
		g_uiFTexID[1] = texturepool->AddTexture("texture/lightMap1.png");
		g_uiFTexID[2] = texturepool->AddTexture("texture/Masonry.Brick.png");
		g_uiFTexID[3] = texturepool->AddTexture("texture/Masonry.Brick.normal1.png");
		g_uiFTexID[4] = texturepool->AddTexture("texture/wi_tata.png");
		g_uiFTexID[5] = texturepool->AddTexture("texture/wi_tata_normal.png");
		g_uiFTexID[6] = texturepool->AddTexture("texture/metal.png");
		babyWall = texturepool->AddTexture("texture/BabyRoomWall.png");
		babyFloor = texturepool->AddTexture("texture/babyFloor.png");
		cotWood = texturepool->AddTexture("texture/Wood.png");

		g_uiSphereCubeMap = CubeMap_load_SOIL("texture/Sunny_PX.png", "texture/Sunny_NX.png", "texture/Sunny_NY.png", "texture/Sunny_PY.png", "texture/Sunny_PZ.png", "texture/Sunny_NZ.png");
	}
};

#endif