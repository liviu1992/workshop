/*
	Va defini fiecare tip de proiectil utilizat
	in joc si modul in care acesta se comporta(in
	Physics).

*/

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <GL/glew.h>
#include "Sprite.h"
#include "Physics.h"

class Projectile{
public:
	Projectile(TextureManager* tm);



	std::shared_ptr<Sprite>  getSprite();
	std::shared_ptr<Physics> getPhysics();

	void Fire(GLfloat x, GLfloat y, GLfloat rotate);
	GLboolean isAlive();
	void setAlive(GLboolean alive);
	~Projectile();
	void Rotate(GLfloat rotate);


private:
	GLfloat x;
	GLfloat y;
	std::shared_ptr<Sprite>  sprite;
	std::shared_ptr<Physics> physics;
	GLfloat projectileWidth;
	GLfloat projectileHeight;
	GLboolean alive;
	TextureManager* tm;

};

#endif