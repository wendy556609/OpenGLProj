#include "GameManager.h"

GameManager* GameManager::_pGameManager = nullptr;

void GameManager::destroyInstance()
{
	CC_SAFE_DELETE(_pGameManager);
}


GameManager::GameManager() {
	Init();
}

void GameManager::Init(){
	initPos = vec4(0.0f, 5.0f, -20.0f, 1.0f);
	room1Clear = false;
	room2Clear = false;
	room3Clear = false;
	room4Clear = false;
	room5Clear = false;
	room6Clear = false;

	room1Enter = true;
	room2Enter = false;
	room4Enter = false;
	room6Enter = false;

	allClear = true;
}

GameManager::~GameManager()
{

}

GameManager* GameManager::create()
{
	if (_pGameManager == nullptr) {
		_pGameManager = new (std::nothrow) GameManager;
	}
	return _pGameManager;
}

GameManager* GameManager::getInstance()
{
	if (_pGameManager == nullptr) {
		_pGameManager = new (std::nothrow) GameManager;
	}
	return _pGameManager;
}
