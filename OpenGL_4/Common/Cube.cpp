#include "Cube.h"

Cube::Cube()
{
	m_iNumVtx = SOLIDCUBE_NUM;
	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;

	m_pPoints = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors = new vec4[m_iNumVtx];
	m_pTex = new vec2[m_iNumVtx];

	m_vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	m_vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	m_vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	m_vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	m_vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	m_vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	m_vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	m_vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	m_iIndex = 0;
	// generate 12 triangles: 36 vertices and 36 colors
	Quad(1, 0, 3, 2);
	Quad(2, 3, 7, 6);
	Quad(3, 0, 4, 7);
	Quad(6, 5, 1, 2);
	Quad(4, 5, 6, 7);
	Quad(5, 4, 0, 1);
	//Print(m_iIndex);

	// 預設將所有的面都設定成灰色
	for (int i = 0; i < m_iNumVtx; i++) m_pColors[i] = vec4(-1.0f, -1.0f, -1.0f, 1.0f);

	SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl");


	// 設定材質
	SetMaterials(vec4(0), vec4(0.85f, 0, 0, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	SetShader();
}

void Cube::Quad(int a, int b, int c, int d)
{
	// Initialize temporary vectors along the quad's edge to
	//   compute its face normal 
	vec4 u = m_vertices[b] - m_vertices[a];
	vec4 v = m_vertices[c] - m_vertices[b];
	vec3 normal = normalize(cross(u, v));

	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[a]; m_iIndex++;
	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[b]; m_iIndex++;
	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[c]; m_iIndex++;
	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[a]; m_iIndex++;
	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[c]; m_iIndex++;
	m_pNormals[m_iIndex] = normal; m_pPoints[m_iIndex] = m_vertices[d]; m_iIndex++;
}

void Cube::Draw()
{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Change to wireframe mode
	DrawingSetShader();
	glDrawArrays(GL_TRIANGLES, 0, SOLIDCUBE_NUM);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Return to solid mode
}


void Cube::DrawW()
{
	DrawingWithoutSetShader();
	glDrawArrays(GL_TRIANGLES, 0, SOLIDCUBE_NUM);
}