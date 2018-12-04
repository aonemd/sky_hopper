#include "coin.h"

Coin *Coin__create(float x, float y, float z) {
	Coin *coin = malloc(sizeof(*coin));

	coin->x          = x;
	coin->y          = y;
	coin->z          = z;
	coin->original_z = z;
	coin->angle      = 0;
	coin->visible    = true;

	return coin;
}

void Coin__render(Coin *self) {
	glPushMatrix();

	glColor3f(0.81, 0.71, 0.23);
	glTranslatef(self->x, self->y, self->z);
	glRotatef(self->angle, 0, 1, 0);

	glutSolidCylinder(0.5, 0.1, 100, 100);

	glPopMatrix();
}

void Coin__update(Coin *self) {
	self->z     += 0.07;
	self->angle += 1;

	if(self->z > 40) {
		self->z = self->original_z - 30;
	}
}
