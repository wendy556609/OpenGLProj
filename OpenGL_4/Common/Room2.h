#ifndef ROOM2_H
#define ROOM2_H
#include "RoomController.h"

#define Room2DoorCount 2

class Room2 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[Room2DoorCount];

	Model *workDesk;
	Flat *computer, *printer;
	Flat *file[4];
public:
	Room2(vec4 pos = vec4(0, 0, 0, 1));
	~Room2();

	bool isSolve[4];

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw() {};
	void SetSolve();

	void Init();

	void DetectCollider();
};

#endif