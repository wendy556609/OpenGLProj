#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H
#include "../header/Angel.h"
#include "TypeDefine.h"
#include "Flat.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "ModelPool.h"
#include "TexturePool.h"

class RoomController
{
private:
	
public:
	// For Objects
	Flat      *_pFloor, *_pTop;
	Flat      *_LeftWall, *_RightWall;
	Flat      *_FrontWall, *_BackWall;

	vec4 roomPos;

	RoomController() {};
	~RoomController() {
		if (_pTop != NULL)delete _pTop;
		if(_pFloor != NULL)delete _pFloor;
		if (_LeftWall != NULL)delete _LeftWall;
		if (_RightWall != NULL)delete _RightWall;
		if (_FrontWall != NULL)delete _FrontWall;
		if (_BackWall != NULL)delete _BackWall;
	};

	virtual void SetProjectionMatrix(mat4 &mpx) = 0;
	virtual void SetViewMatrix(mat4 &mvx) = 0;
	virtual void Update(LightSource *light, float delta) = 0;
	virtual void Draw() = 0;
};

#endif