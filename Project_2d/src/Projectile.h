/*
	Va defini fiecare tip de proiectil utilizat
	in joc si modul in care acesta se comporta(in
	Physics).

*/

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <GL/glew.h>
#include "Sprite.h"

class Projectile{
public:
	Projectile(TextureManager* tm);

	GLfloat getX();
	GLfloat getY();
	GLfloat getSpeed();
	void setPosition(GLfloat x,GLfloat y);
	void setSpeed(GLfloat speed);
	std::shared_ptr<Sprite>  getSprite();
	void Physics();
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	void Fire(GLfloat x, GLfloat y, GLfloat rotate);
	GLboolean isAlive();
	void setAlive(GLboolean alive);
	~Projectile();
	void Rotate(GLfloat rotate);
	GLfloat getWidth();
	GLfloat getHeight();
private:
	GLfloat x;
	GLfloat y;
	GLfloat speed;
	std::shared_ptr<Sprite>  sprite;
	GLfloat projectileWidth;
	GLfloat projectileHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLboolean left;
	GLboolean right;
	GLboolean fired;
	GLboolean alive;
	TextureManager* tm;
	GLfloat rotate;
};

#endif