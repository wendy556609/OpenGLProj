#include "Sphere.h"

Sphere::Sphere(const GLfloat fRadius, const int iSlices, const  int iStacks)
{
	GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
	GLfloat ds = 1.0f / (GLfloat)iSlices;
	GLfloat dt = 1.0f / (GLfloat)iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;     // Looping variables  
	int idx = 0; // 儲存 vertex 順序的索引值

	m_fRadius = fRadius;
	m_iSlices = iSlices;
	m_iStacks = iStacks;
	m_iNumVtx = iStacks*(2 * (iSlices + 1));

	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;

	m_pPoints = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors = new vec4[m_iNumVtx];
	m_pTex = new vec2[m_iNumVtx];


	for (i = 0; i < iStacks; i++) {
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

		// Many sources of OpenGL sphere drawing code uses a triangle fan  
		// for the caps of the sphere. This however introduces texturing   
		// artifacts at the poles on some OpenGL implementations  
		s = 0.0f;
		for (j = 0; j <= iSlices; j++) {
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;

			m_pPoints[idx].x = x * m_fRadius;
			m_pPoints[idx].y = y * m_fRadius;
			m_pPoints[idx].z = z * m_fRadius;
			m_pPoints[idx].w = 1;

			m_pNormals[idx].x = x;
			m_pNormals[idx].y = y;
			m_pNormals[idx].z = z;

			m_pTex[idx].x = s;
			m_pTex[idx].y = t; // 設定貼圖座標
			idx++;

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

			m_pPoints[idx].x = x * m_fRadius;
			m_pPoints[idx].y = y * m_fRadius;
			m_pPoints[idx].z = z * m_fRadius;
			m_pPoints[idx].w = 1;

			m_pNormals[idx].x = x;
			m_pNormals[idx].y = y;
			m_pNormals[idx].z = z;

			m_pTex[idx].x = s;
			m_pTex[idx].y = t - dt; // 設定貼圖座標
			idx++;
			s += ds;
		}
		t -= dt;
	}

	// 預設將所有的面都設定成灰色
	for (int i = 0; i < m_iNumVtx; i++) m_pColors[i] = vec4(-1.0f, -1.0f, -1.0f, 1.0f);

	SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl");

	// 設定材質
	SetMaterials(vec4(0.15f, 0.15f, 0.15f, 1.0f), vec4(0, 0.85f, 0, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SetKaKdKsShini(0.15f, 0.55f, 0.45f, 5);

	SetShader();
}

void Sphere::Draw()
{
	DrawingSetShader();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Change to wireframe mode
	for (int i = 0; i < m_iStacks; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i*(2 * (m_iSlices + 1)), 2 * (m_iSlices + 1));
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Return to solid mode
}

void Sphere::DrawW()
{
	DrawingWithoutSetShader();
	for (int i = 0; i < m_iStacks; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i*(2 * (m_iSlices + 1)), 2 * (m_iSlices + 1));
	}
}

Sphere::~Sphere()
{

}