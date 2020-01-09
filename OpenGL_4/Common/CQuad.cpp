#include <cmath>
#include "CQuad.h"
// Example 4 開始
// 面同 Example 3 朝上(Y軸)
// 每一個 Vertex 增加 Normal ，改成繼曾自 CShape，一併處理相關的設定需求

CQuad::CQuad()
{
	m_iNumVtx = QUAD_NUM;
	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;

	m_pPoints  = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors  = new vec4[m_iNumVtx]; 

	m_pPoints[0] = vec4( -0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[1] = vec4(  0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[2] = vec4(  0.5f, 0.0f, -0.5f, 1.0f);
	m_pPoints[3] = vec4( -0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[4] = vec4(  0.5f, 0.0f, -0.5f, 1.0f);
	m_pPoints[5] = vec4( -0.5f, 0.0f, -0.5f, 1.0f);

	m_pNormals[0] = vec3(  0, 1.0f, 0);  // Normal Vector 的 W 為 0
	m_pNormals[1] = vec3(  0, 1.0f, 0);
	m_pNormals[2] = vec3(  0, 1.0f, 0);
	m_pNormals[3] = vec3(  0, 1.0f, 0);
	m_pNormals[4] = vec3(  0, 1.0f, 0);
	m_pNormals[5] = vec3(  0, 1.0f, 0);

	m_pColors[0] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);  // (r, g, b, a)
	m_pColors[1] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);
	m_pColors[2] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);
	m_pColors[3] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);
	m_pColors[4] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);
	m_pColors[5] = vec4( 1.0f, 1.0f,  1.0f, 1.0f);

	for( int i = 0 ; i < m_iNumVtx ; i++ ) m_pColors[i] = vec4(-1.0f,-1.0f,-1.0f,1.0f);

	SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl"); 
}

void CQuad::SetVtxColors(vec4 vLFColor, vec4 vLRColor, vec4 vTRColor, vec4 vTLColor)
{
	m_pColors[3] = m_pColors[0] = vLFColor;
	m_pColors[1] = vLRColor;
	m_pColors[4] = m_pColors[2] = vTRColor;
	m_pColors[5] = vTLColor;

	// 將所有 vertices 顏色更新到 VBO 中
	glBindBuffer( GL_ARRAY_BUFFER, m_uiBuffer );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx+sizeof(vec3)*m_iNumVtx, sizeof(vec4)*m_iNumVtx, m_pColors ); // vertcies' Color
}

void CQuad::SetVtxColors(vec4 vFColor, vec4 vSColor) // 設定兩個三角形的顏色
{
	m_pColors[0] = m_pColors[1] = m_pColors[2] = vFColor;
	m_pColors[3] = m_pColors[4] = m_pColors[5] = vSColor;

	// 將所有 vertices 顏色更新到 VBO 中
	glBindBuffer( GL_ARRAY_BUFFER, m_uiBuffer );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx+sizeof(vec3)*m_iNumVtx, sizeof(vec4)*m_iNumVtx, m_pColors ); // vertcies' Color
}

void CQuad::Draw()
{
	DrawingSetShader();
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );
}

void CQuad::DrawW()
{
	DrawingWithoutSetShader();
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );
}
