#include "Room.h"

Room::Room(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體

	Create();

	//auto camera = Camera::getInstance();
	//vT.x = 0.0f; vT.y = 10.0f; vT.z = -10;
	//Test = new ModelPool("Model/Sphere.obj", Type_3DMax);
	//Test->SetCubeMapTexName(1);
	//Test->SetViewPosition(camera->getViewPosition());
	//Test->SetShaderName("vsCubeMapping.glsl", "fsCubeMapping.glsl");
	//Test->SetShader();
	//Test->SetTRSMatrix(Translate(vT)*Translate(roomPos)*Scale(1.0f, 1.0f, 1.0f));
	//Test->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.85f, 0.85f, 0.85f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//Test->SetKaKdKsShini(0, 0.8f, 0.5f, 1);
	//Test->SetColor(vec4(0.9f, 0.9f, 0.9f, 1.0f));
	//Test->SetTextureLayer(DIFFUSE_MAP);

	//vT.x = 0.0f; vT.y = 10.0f; vT.z = 2;
	//Aimal = new Flat('B', vec3(2, 2, 2), vT, 90, roomPos);;
	////Aimal->SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl");
	//Aimal->SetShader();
	////Aimal->SetTRSMatrix(Translate(0, 10.0f, 2.0f) * RotateX(90) *Scale(2, 2, 2));
	//Aimal->SetShadingMode(GOURAUD_SHADING);
	//// 設定貼圖
	//Aimal->SetMaterials(vec4(0,0,0,1), vec4(0.85f, 0.85f, 0.85f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//Aimal->SetKaKdKsShini(0, 0.8f, 0.5f, 1);
	//Aimal->SetTextureLayer(DIFFUSE_MAP);
	////Aimal->isTurn = true;
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
	_LeftWall->SetTurn(-90);
	_LeftWall->SetTextureLayer(DIFFUSE_MAP);
	_LeftWall->SetTiling(10, 10); // 原始為 (10, 10)	

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTurn(90);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);
	_RightWall->SetTiling(10, 10); // 原始為 (10, 10)	

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetMirror(true, true);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetTiling(10, 10); // 原始為 (10, 10)	

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);
	_BackWall->SetTiling(10, 10); // 原始為 (10, 10)	
	

	vT.x = 49.75f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(3, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 0; vT.z = 49.75f;
	_door[1] = new Flat('F', vec3(10, 20, 3), vT, -90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(true);

	auto modelNum = ModelNum::getInstance();
	//Model
	babyCot = new Model(modelNum->babyCot);
	babyCot->SetTRSMatrix(Translate(vec4(0, 0, 0, 1))*Translate(roomPos)*Scale(0.5f, 0.5f, 0.5f));
	babyCot->SetMaterials(vec4(0), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	babyCot->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
	babyCot->SetTextureLayer(DIFFUSE_MAP);
	babyCot->SetTiling(1, 1);

	drawer[0] = new Model(modelNum->drawer);
	drawer[0]->SetTRSMatrix(Translate(vec4(0, 0, -40.0f, 1))*Translate(roomPos)*Scale(30.0f, 30.0f, 30.0f));
	drawer[0]->SetMaterials(vec4(1.0f), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	drawer[0]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
	drawer[0]->SetTextureLayer(DIFFUSE_MAP);
	//Print(drawer[0]->m_iNumVtx);
	//drawer[0]->SetTiling(1, 1);

	drawer[1] = new Model(modelNum->drawer);
	drawer[1]->SetTRSMatrix(Translate(vec4(35, 0, -40.0f, 1))*Translate(roomPos)*Scale(30.0f, 30.0f, 30.0f));
	drawer[1]->SetMaterials(vec4(0), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	drawer[1]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
	drawer[1]->SetTextureLayer(DIFFUSE_MAP);
	drawer[1]->SetTiling(1, 1);

	drawer[2] = new Model(modelNum->drawer);
	drawer[2]->SetTRSMatrix(Translate(vec4(-35, 0, -40.0f, 1))*Translate(roomPos)*Scale(30.0f, 30.0f, 30.0f));
	drawer[2]->SetMaterials(vec4(0), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	drawer[2]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);
	drawer[2]->SetTextureLayer(DIFFUSE_MAP);
	drawer[2]->SetTiling(1, 1);

	parant = new Flat('F', vec3(10, 20, 3), vec4(0, 10, 40.0f, 1), -90, roomPos);
	parant->SetMirror(true, true);
	parant->SetTextureLayer(DIFFUSE_MAP);
	parant->SetTiling(1, 1);

	babyUse[0] = new Flat('R', vec3(1, 10, 10), vec4(30, 5, -20.0f, 1), 90, roomPos);
	babyUse[0]->SetTextureLayer(DIFFUSE_MAP);
	babyUse[0]->SetTiling(1, 1);
	babyUse[0]->SetTurn(90);

	babyUse[1] = new Flat('L', vec3(1, 10, 10), vec4(-35, 5, 0.0f, 1), -90, roomPos);
	babyUse[1]->SetTextureLayer(DIFFUSE_MAP);
	babyUse[1]->SetTiling(1, 1);
	babyUse[1]->SetMirror(true, true);

	babyUse[2] = new Flat('R', vec3(1, 10, 10), vec4(30, 5, 30.0f, 1), 90, roomPos);
	babyUse[2]->SetTextureLayer(DIFFUSE_MAP);
	babyUse[2]->SetTiling(1, 1);

	babyUse[3] = new Flat('L', vec3(1, 10, 15), vec4(-30, 5, 25.0f, 1), -90, roomPos);
	babyUse[3]->SetTextureLayer(DIFFUSE_MAP);
	babyUse[3]->SetTiling(1, 1);
	babyUse[3]->SetTurn(-90);
}

void Room::SetProjectionMatrix(mat4 &mpx)
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
	babyCot->SetProjectionMatrix(mpx);
	drawer[0]->SetProjectionMatrix(mpx);
	drawer[1]->SetProjectionMatrix(mpx);
	drawer[2]->SetProjectionMatrix(mpx);

	parant->SetProjectionMatrix(mpx);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->SetProjectionMatrix(mpx);
	}
}

void Room::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door[0]->SetViewMatrix(mvx);
	_door[1]->SetViewMatrix(mvx);
	//Model
	babyCot->SetViewMatrix(mvx);
	drawer[0]->SetViewMatrix(mvx);
	drawer[1]->SetViewMatrix(mvx);
	drawer[2]->SetViewMatrix(mvx);

	parant->SetViewMatrix(mvx);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->SetViewMatrix(mvx);
	}
	//auto camera = Camera::getInstance();
	//Test->SetViewPosition(camera->getViewPosition());
	//Test->SetViewMatrix(mvx);

	//Aimal->SetViewMatrix(mvx);
}

