#ifndef ROOM_H
#define ROOM_H
#include "RoomController.h"

#define DoorCount 2

class Room : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[DoorCount];

	Model *babyCot;
	Model *drawer[3];
	Flat *parant;
	Flat *babyUse[4];
public:
	Room(vec4 pos = vec4(0, 0, 0, 1));
	~Room();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();

	void DetectCollider();
};

#endif