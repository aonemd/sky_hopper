#include "texture_loader.h"

GLuint TextureLoader_load_bmp(const char *filename, int wrap) {
	GLuint texture_id;
	long i;
	char temp;
	FILE *file;
	BitMapInfoHeader infoheader;

	if ((file = fopen(filename, "rb")) == NULL) {
		return -1;
	}

	fseek(file, 18, SEEK_CUR);
	fread(&infoheader.width, sizeof(int), 1, file);

	fread(&infoheader.height, sizeof(int), 1, file);

	fread(&infoheader.planes, sizeof(short int), 1, file);
	if (infoheader.planes != 1) {
		return 0;
	}

	// read the bpp
	fread(&infoheader.bit_count, sizeof(unsigned short int), 1, file);
	if (infoheader.bit_count != 24) {
		return 0;
	}

	fseek(file, 24, SEEK_CUR);

	infoheader.data = (unsigned char *) malloc(infoheader.width * infoheader.height * 3);
	if (infoheader.data == NULL) {
		return 0;
	}

	if ((i = fread(infoheader.data, infoheader.width * infoheader.height * 3, 1, file)) != 1) {
		return 0;
	}

	// reverse all of the colors (bgr -> rgb)
	for (i = 0; i < (infoheader.width * infoheader.height * 3); i += 3) {
		temp = infoheader.data[i];
		infoheader.data[i] = infoheader.data[i + 2];
		infoheader.data[i + 2] = temp;
	}


	fclose(file);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// finally we define the 2d texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.width, infoheader.height, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);
	// and create 2d mipmaps for the minifying function
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.width, infoheader.height, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

	free(infoheader.data);

	return texture_id;
}

GLuint TextureLoader_load_ppm(const char *filename, int width, int height, int wrap) {
	GLuint texture_id;
	Byte *data;
	FILE *file;

	if ((file = fopen(filename, "rb")) == NULL) {
		return -1;
	}

	// read the file into data
	data = (Byte*) malloc(width * height * 3);
	fread(data, 1, width * height * 3, file);
	fclose(file);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	free(data);

	return texture_id;
}

