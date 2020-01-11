#define _CRT_SECURE_NO_WARNINGS 0
#include "PngLoader.h"
#include "SOIL/SOIL.h"
//--------------------------------------------------------------------------------------------
// png_load_SOIL uses SOIL to load png files
//
GLuint png_load_SOIL(const char * file_name, int * width, int * height, bool bMipMap)
{
	GLuint texture;
	GLint iwidth, iheight, ichannel, iformat, row_bytes;
	GLubyte *texArray, *imageData;
	texArray = SOIL_load_image(file_name, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	row_bytes = iwidth*ichannel;
	imageData = (GLubyte *)malloc(row_bytes*iheight * sizeof(GLubyte));

	// �� texArray ���櫫����g�A��� imageData ��
	for (int i = 0; i < iheight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	}
	switch (ichannel)
	{
	case 3:
		iformat = GL_RGB;
		break;
	case 4:
		iformat = GL_RGBA;
		break;
	default:
		fprintf(stderr, "%s: Unknown libpng with %d channel.\n", file_name, ichannel);
		return 0;
		break;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (bMipMap) { // �}�� MipMap �\��
		glTexImage2D(GL_TEXTURE_2D, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { // �S���ϥ� MipMap �\��
		glTexImage2D(GL_TEXTURE_2D, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  //GL_LINEAR
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //GL_LINEAR

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	*width = iwidth; *height = iheight;

	// clean up
	free(texArray);
	free(imageData);
	return texture;
}
//--------------------------------------------------------------------------------------------

GLuint CubeMap_load_SOIL(const char * px, const char * nx, const char * ny, const char * py, const char * pz, const char * nz)
{
	GLuint texture;
	GLint iwidth, iheight, ichannel, iformat, row_bytes;
	GLubyte *texArray, *imageData;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	// �w�]Ū�� Sunny_NX Sunny_PX Sunny_NY Sunny_PY Sunny_NZ Sunny_PZ ���i�v��, ���O png
	// �C�@�i�v���j�p���ۦP, �ҥH imageData ���o�@���N��
	texArray = SOIL_load_image(px, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	row_bytes = iwidth*ichannel;
	imageData = (GLubyte *)malloc(row_bytes*iheight * sizeof(GLubyte));
	// �� texArray ���櫫����g�A��� imageData ��
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	iformat = GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

	texArray = SOIL_load_image(nx, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

					// �]���t�X���ɪ�������g �ҥH PY �P NY �������
	texArray = SOIL_load_image(ny, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

	texArray = SOIL_load_image(py, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

	texArray = SOIL_load_image(pz, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

	texArray = SOIL_load_image(nz, &iwidth, &iheight, &ichannel, SOIL_LOAD_AUTO);
	for (int i = 0; i < iheight; i++) memcpy(imageData + (row_bytes*i), texArray + (iheight - i - 1)*row_bytes, row_bytes);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, iformat, iwidth, iheight, 0, iformat, GL_UNSIGNED_BYTE, imageData);
	free(texArray); // ����

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	free(imageData);
	return texture;
}

//--------------------------------------------------------------------------------------------