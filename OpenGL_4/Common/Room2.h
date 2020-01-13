#ifndef ROOM2_H
#define ROOM2_H
#include "RoomController.h"

#define DoorCount 3

class Room2 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[DoorCount];

	Model *workDesk;
	Flat *computer, *printer;
	Flat *file[4];
public:
	Room2(vec4 pos = vec4(0, 0, 0, 1));
	~Room2();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();

	void DetectCollider();
};

#endif