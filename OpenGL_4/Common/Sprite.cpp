#include "Sprite.h"

Sprite::Sprite()
{
	m_iNumVtx = QUAD_NUM;
	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;
	m_pLightTex = NULL; m_pNormalTex = NULL; m_pTangentV = NULL;

	m_pPoints = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors = new vec4[m_iNumVtx];
	m_pTex = new vec2[m_iNumVtx];

	// ���B�令���������V�� Z ��V 
	m_pPoints[0] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	m_pPoints[1] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	m_pPoints[2] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	m_pPoints[3] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	m_pPoints[4] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	m_pPoints[5] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);

	m_pNormals[0] = vec3(0, 0, 1.0f);  // Normal Vector �� W �� 0
	m_pNormals[1] = vec3(0, 0, 1.0f);
	m_pNormals[2] = vec3(0, 0, 1.0f);
	m_pNormals[3] = vec3(0, 0, 1.0f);
	m_pNormals[4] = vec3(0, 0, 1.0f);
	m_pNormals[5] = vec3(0, 0, 1.0f);

	m_pTex[0] = vec2(0.0f, 0.0f);
	m_pTex[1] = vec2(1.0f, 0.0f);
	m_pTex[2] = vec2(1.0f, 1.0f);
	m_pTex[3] = vec2(0.0f, 0.0f);
	m_pTex[4] = vec2(1.0f, 1.0f);
	m_pTex[5] = vec2(0.0f, 1.0f);

	// Set shader's name
	SetShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");

	// �w�]�� -1.0f, �� Normal �M�w�C��
	m_pColors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	m_pColors[1] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pColors[2] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pColors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pColors[4] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pColors[5] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Sprite �����U�P�k�W���� local �y��
	m_OriginalLL = vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	m_OriginalTR = vec4(0.5f, 0.5f, 0.0f, 1.0f);

	m_bPushed = false;

	SetShader();

}

void Sprite::Init() {
	m_bPushed = false;
	SetColor(m_DefaultColor);
}

Sprite::~Sprite()
{

}

void Sprite::SetBtnTRSMatrix(mat4 &mat)
{
	m_mxTRS = mat;
	m_bTRSUpdated = true;

	if (m_bViewUpdated || m_bTRSUpdated) {
		m_mxMVFinal = m_mxView * m_mxTRS;
		m_bViewUpdated = m_bTRSUpdated = false;
	}
	// �p�� Sprite �b�@�ɮy�Ъ����U���P�k�W������m
	m_LL = m_mxTRS*m_OriginalLL;
	m_TR = m_mxTRS*m_OriginalTR;
}

// �ǤJ���I�w�g�O������ (-1,-1) (1,1) ������ 2D �y��
bool Sprite::OnTouches(const vec2 &tp)
{
	if (m_LL.x <= tp.x && tp.x <= m_TR.x && m_LL.y <= tp.y && tp.y <= m_TR.y) // �ӫ��s�Q����
	{
		if (!m_bPushed) {
			// �ܦ��Ƕ�
			SetColor(vec4(0.5, 0.5, 0.5, 1.0f));
			m_bPushed = true;
		}
		else {
			m_bPushed = false;
			SetColor(m_DefaultColor);
		}
		return true;		// �Ǧ^���I����s
	}
	else return false;	// �Ǧ^�S���I����s
}

void Sprite::SetDefaultColor(vec4 vColor)
{
	m_DefaultColor = vColor;
	SetColor(vColor);
}

void Sprite::Draw()
{
	DrawingSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}

void Sprite::DrawW()
{
	DrawingWithoutSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}