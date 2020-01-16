#ifndef ROOM1_H
#define ROOM1_H
#include "RoomController.h"

#define Room1DoorCount 2

class Room1 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[Room1DoorCount];

	Flat *board, *stand, *teacher;
	Model *desk[4];
public:
	Room1(vec4 pos = vec4(0, 0, 0, 1));
	~Room1();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw() {};

	void Init();

	void DetectCollider();

	void billboard();
};

#endif