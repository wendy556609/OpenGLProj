#include "CShape.h"

CShape::CShape()
{
	m_bTRSUpdated = m_bViewUpdated = m_bProjUpdated = false;
	// ambient 預設為 0, diffuse, specular 的顏色都是灰色 0.5
	// Ka = 0 係數 , kd = 0.8 , ks = 0.2
	m_Material.ambient = vec4(vec3(0));
	m_Material.diffuse = vec4(vec3(0.5f));
	m_Material.specular = vec4(vec3(0.5f));
	m_Material.ka = 0; m_Material.kd = 0.8f; m_Material.ks = 0.2f;
	m_Material.shininess = 2.0f;

	m_iMode = GOURAUD_SHADING;

	// 預設為 RGBA 為 (0.5,0.5,0.5,1.0) , 由這個灰階顏色來代表的物件顏色
	m_fColor[0] = 0.5f; m_fColor[1] = 0.5f; m_fColor[2] = 0.5f; m_fColor[3] = 1.0f;

	m_iLighting[0] = 1; // 預設接受燈光的照明
	m_iLighting[1] = 1;
	m_iLighting[2] = 1;
	m_iLighting[3] = 1;

	m_iTexLayer = 0;		// 預設有一張 Diffuse 貼圖

	m_pPoints = nullptr; 	m_pNormals = nullptr; 	m_pColors = nullptr; 	m_pTex = nullptr;
}

CShape::~CShape()
{
	if( m_pPoints  != NULL ) delete [] m_pPoints;  
	if( m_pNormals != NULL ) delete	[] m_pNormals;
	if( m_pColors  != NULL ) delete	[] m_pColors;
	if( m_pTex != NULL ) delete [] m_pTex;

	if( m_pVXshader != NULL ) delete [] m_pVXshader;
	if( m_pFSshader != NULL ) delete [] m_pFSshader;
}

void CShape::CreateBufferObject()
{
    glGenVertexArrays( 1, &m_uiVao );
    glBindVertexArray( m_uiVao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &m_uiBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_uiBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx + sizeof(vec3)*m_iNumVtx + sizeof(vec4)*m_iNumVtx + sizeof(vec2)*m_iNumVtx, NULL, GL_STATIC_DRAW );
	// sizeof(vec4)*m_iNumVtx + sizeof(vec3)*m_iNumVtx + sizeof(vec4)*m_iNumVtx <- vertices, normal and color

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec4)*m_iNumVtx, m_pPoints );  // vertices
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx, sizeof(vec3)*m_iNumVtx, m_pNormals ); // // vertices' normal
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*m_iNumVtx+sizeof(vec3)*m_iNumVtx, sizeof(vec4)*m_iNumVtx, m_pColors ); // vertcies' Color
	glBufferSubData( GL_ARRAY_BUFFER, (sizeof(vec4) + sizeof(vec3) + sizeof(vec4))*m_iNumVtx, sizeof(vec2)*m_iNumVtx, m_pTex);  //第一張貼圖
}

