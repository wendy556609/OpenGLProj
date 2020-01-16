#ifndef ROOM4_H
#define ROOM4_H
#include "RoomController.h"

#define Room4DoorCount 2

class Room4 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[Room4DoorCount];

	Flat *diandi, *hospitalChair, *heart, *hospitalCarbine;
	Flat *medcine[3];
	Model *hospitalBed;

	Flat *collider;
public:
	Room4(vec4 pos = vec4(0, 0, 0, 1));
	~Room4();

	bool isTurn = false;

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw();

	void Init();

	void DetectCollider();
};

#endif