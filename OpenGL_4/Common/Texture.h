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
	GLuint g_uiFTexID; // 三個物件分別給不同的貼圖
	GLuint Light, NormalMap;
	GLuint g_uiSphereCubeMap;
	GLuint babyWall, babyFloor,	Wood, babyUse[4], parant, bullet;//room1
	GLuint board, stand, desk, window, clock, teacher, zero, one, two;
	GLuint workWall, workBook, printer, computer, file, breakfile;
	GLuint weddingChair, weddingFW, weddingWall, weddingDoor, weddingFloor, churchStand, mushi, husband;
	GLuint heart, hospitalCarbine, hospitalChair, hospitalDoor, hospitalWindow, diandi, medcine, metal;
	GLuint grassland, Sunny_NZ, ladder, RIP, butterfly;

	static Texture* create();		// 建立 TexturePool 的實體
	static Texture *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();		// 釋放取得資源


	void SetTexture() {
		auto texturepool = TexturePool::create();
		g_uiFTexID = texturepool->AddTexture("texture/checker.png");
		babyWall = texturepool->AddTexture("texture/BabyRoomWall.png");
		babyFloor = texturepool->AddTexture("texture/babyFloor.png");
		Wood = texturepool->AddTexture("texture/Wood.png");
		babyUse[0] = texturepool->AddTexture("texture/niaobu.png");
		babyUse[1] = texturepool->AddTexture("texture/naiping.png");
		babyUse[2] = texturepool->AddTexture("texture/naizei.png");
		babyUse[3] = texturepool->AddTexture("texture/toy.png");
		parant = texturepool->AddTexture("texture/parant.png");
		board = texturepool->AddTexture("texture/board.png");
		stand = texturepool->AddTexture("texture/stand.png");
		desk = texturepool->AddTexture("texture/Desk.png");
		window = texturepool->AddTexture("texture/schoolWall.png");
		clock = texturepool->AddTexture("texture/clock.png");
		teacher = texturepool->AddTexture("texture/teacher.png");
		workWall = texturepool->AddTexture("texture/workWall.png");
		workBook = texturepool->AddTexture("texture/workBook.png");
		printer = texturepool->AddTexture("texture/printer.png");
		computer = texturepool->AddTexture("texture/computer.png");
		file = texturepool->AddTexture("texture/file.png");
		weddingChair = texturepool->AddTexture("texture/weddingChair.png");
		weddingFW = texturepool->AddTexture("texture/weddingFW.png");
		weddingWall = texturepool->AddTexture("texture/weddingWall.png");
		grassland = texturepool->AddTexture("texture/grassland.png");
		weddingDoor = texturepool->AddTexture("texture/weddingDoor.png");
		weddingFloor = texturepool->AddTexture("texture/weddingFloor.png");
		churchStand = texturepool->AddTexture("texture/churchStand.png");
		mushi = texturepool->AddTexture("texture/mushi.png");
		husband = texturepool->AddTexture("texture/husband.png");
		heart = texturepool->AddTexture("texture/heart.png");
		hospitalCarbine = texturepool->AddTexture("texture/hospitalCarbine.png");
		diandi = texturepool->AddTexture("texture/diandi.png");
		hospitalChair = texturepool->AddTexture("texture/hospitalChair.png");
		hospitalDoor = texturepool->AddTexture("texture/hospitalDoor.png");
		hospitalWindow = texturepool->AddTexture("texture/hospitalWindow.png");
		medcine = texturepool->AddTexture("texture/medcine.png");
		metal = texturepool->AddTexture("texture/metal.png");
		Light = texturepool->AddTexture("texture/Light.png");
		NormalMap = texturepool->AddTexture("texture/NormalMap.png");
		Sunny_NZ = texturepool->AddTexture("texture/Sunny_NZ.png");
		ladder = texturepool->AddTexture("texture/ladder.png");
		RIP = texturepool->AddTexture("texture/RIP.png");
		butterfly = texturepool->AddTexture("texture/butterfly.png");
		bullet = texturepool->AddTexture("texture/bullet.png");
		breakfile = texturepool->AddTexture("texture/breakfile.png");
		zero = texturepool->AddTexture("texture/0.png");
		one = texturepool->AddTexture("texture/1.png");
		two = texturepool->AddTexture("texture/2.png");

		g_uiSphereCubeMap = CubeMap_load_SOIL("texture/Sunny_PX.png", "texture/Sunny_NX.png", "texture/Sunny_NY.png", "texture/Sunny_PY.png", "texture/Sunny_PZ.png", "texture/Sunny_NZ.png");
	}
};

#endif