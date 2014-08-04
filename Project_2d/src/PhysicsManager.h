#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include <vector>
#include <algorithm>
#include "Projectile.h"
#include "SpriteManager.h"
#include <chrono>
#include <iostream>
#include "SoundManager.h"

class Physics;

class PhysicsManager{
public:
	PhysicsManager(std::vector<Projectile*>* projectiles, TextureManager* tm, SpriteManager* sm, SoundManager* soundManager);
	~PhysicsManager();
	bool Add(Physics*  a_physics);
	bool Remove(Physics*  a_physics);
	void TestCollisions();
	GLboolean TestCollision(Physics* objectA, Physics* objectB);
	int Size();
	bool collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB );
	void LaunchProjectile(Physics* parent);
	void AllAttack();
	SoundManager* getSoundManager();
private:
	std::vector<Physics*> physics;
	std::vector<Projectile*>*projectiles;
	TextureManager* tm;
	SpriteManager* sm;
	PhysicsManager* pm;
	SoundManager* soundManager;
	GLfloat distance_to_engage;



	GLfloat desiredX;
	GLfloat desiredY;

	GLfloat playerX;
	GLfloat playerY;

	
};

#endif