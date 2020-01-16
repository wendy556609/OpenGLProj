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
	_pFloor->SetTextureLayer(DIFFUSE_MAP|NORMAL_MAP);
	_pFloor->SetTrigger(false);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', vec3(100, 1, 100), vT, 180, roomPos);
	_pTop->SetTrigger(false);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', vec3(1, 50, 100), vT, -90, roomPos);
	_LeftWall->SetTrigger(false);
	//_LeftWall->SetTextureLayer(DIFFUSE_MAP);
	_LeftWall->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.5f), vec4(0.0f, 0.0f, 0.0f, 1.0f));

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', vec3(1, 50, 100), vT, 90, roomPos);
	_RightWall->SetTrigger(false);
	_RightWall->SetTextureLayer(DIFFUSE_MAP);
	_RightWall->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_RightWall->SetTurn(90);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', vec3(100, 50, 1), vT, -90, roomPos);
	_FrontWall->SetTrigger(false);
	_FrontWall->SetTextureLayer(DIFFUSE_MAP);
	_FrontWall->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 0.5f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_FrontWall->SetMirror(true, true);
	//_FrontWall->SetTextureLayer(DIFFUSE_MAP | NORMAL_MAP);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', vec3(100, 50, 1), vT, 90, roomPos);
	_BackWall->SetTrigger(false);
	_BackWall->SetTextureLayer(DIFFUSE_MAP);

	vT.x = -49.5f; vT.y = 10.0f; vT.z = 0;
	_door[0] = new Flat('L', vec3(2, 20, 10), vT, -90, roomPos);
	_door[0]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[0]->SetTrigger(true);
	vT.x = 49.5f; vT.z = 30.0f;
	_door[1] = new Flat('R', vec3(2, 15, 20), vT, 90, roomPos);
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(false);

	auto modelNum = ModelNum::getInstance();
	////Model
	RIP = new Model(modelNum->RIP);
	RIP->SetTRSMatrix(Translate(vec4(30, 0, 0, 1))*Translate(roomPos)*RotateY(-90)*Scale(1.0f, 1.0f, 1.0f));
	RIP->SetTextureLayer(DIFFUSE_MAP);
	RIP->_collider.Init(5, 10, 5, vec4(30, 0, 0, 1)+roomPos);

	auto camera = Camera::getInstance();
	cube[0] = new Model(modelNum->cube);
	cube[0]->SetCubeMapTexName(1);
	cube[0]->SetViewPosition(camera->getViewPosition());
	cube[0]->SetShaderName("vsCubeMapping.glsl", "fsCubeMapping.glsl");
	cube[0]->SetShader();
	cube[0]->SetTRSMatrix(Translate(vec4(-10, -0.5f, 52, 1))*Translate(roomPos)*Scale(20.0f, 20.0f, 1));
	cube[0]->SetTextureLayer(DIFFUSE_MAP);

	cube[1] = new Model(modelNum->cube);
	cube[1]->SetCubeMapTexName(1);
	cube[1]->SetViewPosition(camera->getViewPosition());
	cube[1]->SetShaderName("vsCubeMapping.glsl", "fsCubeMapping.glsl");
	cube[1]->SetShader();
	cube[1]->SetTRSMatrix(Translate(vec4(52, -0.5f, -10, 1))*Translate(roomPos)*Scale(1, 20.0f, 20.0f));
	cube[1]->SetTextureLayer(DIFFUSE_MAP);

	vT.x = -25.0f; vT.y = 15; vT.z = 30;
	butterfly[0] = new Flat('F', vec3(5, 5, 5), vT, -90, roomPos);
	butterfly[0]->SetTrigger(false);
	butterfly[0]->SetTextureLayer(DIFFUSE_MAP);
	butterfly[0]->SetMirror(true, true);
	_pos[0] = vec4(-25.0f, 15, 30, 1);
	initPos = vec4(-25.0f, 15, 30, 1);

	vT.x = 35.0f; vT.y = 25; vT.z = 0;
	butterfly[1] = new Flat('R', vec3(1, 5, 5), vT, 90, roomPos);
	butterfly[1]->SetTrigger(false);
	butterfly[1]->SetTextureLayer(DIFFUSE_MAP);
	butterfly[1]->SetTurn(90);
	butterfly[1]->SetMirror(true, false);
	butterfly[1]->SetTrigger(true);
	_pos[1] = vec4(30, 25, 0, 1);
	_direct = vec4(0, 1, -1, 1);

	vT.x = -25; vT.y = 5; vT.z = 30;
	flower = new Flat('F', vec3(5, 10, 5), vT, -90, roomPos);
	flower->SetTrigger(true);
	flower->SetTextureLayer(DIFFUSE_MAP | LIGHT_MAP);
	flower->SetMaterials(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	flower->SetMirror(true, true);
	flower->SetTurn(-90);
}

