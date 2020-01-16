#include "Room.h"

Room::Room(vec4 pos)
{
	vec4 vT;
	roomPos = pos;
	// 產生物件的實體

	Create();
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
	_door = new Flat('L', vec3(2, 20, 10), vT, -90, roomPos);
	_door->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door->SetTrigger(false);

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
	parant->SetTextureLayer(DIFFUSE_MAP | LIGHT_MAP);

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

	bullet = new CQuad;
	bullet->SetTextureLayer(DIFFUSE_MAP);
	bullet->SetShader();
	bullet->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.5f, 0.5f, 0.5f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	bullet->SetTRSMatrix(Translate(vec4(0, -5, 0, 1)));
	bullet->_collider.Init(0.5f, 0.5f, 0.5f);
	bulletPos = vec4(0, 0, 0, 1);

	gun = new Flat('F', vec3(10, 5, 3), vec4(25, 2.5f, 45.0f, 1), -90, roomPos);
	gun->SetMirror(false, true);
	gun->SetTextureLayer(DIFFUSE_MAP | LIGHT_MAP);
	gun->SetTrigger(true);
}

void Room::Init() {
	_door->SetTrigger(false);
	_door->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	bullet->SetTRSMatrix(Translate(vec4(0, -5, 0, 1)));
	gun->SetTRSMatrix(Translate(vec4(25, 2.5f, 45.0f, 1))*Translate(roomPos)*Scale(10, 5, 3)*RotateX(-90));
	gun->SetTrigger(true);
	isTake = false;
};

void Room::SetProjectionMatrix(mat4 &mpx)
{
	_pFloor->SetProjectionMatrix(mpx);
	_pTop->SetProjectionMatrix(mpx);
	_LeftWall->SetProjectionMatrix(mpx);
	_RightWall->SetProjectionMatrix(mpx);
	_FrontWall->SetProjectionMatrix(mpx);
	_BackWall->SetProjectionMatrix(mpx);

	_door->SetProjectionMatrix(mpx);
	//Model
	babyCot->SetProjectionMatrix(mpx);
	drawer[0]->SetProjectionMatrix(mpx);
	drawer[1]->SetProjectionMatrix(mpx);
	drawer[2]->SetProjectionMatrix(mpx);

	parant->SetProjectionMatrix(mpx);

	gun->SetProjectionMatrix(mpx);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->SetProjectionMatrix(mpx);
	}

	bullet->SetProjectionMatrix(mpx);
}

void Room::SetViewMatrix(mat4 &mvx) {
	_pFloor->SetViewMatrix(mvx);
	_pTop->SetViewMatrix(mvx);
	_LeftWall->SetViewMatrix(mvx);
	_RightWall->SetViewMatrix(mvx);
	_FrontWall->SetViewMatrix(mvx);
	_BackWall->SetViewMatrix(mvx);

	_door->SetViewMatrix(mvx);
	//Model
	babyCot->SetViewMatrix(mvx);
	drawer[0]->SetViewMatrix(mvx);
	drawer[1]->SetViewMatrix(mvx);
	drawer[2]->SetViewMatrix(mvx);

	parant->SetViewMatrix(mvx);

	gun->SetViewMatrix(mvx);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->SetViewMatrix(mvx);
	}

	bullet->SetViewMatrix(mvx);
}

void Room::Update(LightSource *light, float delta) {
	auto gameManager = GameManager::create();
	_pFloor->Update(light, delta);
	_pTop->Update(light, delta);
	_LeftWall->Update(light, delta);
	_RightWall->Update(light, delta);
	_FrontWall->Update(light, delta);
	_BackWall->Update(light, delta);

	_door->Update(light, delta);
	//Model
	babyCot->Update(light, delta);
	drawer[0]->Update(light, delta);
	drawer[1]->Update(light, delta);
	drawer[2]->Update(light, delta);

	parant->Update(light, delta);

	if(gameManager->room2Enter){
		gun->SetTRSMatrix(Translate(vec4(25, 2.5f, 45.0f, 1))*Translate(roomPos)*Scale(10, 5, 3)*RotateX(-90));
		gun->SetTrigger(true);
		isTake = false;
	}
	else if (isTake) {
		billboard();
	}

	gun->Update(light, delta);

	for (int i = 0; i < 4; i++)
	{
		babyUse[i]->Update(light, delta);
	}

	bullet->Update(light, delta);

	DetectCollider();
}

