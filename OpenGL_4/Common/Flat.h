#ifndef Flat_H
#define Flat_H

#include "TypeDefine.h"
#include "CQuad.h"
#include "Collider.h"

class Flat
{
private:
	CQuad *_pSquares;
	vec3    _iGridSize;
	GLuint _uiShaderHandle;
	vec4  _pos;

public:
	Flat(char direct = 'L', vec3 iSize = vec3(0), vec4 pos = vec4(0.0f), float angle = 0.0f, vec4 roomPos = vec4(0.0f));
	~Flat();

	Collider GetCollider() { return _pSquares->GetCollider(); };
	void SetTrigger(bool trigger);
	bool GetTrigger() { return _pSquares->GetTrigger(); };

	void SetShader();
	void SetProjectionMatrix(mat4 &mat);
	void SetViewMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetShadingMode(int iMode);
	void Update(const LightSource *Lights, float dt);
	void SetColor(vec4 &vColor);
	void Draw();

	void SetMaterials(color4 ambient, color4 diffuse, color4 specular);
	void SetKaKdKsShini(float ka, float kd, float ks, float shininess); // ka kd ks shininess

	void SetTiling(float uTiling, float vTiling);
	void SetLightMapTiling(float uTiling, float vTiling);
	void SetTextureLayer(int texlayer);
	void SetMirror(bool uAxis, bool vAxis);
};

#endif