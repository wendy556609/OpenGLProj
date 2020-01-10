// Phong reflection model
#version 150

#define PointNum 4

#define NONE_MAP    0
#define DIFFUSE_MAP 1
#define LIGHT_MAP   2
#define NORMAL_MAP  4

in vec4 vPosition;	  // Vertex Position
in vec3 vNormal;    // Vertex Normal
in vec4 vVtxColor;  // Vertex Color

in vec2 vDiffuseMapCoord;
in vec2 vLightMapCoord;
in vec2 vNormalMapCoord;
in vec3 vTangentV;

out vec3 fN;// 輸出 Normal 在鏡頭座標下的方向
out vec3 fL[PointNum];// 輸出 Light Direction 在鏡頭座標下的方向
out vec3 fV;// 輸出 View Direction 在鏡頭座標下的方向
out vec3 vE[PointNum];

out vec2 DiffuseMapUV;  // 輸出貼圖座標
out vec2 LightMapUV;    // 輸出貼圖座標
out vec2 NormalMapUV;  // 輸出貼圖座標

uniform int iTexLayer;

uniform mat4  ModelView;   // Model View Matrix
uniform mat4  Projection;  // Projection Matrix
uniform vec4  LightInView[PointNum]; // Light's position in View Space

void main()
{
	vec4 vPosInView = ModelView * vPosition;
	// 目前已經以鏡頭座標為基礎, 所以 View 的位置就是 (0,0,0), 所以位置的負向就是 View Dir
	//fV = -vPosInView.xyz;

	// 以下兩行用於計算對物件進行 non-uniform scale 時，物件 normal 的修正計算
	//		mat3 ITModelView = transpose(inverse(mat3(ModelView)); 
	//		vec3 vN = normalize(ITModelView * vNormal); 
	mat3 ITModelView = transpose(inverse(mat3(ModelView))); 

	vec3 tmpV;
	vec3 vn;
	vec3 vt;
	vec3 vb;

	if(iTexLayer != (DIFFUSE_MAP|NORMAL_MAP) ){
		fV = -vPosInView.xyz;
		fN = (ModelView * vec4(vNormal, 0.0)).xyz;

		for(int i = 0;i < PointNum; i++){
			fL[i] = vec3(LightInView[i].xyz - vPosInView.xyz);
		}	
	}
	else{
		vn = normalize(ITModelView * vNormal);
		vt = normalize(ITModelView * vTangentV);
		vb = cross(vn, vt);

		for(int i = 0;i < PointNum; i++){
			tmpV = vec3(LightInView[i].xyz - vPosInView.xyz);
			vE[i].x = dot(tmpV, vt);
			vE[i].y = dot(tmpV, vb);
			vE[i].z = dot(tmpV, vn);
			fL[i] = vec3(LightInView[i].xyz - vPosInView.xyz);
		}	

		tmpV = -vPosInView.xyz;
		fV.x = dot(tmpV, vt);
		fV.y = dot(tmpV, vb);
		fV.z = dot(tmpV, vn);
	}


	gl_Position = Projection * vPosInView;
	DiffuseMapUV = vDiffuseMapCoord;
	LightMapUV  = vLightMapCoord;
	NormalMapUV = vNormalMapCoord;
}
