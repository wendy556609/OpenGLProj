#ifndef SPHERE_H
#define SPHERE_H
#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define SOLIDCUBE_NUM 36  // 6 faces, 2 triangles/face , 3 vertices/triangle

class Sphere : public CShape
{
private:
	GLfloat m_fRadius;
	GLint m_iSlices, m_iStacks;

	vec4 m_Points[SOLIDCUBE_NUM];
	vec3 m_Normals[SOLIDCUBE_NUM];
	vec4 m_vertices[8];
	int  m_iIndex;

public:
	Sphere(const GLfloat fRadius = 1.0f, const int iSlices = 12, const  int iStacks = 6);
	~Sphere();
	// Sphere 的繪製方始使用多組的 GL_TRIANGLE_STRIP 來繪製, 因此沒有辦法提供 Flat Shading，
	// 只有以 vertex 為基礎的計算顏色的 Ground Shading
	
	void Draw();
	void DrawW(); // 呼叫不再次設定 Shader 的描繪方式

};

#endif