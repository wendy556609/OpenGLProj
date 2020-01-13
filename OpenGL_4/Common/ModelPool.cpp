#include "ModelPool.h"


ModelPool* ModelPool::_pModelPool = nullptr;

void ModelPool::destroyInstance()
{
	if (_iNumTextures != 0) { // 這邊很重要!!，釋放所有貼圖的名稱與貼圖物件
		for (int i = 0; i < _iNumTextures; i++) {
			delete _Pool[i]._pPoints;
			delete _Pool[i]._pNormals;
			delete _Pool[i]._pTex;
		}
	}
	CC_SAFE_DELETE(_pModelPool);
}

ModelPool::ModelPool() {	
	_iNumTextures = 0;
	for (int i = 0; i < TEXTUREPOOL_MAX; i++) {
		_Pool[i]._iNumVtx = 0;
		_Pool[i]._pPoints = NULL;
		_Pool[i]._pNormals = NULL;
		_Pool[i]._pTex = NULL;
	}
}

ModelPool* ModelPool::create()
{
	if (_pModelPool == nullptr) {
		_pModelPool = new (std::nothrow) ModelPool;
	}
	return _pModelPool;
}

ModelPool* ModelPool::getInstance()
{
	if (_pModelPool == nullptr) {
		_pModelPool = new (std::nothrow) ModelPool;
	}
	return _pModelPool;
}

int ModelPool::AddModel(const char *path)
{
	std::vector<float> vertices, normals, colors;

	LoadObj(path, &vertices, &colors, &normals);
	_Pool[_iNumTextures]._iNumVtx = vertices.size() / 3;
	_Pool[_iNumTextures]._pPoints = new vec4[_Pool[_iNumTextures]._iNumVtx];
	_Pool[_iNumTextures]._pNormals = new vec3[_Pool[_iNumTextures]._iNumVtx];
	_Pool[_iNumTextures]._pTex = new vec2[_Pool[_iNumTextures]._iNumVtx];

	for (int i = 0; i < _Pool[_iNumTextures]._iNumVtx; i++)
	{
		_Pool[_iNumTextures]._pPoints[i] = vec4(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2], 1.0f);
		_Pool[_iNumTextures]._pNormals[i] = vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
		_Pool[_iNumTextures]._pTex[i] = vec2(colors[i * 3], colors[i * 3 + 1]);
	}
	_iNumTextures++;
	return(_iNumTextures - 1);
}