#include "Room3.h"

Room3::Room3(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	Create();
}

void Room3::Create() {
	vec4 vT;

	vT.x = 0; vT.y = 0; vT.z = 0;
	_pFloor = new Flat('M', vec3(100, 1, 100), vT, 0, roomPos);
	_pFloor->SetTextureLayer(DIFFUSE_MAP | LIGHT_MAP);
	_pFloor->SetTrigger(false);
	_pFloor->SetMirror(true, true);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', vec3(100, 1, 100), vT, 180, roomPos);
	_pTop->SetTrigger(false);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', vec3(1, 50, 100), vT, -90, roomPos);
	_LeftWall->SetTrigger(false);
	_LeftWall->SetTextureLayer(DIFFUSE_MAP);
	//_LeftWall->SetTiling(1, 1); // 原始為 (10, 10)	
	_LeftWall->SetTurn(-90);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);
	//_RightWall->SetTiling(1, 1); // 原始為 (10, 10)	
	_RightWall->SetTurn(90);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetTiling(3, 1);
	_FrontWall->SetMirror(false, true);
	//_FrontWall->SetTextureLayer(DIFFUSE_MAP | NORMAL_MAP);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);
	_BackWall->SetTiling(3, 1);

	vT.x = 49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(2, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0.0f; vT.z = 49.5f;
	_door[1] = new Flat('F', vec3(10, 20, 2), vT, -90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(false);

	////Model
	churchStand = new Flat('L', vec3(3, 15, 10), vec4(-30.0f, 7.5f, 0.0f, 1), -90, roomPos);
	churchStand->SetTextureLayer(DIFFUSE_MAP);
	churchStand->SetTurn(-90);

	chair[0] = new Flat('B', vec3(10, 10, 1), vec4(40.0f, 5.0f, -25.0f, 1), 90, roomPos);
	chair[0]->SetTextureLayer(DIFFUSE_MAP);	
	chair[0]->SetMirror(true, false);

	chair[1] = new Flat('B', vec3(10, 10, 1), vec4(25.0f, 5.0f, -25.0f, 1), 90, roomPos);
	chair[1]->SetTextureLayer(DIFFUSE_MAP);
	chair[1]->SetMirror(true, false);

	chair[2] = new Flat('B', vec3(10, 10, 1), vec4(10.0f, 5.0f, -25.0f, 1), 90, roomPos);
	chair[2]->SetTextureLayer(DIFFUSE_MAP);	
	chair[2]->SetMirror(true, false);

	chair[3] = new Flat('F', vec3(10, 10, 3), vec4(40.0f, 5.0f, 25.0f, 1), -90, roomPos);
	chair[3]->SetTextureLayer(DIFFUSE_MAP);
	chair[3]->SetMirror(true, true);

	chair[4] = new Flat('F', vec3(10, 10, 3), vec4(25.0f, 5.0f, 25.0f, 1), -90, roomPos);
	chair[4]->SetTextureLayer(DIFFUSE_MAP);
	chair[4]->SetMirror(true, true);

	chair[5] = new Flat('F', vec3(10, 10, 3), vec4(10.0f, 5.0f, 25.0f, 1), -90, roomPos);
	chair[5]->SetTextureLayer(DIFFUSE_MAP);
	chair[5]->SetMirror(true, true);
	
	mushi = new Flat('L', vec3(3, 20, 8), vec4(-35.0f, 10, 0.0f, 1), -90, roomPos);
	mushi->SetTextureLayer(DIFFUSE_MAP);
	mushi->SetTurn(-90);

	husband = new Flat('F', vec3(3, 20, 10), vec4(-20.0f, 10.0f, 5, 1), -90, roomPos);//Light=vec4(-20.0f, 10.0f, -5, 1)
	husband->SetTextureLayer(DIFFUSE_MAP|LIGHT_MAP);
	husband->SetMirror(true, true);

	collider = new Flat('F', vec3(4, 25, 2), vec4(-20.0f, 12.5f, -5, 1), -90, roomPos);
	collider->SetTrigger(true);
}
void Room3::SetProjectionMatrix(mat4 &mpx)
{
	_pFloor->SetProjectionMatrix(mpx);
	_pTop->SetProjectionMatrix(mpx);
	_LeftWall->SetProjectionMatrix(mpx);
	_RightWall->SetProjectionMatrix(mpx);
	_FrontWall->SetProjectionMatrix(mpx);
	_BackWall->SetProjectionMatrix(mpx);

	_door[0]->SetProjectionMatrix(mpx);
	_door[1]->SetProjectionMatrix(mpx);
	//Model
	churchStand->SetProjectionMatrix(mpx);

	for (int i = 0; i < 6; i++)
	{
		chair[i]->SetProjectionMatrix(mpx);
	}

	mushi->SetProjectionMatrix(mpx);

	husband->SetProjectionMatrix(mpx);

	//collider->SetProjectionMatrix(mpx);
}

void Room3::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	//Model
	churchStand->SetViewMatrix(mvx);

	for (int i = 0; i < 6; i++)
	{
		chair[i]->SetViewMatrix(mvx);
	}

	mushi->SetViewMatrix(mvx);

	husband->SetViewMatrix(mvx);
}

void Room3::Update(LightSource *light, float delta) {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::create();
	if (gameManager->room4Clear) {
		light[0].isLighting = 1;
		light[1].isLighting = 0;
	}
	else {
		vec4 direct;
		light[0].isLighting = 0;
		light[1].isLighting = 1;
		direct = vec4(camera->_pos.x, 0, camera->_pos.z, 1) - light[1].position;
		light[1].spotDirection = vec3(direct.x, direct.y, direct.z);
	}

	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	//Model
	churchStand->Update(light, delta);

	for (int i = 0; i < 6; i++)
	{
		chair[i]->Update(light, delta);
	}

	mushi->Update(light, delta);

	husband->Update(light, delta);

	DetectCollider();
}

void Room3::DetectCollider() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::create();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if (!_LeftWall->GetTrigger())camera->Room4isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room4isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room4isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room4isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room4isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room4isTouch = true;
	}
	else camera->Room4isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room4isTouch = false;
		if (gameManager->room3Clear)gameManager->room4Enter = true;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room4isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), collider->GetCollider())) {
		gameManager->room4Clear = true;
	}

	if (gameManager->room4Clear) {
		_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_door[1]->SetTrigger(true);
	}
}

void Room3::Init() {
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(false);
};

void Room3::Draw()
{
	auto texture = Texture::getInstance();
	auto gameManager = GameManager::create();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->weddingFloor);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->Light);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->weddingFW);
	_LeftWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->weddingDoor);
	_RightWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->weddingWall);
	_FrontWall->Draw();
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_door[0]->Draw();
	_door[1]->Draw();
	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->mushi);
	mushi->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->churchStand);
	churchStand->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->husband);
	glActiveTexture(GL_TEXTURE1);
	if(gameManager->room4Clear) glBindTexture(GL_TEXTURE_2D, texture->WhiteLight);
	else glBindTexture(GL_TEXTURE_2D, 0);
	husband->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->weddingChair);
	chair[5]->Draw();
	chair[4]->Draw();
	chair[3]->Draw();
	chair[2]->Draw();
	chair[1]->Draw();
	chair[0]->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

}

Room3::~Room3() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if(churchStand != NULL)delete churchStand;

	for (int i = 0; i < 6; i++)
	{
		if (chair[i] != NULL)delete chair[i];
	}
	
	if(mushi != NULL)delete mushi;

	if(husband != NULL)delete husband;

	if(collider != NULL)delete collider;
}