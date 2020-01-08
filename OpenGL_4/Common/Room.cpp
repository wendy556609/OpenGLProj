#include "Room.h"

Room::Room()
{
	mat4 mxT;
	vec4 vT, vColor;
	// 產生物件的實體
	vT.x = 0; vT.y = 0; vT.z = 0;
	_pFloor = new Flat('M', iSize, vT);

	vT.x = 0; vT.y = 50.0f; vT.z = 0;
	_pTop = new Flat('T', iSize, vT);

	vT.x = -50.0f; vT.y = 25.0f; vT.z = 0;
	_LeftWall = new Flat('L', iSize, vT);

	vT.x = 50.0f; vT.y = 25.0f; vT.z = 0;
	_RightWall = new Flat('R', iSize, vT);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = 50.0f;
	_FrontWall = new Flat('F', iSize, vT);

	vT.x = 0.0f; vT.y = 25.0f; vT.z = -50.0f;
	_BackWall = new Flat('B', iSize, vT);

	////Model

	_pTeaPot = new ModelPool("Model/TeaPot.obj", Type_3DMax);
	_pTeaPot->SetTRSMatrix(Translate(vec4(0, 5.3f, 0, 1))*Scale(2.0f, 2.0f, 2.0f));
	_pTeaPot->SetMaterials(vec4(0), vec4(0.75f, 0.75f, 0.75f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pTeaPot->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pTable = new ModelPool("Model/table.obj", Type_3DMax);
	_pTable->SetTRSMatrix(Translate(vec4(0, 0.0f, 0, 1))*Scale(0.5f, 0.5f, 0.5f));
	_pTable->SetMaterials(vec4(0), vec4(0.72f, 0.45f, 0.2f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pTable->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pBench[0] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[0]->SetTRSMatrix(Translate(vec4(-25.0f, 0.0f, 25.0f, 1))*RotateY(135.0f)*Scale(1.0f, 1.0f, 1.0f));
	_pBench[0]->SetMaterials(vec4(0), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pBench[0]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pBench[1] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[1]->SetTRSMatrix(Translate(vec4(25.0f, 0.0f, 25.0f, 1))*RotateY(-135.0f)*Scale(1.0f, 1.0f, 1.0f));
	_pBench[1]->SetMaterials(vec4(0), vec4(1.0f, 1.0f, 1.0f, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_pBench[1]->SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	_pBench[2] = new ModelPool("Model/Bench.obj", Type_3DMax);
	_pBench[2]->SetTRSMatrix(Translate(vec4(0, 0.0f, -30.0f, 1))*Scale(1.0f, 1.0f, 1.0f));
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

	DetectCollider();
}

void Room::DetectCollider() {
	//auto camera = Camera::create();
	//if (CheckCollider(camera->GetCollider(), _pFloor->GetCollider()))
	//{
	//	camera->isTouch = true;
	//}
	//else {
	//	camera->isTouch = false;
	//}
}

void Room::Draw()
{
	_pFloor->Draw();
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
}

Room::~Room() {	
	if (_pTeaPot != NULL)delete _pTeaPot;
	if (_pTable != NULL)delete _pTable;
	if (_pBench[0] != NULL)delete _pBench[0];
	if (_pBench[1] != NULL)delete _pBench[1];
	if (_pBench[2] != NULL)delete _pBench[2];
}