void CShape::SetShader(GLuint uiShaderHandle)
{
	// 改放置這裡, 方便每一個物件的設定
	CreateBufferObject();

	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) m_uiProgram = InitShader(m_pVXshader, m_pFSshader);
	else m_uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(m_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	m_uiModelView = glGetUniformLocation(m_uiProgram, "ModelView");
	// m_mxMVFinal , m_mxModelView 宣告時就是單位矩陣
	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);

	m_uiProjection = glGetUniformLocation(m_uiProgram, "Projection");
	// m_mxProjection 宣告時就是單位矩陣
	glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);

	m_uiColor = glGetUniformLocation(m_uiProgram, "vObjectColor");
	glUniform4fv(m_uiColor, 1, m_fColor);	
		
	GLuint vNormal = glGetAttribLocation(m_uiProgram, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4)*m_iNumVtx));

	GLuint vColorVtx = glGetAttribLocation(m_uiProgram, "vVtxColor");  // vertices' color 
	glEnableVertexAttribArray(vColorVtx);
	glVertexAttribPointer(vColorVtx, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4)*m_iNumVtx + sizeof(vec3)*m_iNumVtx));
	
	GLuint vDifMapCoord = glGetAttribLocation(m_uiProgram, "vDiffuseMapCoord");  // vertices' texture coordinates
	glEnableVertexAttribArray(vDifMapCoord);
	glVertexAttribPointer(vDifMapCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((sizeof(vec4) + sizeof(vec3) + sizeof(vec4))*m_iNumVtx));
	glUniform1i(glGetUniformLocation(m_uiProgram, "diffuMap"), 0);

	SetAPI();

	m_uiShininess = glGetUniformLocation(m_uiProgram, "fShininess");
	glUniform1f(m_uiShininess, m_Material.shininess);	

	m_uiTexLayer = glGetUniformLocation(m_uiProgram, "iTexLayer");
	glUniform1i(m_uiTexLayer, m_iTexLayer);	// 貼圖的個數，預設為 1，直接傳入 pixel shader

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CShape::SetAPI() {
	/////Light0
	m_uiLightInView[0] = glGetUniformLocation(m_uiProgram, "LightInView[0]");
	glUniform4fv(m_uiLightInView[0], 1, m_vLightInView[0]);

	m_uiDiffuseProduct[0] = glGetUniformLocation(m_uiProgram, "DiffuseProduct[0]");
	glUniform4fv(m_uiDiffuseProduct[0], 1, m_DiffuseProduct[0]);

	m_uiDiffuse[0] = glGetUniformLocation(m_uiProgram, "Diffuse[0]");
	glUniform4fv(m_uiDiffuse[0], 1, m_Diffuse[0]);

	m_uiSpecular[0] = glGetUniformLocation(m_uiProgram, "SpecularProduct[0]");
	glUniform4fv(m_uiSpecular[0], 1, m_SpecularProduct[0]);

	m_uiSpotCutoff[0] = glGetUniformLocation(m_uiProgram, "spotCutoff[0]");
	glUniform1f(m_uiSpotCutoff[0], m_spotCutoff[0]);

	m_uiAmbient[0] = glGetUniformLocation(m_uiProgram, "AmbientProduct[0]");
	glUniform4fv(m_uiAmbient[0], 1, m_AmbientProduct[0]);

	m_uiLightType[0] = glGetUniformLocation(m_uiProgram, "lightType[0]");
	glUniform1i(m_uiLightType[0], lightType[0]);

	m_uiLightDir[0] = glGetUniformLocation(m_uiProgram, "LightDir[0]");
	glUniform4fv(m_uiLightDir[0], 1, m_LightDir[0]);

	m_uiSpotExponent[0] = glGetUniformLocation(m_uiProgram, "spotExponent[0]");
	glUniform1f(m_uiSpotExponent[0], m_SpotExponent[0]);

	m_uiLighting[0] = glGetUniformLocation(m_uiProgram, "iLighting[0]");
	glUniform1i(m_uiLighting[0], m_iLighting[0]);

	/////Light1
	m_uiLightInView[1] = glGetUniformLocation(m_uiProgram, "LightInView[1]");
	glUniform4fv(m_uiLightInView[1], 1, m_vLightInView[1]);

	m_uiDiffuseProduct[1] = glGetUniformLocation(m_uiProgram, "DiffuseProduct[1]");
	glUniform4fv(m_uiDiffuseProduct[1], 1, m_DiffuseProduct[1]);

	m_uiDiffuse[1] = glGetUniformLocation(m_uiProgram, "Diffuse[1]");
	glUniform4fv(m_uiDiffuse[1], 1, m_Diffuse[1]);

	m_uiSpecular[1] = glGetUniformLocation(m_uiProgram, "SpecularProduct[1]");
	glUniform4fv(m_uiSpecular[1], 1, m_SpecularProduct[1]);

	m_uiSpotCutoff[1] = glGetUniformLocation(m_uiProgram, "spotCutoff[1]");
	glUniform1f(m_uiSpotCutoff[1], m_spotCutoff[1]);	

	m_uiAmbient[1] = glGetUniformLocation(m_uiProgram, "AmbientProduct[1]");
	glUniform4fv(m_uiAmbient[1], 1, m_AmbientProduct[1]);

	m_uiLightType[1] = glGetUniformLocation(m_uiProgram, "lightType[1]");
	glUniform1i(m_uiLightType[1], lightType[1]);

	m_uiLightDir[1] = glGetUniformLocation(m_uiProgram, "LightDir[1]");
	glUniform4fv(m_uiLightDir[1], 1, m_LightDir[1]);

	m_uiSpotExponent[1] = glGetUniformLocation(m_uiProgram, "spotExponent[1]");
	glUniform1f(m_uiSpotExponent[1], m_SpotExponent[1]);

	m_uiLighting[1] = glGetUniformLocation(m_uiProgram, "iLighting[1]");
	glUniform1i(m_uiLighting[1], m_iLighting[1]);

	/////Light2
	m_uiLightInView[2] = glGetUniformLocation(m_uiProgram, "LightInView[2]");
	glUniform4fv(m_uiLightInView[2], 1, m_vLightInView[2]);

	m_uiDiffuseProduct[2] = glGetUniformLocation(m_uiProgram, "DiffuseProduct[2]");
	glUniform4fv(m_uiDiffuseProduct[2], 1, m_DiffuseProduct[2]);

	m_uiDiffuse[2] = glGetUniformLocation(m_uiProgram, "Diffuse[2]");
	glUniform4fv(m_uiDiffuse[2], 1, m_Diffuse[2]);

	m_uiSpecular[2] = glGetUniformLocation(m_uiProgram, "SpecularProduct[2]");
	glUniform4fv(m_uiSpecular[2], 1, m_SpecularProduct[2]);

	m_uiSpotCutoff[2] = glGetUniformLocation(m_uiProgram, "spotCutoff[2]");
	glUniform1f(m_uiSpotCutoff[2], m_spotCutoff[2]);

	m_uiAmbient[2] = glGetUniformLocation(m_uiProgram, "AmbientProduct[2]");
	glUniform4fv(m_uiAmbient[2], 1, m_AmbientProduct[2]);

	m_uiLightType[2] = glGetUniformLocation(m_uiProgram, "lightType[2]");
	glUniform1i(m_uiLightType[2], lightType[2]);

	m_uiLightDir[2] = glGetUniformLocation(m_uiProgram, "LightDir[2]");
	glUniform4fv(m_uiLightDir[2], 1, m_LightDir[2]);

	m_uiSpotExponent[2] = glGetUniformLocation(m_uiProgram, "spotExponent[2]");
	glUniform1f(m_uiSpotExponent[2], m_SpotExponent[2]);

	m_uiLighting[2] = glGetUniformLocation(m_uiProgram, "iLighting[2]");
	glUniform1i(m_uiLighting[2], m_iLighting[2]);

	/////Light3
	m_uiLightInView[3] = glGetUniformLocation(m_uiProgram, "LightInView[3]");
	glUniform4fv(m_uiLightInView[3], 1, m_vLightInView[3]);

	m_uiDiffuseProduct[3] = glGetUniformLocation(m_uiProgram, "DiffuseProduct[3]");
	glUniform4fv(m_uiDiffuseProduct[3], 1, m_DiffuseProduct[3]);

	m_uiDiffuse[3] = glGetUniformLocation(m_uiProgram, "Diffuse[3]");
	glUniform4fv(m_uiDiffuse[3], 1, m_Diffuse[3]);

	m_uiSpecular[3] = glGetUniformLocation(m_uiProgram, "SpecularProduct[3]");
	glUniform4fv(m_uiSpecular[3], 1, m_SpecularProduct[3]);

	m_uiSpotCutoff[3] = glGetUniformLocation(m_uiProgram, "spotCutoff[3]");
	glUniform1f(m_uiSpotCutoff[3], m_spotCutoff[3]);

	m_uiAmbient[3] = glGetUniformLocation(m_uiProgram, "AmbientProduct[3]");
	glUniform4fv(m_uiAmbient[3], 1, m_AmbientProduct[3]);

	m_uiLightType[3] = glGetUniformLocation(m_uiProgram, "lightType[3]");
	glUniform1i(m_uiLightType[3], lightType[3]);

	m_uiLightDir[3] = glGetUniformLocation(m_uiProgram, "LightDir[3]");
	glUniform4fv(m_uiLightDir[3], 1, m_LightDir[3]);

	m_uiSpotExponent[3] = glGetUniformLocation(m_uiProgram, "spotExponent[3]");
	glUniform1f(m_uiSpotExponent[3], m_SpotExponent[3]);

	m_uiLighting[3] = glGetUniformLocation(m_uiProgram, "iLighting[3]");
	glUniform1i(m_uiLighting[3], m_iLighting[3]);
}

