#ifndef MODELPOOL_H
#define MODELPOOL_H

#include "../header/Angel.h"
#include "CShape.h"

class ModelPool: public CShape
{
public:
	ModelPool(const char*  path, char type = Type_3DMax);
	~ModelPool() {};

	int Num;

	void Draw();
	void DrawW();
protected:
	
};

#endif