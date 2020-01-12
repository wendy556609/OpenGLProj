#include "Room4.h"

Room4::Room4(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	Create();
}

void Room4::Create() {
	vec4 vT;

	vT.x = 0; vT.y = 0; vT.z = 0;
	_pFloor = new Flat('M', vec3(100, 1, 100), vT, 0, roomPos);
	_pFloor->SetTextureLayer(DIFFUSE_MAP);
	_pFloor->SetTiling(10, 10); // 原始為 (10, 10)	
	_pFloor->SetTrigger(false);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', vec3(100, 1, 100), vT, 180, roomPos);
	_pTop->SetTrigger(false);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', vec3(1, 50, 100), vT, -90, roomPos);
	_LeftWall->SetTrigger(false);

	vT.x = 49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('R', vec3(3, 20, 10), vT, 90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0.0f; vT.z = -49.5f;
	_door[1] = new Flat('B', vec3(10, 20, 3), vT, 90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(true);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	//_FrontWall->SetTextureLayer(DIFFUSE_MAP | NORMAL_MAP);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);

	////Model

	_pTeaPot = new ModelPool("Model/TeaPot.obj", Type_3DMax);
	_pTeaPot->SetTRSMatrix(Translate(vec4(0, 5.3f, 0, 1))*Translate(roomPos)*Scale(2.0f, 2.0f, 2.0f));
	_pTeaPot->SetMaterials(vec4(0), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pTeaPot->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pTable = new ModelPool("Model/table.obj", Type_3DMax);
	_pTable->SetTRSMatrix(Translate(vec4(0, 0.0f, 0, 1))*Translate(roomPos)*Scale(0.5f, 0.5f, 0.5f));
	_pTable->SetMaterials(vec4(0), vec4(0.72f, 0.45f, 0.2f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pTable->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
}
void Room4::SetProjectionMatrix(mat4 &mpx)
{
	_pFloor->SetProjectionMatrix(mpx);
	_pTop->SetProjectionMatrix(mpx);
	_LeftWall->SetProjectionMatrix(mpx);
	_RightWall->SetProjectionMatrix(mpx);
	_FrontWall->SetProjectionMatrix(mpx);
	_BackWall->SetProjectionMatrix(mpx);
	//Model
	_pTeaPot->SetProjectionMatrix(mpx);
	_pTable->SetProjectionMatrix(mpx);

	_door[0]->SetProjectionMatrix(mpx);
	_door[1]->SetProjectionMatrix(mpx);
}

void Room4::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);
	//Model
	_pTeaPot->SetViewMatrix(mvx);
	_pTable->SetViewMatrix(mvx);
	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
}

void Room4::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);
	//Model
	_pTeaPot->Update(light, delta);
	_pTable->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);

	DetectCollider();
}

void Room4::DetectCollider() {
	auto camera = Camera::getInstance();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if (!_LeftWall->GetTrigger())camera->Room5isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room5isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room5isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room5isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room5isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room5isTouch = true;
	}
	else camera->Room5isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room5isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room5isTouch = false;
	}
}

void Room4::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_uiFTexID[0]);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, g_uiFTexID[1]);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	_LeftWall->Draw();
	_RightWall->Draw();
	_FrontWall->Draw();
	_BackWall->Draw();
	//Model
	_pTeaPot->Draw();
	_pTable->Draw();

	_door[0]->Draw();
	_door[1]->Draw();
}

Room4::~Room4() {
	if (_pTeaPot != NULL)delete _pTeaPot;
	if (_pTable != NULL)delete _pTable;
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];
}