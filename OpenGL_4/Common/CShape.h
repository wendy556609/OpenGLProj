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
	GLuint  m_uiTexLayer;	// 貼圖的層次，預設就是一層 diffuse
	GLuint	m_uiCubeMap, m_uiViewPos, m_uiTRS;
	GLuint  m_uiCubeMapTexName;  // 傳入 pixel shader 中的 Cube map 的貼圖編號， 

	//API
	point4  m_vLightInView[LightCount];	 // 光源在世界座標的位置
	GLuint  m_uiLightInView[LightCount];	 // 光源在 shader 的位置
	GLuint  m_uiAmbient[LightCount];		 // light's ambient  與 Object's ambient  與 ka 的乘積
	GLuint  m_uiDiffuse[LightCount];
	GLuint  m_uiDiffuseProduct[LightCount];		 // light's diffuse  與 Object's diffuse  與 kd 的乘積
	GLuint  m_uiSpecular[LightCount];	 // light's specular 與 Object's specular 與 ks 的乘積
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
	int lightType[LightCount]; // 燈光種類
	int    m_iLighting[LightCount];	// 設定是否要打燈

	//Texure
	int    m_iTexLayer;		// 設定貼圖的層次，0 表示沒有貼圖

	// For Matrices
	mat4    m_mxView, m_mxProjection, m_mxTRS;
	mat4    m_mxMVFinal;
	mat3    m_mxMV3X3Final, m_mxITMV;	// 使用在計算 物體旋轉後的新 Normal
	mat3		m_mxITView;		// View Matrix 的 Inverse Transport 
	bool    m_bProjUpdated, m_bViewUpdated, m_bTRSUpdated;

	// For materials
	Material m_Material;

	// For Shading Mode
	// 0: Flat shading, 1: Gouraud shading, 0 for default
	// 要變更上色模式，利用 SetShadingMode 來改變
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
