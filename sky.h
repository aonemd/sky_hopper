#ifndef _sky_h_
#define _sky_h_

#include <stdbool.h>

#ifdef OS_WIN
#include <glut.h>
#else
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

void Sky__render(GLuint texture_id);

#endif