void Room::Update(LightSource *light, float delta) {
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door[0]->Update(light, delta);
	_door[1]->Update(light, delta);
	//Model
	babyCot->Update(light, delta);
	drawer[0]->Update(light, delta);
	drawer[1]->Update(light, delta);
	drawer[2]->Update(light, delta);

	parant->Update(light, delta);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->Update(light, delta);
	}

	DetectCollider();
}

void Room::DetectCollider() {
	auto camera = Camera::getInstance();
	if (CheckCollider(camera->GetCollider(), _LeftWall->GetCollider()))
	{
		if(!_LeftWall->GetTrigger())camera->Room1isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _RightWall->GetCollider()))
	{
		if (!_RightWall->GetTrigger())camera->Room1isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _FrontWall->GetCollider()))
	{
		if (!_FrontWall->GetTrigger())camera->Room1isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _BackWall->GetCollider()))
	{
		if (!_BackWall->GetTrigger())camera->Room1isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	{
		if (!_pFloor->GetTrigger())camera->Room1isTouch = true;
	}
	else if (CheckCollider(camera->GetCollider(), _pTop->GetCollider()))
	{
		if (!_pTop->GetTrigger())camera->Room1isTouch = true;
	}
	else camera->Room1isTouch = false;

	if (CheckCollider(camera->GetCollider(), _door[0]->GetCollider())) {
		if (_door[0]->GetTrigger())camera->Room1isTouch = false;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger())camera->Room1isTouch = false;
	}
}

void Room::Draw()
{
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyFloor);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyWall); 
	_LeftWall->Draw();	
	_RightWall->Draw();
	_FrontWall->Draw();	
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_door[0]->Draw();
	_door[1]->Draw();
	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->Wood);	
	babyCot->Draw();
	drawer[0]->Draw();
	drawer[1]->Draw();
	drawer[2]->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->parant);
	parant->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyUse[0]);
	babyUse[0]->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyUse[1]);
	babyUse[1]->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyUse[2]);
	babyUse[2]->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->babyUse[3]);
	babyUse[3]->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	//glActiveTexture(GL_TEXTURE0); // select active texture 0
	//glBindTexture(GL_TEXTURE_2D, texture->g_uiFTexID[4]); // 與 Diffuse Map 結合
	//Aimal->Draw();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glActiveTexture(GL_TEXTURE0); // select active texture 0
	//glBindTexture(GL_TEXTURE_2D, texture->g_uiFTexID[6]); // 與 Diffuse Map 結合
	//glActiveTexture(GL_TEXTURE1); // select active texture 1
	//glBindTexture(GL_TEXTURE_CUBE_MAP, texture->g_uiSphereCubeMap);
	//Test->Draw();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

Room::~Room() {	
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if (babyCot != NULL)delete babyCot;
	if(drawer[0] != NULL)delete drawer[0];
	if (drawer[1] != NULL)delete drawer[1];
	if (drawer[2] != NULL)delete drawer[2];

	if (parant != NULL)delete parant;

	for (int i = 0; i < 4; i++)
	{
		if (babyUse[i] != NULL)delete babyUse[i];
	}
}