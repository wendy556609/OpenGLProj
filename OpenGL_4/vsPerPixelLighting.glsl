// Phong reflection model
#version 130

#define PointNum 4

in vec4 vPosition;	  // Vertex Position
in vec3 vNormal;    // Vertex Normal
in vec4 vVtxColor;  // Vertex Color

out vec3 fN;// 輸出 Normal 在鏡頭座標下的方向
out vec3 fL[PointNum];// 輸出 Light Direction 在鏡頭座標下的方向
out vec3 fV;// 輸出 View Direction 在鏡頭座標下的方向

uniform mat4  ModelView;   // Model View Matrix
uniform mat4  Projection;  // Projection Matrix
uniform vec4  LightInView[PointNum]; // Light's position in View Space

void main()
{
	vec4 vPosInView = ModelView * vPosition;
	// 目前已經以鏡頭座標為基礎, 所以 View 的位置就是 (0,0,0), 所以位置的負向就是 View Dir
	fV = -vPosInView.xyz;

	// 以下兩行用於計算對物件進行 non-uniform scale 時，物件 normal 的修正計算
	//		mat3 ITModelView = transpose(inverse(mat3(ModelView)); 
	//		vec3 vN = normalize(ITModelView * vNormal); 
	fN = (ModelView * vec4(vNormal, 0.0)).xyz;

	for(int i = 0;i < PointNum; i++){
		fL[i] = vec3(LightInView[i].xyz - vPosInView.xyz);
	}

	gl_Position = Projection * vPosInView;
}
