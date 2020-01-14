// #define CHANGE_COLOR
#version 130

#define PointNum 4

#define NONE_MAP    0
#define DIFFUSE_MAP 1
#define LIGHT_MAP   2
#define CUBIC_MAP   8

in vec3 v3N;
in vec3 v3L[PointNum];
in vec3 v3E;

in vec2 DiffuseMapUV; // 輸入貼圖座標
in vec2 LightMapUV; // 輸入貼圖座標
in vec3 ReflView;   // View 在該 Vertex 相對應於 Normal 的反射向量 

uniform int iTexLayer;

// 以下為新增的部分
uniform vec4  LightInView[PointNum];        // Light's position in View Space
uniform vec4  AmbientProduct[PointNum];  // light's ambient  與 Object's ambient  與 ka 的乘積
uniform vec4  DiffuseProduct[PointNum];  // light's diffuse  與 Object's diffuse  與 kd 的乘積
uniform vec4  SpecularProduct[PointNum]; // light's specular 與 Object's specular 與 ks 的乘積
uniform float fShininess;
uniform int   iLighting[PointNum];
uniform vec4  vObjectColor;    // 代表物件的單一顏色

uniform float spotCutoff[PointNum];
uniform int lightType[PointNum];
uniform vec3 LightDir[PointNum];
uniform float spotExponent[PointNum];

// For Texture Sampler
uniform sampler2D   diffuMap; // 貼圖的參數設定
uniform sampler2D   lightMap; // 貼圖的參數設定
uniform samplerCube cubeMap; // 貼圖的參數設定

void main()
{
	// 先宣告 diffuse 與 specular
	vec4 ambient = vec4(0.0,0.0,0.0,1.0);
    vec4 diffuse = vec4(0.0,0.0,0.0,1.0);
	vec4 specular = vec4(0.0,0.0,0.0,1.0);
	vec4 LightingColor = vec4(0.0,0.0,0.0,1.0);
	
for(int i = 0 ;i < PointNum;i++){
	if( iLighting[i] != 1 ) {
#ifndef CHANGE_COLOR
		// 直接使用傳入的 LightMap
		gl_FragColor = vObjectColor * (0.325 *texture2D(diffuMap, DiffuseMapUV) + 0.675 * textureCube(cubeMap, ReflView));
#else
		vec4 lightMap = texture2D(lightMap, LightMapUV);	
		lightMap = lightMap * vec4(0.79,0.95, 0.96, 1.0);
		gl_FragColor = vObjectColor * texture2D(diffuMap, DiffuseMapUV) * lightMap;
#endif
		gl_FragColor.w = 1.0f;
	}
	else {	
		
		// 1. 計算 Ambient color : Ia = AmbientProduct = Ka * Material.ambient * La = 
		ambient = AmbientProduct[i]; // m_sMaterial.ka * m_sMaterial.ambient * vLightI;

		if(lightType[i] == 0){
		// 單位化傳入的 Normal Dir
		vec3 vN = normalize(v3N); 

		// 2. 單位化傳入的 Light Dir
		vec3 vL = normalize(v3L[i]); // normalize light vector

		// 5. 計算 L dot N
		float fLdotN = vL.x*vN.x + vL.y*vN.y + vL.z*vN.z;
		if( fLdotN >= 0 ) { // 該點被光源照到才需要計算
			// Diffuse Color : Id = Kd * Material.diffuse * Ld * (L dot N)
			diffuse = fLdotN * DiffuseProduct[i]; 

			// Specular color
			// Method 1: Phone Model
			// 計算 View Vector
			// 單位化傳入的 fE , View Direction
			vec3 vV = normalize(v3E);

			//計算 Light 的 反射角 vRefL = 2 * fLdotN * vN - L
			// 同時利用 normalize 轉成單位向量
			vec3 vRefL = normalize(2.0f * (fLdotN) * vN - vL);

			//   計算  vReflectedL dot View
			float RdotV = vRefL.x*vV.x + vRefL.y*vV.y + vRefL.z*vV.z;

			// Specular Color : Is = Ks * Material.specular * Ls * (R dot V)^Shininess;
			if( RdotV > 0 ) specular = SpecularProduct[i] * pow(RdotV, fShininess) ;
		}
		else{
			ambient = vec4(0.0,0.0,0.0,1.0);
			diffuse =  vec4(0.0,0.0,0.0,1.0);
			specular =  vec4(0.0,0.0,0.0,1.0);
		}
		}
	}
		LightingColor = ambient + diffuse + specular;  // 計算顏色 ambient + diffuse + specular;
		LightingColor.w = DiffuseProduct[0].w;	// 設定為傳入材質的 alpha,	DiffuseProduct.w
		//LightingColor.w = 1.0;	// 設定 alpha 為 1.0

		gl_FragColor = vec4(1.0,1.0,1.0,1.0) * (0.325 *texture2D(diffuMap, DiffuseMapUV) + 0.675 * textureCube(cubeMap, ReflView));
	}
}
