#version 130
#define NONE_MAP    0
#define DIFFUSE_MAP 1

in vec4 color;
in vec2 DiffuseMapUV;

uniform int iTexLayer;

uniform sampler2D diffuMap; // 貼圖的參數設定
void main()
{
    if( iTexLayer == NONE_MAP ) gl_FragColor = color;
	else if( iTexLayer == DIFFUSE_MAP ) gl_FragColor = color * texture2D(diffuMap, DiffuseMapUV);
}
