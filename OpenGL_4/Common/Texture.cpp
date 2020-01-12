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
