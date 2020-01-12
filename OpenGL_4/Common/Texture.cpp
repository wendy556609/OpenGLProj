#include "Texture.h"

Texture* Texture::_pTexture = nullptr;

void Texture::destroyInstance()
{
	CC_SAFE_DELETE(_pTexture);
}


Texture::Texture() {
}

Texture::~Texture()
{

}

Texture* Texture::create()
{
	if (_pTexture == nullptr) {
		_pTexture = new (std::nothrow) Texture;
	}
	return _pTexture;
}

Texture* Texture::getInstance()
{
	if (_pTexture == nullptr) {
		_pTexture = new (std::nothrow) Texture;
	}
	return _pTexture;
}

void Texture::SetTexture() {
	auto texturepool = TexturePool::create();
	g_uiFTexID[0] = texturepool->AddTexture("texture/checker.png");
	g_uiFTexID[1] = texturepool->AddTexture("texture/lightMap1.png");
	g_uiFTexID[2] = texturepool->AddTexture("texture/Masonry.Brick.png");
	g_uiFTexID[3] = texturepool->AddTexture("texture/Masonry.Brick.normal1.png");
	g_uiFTexID[4] = texturepool->AddTexture("texture/wi_tata.png");
	g_uiFTexID[5] = texturepool->AddTexture("texture/wi_tata_normal.png");
	g_uiFTexID[6] = texturepool->AddTexture("texture/metal.png");

	g_uiSphereCubeMap = CubeMap_load_SOIL("texture/Sunny_PX.png", "texture/Sunny_NX.png", "texture/Sunny_NY.png", "texture/Sunny_PY.png", "texture/Sunny_PZ.png", "texture/Sunny_NZ.png");
};