#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <GL/glew.h>
#include "Sprite.h"

class Projectile{
public:
	Projectile(TextureManager*);

	GLfloat getX();
	GLfloat getY();
	GLfloat getSpeed();
	void setPosition(GLfloat x,GLfloat y);
	void setSpeed(GLfloat speed);
	Sprite* getSprite();
	void Physics();
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	void Fire(GLfloat x, GLfloat y);
	GLboolean isAlive();

private:
	GLfloat x;
	GLfloat y;
	GLfloat speed;
	Sprite* sprite;
	GLfloat projectileWidth;
	GLfloat projectileHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLboolean left;
	GLboolean right;
	GLboolean fired;
	GLboolean alive;

};

#endif