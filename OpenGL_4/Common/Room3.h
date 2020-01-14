#ifndef ROOM3_H
#define ROOM3_H
#include "RoomController.h"

#define DoorCount 3

class Room3 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[DoorCount];

	Flat *churchStand;
	Flat *chair[6];
	Flat *mushi, *husband;
public:
	Room3(vec4 pos = vec4(0, 0, 0, 1));
	~Room3();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw() {};

	void DetectCollider();
};

#endif