void CShape::DrawingSetShader()
{
	glUseProgram( m_uiProgram );
	glBindVertexArray( m_uiVao );
	glUniformMatrix4fv( m_uiModelView, 1, GL_TRUE, m_mxMVFinal );

	if( m_bProjUpdated ) {
		glUniformMatrix4fv( m_uiProjection, 1, GL_TRUE, m_mxProjection );
		m_bProjUpdated = false;
	}
// 將資訊更新到 Shader 中
#ifdef LIGHTING_WITHGPU
		glUniform4fv(m_uiColor, 1, m_fColor);
		for (int i = 0; i < LightCount; i++)
		{
			glUniform1i(m_uiLightType[i], lightType[i]);
			glUniform1f(m_uiSpotExponent[i], m_SpotExponent[i]);
			glUniform3fv(m_uiLightDir[i], 1, m_LightDir[i]);
			glUniform4fv(m_uiLightInView[i], 1, m_vLightInView[i]);
			glUniform4fv(m_uiDiffuseProduct[i], 1, m_DiffuseProduct[i]);
			glUniform4fv(m_uiDiffuse[i], 1, m_Diffuse[i]);
			glUniform4fv(m_uiSpecular[i], 1, m_SpecularProduct[i]);
			glUniform1f(m_uiSpotCutoff[i], m_spotCutoff[i]);
			glUniform4fv(m_uiAmbient[i], 1, m_AmbientProduct[i]);
			glUniform1i(m_uiLighting[i], m_iLighting[i]);
		}
		glUniform1f(m_uiShininess, m_Material.shininess);
		glUniform1i(m_uiTexLayer, m_iTexLayer);
#endif
}

