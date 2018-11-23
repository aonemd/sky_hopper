#ifndef _texture_loader_h_
#define _texture_loader_h_

#include <stdio.h>
#include "GL/freeglut.h"

typedef unsigned char Byte;

typedef struct {
	int            width;          /* Width of image */
	int            height;         /* Height of image */
	unsigned short planes;         /* Number of color planes */
	unsigned short bit_count;	   /* Number of bits per pixel */
	unsigned char *data;
} BitMapInfoHeader;

GLuint TextureLoader__load_bmp(const char *filename, int wrap);
GLuint TextureLoader__load_ppm(const char *filename, int width, int height, int wrap);

#endif
