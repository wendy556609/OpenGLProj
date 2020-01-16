#ifndef ROOM_H
#define ROOM_H
#include "RoomController.h"


class Room : public RoomController
{
private:
	int iSize = 100;
	Flat *_door;

	Model *babyCot;
	Model *drawer[3];
	Flat *parant;
	Flat *babyUse[4];
	Flat *gun;
	CQuad *bullet;
public:
	Room(vec4 pos = vec4(0, 0, 0, 1));
	~Room();

	bool isTake = false;

	vec4 bulletPos;

	void Create();

	void SetProjectionMatrix(mat4 &mpx);
	void SetViewMatrix(mat4 &mvx);
	void Update(LightSource *light, float delta);
	void Draw();
	void AlphaDraw() {};
	void Shoot(vec4 front);

	void SetTake();
	void billboard();

	void Init();

	void DetectCollider();
};

#endif