// 此處預設使用前一個描繪物件所使用的 Shader
void CShape::DrawingWithoutSetShader()
{
	glBindVertexArray( m_uiVao );
	glUniformMatrix4fv( m_uiModelView, 1, GL_TRUE, m_mxMVFinal );

	if( m_bProjUpdated ) {
		glUniformMatrix4fv( m_uiProjection, 1, GL_TRUE, m_mxProjection );
		m_bProjUpdated = false;
	}
#ifdef LIGHTING_WITHGPU

		glUniform4fv(m_uiColor, 1, m_fColor);
		for (int i = 0; i < LightCount; i++)
		{
			glUniform1i(m_uiLightType[i], lightType[i]);
			glUniform1f(m_uiSpotExponent[i], m_SpotExponent[i]);
			glUniform3fv(m_uiLightDir[i], 1, m_LightDir[i]);
			glUniform4fv(m_uiLightInView[i], 1, m_vLightInView[i]);
			glUniform4fv(m_uiDiffuseProduct[i], 1, m_DiffuseProduct[i]);
			glUniform4fv(m_uiSpecular[i], 1, m_SpecularProduct[i]);
			glUniform1f(m_uiSpotCutoff[i], m_spotCutoff[i]);
			glUniform4fv(m_uiAmbient[i], 1, m_AmbientProduct[i]);
			glUniform4fv(m_uiDiffuse[i], 1, m_Diffuse[i]);
			glUniform1i(m_uiLighting[i], m_iLighting[i]);
		}
		glUniform1f(m_uiShininess, m_Material.shininess);
		glUniform1i(m_uiTexLayer, m_iTexLayer);
#endif
}

