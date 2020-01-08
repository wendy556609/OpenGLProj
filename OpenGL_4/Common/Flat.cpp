#include "Flat.h"

Flat::~Flat()
{
	delete _pSquares;
}

Flat::Flat(char direct, int iSize, vec4 pos, float angle,vec3 normal)
{
	mat4 mxT;
	// 建立實體
	_iGridSize = iSize;
	_pSquares = new CQuad;
	_pos = pos;

	SetNormal(normal);

	SetShader();

	SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.5f, 0.5f, 0.5f, 1), vec4(0.5f, 0.5f, 0.5f, 1.0f));
	SetKaKdKsShini(0, 0.8f, 0.5f, 1);

	mxT = Translate(_pos);
	if (direct == 'L' || direct == 'l' || direct == 'R' || direct == 'r') {
		SetTRSMatrix(mxT*RotateZ(angle)*Scale(iSize / 2, 1, iSize));
	}
	else if (direct == 'F' || direct == 'f' || direct == 'B' || direct == 'b') {
		SetTRSMatrix(mxT*RotateX(angle)*Scale(iSize, 1, iSize / 2));
	}
	else if (direct == 'T' || direct == 't' || direct == 'M' || direct == 'm') {
		SetTRSMatrix(mxT*RotateZ(angle)*Scale(iSize, 1, iSize));
	}

	SetColor(vec4(0.6f));
}

void Flat::SetNormal(vec3 normal) {
	_pSquares->SetNormal(normal);
}

void Flat::SetShadingMode(int iMode) {
	_pSquares->SetShadingMode(iMode);
}

void Flat::SetShader()
{
	//// 產生每一個 Square 的位置與座標
	mat4 mxT;

	_pSquares->SetShader();
}

void Flat::SetProjectionMatrix(mat4 &mat)
{
	_pSquares->SetProjectionMatrix(mat);
}

void Flat::SetTRSMatrix(mat4 &mat)
{
	_pSquares->SetTRSMatrix(mat);
}

void Flat::Draw()
{
	_pSquares->Draw();
}

void Flat::SetViewMatrix(mat4 &mat)
{
	_pSquares->SetViewMatrix(mat);
}

void Flat::Update(const LightSource *Lights, float dt) {
	_pSquares->Update(Lights, dt);
}

void Flat::SetMaterials(color4 ambient, color4 diffuse, color4 specular)
{
	_pSquares->SetMaterials(ambient, diffuse, specular);
}

void Flat::SetKaKdKsShini(float ka, float kd, float ks, float shininess) // ka kd ks shininess
{
	_pSquares->SetKaKdKsShini(ka, kd, ks, shininess);
}

void Flat::SetColor(vec4 &vColor) {
	_pSquares->SetColor(vColor);
}