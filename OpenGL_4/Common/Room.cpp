#include "Room.h"

Room::Room(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體
	g_uiSphereCubeMap = CubeMap_load_SOIL("texture/Sunny_PX.png", "texture/Sunny_NX.png", "texture/Sunny_NY.png", "texture/Sunny_PY.png", "texture/Sunny_PZ.png", "texture/Sunny_NZ.png");

	Create();

	auto camera = Camera::getInstance();
	vT.x = 0.0f; vT.y = 10.0f; vT.z = -10;
	Test = new ModelPool("Model/Sphere.obj", Type_3DMax);
	Test->SetCubeMapTexName(1);
	Test->SetViewPosition(camera->getViewPosition());
	Test->SetShaderName("vsCubeMapping.glsl", "fsCubeMapping.glsl");
	Test->SetShader();
	Test->SetTRSMatrix(Translate(vT)*Translate(roomPos)*Scale(1.0f, 1.0f, 1.0f));
	Test->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.85f, 0.85f, 0.85f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Test->SetKaKdKsShini(0, 0.8f, 0.5f, 1);
	Test->SetColor(vec4(0.9f, 0.9f, 0.9f, 1.0f));
	Test->SetTextureLayer(DIFFUSE_MAP);
}

void Room::Create() {
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

	vT.x = -49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(3, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = -50.5f;
	_door[1] = new Flat('R', vec3(3, 20, 10), vT, 90, roomPos);
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

	_pBench[0] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[0]->SetTRSMatrix(Translate(vec4(-25.0f, 0.0f, 25.0f, 1))*Translate(roomPos)*RotateY(135.0f)*Scale(1.0f, 1.0f, 1.0f));
	_pBench[0]->SetMaterials(vec4(0), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pBench[0]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pBench[1] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[1]->SetTRSMatrix(Translate(vec4(25.0f, 0.0f, 25.0f, 1))*Translate(roomPos)*RotateY(-135.0f)*Scale(1.0f, 1.0f, 1.0f));
	_pBench[1]->SetMaterials(vec4(0), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pBench[1]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pBench[2] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[2]->SetTRSMatrix(Translate(vec4(0, 0.0f, -30.0f, 1))*Translate(roomPos)*Scale(1.0f, 1.0f, 1.0f));
	_pBench[2]->SetMaterials(vec4(0), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pBench[2]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
}

void Room::SetProjectionMatrix(mat4 &mpx)
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
	_pBench[0]->SetProjectionMatrix(mpx);
	_pBench[1]->SetProjectionMatrix(mpx);
	_pBench[2]->SetProjectionMatrix(mpx);

	_door[0]->SetProjectionMatrix(mpx);
	_door[1]->SetProjectionMatrix(mpx);

	Test->SetProjectionMatrix(mpx);
}

void Room::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);
	//Model
	_pTeaPot->SetViewMatrix(mvx);
	_pTable->SetViewMatrix(mvx);
	_pBench[0]->SetViewMatrix(mvx);
	_pBench[1]->SetViewMatrix(mvx);
	_pBench[2]->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);

	auto camera = Camera::getInstance();
	Test->SetViewPosition(camera->getViewPosition());
	Test->SetViewMatrix(mvx);
}

void Room::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);
	//Model
	_pTeaPot->Update(light, delta);
	_pTable->Update(light, delta);
	_pBench[0]->Update(light, delta);
	_pBench[1]->Update(light, delta);
	_pBench[2]->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);

	Test->Update(light, delta);

	DetectCollider();
}

void Room::DetectCollider() {
	auto camera = Camera::create();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if(!_LeftWall->GetTrigger())camera->isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->isTouch = true;
	}
	else camera->isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->isTouch = false;
	}
}

void Room::Draw()
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
	_pBench[0]->Draw();
	_pBench[1]->Draw();
	_pBench[2]->Draw();

	_door[0]->Draw();
	_door[1]->Draw();
	glActiveTexture(GL_TEXTURE0); // select active texture 0
	glBindTexture(GL_TEXTURE_2D, g_uiFTexID[6]); // 與 Diffuse Map 結合
	glActiveTexture(GL_TEXTURE1); // select active texture 1
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_uiSphereCubeMap);
	Test->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

Room::~Room() {	
	if (_pTeaPot != NULL)delete _pTeaPot;
	if (_pTable != NULL)delete _pTable;
	if (_pBench[0] != NULL)delete _pBench[0];
	if (_pBench[1] != NULL)delete _pBench[1];
	if (_pBench[2] != NULL)delete _pBench[2];
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];
	if (Test != NULL)delete Test;
}