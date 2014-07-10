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
#include "SettingsManager.h"
#include "Combatant.h"
class Projectile{
public:
	Projectile(TextureManager* tm);



	Sprite*  getSprite();
	Physics* getPhysics();

	void Fire(GLfloat x, GLfloat y, GLfloat rotate);
	GLboolean isAlive();
	void setAlive(GLboolean alive);
	~Projectile();
	void Rotate(GLfloat rotate);
	Combatant* getCombatant();

private:
	GLfloat x;
	GLfloat y;
	Sprite*  sprite;
	Physics* physics;
	GLfloat projectileWidth;
	GLfloat projectileHeight;
	GLboolean alive;
	TextureManager* tm;
	Combatant* combatant;
	GLint health;

};

#endif