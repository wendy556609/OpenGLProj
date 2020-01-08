#ifndef Flat_H
#define Flat_H

#include "TypeDefine.h"
#include "CQuad.h"
#include "Collider.h"

class Flat
{
private:
	CQuad *_pSquares;
	int    _iGridSize;
	GLuint _uiShaderHandle;
	vec4  _pos;

public:
	Flat(char direct = 'L', int iSize = 6, vec4 pos = vec4(0.0f), float angle = 0.0f, vec3 normal = vec3(0, 1.0f, 0));
	~Flat();

	void SetNormal(vec3 normal);

	void SetShader();
	void SetProjectionMatrix(mat4 &mat);
	void SetViewMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetShadingMode(int iMode);
	void Update(float dt, point4 vLightPos, color4 vLightI);
	void Update(float dt, const LightSource &Lights);
	void Update(const LightSource *Lights, float dt);
	void SetColor(vec4 &vColor);
	void Draw();

	void SetMaterials(color4 ambient, color4 diffuse, color4 specular);
	void SetKaKdKsShini(float ka, float kd, float ks, float shininess); // ka kd ks shininess
};

#endif