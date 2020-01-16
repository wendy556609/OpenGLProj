#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../Header/Angel.h"
#include "Camera.h"

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

class GameManager
{
protected:
	GameManager();			// 避免被誤用
	~GameManager();
	void initDefault() {};
	static GameManager* _pGameManager;
private:

public:
	vec4 initPos;
	bool room1Clear;
	bool room2Clear;
	bool room3Clear;
	bool room4Clear;
	bool room5Clear;
	bool room6Clear;

	bool room2Enter;
	bool room6Enter;

	bool allClear;

	static GameManager* create();		// 建立 TexturePool 的實體
	static GameManager *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();		// 釋放取得資源
	void Init();

};

#endif