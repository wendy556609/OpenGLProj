#include "TexturePool.h"
#include "../PngLoader.h"

TexturePool* TexturePool::_pTexturePool = nullptr;

void TexturePool::destroyInstance()
{
	if (_iNumTextures != 0) { // 這邊很重要!!，釋放所有貼圖的名稱與貼圖物件
		for (int i = 0; i < _iNumTextures; i++) {
			glDeleteTextures(1, &_Pool[i].uiTextureID);
			delete _Pool[i].TextureName;
		}
	}
	CC_SAFE_DELETE(_pTexturePool);
}


TexturePool::TexturePool() {
	_iNumTextures = 0;
	for (int i = 0; i < TEXTUREPOOL_MAX; i++) {
		_Pool[i].TextureName = NULL;
		_Pool[i].uiTextureID = -1;
		_Pool[i].iTexHeight = _Pool[i].iTexWidth = 0;
	}
}

TexturePool::~TexturePool()
{

}

TexturePool* TexturePool::create()
{
	if (_pTexturePool == nullptr) {
		_pTexturePool = new (std::nothrow) TexturePool;
	}
	return _pTexturePool;
}

TexturePool* TexturePool::getInstance()
{
	if (_pTexturePool == nullptr) {
		_pTexturePool = new (std::nothrow) TexturePool;
	}
	return _pTexturePool;
}

GLuint TexturePool::AddTexture(char *texName)
{
	// 先將 texName 複製一份到 _pool 中
	int len = strlen(texName);
	_Pool[_iNumTextures].TextureName = new char[len + 1];
	memcpy(_Pool[_iNumTextures].TextureName, texName, len);
	_Pool[_iNumTextures].TextureName[len] = '\0';
	_Pool[_iNumTextures].uiTextureID = png_load_SOIL(texName, &(_Pool[_iNumTextures].iTexWidth), &(_Pool[_iNumTextures].iTexHeight), true);
	_iNumTextures++;
	return(_Pool[_iNumTextures - 1].uiTextureID);
}