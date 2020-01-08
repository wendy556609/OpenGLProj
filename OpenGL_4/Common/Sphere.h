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
	// Sphere ��ø�s��l�ϥΦh�ժ� GL_TRIANGLE_STRIP ��ø�s, �]���S����k���� Flat Shading�A
	// �u���H vertex ����¦���p���C�⪺ Ground Shading
	
	void Draw();
	void DrawW(); // �I�s���A���]�w Shader ���yø�覡

};

#endif