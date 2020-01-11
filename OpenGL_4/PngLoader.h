#ifndef PNGLOADER_H_
#define PNGLOADER_H_

#include "header/Angel.h"
//#include <GLES/gl.h>

GLuint png_load_LIBPNG(const char * file_name, int * width, int * height, bool bMipMap);
GLuint png_load_SOIL(const char * file_name, int * width, int * height, bool bMipMap);
GLuint CubeMap_load_SOIL(const char * px, const char * nx, const char * ny, const char * py, const char * pz, const char * nz);

#endif
