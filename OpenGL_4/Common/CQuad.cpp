#include <cmath>
#include "CQuad.h"
// Example 4 �}�l
// ���P Example 3 �¤W(Y�b)
// �C�@�� Vertex �W�[ Normal �A�令�~���� CShape�A�@�ֳB�z�������]�w�ݨD

CQuad::CQuad()
{
	m_iNumVtx = QUAD_NUM;
	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;
	m_pLightTex = NULL; m_pNormalTex = NULL; m_pTangentV = NULL;

	m_pPoints  = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors  = new vec4[m_iNumVtx]; 
	m_pTex = new vec2[m_iNumVtx];
	m_pLightTex = new vec2[m_iNumVtx];
	m_pNormalTex = new vec2[m_iNumVtx];
	m_pTangentV = new vec3[m_iNumVtx];

	m_pPoints[0] = vec4( -0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[1] = vec4(  0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[2] = vec4(  0.5f, 0.0f, -0.5f, 1.0f);
	m_pPoints[3] = vec4( -0.5f, 0.0f,  0.5f, 1.0f);
	m_pPoints[4] = vec4(  0.5f, 0.0f, -0.5f, 1.0f);
	m_pPoints[5] = vec4( -0.5f, 0.0f, -0.5f, 1.0f);

	m_pNormals[0] = vec3(  0, 1.0f, 0);  // Normal Vector �� W �� 0
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

	m_pTex[0] = vec2(0.0f, 0.0f);
	m_pTex[1] = vec2(1.0f, 0.0f);
	m_pTex[2] = vec2(1.0f, 1.0f);
	m_pTex[3] = vec2(0.0f, 0.0f);
	m_pTex[4] = vec2(1.0f, 1.0f);
	m_pTex[5] = vec2(0.0f, 1.0f);

	m_pLightTex[0] = vec2(0.0f, 0.0f);
	m_pLightTex[1] = vec2(1.0f, 0.0f);
	m_pLightTex[2] = vec2(1.0f, 1.0f);
	m_pLightTex[3] = vec2(0.0f, 0.0f);
	m_pLightTex[4] = vec2(1.0f, 1.0f);
	m_pLightTex[5] = vec2(0.0f, 1.0f);

	m_pNormalTex[0] = vec2(0.0f, 0.0f);
	m_pNormalTex[1] = vec2(1.0f, 0.0f);
	m_pNormalTex[2] = vec2(1.0f, 1.0f);
	m_pNormalTex[3] = vec2(0.0f, 0.0f);
	m_pNormalTex[4] = vec2(1.0f, 1.0f);
	m_pNormalTex[5] = vec2(0.0f, 1.0f);

	for (int i = 0; i < 6; i += 3) { // �T�� vertex �@��
		float dU1 = m_pNormalTex[i + 1].x - m_pNormalTex[i].x;
		float dV1 = m_pNormalTex[i + 1].y - m_pNormalTex[i].y;
		float dU2 = m_pNormalTex[i + 2].x - m_pNormalTex[i].x;
		float dV2 = m_pNormalTex[i + 2].y - m_pNormalTex[i].y;
		float f = 1.0f / (dU1 * dV2 - dU2*dV1);
		vec4 E1 = m_pPoints[i + 1] - m_pPoints[i];
		vec4 E2 = m_pPoints[i + 2] - m_pPoints[i];

		vec3 tangent;
		tangent.x = f*(dV2 * E1.x + E2.x * (-dV1));
		tangent.y = f*(dV2 * E1.y + E2.y * (-dV1));
		tangent.z = f*(dV2 * E1.z + E2.z * (-dV1));

		m_pTangentV[i] += tangent;
		m_pTangentV[i + 1] += tangent;
		m_pTangentV[i + 2] = tangent;
	}
	for (int i = 0; i < 6; i++)m_pTangentV[i] = normalize(m_pTangentV[i]);
		
	for( int i = 0 ; i < m_iNumVtx ; i++ ) m_pColors[i] = vec4(-1.0f,-1.0f,-1.0f,1.0f);

	_normal = vec4(0, 1.0f, 0, 0);

	SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl"); 
}

void CQuad::SetVtxColors(vec4 vLFColor, vec4 vLRColor, vec4 vTRColor, vec4 vTLColor)
{
	m_pColors[3] = m_pColors[0] = vLFColor;
	m_pColors[1] = vLRColor;
	m_pColors[4] = m_pColors[2] = vTRColor;
	m_pColors[5] = vTLColor;

	// �N�Ҧ� vertices �C���s�� VBO ��
	glBindBuffer( GL_ARRAY_BUFFER, m_uiBuffer );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx+sizeof(vec3)*m_iNumVtx, sizeof(vec4)*m_iNumVtx, m_pColors ); // vertcies' Color
}

void CQuad::SetVtxColors(vec4 vFColor, vec4 vSColor) // �]�w��ӤT���Ϊ��C��
{
	m_pColors[0] = m_pColors[1] = m_pColors[2] = vFColor;
	m_pColors[3] = m_pColors[4] = m_pColors[5] = vSColor;

	// �N�Ҧ� vertices �C���s�� VBO ��
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
