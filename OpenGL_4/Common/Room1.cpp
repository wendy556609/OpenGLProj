#include "Room1.h"

Room1::Room1(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	Create();
}

void Room1::Create() {
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
	_LeftWall->SetTextureLayer(DIFFUSE_MAP);
	_LeftWall->SetTiling(1, 1);
	_LeftWall->SetTurn(-90);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);
	_RightWall->SetTiling(1, 1);
	_RightWall->SetTurn(90);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetTiling(5, 1);
	_FrontWall->SetMirror(false, true);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);
	_BackWall->SetTiling(5, 1);

	vT.x = -49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(2, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0.0f; vT.z = 49.5f;
	_door[1] = new Flat('F', vec3(10, 20, 2), vT, -90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(false);

	auto modelNum = ModelNum::getInstance();
	////Model
	board = new Flat('R', vec3(1, 25, 40), vec4(49.5f, 20.0f, 0, 1), 90, roomPos);
	board->SetTextureLayer(DIFFUSE_MAP);
	board->SetTiling(1, 1);
	board->SetTurn(90);

	stand = new Flat('R', vec3(1, 15, 10), vec4(25.0f, 7.5f, 0, 1), 90, roomPos);
	stand->SetTextureLayer(DIFFUSE_MAP);
	stand->SetTiling(1, 1);
	stand->SetTurn(90);

	teacher = new Flat('R', vec3(1, 20, 15), vec4(30.0f, 10.0f, 15, 1), 90, roomPos);
	teacher->SetTextureLayer(DIFFUSE_MAP);
	teacher->SetTiling(1, 1);
	teacher->SetTurn(90);
	teacher->SetNormal(RotateZ(90));

	desk[0] = new Model(modelNum->desk);
	desk[0]->SetTextureLayer(DIFFUSE_MAP);
	desk[0]->SetTiling(1, 1);
	desk[0]->SetTRSMatrix(Translate(vec4(0, 0, 15, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.5f, 1.5f, 1.5f));

	desk[1] = new Model(modelNum->desk);
	desk[1]->SetTextureLayer(DIFFUSE_MAP);
	desk[1]->SetTiling(1, 1);
	desk[1]->SetTRSMatrix(Translate(vec4(0, 0, -15, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.5f, 1.5f, 1.5f));

	desk[2] = new Model(modelNum->desk);
	desk[2]->SetTextureLayer(DIFFUSE_MAP);
	desk[2]->SetTiling(1, 1);
	desk[2]->SetTRSMatrix(Translate(vec4(-20, 0, 15, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.5f, 1.5f, 1.5f));
	
	desk[3] = new Model(modelNum->desk);
	desk[3]->SetTextureLayer(DIFFUSE_MAP);
	desk[3]->SetTiling(1, 1);
	desk[3]->SetTRSMatrix(Translate(vec4(-20, 0, -15, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.5f, 1.5f, 1.5f));

}

void Room1::SetProjectionMatrix(mat4 &mpx)
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
	board->SetProjectionMatrix(mpx);
	stand->SetProjectionMatrix(mpx);
	teacher->SetProjectionMatrix(mpx);

	for (int i = 0; i < 4; i++)
	{
		desk[i]->SetProjectionMatrix(mpx);
	}

}

void Room1::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	//Model
	board->SetViewMatrix(mvx);
	stand->SetViewMatrix(mvx);
	teacher->SetViewMatrix(mvx);

	for (int i = 0; i < 4; i++)
	{
		desk[i]->SetViewMatrix(mvx);
	}
}

void Room1::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	//Model
	board->Update(light, delta);
	stand->Update(light, delta);
	teacher->Update(light, delta);

	for (int i = 0; i < 4; i++)
	{
		desk[i]->Update(light, delta);
	}

	billboard();

	DetectCollider();
}

void Room1::billboard() {
	auto camera = Camera::getInstance();
	//bool view;
	mat4 mat;
	mat4 rotate;
	float angleCosine;
	vec4 vec = normalize(camera->_pos - teacher->_pos);
	vec4 lookAt = vec4(-1, 0, 0, 1);

	angleCosine = vec.x*lookAt.x + 0*lookAt.y + vec.z*lookAt.z;
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999)){
		if (camera->_pos.z <= teacher->_pos.z) {
			rotate = RotateY(360.0f-acos(angleCosine) * 180 / 3.14);
		}
		else {
			rotate = RotateY(acos(angleCosine) * 180 / 3.14);// * 180 / 3.14
		}

	}

	teacher->SetTRSMatrix(Translate(vec4(30.0f, 10.0f, 15, 1))*Translate(roomPos)*Scale(15, 20, 15)*rotate*Translate(vec4(0, 0, 0, 1))*RotateZ(90));
}

void Room1::DetectCollider() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::create();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if (!_LeftWall->GetTrigger())camera->Room2isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room2isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room2isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room2isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room2isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room2isTouch = true;
	}
	else camera->Room2isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room2isTouch = false;
		if(gameManager->room1Clear)gameManager->room2Enter = true;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room2isTouch = false;
		gameManager->room2Enter = true;
	}

	if (gameManager->room2Clear) {
		_door[1]->SetTrigger(true);
		_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void Room1::Init() {
	_door[1]->SetTrigger(false);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
};

void Room1::Draw()
{
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->Wood);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->clock);
	_LeftWall->Draw();
	_RightWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->window);
	_FrontWall->Draw();
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_door[0]->Draw();
	_door[1]->Draw();
	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->desk);
	for (int i = 0; i < 4; i++)
	{
		desk[i]->Draw();
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->board);
	board->Draw();

	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->teacher);
	teacher->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->stand);
	stand->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}

Room1::~Room1() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if (board != NULL)delete board;
	if (stand != NULL)delete stand;

	if(teacher != NULL)delete teacher;
	for (int i = 0; i < 4; i++)
	{
		if (desk[i] != NULL)delete desk[i];
	}
}