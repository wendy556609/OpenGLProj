#include "ModelPool.h"
#include "../ObjLoader.h"

ModelPool::ModelPool(const char* path, char type) {
	std::vector<float> vertices, normals, colors;
	
	LoadObj(path, &vertices, &colors, &normals, type);

	m_iNumVtx = vertices.size() / 3;
	m_pPoints = NULL; m_pNormals = NULL; m_pTex = NULL;

	m_pPoints = new vec4[m_iNumVtx];
	m_pNormals = new vec3[m_iNumVtx];
	m_pColors = new vec4[m_iNumVtx];
	m_pTex = new vec2[m_iNumVtx];

	for (int i = 0; i < m_iNumVtx; i++)
	{
		m_pPoints[i] = vec4(vertices[i * 3], vertices[ i * 3 + 1 ], vertices[i * 3 + 2], 1.0f);
		m_pNormals[i] = vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
		m_pTex[i] = vec2(colors[i * 3], colors[i * 3 + 1]);
		m_pColors[i] = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}
	
	SetShaderName("vsPerPixelLighting.glsl", "fsPerPixelLighting.glsl");

	SetMaterials(vec4(0), vec4(1.0f, 1.0, 1.0, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SetKaKdKsShini(0.15f, 0.8f, 0.2f, 2);

	SetShader();
}

void ModelPool::Draw()
{
	DrawingSetShader();
	glDrawArrays(GL_TRIANGLES, 0, m_iNumVtx);
}

void ModelPool::DrawW()
{
	DrawingWithoutSetShader();
	glDrawArrays(GL_TRIANGLES, 0, m_iNumVtx);
}