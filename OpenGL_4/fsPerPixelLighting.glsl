#version 130

//#define NPR
//#define SILHOUETTE
#define PointNum 4

#define NONE_MAP    0
#define DIFFUSE_MAP 1
#define LIGHT_MAP   2
#define NORMAL_MAP  4

in vec3 fN;
in vec3 fL[PointNum];
in vec3 fV;

in vec2 DiffuseMapUV;   // 輸入 Diffuse Map 貼圖座標
in vec2 LightMapUV;   // 輸入 Light Map 貼圖座標

uniform int iTexLayer;

// 以下為新增的部分
uniform vec4  LightInView[PointNum];        // Light's position in View Space
uniform vec4  AmbientProduct[PointNum];  // light's ambient  與 Object's ambient  與 ka 的乘積
uniform vec4  DiffuseProduct[PointNum];  // light's diffuse  與 Object's diffuse  與 kd 的乘積
uniform vec4  Diffuse[PointNum];
uniform vec4  SpecularProduct[PointNum]; // light's specular 與 Object's specular 與 ks 的乘積
uniform float fShininess;
uniform int   iLighting[PointNum];
uniform vec4  vObjectColor;    // 代表物件的單一顏色
uniform float spotCutoff[PointNum];
uniform int lightType[PointNum];
uniform vec3 LightDir[PointNum];
uniform float spotExponent[PointNum];

uniform sampler2D diffuMap; // 貼圖的參數設定
uniform sampler2D lightMap; // 貼圖的參數設定

