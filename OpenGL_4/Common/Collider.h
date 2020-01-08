#pragma once
#include "../Header/Angel.h"

class Collider {
private:
	float DistanceX;
	float DistanceY;
	float DistanceZ;

	vec4 Pos;
public:
	vec4 rightTop;
	vec4 leftButtom;

	int hp;
	bool isDestroy = false;
	bool isHurt = false;

	void Init(float x, float y, float z, vec4 position = 0);//ªì©lCollider
	void SetCubeCollider(vec4 position);//³]¥ßCollider
	vec4 GetPlayerPos() { return Pos; }
};

GLboolean CheckCollider(Collider one, Collider two);