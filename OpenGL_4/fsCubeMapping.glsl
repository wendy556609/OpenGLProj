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

in vec2 DiffuseMapUV; // ��J�K�Ϯy��
in vec2 LightMapUV; // ��J�K�Ϯy��
in vec3 ReflView;   // View �b�� Vertex �۹����� Normal ���Ϯg�V�q 

uniform int iTexLayer;

// �H�U���s�W������
uniform vec4  LightInView[PointNum];        // Light's position in View Space
uniform vec4  AmbientProduct[PointNum];  // light's ambient  �P Object's ambient  �P ka �����n
uniform vec4  DiffuseProduct[PointNum];  // light's diffuse  �P Object's diffuse  �P kd �����n
uniform vec4  SpecularProduct[PointNum]; // light's specular �P Object's specular �P ks �����n
uniform float fShininess;
uniform int   iLighting[PointNum];
uniform vec4  vObjectColor;    // �N���󪺳�@�C��

uniform float spotCutoff[PointNum];
uniform int lightType[PointNum];
uniform vec3 LightDir[PointNum];
uniform float spotExponent[PointNum];

// For Texture Sampler
uniform sampler2D   diffuMap; // �K�Ϫ��ѼƳ]�w
uniform sampler2D   lightMap; // �K�Ϫ��ѼƳ]�w
uniform samplerCube cubeMap; // �K�Ϫ��ѼƳ]�w

void main()
{
	// ���ŧi diffuse �P specular
	vec4 ambient = vec4(0.0,0.0,0.0,1.0);
    vec4 diffuse = vec4(0.0,0.0,0.0,1.0);
	vec4 specular = vec4(0.0,0.0,0.0,1.0);
	vec4 LightingColor = vec4(0.0,0.0,0.0,1.0);
	
for(int i = 0 ;i < PointNum;i++){
	if( iLighting[i] != 1 ) {
#ifndef CHANGE_COLOR
		// �����ϥζǤJ�� LightMap
		gl_FragColor = vObjectColor * (0.325 *texture2D(diffuMap, DiffuseMapUV) + 0.675 * textureCube(cubeMap, ReflView));
#else
		vec4 lightMap = texture2D(lightMap, LightMapUV);	
		lightMap = lightMap * vec4(0.79,0.95, 0.96, 1.0);
		gl_FragColor = vObjectColor * texture2D(diffuMap, DiffuseMapUV) * lightMap;
#endif
		gl_FragColor.w = 1.0f;
	}
	else {	
		
		// 1. �p�� Ambient color : Ia = AmbientProduct = Ka * Material.ambient * La = 
		ambient = AmbientProduct[i]; // m_sMaterial.ka * m_sMaterial.ambient * vLightI;

		if(lightType[i] == 0){
		// ���ƶǤJ�� Normal Dir
		vec3 vN = normalize(v3N); 

		// 2. ���ƶǤJ�� Light Dir
		vec3 vL = normalize(v3L[i]); // normalize light vector

		// 5. �p�� L dot N
		float fLdotN = vL.x*vN.x + vL.y*vN.y + vL.z*vN.z;
		if( fLdotN >= 0 ) { // ���I�Q�����Ө�~�ݭn�p��
			// Diffuse Color : Id = Kd * Material.diffuse * Ld * (L dot N)
			diffuse = fLdotN * DiffuseProduct[i]; 

			// Specular color
			// Method 1: Phone Model
			// �p�� View Vector
			// ���ƶǤJ�� fE , View Direction
			vec3 vV = normalize(v3E);

			//�p�� Light �� �Ϯg�� vRefL = 2 * fLdotN * vN - L
			// �P�ɧQ�� normalize �ন���V�q
			vec3 vRefL = normalize(2.0f * (fLdotN) * vN - vL);

			//   �p��  vReflectedL dot View
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
		LightingColor = ambient + diffuse + specular;  // �p���C�� ambient + diffuse + specular;
		LightingColor.w = DiffuseProduct[0].w;	// �]�w���ǤJ���誺 alpha,	DiffuseProduct.w
		//LightingColor.w = 1.0;	// �]�w alpha �� 1.0

		gl_FragColor = vec4(1.0,1.0,1.0,1.0) * (0.325 *texture2D(diffuMap, DiffuseMapUV) + 0.675 * textureCube(cubeMap, ReflView));
	}
}
