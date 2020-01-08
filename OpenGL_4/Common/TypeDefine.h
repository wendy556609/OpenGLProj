#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H
#include "../Header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

typedef struct MaterialParameters {
	color4 ambient;		// ambient 顏色
	color4 diffuse;		
	color4 specular;
	color4 emission;
	float  ka, kd, ks;	// 簡化計算, 假設 RGB 三個顏色上的反射係數皆相同
	float  shininess;
} Material;

typedef struct LightSourceParameters  
{  
	int type;
    color4 ambient;  
    color4 diffuse;  
    color4 specular;  
    point4 position;  
    point4 halfVector;
	vec3 spotTarget;
    vec3 spotDirection; 
    float spotExponent;  
    float spotCutoff; // (range: [0.0,90.0], 180.0)  
    float spotCosCutoff; // (range: [1.0,0.0],-1.0)  
    float constantAttenuation;  
    float linearAttenuation;  
    float quadraticAttenuation;
	int isLighting;

	void UpdateDirection(){
		spotDirection.x = spotTarget.x - position.x;
		spotDirection.y = spotTarget.y - position.y;
		spotDirection.z = spotTarget.z - position.z;
		spotDirection = normalize(spotDirection);
	}
} LightSource;


#endif