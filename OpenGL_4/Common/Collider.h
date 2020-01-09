#pragma once
#include "../Header/Angel.h"

class Collider {
private:
	float DistanceX;
	float DistanceY;
	float DistanceZ;
	bool isTrigger = false;

	vec4 Pos;
public:

	vec4 rightTop;
	vec4 leftButtom;

	void Init(float x, float y, float z, vec4 position = 0, bool trigger = false);//ªì©lCollider
	void SetCubeCollider(vec4 position);//³]¥ßCollider
	void SetTrigger(bool trigger) { isTrigger = trigger; };
	bool GetTrigger() { return isTrigger; };
	vec4 GetPlayerPos() { return Pos; }
};

GLboolean CheckCollider(Collider one, Collider two);