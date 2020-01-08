#include "Collider.h"

void Collider::Init(float x, float y, float z, vec4 position) {
	DistanceX = x;
	DistanceY = y;
	DistanceZ = z;	
	SetCubeCollider(position);
}

void Collider::SetCubeCollider(vec4 position) {
	rightTop = vec4(position.x + DistanceX, position.y + DistanceY, position.z + DistanceZ, 1.0f);
	leftButtom = vec4(position.x - DistanceX, position.y - DistanceY, position.z - DistanceZ, 1.0f);
	Pos = position;
}

GLboolean CheckCollider(Collider one, Collider two) {
	bool collisionX = (one.leftButtom.x <= two.rightTop.x && one.leftButtom.x >= two.leftButtom.x) ||
		(one.rightTop.x <= two.rightTop.x && one.rightTop.x >= two.leftButtom.x) ||
		(two.leftButtom.x <= one.rightTop.x && two.leftButtom.x >= one.leftButtom.x) ||
		(two.rightTop.x <= one.rightTop.x && two.rightTop.x >= one.leftButtom.x);
	bool collisionY = (one.leftButtom.y <= two.rightTop.y && one.leftButtom.y >= two.leftButtom.y) ||
		(one.rightTop.y <= two.rightTop.y && one.rightTop.y >= two.leftButtom.y) ||
		(two.leftButtom.y <= one.rightTop.y && two.leftButtom.y >= one.leftButtom.y) ||
		(two.rightTop.y <= one.rightTop.y && two.rightTop.y >= one.leftButtom.y);
	bool collisionZ = (one.leftButtom.z <= two.rightTop.z && one.leftButtom.z >= two.leftButtom.z) ||
		(one.rightTop.z <= two.rightTop.z && one.rightTop.z >= two.leftButtom.z) ||
		(two.leftButtom.z <= one.rightTop.z && two.leftButtom.z >= one.leftButtom.z) ||
		(two.rightTop.z <= one.rightTop.z && two.rightTop.z >= one.leftButtom.z);
	return collisionX&&collisionY&&collisionZ;
}