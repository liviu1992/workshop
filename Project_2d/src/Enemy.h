#ifndef ENEMY_H
#define ENEMY_H
#include <GL/glew.h>
#include "Sprite.h"
enum movement{
	LEFTRIGHT, CIRC, SIN
};

enum enemyType{
	SCOUT_ENEMY,
	BASIC_ENEMY,
	ASSAULT_ENEMY
};
class Enemy{
public:
	Enemy(TextureManager* tm, enemyType type);
	GLfloat getX();
	GLfloat getY();
	GLfloat getSpeed();
	void setPosition(GLfloat x,GLfloat y);
	void setSpeed(GLfloat speed);
	Sprite* getSprite();
	void Physics();
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
private:
	GLfloat x;
	GLfloat y;
	GLfloat speed;
	Sprite* sprite;
	GLfloat enemyWidth;
	GLfloat enemyHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLboolean left;
	GLboolean right;
	movement mov;
};
#endif