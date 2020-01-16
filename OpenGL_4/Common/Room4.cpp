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
	//_pFloor->SetTiling(10, 10); // 原始為 (10, 10)	
	_pFloor->SetTrigger(false);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', vec3(100, 1, 100), vT, 180, roomPos);
	_pTop->SetTrigger(false);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', vec3(1, 50, 100), vT, -90, roomPos);
	_LeftWall->SetTrigger(false);
	_LeftWall->SetTextureLayer(DIFFUSE_MAP);
	_LeftWall->SetTurn(-90);
	_LeftWall->SetTiling(3, 1);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);	
	_RightWall->SetTurn(90);
	_RightWall->SetTiling(3, 1);
	_RightWall->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetTiling(2, 1);
	_FrontWall->SetMirror(false, true);
	//_FrontWall->SetTextureLayer(DIFFUSE_MAP | NORMAL_MAP);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);
	_BackWall->SetTiling(1, 1);

	vT.x = 49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('R', vec3(2, 20, 10), vT, 90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(false);
	vT.x = 0.0f; vT.z = -49.5f;
	_door[1] = new Flat('B', vec3(10, 20, 2), vT, 90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(true);

	auto modelNum = ModelNum::getInstance();
	////Model	
	hospitalBed = new Model(modelNum->hospitalBed);
	hospitalBed->SetTRSMatrix(Translate(vec4(0, 0, 35, 1))*Translate(roomPos)*RotateY(-90)*Scale(10.0f, 10.0f, 10.0f));
	hospitalBed->SetTextureLayer(DIFFUSE_MAP | LIGHT_MAP);

	diandi = new Flat('F', vec3(10, 20, 1), vec4(15, 10, 35, 1), -90, roomPos);
	diandi->SetTextureLayer(DIFFUSE_MAP);
	diandi->SetMirror(false, true);

	heart = new Flat('F', vec3(10, 20, 1), vec4(-15, 10, 35, 1), -90, roomPos);
	heart->SetTextureLayer(DIFFUSE_MAP);
	heart->SetMirror(false, true);

	hospitalCarbine = new Flat('L', vec3(1, 20, 15), vec4(-35, 10, 0, 1), -90, roomPos);
	hospitalCarbine->SetTextureLayer(DIFFUSE_MAP);
	hospitalCarbine->SetTurn(-90);

	hospitalChair = new Flat('L', vec3(1, 20, 20), vec4(-25, 5, 25, 1), -90, roomPos);
	hospitalChair->SetTextureLayer(DIFFUSE_MAP);
	hospitalChair->SetTurn(-90);

	medcine[0] = new Flat('R', vec3(1, 10, 10), vec4(30, 5, -25, 1), 90, roomPos);
	medcine[0]->SetTextureLayer(DIFFUSE_MAP);
	medcine[0]->SetTurn(90);

	medcine[1] = new Flat('F', vec3(10, 10, 1), vec4(35, 5, 25, 1), -90, roomPos);
	medcine[1]->SetMirror(true, true);
	medcine[1]->SetTextureLayer(DIFFUSE_MAP);

	medcine[2] = new Flat('B', vec3(10, 10, 1), vec4(-25.0f, 5.0f, -30.0f, 1), 90, roomPos);
	medcine[2]->SetTextureLayer(DIFFUSE_MAP);
	medcine[2]->SetMirror(true, false);

	collider = new Flat('F', vec3(4, 25, 2), vec4(0, 0, 35, 1), -90, roomPos);
	collider->SetTrigger(true);
}
void Room4::SetProjectionMatrix(mat4 &mpx)
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
	hospitalBed->SetProjectionMatrix(mpx);

	diandi->SetProjectionMatrix(mpx);
	hospitalChair->SetProjectionMatrix(mpx);
	heart->SetProjectionMatrix(mpx);
	hospitalCarbine->SetProjectionMatrix(mpx);

	for (int i = 0; i < 3; i++)
	{
		medcine[i]->SetProjectionMatrix(mpx);
	}
}

void Room4::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	//Model
	hospitalBed->SetViewMatrix(mvx);

	diandi->SetViewMatrix(mvx);
	hospitalChair->SetViewMatrix(mvx);
	heart->SetViewMatrix(mvx);
	hospitalCarbine->SetViewMatrix(mvx);

	for (int i = 0; i < 3; i++)
	{
		medcine[i]->SetViewMatrix(mvx);
	}
}

void Room4::Update(LightSource *light, float delta) {
	auto gameManager = GameManager::create();
	if (gameManager->room5Clear)light[0].diffuse = vec4(0.8f, 0.5f, 0.5f, 1.0f);
	else light[0].diffuse = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	//Model
	hospitalBed->Update(light, delta);

	diandi->Update(light, delta);
	hospitalChair->Update(light, delta);
	heart->Update(light, delta);
	hospitalCarbine->Update(light, delta);

	for (int i = 0; i < 3; i++)
	{
		medcine[i]->Update(light, delta);
	}

	DetectCollider();
}

void Room4::DetectCollider() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::create();
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
		gameManager->room6Enter = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room5isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), collider->GetCollider())) {
		gameManager->room5Clear = true;
	}

	if (gameManager->room5Clear) {
		_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_door[0]->SetTrigger(true);
		_RightWall->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Room4::Init() {
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(false);
	_RightWall->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
};

void Room4::Draw()
{
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->metal);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, g_uiFTexID[1]);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->hospitalWindow);
	_LeftWall->Draw();
	_FrontWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->hospitalDoor);
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_door[1]->Draw();

	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->metal);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->WhiteLight);
	hospitalBed->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Room4::AlphaDraw() {
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->hospitalWindow);
	_RightWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->diandi);
	diandi->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->hospitalChair);
	hospitalChair->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->heart);
	heart->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->hospitalCarbine);
	hospitalCarbine->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_door[0]->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->medcine);
	medcine[1]->Draw();
	medcine[0]->Draw();
	medcine[2]->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

Room4::~Room4() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if (hospitalBed != NULL)delete hospitalBed;

	if (diandi != NULL)delete diandi;
	if (hospitalChair != NULL)delete hospitalChair;
	if (heart != NULL)delete heart;
	if (hospitalCarbine != NULL)delete hospitalCarbine;
	
	if (medcine[0] != NULL)delete medcine[0];
	if (medcine[1] != NULL)delete medcine[1];
	if (medcine[2] != NULL)delete medcine[2];

	if (collider != NULL)delete collider;
}