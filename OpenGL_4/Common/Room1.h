#ifndef ROOM1_H
#define ROOM1_H
#include "RoomController.h"

#define DoorCount 2

class Room1 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[DoorCount];
	ModelPool *_pTeaPot;
	ModelPool *_pTable;
public:
	Room1(vec4 pos = vec4(0, 0, 0, 1));
	~Room1();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();

	void DetectCollider();
};

#endif