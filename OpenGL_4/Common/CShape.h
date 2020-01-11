#ifndef CSHAPE_H
#define CSHAPE_H
#include "../Header/Angel.h"
#include "TypeDefine.h"
#include "TexturePool.h"
#include "Collider.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define LightCount 4
#define FLAT_SHADING    0
#define GOURAUD_SHADING 1

#define LIGHTING_WITHGPU

#define SPOT_LIGHT 1

#define Type_3DMax 'M'
#define Type_Blender 'B'

class CShape 
{
protected:
	vec4 *m_pPoints;
	vec3 *m_pNormals;
	vec4 *m_pColors;
	vec2 *m_pTex;
	vec2 *m_pLightTex;
	vec2 *m_pNormalTex;
	vec3 *m_pTangentV;
	int  m_iNumVtx;

	GLfloat m_fColor[4]; // Object's color
	// For shaders' name
	char *m_pVXshader, *m_pFSshader;

	// For VAO
	GLuint m_uiVao;

	// For Shader
	GLuint  m_uiModelView, m_uiProjection, m_uiColor;
	GLuint  m_uiProgram;
	GLuint  m_uiBuffer;
	GLuint  m_uiTexLayer;	// �K�Ϫ��h���A�w�]�N�O�@�h diffuse
	GLuint	m_uiCubeMap, m_uiViewPos, m_uiTRS;
	GLuint  m_uiCubeMapTexName;  // �ǤJ pixel shader ���� Cube map ���K�Ͻs���A 

	//API
	point4  m_vLightInView[LightCount];	 // �����b�@�ɮy�Ъ���m
	GLuint  m_uiLightInView[LightCount];	 // �����b shader ����m
	GLuint  m_uiAmbient[LightCount];		 // light's ambient  �P Object's ambient  �P ka �����n
	GLuint  m_uiDiffuse[LightCount];
	GLuint  m_uiDiffuseProduct[LightCount];		 // light's diffuse  �P Object's diffuse  �P kd �����n
	GLuint  m_uiSpecular[LightCount];	 // light's specular �P Object's specular �P ks �����n
	GLuint  m_uiShininess;
	GLuint  m_uiLighting[LightCount];
	GLuint  m_uiSpotCutoff[LightCount];
	GLuint  m_uiLightType[LightCount];
	GLuint  m_uiLightDir[LightCount];
	GLuint  m_uiSpotExponent[LightCount];

	LightSource m_Light1;

	point4  m_v4Eye;
	//Light
	color4 m_Diffuse[LightCount];
	color4 m_AmbientProduct[LightCount];
	color4 m_DiffuseProduct[LightCount];
	color4 m_SpecularProduct[LightCount];
	vec3 m_LightDir[LightCount];
	float m_SpotExponent[LightCount];
	float m_spotCutoff[LightCount];
	int lightType[LightCount]; // �O������
	int    m_iLighting[LightCount];	// �]�w�O�_�n���O

	//Texure
	int    m_iTexLayer;		// �]�w�K�Ϫ��h���A0 ��ܨS���K��

	// For Matrices
	mat4    m_mxView, m_mxProjection, m_mxTRS;
	mat4    m_mxMVFinal;
	mat3    m_mxMV3X3Final, m_mxITMV;	// �ϥΦb�p�� �������᪺�s Normal
	mat3		m_mxITView;		// View Matrix �� Inverse Transport 
	bool    m_bProjUpdated, m_bViewUpdated, m_bTRSUpdated;

	// For materials
	Material m_Material;

	// For Shading Mode
	// 0: Flat shading, 1: Gouraud shading, 0 for default
	// �n�ܧ�W��Ҧ��A�Q�� SetShadingMode �ӧ���
	int m_iMode;		

	void		CreateBufferObject();
	void		DrawingSetShader();
	void		DrawingWithoutSetShader();

public:
	Collider _collider;

	CShape();

	void SetAPI();

	virtual ~CShape();
	virtual void Draw() = 0;
	virtual void DrawW() = 0; // Drawing without setting shaders
	void Update(const LightSource *Lights, float dt);
	void Update(float dt);

	void SetShaderName(const char vxShader[], const char fsShader[]);
	void SetShader(GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	void SetColor(vec4 vColor);
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);

	// For setting materials 
	void SetMaterials(color4 ambient, color4 diffuse, color4 specular);
	void SetKaKdKsShini(float ka, float kd, float ks, float shininess); // ka kd ks shininess

	// For Lighting Calculation
	void SetShadingMode(int iMode) {m_iMode = iMode;}
	void SetTextureLayer(int texlayer);
	void SetTiling(float uTiling, float vTiling);
	void SetLightMapTiling(float uTiling, float vTiling);
	void SetMirror(bool uAxis, bool vAxis);

	Collider GetCollider() { return _collider; };
	void SetTrigger(bool trigger) { _collider.SetTrigger(trigger); };
	bool GetTrigger() { return _collider.GetTrigger(); };

	void SetCubeMapTexName(GLuint uiTexName) {
		m_uiCubeMapTexName = uiTexName;
	}
	void SetViewPosition(point4 vEye) {
		m_v4Eye = vEye;
	}
};

#endif
