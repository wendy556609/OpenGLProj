#version 130

in  vec4 vPosition;
in vec2 vDiffuseMapCoord;

out vec4 color;
out vec2 DiffuseMapUV;

#define NONE_MAP    0
#define DIFFUSE_MAP 1

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 vObjectColor;

uniform int iTexLayer;

void main()
{
    gl_Position = Projection * ModelView * vPosition;
	color = vObjectColor;

	DiffuseMapUV = vDiffuseMapCoord;
}
