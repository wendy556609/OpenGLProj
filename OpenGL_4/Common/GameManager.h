#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../Header/Angel.h"
#include "Camera.h"

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

class GameManager
{
protected:
	GameManager();			// �קK�Q�~��
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

	static GameManager* create();		// �إ� TexturePool ������
	static GameManager *getInstance();	// ���o  TexturePool ������

	void destroyInstance();		// ������o�귽
	void Init();

};

#endif