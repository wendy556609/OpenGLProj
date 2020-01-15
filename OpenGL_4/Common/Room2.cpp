#include "Room2.h"

Room2::Room2(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	Create();
}

void Room2::Create() {
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
	_LeftWall->SetTiling(2, 1);
	_LeftWall->SetTurn(-90);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);
	_RightWall->SetTiling(2, 1);
	_RightWall->SetTurn(90);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetTiling(2, 1);
	_FrontWall->SetMirror(false, true);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);
	_BackWall->SetTiling(2, 1);

	vT.x = -49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(3, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0.0f; vT.z = -49.5f;
	_door[1] = new Flat('B', vec3(10, 20, 3), vT, 90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(true);
	vT.x = 0.0f; vT.z = 49.5f;
	_door[2] = new Flat('F', vec3(10, 20, 3), vT, -90, roomPos);
	_door[2]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[2]->SetTrigger(true);

	auto modelNum = ModelNum::getInstance();
	////Model
	computer = new Flat('F', vec3(10, 5, 1), vec4(0, 12.5f, 5.0f, 1), -90, roomPos);
	computer->SetMirror(true, true);
	computer->SetTextureLayer(DIFFUSE_MAP);
	computer->SetTiling(1, 1);

	printer = new Flat('F', vec3(15, 20, 1), vec4(-30, 10.0f, 30, 1), -90, roomPos);
	printer->SetMirror(true, true);
	printer->SetTextureLayer(DIFFUSE_MAP);
	printer->SetTiling(1, 1);

	file[0] = new Flat('F', vec3(10, 5, 2), vec4(7.5, 12.5f, 5, 1), -90, roomPos);
	file[0]->SetMirror(true, true);
	file[0]->SetTextureLayer(DIFFUSE_MAP);
	file[0]->SetTiling(1, 1);

	file[1] = new Flat('R', vec3(2, 10, 15), vec4(30, 5.0f, -10, 1), 90, roomPos);
	file[1]->SetTextureLayer(DIFFUSE_MAP);
	file[1]->SetTiling(1, 1);
	file[1]->SetTurn(90);

	file[2] = new Flat('L', vec3(2, 10, 15), vec4(-25, 5.0f, -20, 1), -90, roomPos);
	file[2]->SetTextureLayer(DIFFUSE_MAP);
	file[2]->SetTiling(1, 1);
	file[2]->SetTurn(-90);

	file[3] = new Flat('F', vec3(15, 10, 2), vec4(25, 5.0f, 40, 1), -90, roomPos);
	file[3]->SetMirror(true, true);
	file[3]->SetTextureLayer(DIFFUSE_MAP);
	file[3]->SetTiling(1, 1);

	workDesk = new Model(modelNum->workDesk);
	workDesk->SetTRSMatrix(Translate(vec4(0, 0, 0, 1))*Translate(roomPos)*RotateY(-90)*Scale(25.0f, 25.0f, 25.0f));
	workDesk->SetMaterials(vec4(0.95f, 0.95f, 0.95f, 1), vec4(0.85f, 0.85f, 0.85f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	workDesk->SetKaKdKsShini(0, 0.8f, 0.5f, 1);

	for (int i = 0; i < 4; i++)
	{
		isSolve[i] = false;
	}
	
}
void Room2::SetProjectionMatrix(mat4 &mpx)
{
	_pFloor->SetProjectionMatrix(mpx);
	_pTop->SetProjectionMatrix(mpx);
	_LeftWall->SetProjectionMatrix(mpx);
	_RightWall->SetProjectionMatrix(mpx);
	_FrontWall->SetProjectionMatrix(mpx);
	_BackWall->SetProjectionMatrix(mpx);
	//Model
	computer->SetProjectionMatrix(mpx);
	printer->SetProjectionMatrix(mpx);
	file[0]->SetProjectionMatrix(mpx);
	file[1]->SetProjectionMatrix(mpx);
	file[2]->SetProjectionMatrix(mpx);
	file[3]->SetProjectionMatrix(mpx);

	workDesk->SetProjectionMatrix(mpx);

	_door[0]->SetProjectionMatrix(mpx);
	_door[1]->SetProjectionMatrix(mpx);
	_door[2]->SetProjectionMatrix(mpx);
}

void Room2::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);
	//Model
	workDesk->SetViewMatrix(mvx);

	computer->SetViewMatrix(mvx);
	printer->SetViewMatrix(mvx);
	file[0]->SetViewMatrix(mvx);
	file[1]->SetViewMatrix(mvx);
	file[2]->SetViewMatrix(mvx);
	file[3]->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	_door[2]->SetViewMatrix(mvx);
}

void Room2::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);
	//Model
	computer->Update(light, delta);
	printer->Update(light, delta);
	file[0]->Update(light, delta);
	file[1]->Update(light, delta);
	file[2]->Update(light, delta);
	file[3]->Update(light, delta);

	workDesk->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	_door[2]->Update(light, delta);

	if (isSolve[0]) {
		file[0]->SetTRSMatrix(Translate(vec4(7.5, 15.0f, 5, 1)+roomPos)*Scale(5, 10, 2)*RotateX(-90));
	}
	else {
		file[0]->SetTRSMatrix(Translate(vec4(7.5, 12.5f, 5, 1)+roomPos)*Scale(10, 5, 2)*RotateX(-90));
	}
	if (isSolve[1]) {
		file[1]->SetTRSMatrix(Translate(vec4(30, 7.5f, -10, 1)+roomPos)*Scale(2, 15, 10)*RotateZ(90));
	}
	else {
		file[1]->SetTRSMatrix(Translate(vec4(30, 5.0f, -10, 1)+roomPos)*Scale(2, 10, 15)*RotateZ(90));
	}
	if (isSolve[2]) {
		file[2]->SetTRSMatrix(Translate(vec4(-25, 7.5f, -20, 1)+roomPos)*Scale(2, 15, 10)*RotateZ(-90));
	}
	else {
		file[2]->SetTRSMatrix(Translate(vec4(-25, 5.0f, -20, 1)+roomPos)*Scale(2, 10, 15)*RotateZ(-90));
	}
	if (isSolve[3]) {
		file[3]->SetTRSMatrix(Translate(vec4(25, 7.5f, 40, 1) + roomPos)*Scale(10, 15, 2)*RotateX(-90));
	}
	else {
		file[3]->SetTRSMatrix(Translate(vec4(25, 5.0f, 40, 1) + roomPos)*Scale(15, 10, 2)*RotateX(-90));
	}

	DetectCollider();
}

