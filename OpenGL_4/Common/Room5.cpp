#include "Room5.h"

Room5::Room5(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	Create();
}

void Room5::Create() {
	vec4 vT;

	vT.x = 0; vT.y = 0; vT.z = 0;
	_pFloor = new Flat('M', vec3(100, 1, 100), vT, 0, roomPos);
	_pFloor->SetTextureLayer(DIFFUSE_MAP);
	_pFloor->SetTrigger(false);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', vec3(100, 1, 100), vT, 180, roomPos);
	_pTop->SetTrigger(false);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', vec3(1, 50, 100), vT, -90, roomPos);
	_LeftWall->SetTrigger(false);
	_LeftWall->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.2f), vec4(0.0f, 0.0f, 0.0f, 1.0f));

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.2f), vec4(0.0f, 0.0f, 0.0f, 1.0f));

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.2f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//_FrontWall->SetTextureLayer(DIFFUSE_MAP | NORMAL_MAP);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);

	vT.x = -49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(3, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0.0f; vT.z = -49.5f;
	_door[1] = new Flat('B', vec3(10, 20, 3), vT, 90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(true);

	auto modelNum = ModelNum::getInstance();
	////Model
	RIP = new Model(modelNum->RIP);
	RIP->SetTRSMatrix(Translate(vec4(30, 0, 0, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.0f, 1.0f, 1.0f));
	RIP->SetTextureLayer(DIFFUSE_MAP);
}
void Room5::SetProjectionMatrix(mat4 &mpx)
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
	RIP->SetProjectionMatrix(mpx);


}

void Room5::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	//Model
	RIP->SetViewMatrix(mvx);
}

void Room5::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	//Model
	RIP->Update(light, delta);

	DetectCollider();
}

void Room5::DetectCollider() {
	auto camera = Camera::getInstance();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if (!_LeftWall->GetTrigger())camera->Room6isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room6isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room6isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room6isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room6isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room6isTouch = true;
	}
	else camera->Room6isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room6isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room6isTouch = false;
	}
}

void Room5::Draw()
{
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->grassland);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, g_uiFTexID[1]);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	_BackWall->Draw();

	_door[0]->Draw();
	_door[1]->Draw();
	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->metal);
	RIP->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Room5::AlphaDraw() {
	//glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, 0);
	_RightWall->Draw();
	_FrontWall->Draw();
	_LeftWall->Draw();
	//glDepthMask(GL_TRUE);
}

Room5::~Room5() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if(RIP != NULL)delete RIP;
}