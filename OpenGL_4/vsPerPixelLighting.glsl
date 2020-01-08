// Phong reflection model
#version 130

#define PointNum 4

in vec4 vPosition;	  // Vertex Position
in vec3 vNormal;    // Vertex Normal
in vec4 vVtxColor;  // Vertex Color

out vec3 fN;// ��X Normal �b���Y�y�ФU����V
out vec3 fL[PointNum];// ��X Light Direction �b���Y�y�ФU����V
out vec3 fV;// ��X View Direction �b���Y�y�ФU����V

uniform mat4  ModelView;   // Model View Matrix
uniform mat4  Projection;  // Projection Matrix
uniform vec4  LightInView[PointNum]; // Light's position in View Space

void main()
{
	vec4 vPosInView = ModelView * vPosition;
	// �ثe�w�g�H���Y�y�Ь���¦, �ҥH View ����m�N�O (0,0,0), �ҥH��m���t�V�N�O View Dir
	fV = -vPosInView.xyz;

	// �H�U���Ω�p��磌��i�� non-uniform scale �ɡA���� normal ���ץ��p��
	//		mat3 ITModelView = transpose(inverse(mat3(ModelView)); 
	//		vec3 vN = normalize(ITModelView * vNormal); 
	fN = (ModelView * vec4(vNormal, 0.0)).xyz;

	for(int i = 0;i < PointNum; i++){
		fL[i] = vec3(LightInView[i].xyz - vPosInView.xyz);
	}

	gl_Position = Projection * vPosInView;
}
