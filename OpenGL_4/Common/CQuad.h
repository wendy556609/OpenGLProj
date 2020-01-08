#ifndef CQUAD_H
#define CQUAD_H
#include "../header/Angel.h"
#include "CShape.h"

#define QUAD_NUM 6		// 2 faces, 2 triangles/face 

class CQuad : public CShape
{
private:

	//vec4 m_Points[QUAD_NUM];
	//vec3 m_Normal[QUAD_NUM];	// 用 vec3 來宣告是為了節省計算, 如果要讓程式寫起來更方便，可改用 vec4 來宣告
	//vec4 m_Colors[QUAD_NUM];

public:
	CQuad();

	void SetNormal(vec3 normal);

	GLuint GetShaderHandle() { return m_uiProgram;} 
	void SetVtxColors(vec4 vLFColor, vec4 vLRColor, vec4 vTRColor, vec4 vTLColor); // four Vertices' Color
	void SetVtxColors(vec4 vFColor, vec4 vSColor);	// three Vertices' Color with idx as the first 

	void Draw();
	void DrawW();
};




#endif