void  Room2::SetSolve() {
	auto camera = Camera::getInstance();
	if (CheckCollider(camera->GetCollider(), file[0]->GetCollider())) {
		isSolve[0] = true;
	}
	else if (CheckCollider(camera->GetCollider(), file[1]->GetCollider())) {
		isSolve[1] = true;
	}
	else if (CheckCollider(camera->GetCollider(), file[2]->GetCollider())) {
		isSolve[2] = true;
	}
	else if (CheckCollider(camera->GetCollider(), file[3]->GetCollider())) {
		isSolve[3] = true;
	}
}

void Room2::DetectCollider() {
	auto camera = Camera::getInstance();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if (!_LeftWall->GetTrigger())camera->Room3isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room3isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room3isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room3isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room3isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room3isTouch = true;
	}
	else camera->Room3isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room3isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room3isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[2]->GetCollider())) {
		if (_door[2]->GetTrigger())camera->Room3isTouch = false;
	}
}

void Room2::Draw()
{
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->g_uiFTexID);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, g_uiFTexID[1]);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->workWall);	
	_FrontWall->Draw();
	_RightWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->workBook);
	_LeftWall->Draw();
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_door[0]->Draw();
	_door[1]->Draw();
	_door[2]->Draw();
	//Model
	workDesk->Draw();

	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->printer);
	printer->Draw();	
	if (isSolve[2]) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->file);
		file[2]->Draw();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->breakfile);
		file[2]->Draw();
	}
	if (isSolve[3]) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->file);
		file[3]->Draw();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->breakfile);
		file[3]->Draw();
	}	
	if (isSolve[0]) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->file);
		file[0]->Draw();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->breakfile);
		file[0]->Draw();
	}

	if (isSolve[1]) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->file);
		file[1]->Draw();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->breakfile);
		file[1]->Draw();
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->computer);
	computer->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);

}

Room2::~Room2() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];
	if (_door[2] != NULL)delete _door[2];

	if (computer != NULL)delete computer;
	if (printer != NULL)delete printer;
	if (file[0] != NULL)delete file[0];
	if (file[1] != NULL)delete file[1];
	if (file[2] != NULL)delete file[2];
	if (file[3] != NULL)delete file[3];

	if (workDesk != NULL)delete workDesk;
}