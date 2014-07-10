#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "Physics.h"
#include <vector>
#include <algorithm>


	



class PhysicsManager{
public:
	PhysicsManager();
	~PhysicsManager();
	bool Add(Physics*  a_physics);
	bool Remove(Physics*  a_physics);
	void TestCollisions();
	GLboolean TestCollision(Physics* objectA, Physics* objectB);
	int Size();
	bool collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB );
private:
	std::vector<Physics*> physics;
};

#endif