void Room5::Init() {
	bool isTake = false;
	_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_door[1]->SetTrigger(false);
	flower->SetTRSMatrix(Translate(vec4(-25, 5, 30, 1))*Translate(roomPos)*Scale(5, 10, 5)*RotateX(-90));
	flower->SetTrigger(true);
	flower->SetTurn(90);
};

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

	cube[0]->SetProjectionMatrix(mpx);
	cube[1]->SetProjectionMatrix(mpx);

	butterfly[0]->SetProjectionMatrix(mpx);
	butterfly[1]->SetProjectionMatrix(mpx);
	flower->SetProjectionMatrix(mpx);
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

	auto camera = Camera::getInstance();
	cube[0]->SetViewPosition(camera->getViewPosition());
	cube[0]->SetViewMatrix(mvx);
	cube[1]->SetViewPosition(camera->getViewPosition());
	cube[1]->SetViewMatrix(mvx);

	butterfly[0]->SetViewMatrix(mvx);
	butterfly[1]->SetViewMatrix(mvx);
	flower->SetViewMatrix(mvx);
	//auto camera = Camera::getInstance();
	//Test->SetViewPosition(camera->getViewPosition());
	//Test->SetViewMatrix(mvx);
}

void Room5::Update(LightSource *light, float delta) {
	auto camera = Camera::getInstance();
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

	cube[0]->Update(light, delta);
	cube[1]->Update(light, delta);

	butterfly[0]->Update(light, delta);
	butterfly[1]->Update(light, delta);

	flower->Update(light, delta);

	if (isTake) {
		billboard();
	}

	DetectCollider();

	Fly(delta);
}

void Room5::billboard() {
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
	
	flower->SetTRSMatrix(Translate(camera->getViewPosition())*Scale(5, 10, 5)*rotate*Translate(vec4(0, 0, 1, 1))*RotateX(-90));
}

void Room5::SetTake() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::getInstance();
	if (CheckCollider(camera->GetCollider(), flower->GetCollider()) && !isTake) {
		if(flower->GetTrigger())isTake = true;
		flower->SetTrigger(false);
	}
	else if (CheckCollider(camera->GetCollider(), RIP->GetCollider()) && isTake) {
		isTake = false;
		gameManager->room6Clear = true;
		_door[1]->SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_door[1]->SetTrigger(true);
		flower->SetTRSMatrix(Translate(vec4(25, 0.5f, 0, 1))*Translate(roomPos)*RotateX(0)*Scale(10, 5, 5));
		flower->SetTurn(-90);
	}
}

void Room5::Fly(float delta) {
	float speed = 10.0f;
	switch (turn)
	{
	case 1:
		_pos[0].x -= speed *delta;
		if (_pos[0].x <= -35) {
			_pos[0].x = -35;
			turn = 2;
			butterfly[0]->SetMirror(true, false);
		}
		_pos[0].y = 15.0f + (-3.0f / 25.0f)*(_pos[0].x + 30.0f)*(_pos[0].x + 30.0f) + 3.0f;
		//Print(_pos[0]);
		break;
	case 2:
		_pos[0].x += speed *delta;
		if (_pos[0].x >= -25) {
			_pos[0].x = -25;
			turn = 3;			
		}
		_pos[0].y = 15.0f + (3.0f / 25.0f)*(_pos[0].x + 30.0f)*(_pos[0].x + 30.0f) - 3.0f;
		break;
	case 3:
		_pos[0].x += speed *delta;
		if (_pos[0].x >= -15) {
			_pos[0].x = -15;
			turn = 4;			
			butterfly[0]->SetMirror(true, false);
		}
		_pos[0].y = 15.0f + (-3.0f / 25.0f)*(_pos[0].x + 20.0f)*(_pos[0].x + 20.0f) + 3.0f;
		break;
	case 4:
		_pos[0].x -= speed *delta;
		if (_pos[0].x <= -25) {
			_pos[0].x = -25;
			turn = 1;			
		}
		_pos[0].y = 15.0f + (3.0f / 25.0f)*(_pos[0].x + 20.0f)*(_pos[0].x + 20.0f) - 3.0f;
		break;
	default:
		break;
	}
	butterfly[0]->SetPosition(_pos[0]);

	_pos[1] += _direct *delta*10.0f;
	butterfly[1]->SetPosition(_pos[1]);
}