void main()
{
	// 先宣告 diffuse 與 specular
	vec4 ambient = vec4(0.0,0.0,0.0,1.0);
    vec4 diffuse = vec4(0.0,0.0,0.0,1.0);
	vec4 specular = vec4(0.0,0.0,0.0,1.0);
	vec4 result = vec4(0.0,0.0,0.0,1.0);
	vec4 fLightI = vec4(0.0,0.0,0.0,1.0);

	vec3 LD;
	vec3 vL = vec3(0.0,0.0,0.0);
	vec3 vV = vec3(0.0,0.0,0.0);
	vec3 vRefL = vec3(0.0,0.0,0.0);
	float fLdotN = 0.0f;
	float RdotV = 0.0f;
	float fLdotLDir = 0.0f;

	vec3 vLight; // 用 vec3 來宣告是為了節省計算, 如果要讓程式寫起來更方便，可改用 vec4 來宣告

	float epsilon = 0.0f;
	float intensity = 0.0f;
	
	
		// 1. 計算 Ambient color : Ia = AmbientProduct = Ka * Material.ambient * La = 
		

		// 單位化傳入的 Normal Dir
		vec3 vN = normalize(fN); 

	for(int i = 0 ;i < PointNum;i++){

	if( iLighting[i] != 1 ) {
		ambient = vec4(0.0,0.0,0.0,1.0);
		diffuse = vec4(0.0,0.0,0.0,1.0);
		specular = vec4(0.0,0.0,0.0,1.0);
	}
	else {	
		ambient = AmbientProduct[i]; // m_sMaterial.ka * m_sMaterial.ambient * vLightI;

		vL = normalize(fL[i]); // normalize light vector

		fLdotN = vL.x*vN.x + vL.y*vN.y + vL.z*vN.z;

		LD = normalize(LightDir[i]);

		fLdotLDir = -(vL.x*LD.x + vL.y*LD.y + vL.z*LD.z);

		if(lightType[i] == 1){		
			//epsilon = 30.0f - spotCutoff[i];

			//intensity = clamp((fLdotLDir - spotCutoff[i]) / epsilon,0.0, 1.0);	

			if( fLdotLDir >= spotCutoff[i] ) { // 該點被光源照到才需要計算

				fLightI = Diffuse[i] * pow(fLdotLDir, spotExponent[i]);

				// Diffuse Color : Id = Kd * Material.diffuse * Ld * (L dot N)
				diffuse = fLdotN * DiffuseProduct[i] * pow(fLdotLDir, spotExponent[i]); 		

				// Specular color
				// Method 1: Phone Model
				// 計算 View Vector
				// 單位化傳入的 fV , View Direction
				vV = normalize(fV);

				//計算 Light 的 反射角 vRefL = 2 * fLdotN * vN - L
				// 同時利用 normalize 轉成單位向量
				vRefL = normalize(2.0f * (fLdotN) * vN - vL);

				//   計算  vReflectedL dot View
				RdotV = vRefL.x*vV.x + vRefL.y*vV.y + vRefL.z*vV.z;

				// Specular Color : Is = Ks * Material.specular * Ls * (R dot V)^Shininess;
				if( RdotV > 0 ) specular = SpecularProduct[i]  * fLightI * pow(RdotV, fShininess)*intensity; 
				//specular = SpecularProduct[i]  * fLightI * pow(RdotV, fShininess);
			}
			else{
				ambient = vec4(0.0,0.0,0.0,1.0);
				diffuse = vec4(0.0,0.0,0.0,1.0); 
				specular =  vec4(0.0,0.0,0.0,1.0);
			}
		}
		else if(lightType[i] == 0){
			
			if( fLdotN >= 0 ) { // 該點被光源照到才需要計算
				
				// Diffuse Color : Id = Kd * Material.diffuse * Ld * (L dot N)
				diffuse = fLdotN * DiffuseProduct[i]; 		

				// Specular color
				// Method 1: Phone Model
				// 計算 View Vector
				// 單位化傳入的 fV , View Direction
				vV = normalize(fV);

				//計算 Light 的 反射角 vRefL = 2 * fLdotN * vN - L
				// 同時利用 normalize 轉成單位向量
				vRefL = normalize(2.0f * (fLdotN) * vN - vL);

				//   計算  vReflectedL dot View
				RdotV = vRefL.x*vV.x + vRefL.y*vV.y + vRefL.z*vV.z;

				// Specular Color : Is = Ks * Material.specular * Ls * (R dot V)^Shininess;
				if( RdotV > 0 ) specular = SpecularProduct[i] * pow(RdotV, fShininess); 
			}
			else{
				ambient = vec4(0.0,0.0,0.0,1.0);
				diffuse =  vec4(0.0,0.0,0.0,1.0);
				specular =  vec4(0.0,0.0,0.0,1.0);
			}
		}
		
		
	}
	result += ambient + diffuse + specular;
}		// 2. 單位化傳入的 Light Dir
		

		// 5. 計算 L dot N
		
		

		gl_FragColor = vec4(result.xyz, 1.0);  // 計算顏色 ambient + diffuse + specular;
		gl_FragColor.w = 1.0;	// 設定 alpha 為 1.0
		// gl_FragColor = vec4((ambient + diffuse + specular).xyz, 1.0);
#ifdef SILHOUETTE
	vec4 edgeColor = vec4(1.0, 0.0, 0.0, 1.0);
	if( abs(dot(normalize(fN), normalize(fV))) < 0.2)  gl_FragColor = edgeColor;
#endif

		if( iTexLayer == NONE_MAP ) gl_FragColor = gl_FragColor;
		else if( iTexLayer == DIFFUSE_MAP || iTexLayer == (DIFFUSE_MAP|NORMAL_MAP) ) gl_FragColor = gl_FragColor * texture2D(diffuMap, DiffuseMapUV);
		//else if (iTexLayer == (DIFFUSE_MAP | LIGHT_MAP))
			//{
				//gl_FragColor = (0.65 * gl_FragColor * texture2D(diffuMap, DiffuseMapUV) + texture2D(diffuMap, DiffuseMapUV) *
				//																			   texture2D(lightMap, LightMapUV) * vec4(0.0f, 1.0f, 1.0f, 1.00));

				//			float t = 0.15 + 0.75 * abs(sin(fElapsedTime * 3.1415926 * 0.125));
				//			gl_FragColor =  ( 0.55 * LightingColor * texture2D(diffuMap, DiffuseMapUV)  + // texture2D(diffuMap, DiffuseMapUV) *
				//							texture2D(lightMap, LightMapUV) * vec4(0.0f, 1.0f, 1.0f, 1.0) * t);
			//}
	
}
