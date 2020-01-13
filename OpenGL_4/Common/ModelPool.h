#ifndef MODELPOOL_H
#define MODELPOOL_H

#define	TEXTUREPOOL_MAX 100

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

#include "../header/Angel.h"
//#include "CShape.h"
#include "../ObjLoader.h"

typedef struct structModelElement {
	int _iNumVtx;
	vec4  *_pPoints;
	vec3  *_pNormals;
	vec2  *_pTex;
} ModelElement;
class ModelPool
{
	int _iNumTextures;
	ModelElement _Pool[TEXTUREPOOL_MAX];
public:
	static ModelPool* create();		// 建立 TexturePool 的實體
	static ModelPool *getInstance();	// 取得  TexturePool 的實體

	void destroyInstance();
	int AddModel(const char *path);
	ModelElement getModel(int modelNum) { return _Pool[modelNum]; }

protected:
	ModelPool();
	~ModelPool() {};

	static ModelPool* _pModelPool;
};

#endif