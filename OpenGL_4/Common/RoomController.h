#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H
#include "../header/Angel.h"
#include "TypeDefine.h"
#include "Flat.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "ModelPool.h"

class RoomController
{
private:
	
public:
	GLuint g_uiFTexID[6]; // 三個物件分別給不同的貼圖
	int g_iTexWidth, g_iTexHeight;
	// For Objects
	Flat      *_pFloor, *_pTop;
	Flat      *_LeftWall, *_RightWall;
	Flat      *_FrontWall, *_BackWall;

	vec4 roomPos;

	RoomController() { SetTexture(); };
	~RoomController() {
		if (_pTop != NULL)delete _pTop;
		if(_pFloor != NULL)delete _pFloor;
		if (_LeftWall != NULL)delete _LeftWall;
		if (_RightWall != NULL)delete _RightWall;
		if (_FrontWall != NULL)delete _FrontWall;
		if (_BackWall != NULL)delete _BackWall;
	};

	virtual void Create() = 0;
	void SetTexture() {
		auto texturepool = TexturePool::create();
		g_uiFTexID[0] = texturepool->AddTexture("texture/checker.png");
		g_uiFTexID[1] = texturepool->AddTexture("texture/lightMap1.png");
		g_uiFTexID[2] = texturepool->AddTexture("texture/Masonry.Brick.png");
		g_uiFTexID[3] = texturepool->AddTexture("texture/Masonry.Brick.normal1.png");
		g_uiFTexID[4] = texturepool->AddTexture("texture/wi_tata.png");
		g_uiFTexID[5] = texturepool->AddTexture("texture/wi_tata_normal.png");
	};

	virtual void SetProjectionMatrix(mat4 &mpx) = 0;
	virtual void SetViewMatrix(mat4 &mvx) = 0;
	virtual void Update(LightSource *light, float delta) = 0;
	virtual void Draw() = 0;
};

#endif