void CShape::SetShaderName(const char vxShader[], const char fsShader[])
{
	int len;
	len = strlen(vxShader);
	m_pVXshader = new char[len+1];
	memcpy(m_pVXshader, vxShader, len+1);

	len = strlen(fsShader);
	m_pFSshader = new char[len+1];
	memcpy(m_pFSshader, fsShader, len+1);
}

void CShape::SetViewMatrix(mat4 &mat)
{
	m_mxView = mat;
	m_bViewUpdated = true;
}

void CShape::SetTRSMatrix(mat4 &mat)
{
	m_mxTRS = mat;
	m_bTRSUpdated = true;
}

void CShape::SetProjectionMatrix(mat4 &mat)
{
	m_mxProjection = mat;
	m_bProjUpdated = true;
}

void CShape::SetColor(vec4 vColor)
{
	m_fColor[0] = vColor.x;
	m_fColor[1] = vColor.y;
	m_fColor[2] = vColor.z;
	m_fColor[3] = vColor.w;
	glUniform4fv(m_uiColor, 1, m_fColor); 
}

void CShape::SetMaterials(color4 ambient, color4 diffuse, color4 specular)
{
	m_Material.ambient =  ambient;
	m_Material.diffuse =  diffuse;
	m_Material.specular = specular;
}

void CShape::SetKaKdKsShini(float ka, float kd, float ks, float shininess) // ka kd ks shininess
{
	m_Material.ka = ka;
	m_Material.kd = kd;
	m_Material.ks = ks;
	m_Material.shininess = shininess;
}

void CShape::Update(const LightSource *Lights, float dt)
{
	if (m_bViewUpdated || m_bTRSUpdated) {
		m_mxMVFinal = m_mxView * m_mxTRS;
		m_mxMV3X3Final = mat3(	// 只取前面的 3X3 矩陣的內容
			m_mxView._m[0].x, m_mxView._m[1].x, m_mxView._m[2].x,
			m_mxView._m[0].y, m_mxView._m[1].y, m_mxView._m[2].y,
			m_mxView._m[0].z, m_mxView._m[1].z, m_mxView._m[2].z);
		m_bViewUpdated = m_bTRSUpdated = false;
	}

	

	for (int i = 0; i < LightCount; i++)
	{
		m_AmbientProduct[i] = m_Material.ka * m_Material.ambient  * Lights[i].ambient;
		lightType[i] = Lights[i].type;
		m_LightDir[i] = m_mxMV3X3Final * Lights[i].spotDirection;
		m_SpotExponent[i] = Lights[i].spotExponent;
		m_vLightInView[i] = m_mxView * Lights[i].position;
		m_DiffuseProduct[i] = m_Material.kd * m_Material.diffuse  * Lights[i].diffuse;
		m_Diffuse[i] = Lights[i].diffuse;
		m_SpecularProduct[i] = m_Material.ks * m_Material.specular * Lights[i].specular;
		m_spotCutoff[i] = Lights[i].spotCosCutoff;
		m_iLighting[i] = Lights[i].isLighting;
	}

}

void CShape::SetTextureLayer(int texlayer)
{
	m_iTexLayer = texlayer;
}

void CShape::Update(float dt)
{
	if (m_bViewUpdated || m_bTRSUpdated) { // Model View 的相關矩陣內容有更動
		m_mxMVFinal = m_mxView * m_mxTRS;
		m_mxITView = InverseTransposeMatrix(m_mxMVFinal);
		m_bViewUpdated = m_bTRSUpdated = false;
	}
}

void CShape::SetTiling(float uTiling, float vTiling)  // 對 U軸 與 V軸 進行拼貼的縮放
{
	for (int i = 0; i < m_iNumVtx; i++) {
		m_pTex[i].x *= uTiling; m_pTex[i].y *= vTiling;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(vec4) + sizeof(vec3) + sizeof(vec4))*m_iNumVtx, sizeof(vec2)*m_iNumVtx, m_pTex); // vertcies' Color
}