void Room::DetectCollider() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::create();
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

	if (CheckCollider(camera->GetCollider(), _door->GetCollider())) {
		if (_door->GetTrigger())camera->Room1isTouch = false;
		gameManager->room2Enter = false;
	}
	else if (CheckCollider(camera->GetCollider(), parant->GetCollider())) {
		gameManager->room1Clear = true;
		_door->SetTrigger(true);
		_door->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void Room::billboard() {
	auto camera = Camera::getInstance();

	mat4 rotate;
	float angleCosine;

	vec4 vec = normalize(camera->_front);
	vec4 lookAt = vec4(0, 0, -1, 1);

	angleCosine = -(vec.x*lookAt.x + 0 * lookAt.y + vec.z*lookAt.z);
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999)) {
		if (camera->_front.x <= 0) {
			rotate = RotateY(360.0f - acos(angleCosine) * 180 / 3.14);
		}
		else {
			rotate = RotateY(acos(angleCosine) * 180 / 3.14);// * 180 / 3.14
		}

	}

	gun->SetTRSMatrix(Translate(camera->getViewPosition())*Scale(10, 5, 5)*rotate*Translate(vec4(-1, 0, 1, 1))*RotateX(-90));
}

void Room::SetTake() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::getInstance();
	if (CheckCollider(camera->GetCollider(), gun->GetCollider()) && !isTake) {
		if (gun->GetTrigger())isTake = true;
		gun->SetTrigger(false);
	}
}

void Room::Shoot(vec4 front) {
	mat4 mat;
	bulletPos = front * 100.5f;
	bulletPos.w = 1;
	if (bulletPos.x <= -50) {
		bulletPos.x = -49.8f;
		mat = RotateZ(-90);
	}
	if (bulletPos.x >= 50) {
		bulletPos.x = 49.8f;
		mat = RotateZ(90);
	}
	if (bulletPos.z >= 50) {
		bulletPos.z = 49.8f;
		mat = RotateX(-90);
	}
	if (bulletPos.z <= -50) {
		bulletPos.z = -49.8f;
		mat = RotateX(90);
	}
	if (bulletPos.y >= 50) {
		bulletPos.y = 49.8f;
		mat = RotateX(180);
	}
	if (bulletPos.y <= 0) {
		bulletPos.y = 0.2f;
		mat = RotateX(0);
	}
	bullet->SetTRSMatrix(Translate(bulletPos) * Translate(vec4(0, 0, 0, 1))*Scale(1, 1, 1) * mat);
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

	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->Wood);	
	babyCot->Draw();
	drawer[0]->Draw();
	drawer[1]->Draw();
	drawer[2]->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDepthMask(GL_FALSE);

	_door->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->bullet);
	bullet->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->parant);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->WhiteLight);
	parant->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->gun);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->WhiteLight);
	gun->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDepthMask(GL_TRUE);
}

Room::~Room() {	
	if (_door != NULL)delete _door;

	if (babyCot != NULL)delete babyCot;
	if(drawer[0] != NULL)delete drawer[0];
	if (drawer[1] != NULL)delete drawer[1];
	if (drawer[2] != NULL)delete drawer[2];

	if (parant != NULL)delete parant;

	if(gun != NULL)delete gun;

	for (int i = 0; i < 4; i++)
	{
		if (babyUse[i] != NULL)delete babyUse[i];
	}

	if (bullet != NULL)delete bullet;
}