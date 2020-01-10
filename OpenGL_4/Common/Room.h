#ifndef ROOM_H
#define ROOM_H
#include "RoomController.h"

#define DoorCount 2

class Room : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[DoorCount];
	ModelPool *Test;
	ModelPool *_pTeaPot;
	ModelPool *_pTable;
	ModelPool *_pBench[3];
public:
	Room(vec4 pos = vec4(0, 0, 0, 1));
	~Room();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();

	void DetectCollider();
};

#endif