#ifndef MODEL_H
#define MODEL_H

#include "../header/Angel.h"
#include "CShape.h"
#include "ModelPool.h"

class Model : public CShape
{
public:
	//Model(const char*  path, char type = Type_3DMax);
	Model(int modelNum);
	~Model() {};

	int Num;

	void Draw();
	void DrawW();
protected:

};



class ModelNum
{
protected:
	ModelNum();			// �קK�Q�~��
	~ModelNum();
	void initDefault() {};
	static ModelNum* _pModelNum;
public:
	int babyCot, drawer;
	int desk;
	int workDesk;


	static ModelNum* create();		// �إ� TexturePool ������
	static ModelNum *getInstance();	// ���o  TexturePool ������

	void destroyInstance();

	void SetModel() {
		auto modelpool = ModelPool::create();
		babyCot = modelpool->AddModel("Model/BabyCot.obj");
		drawer = modelpool->AddModel("Model/Drawer.obj");
		desk = modelpool->AddModel("Model/Desk.obj");
		workDesk = modelpool->AddModel("Model/workDesk.obj");
	};

};

#endif