void Room5::DetectCollider() {
	auto camera = Camera::getInstance();
	auto gameManager = GameManager::getInstance();
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
		gameManager->room6Enter = true;
	}
	else if (CheckCollider(camera->GetCollider(), _door[1]->GetCollider())) {
		if (_door[1]->GetTrigger()) {
			camera->Room6isTouch = false;
			gameManager->room6Enter = false;
			gameManager->allClear = true;
		}
	}


	if (CheckCollider(butterfly[1]->GetCollider(), _pFloor->GetCollider())) {
		if (butterfly[1]->GetTrigger()) {
			_direct.y *= -1;
			butterfly[1]->SetTrigger(false);
		}
	}
	else if (CheckCollider(butterfly[1]->GetCollider(), _FrontWall->GetCollider())) {
		if (butterfly[1]->GetTrigger()) {
			_direct.z *= -1;
			butterfly[1]->SetMirror(true, false);
			butterfly[1]->SetTrigger(false);
		}	
	}
	else if (CheckCollider(butterfly[1]->GetCollider(), _BackWall->GetCollider())) {
		if (butterfly[1]->GetTrigger()) {
			_direct.z *= -1;
			butterfly[1]->SetMirror(true, false);
			butterfly[1]->SetTrigger(false);
		}
	}
	else if (CheckCollider(butterfly[1]->GetCollider(), _pTop->GetCollider())) {
		if (butterfly[1]->GetTrigger()) {
			_direct.y *= -1;
			butterfly[1]->SetTrigger(false);
		}
	}
	else {
		butterfly[1]->SetTrigger(true);
	}
}

void Room5::Draw()
{
	auto gameManager = GameManager::getInstance();
	auto texture = Texture::getInstance();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->grassland);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture->NormalMap);
	_pFloor->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_pTop->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->Sunny_NZ);
	_BackWall->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_door[0]->Draw();

	//Model
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->metal);
	RIP->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0); // select active texture 0
	glBindTexture(GL_TEXTURE_2D, texture->metal); // 與 Diffuse Map 結合
	glActiveTexture(GL_TEXTURE1); // select active texture 1
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->g_uiSphereCubeMap);
	cube[0]->Draw();
	cube[1]->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (gameManager->room6Clear)_door[1]->Draw();

	glDepthMask(GL_FALSE);	
	if(!gameManager->room6Clear)_door[1]->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->ladder);
	_RightWall->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->RIP);
	_FrontWall->Draw();
	glDepthMask(GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
		//glActiveTexture(GL_TEXTURE0); // select active texture 0
		//glBindTexture(GL_TEXTURE_2D, texture->g_uiFTexID[6]); // 與 Diffuse Map 結合
		//glActiveTexture(GL_TEXTURE1); // select active texture 1
		//glBindTexture(GL_TEXTURE_CUBE_MAP, texture->g_uiSphereCubeMap);
		//Test->Draw();
		//glBindTexture(GL_TEXTURE_2D, 0);
}

void Room5::AlphaDraw() {
	//glDepthMask(GL_FALSE);
	//glBindTexture(GL_TEXTURE_2D, 0);	
	auto texture = Texture::getInstance();
	_LeftWall->Draw();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->butterfly);
	butterfly[1]->Draw();
	butterfly[0]->Draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->flower);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->WhiteLight);
	flower->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDepthMask(GL_TRUE);
}

Room5::~Room5() {
	if (_door[0] != NULL)delete _door[0];
	if (_door[1] != NULL)delete _door[1];

	if(RIP != NULL)delete RIP;
	if(cube[0] != NULL)delete cube[0];
	if (cube[1] != NULL)delete cube[1];

	if (butterfly[0] != NULL)delete butterfly[0];
	if (butterfly[1] != NULL)delete butterfly[1];

	if (flower != NULL)delete flower;
}