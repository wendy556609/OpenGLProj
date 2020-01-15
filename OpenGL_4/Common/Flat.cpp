#include "Flat.h"

Flat::~Flat()
{
	delete _pSquares;
}

Flat::Flat(char direct, vec3 iSize, vec4 pos, float angle, vec4 roomPos)
{
	mat4 mxT;
	// 建立實體
	_iGridSize = iSize;
	_pSquares = new CQuad;
	_pos = vec4(pos.x + roomPos.x, pos.y + roomPos.y, pos.z + roomPos.z, pos.w);
	_roomPos = roomPos;
	SetShader();

	SetMaterials(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.5f, 0.5f, 0.5f, 1), vec4(0.5f, 0.5f, 0.5f, 1.0f));
	SetKaKdKsShini(0, 0.8f, 0.5f, 2);
	mT = 1;
	mxT = Translate(_pos);
	if (direct == 'L' || direct == 'l' || direct == 'R' || direct == 'r') {
		SetTRSMatrix(mxT*Scale(iSize.x, iSize.y, iSize.z)*RotateZ(angle));
		_pSquares->_collider.Init(iSize.x, iSize.y / 2, iSize.z / 2, _pos);
		mT = Translate(roomPos)*Scale(iSize.x, iSize.y, iSize.z)*RotateZ(angle);
	}
	else if (direct == 'F' || direct == 'f' || direct == 'B' || direct == 'b') {
		SetTRSMatrix(mxT*Scale(iSize.x, iSize.y, iSize.z)*RotateX(angle));
		_pSquares->_collider.Init(iSize.x / 2, iSize.y / 2, iSize.z, _pos);
		mT = Translate(roomPos)*Scale(iSize.x, iSize.y, iSize.z)*RotateX(angle);
	}
	else if (direct == 'T' || direct == 't' || direct == 'M' || direct == 'm') {
		SetTRSMatrix(mxT*Scale(iSize.x, iSize.y, iSize.z)*RotateX(angle));
		_pSquares->_collider.Init(iSize.x / 2, iSize.y, iSize.z / 2, _pos);
		mT = Translate(roomPos)*Scale(iSize.x, iSize.y, iSize.z)*RotateX(angle);
	}

	SetColor(vec4(0.6f));
}

void Flat::SetPosition(vec4 &vec) {
	mat4 mat = Translate(vec);
	_pSquares->SetTRSMatrix(mat*mT);
	_pSquares->_collider.SetCubeCollider(vec + _roomPos);
}

void Flat::SetTrigger(bool trigger) {
	_pSquares->SetTrigger(trigger);
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

void Flat::SetTiling(float uTiling, float vTiling) {
	_pSquares->SetTiling(uTiling, vTiling);
}

void Flat::SetLightMapTiling(float uTiling, float vTiling)
{
	_pSquares->SetLightMapTiling(uTiling, vTiling);
}

void Flat::SetTextureLayer(int texlayer)
{
	_pSquares->SetTextureLayer(texlayer);
}

void Flat::SetMirror(bool uAxis, bool vAxis) // U軸 與 V軸 是否要鏡射
{
	_pSquares->SetMirror(uAxis, vAxis);
}

void Flat::SetTurn(int angle) {
	_pSquares->SetTurn(angle);
}