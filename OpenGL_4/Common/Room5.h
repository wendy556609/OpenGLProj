#ifndef ROOM5_H
#define ROOM5_H
#include "RoomController.h"

#define Room5DoorCount 2

class Room5 : public RoomController
{
private:
	int iSize = 100;
	Flat *_door[Room5DoorCount];
	Flat *butterfly[2];
	Flat *flower;

	Model *RIP;
	Model *cube[2];

	vec4 _pos[2];
	vec4 _direct;

	vec4 initPos;

	int turn = 1;

	bool isTake = false;
public:
	Room5(vec4 pos = vec4(0, 0, 0, 1));
	~Room5();

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw();
	void Fly(float delta);
	void SetTake();
	void billboard();

	void Init();

	void DetectCollider();
};

#endif