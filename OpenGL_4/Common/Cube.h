#ifndef CUBE_H
#define CUBE_H
#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define SOLIDCUBE_NUM 36  // 6 faces, 2 triangles/face , 3 vertices/triangle

class Cube : public CShape
{
private:
	vec4 m_vertices[8];
	int  m_iIndex;

	void Quad(int a, int b, int c, int d);
public:
	Cube();
	~Cube() {};

	void Draw();
	void DrawW();
};

#endif