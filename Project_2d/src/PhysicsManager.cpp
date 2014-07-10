#include "PhysicsManager.h"

bool PhysicsManager::collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB ){
	GLfloat xA, yA, XA, YA, xB, yB, XB, YB;
	
	xA = cxA - wA/2;
	XA = cxA + wA/2;
	xB = cxB - wB/2;
	XB = cxB + wB/2;
	yA = cyA - wA/2;
	YA = cyA + wA/2;
	yB = cyB - hB/2;
	YB = cyB + hB/2;

	if (XA<xB || XB<xA || YA<yB || YB<yA){
		return false;
	}
	return true;

}

PhysicsManager::PhysicsManager(){
	std::cout << "PhysicsManager initializes" << std::endl;
	
}
bool PhysicsManager::Add(Physics*  a_physics){
	int size = physics.size();
	this->physics.push_back(a_physics);
	if (size==physics.size()+1){
		return true;
	} else {
		return false;
	}
}
bool PhysicsManager::Remove(Physics*  a_physics){
	bool result = false;
	for (unsigned int i=0; i<this->physics.size(); i++){
		if (a_physics==this->physics.at(i)){		
			this->physics.erase(this->physics.begin()+i);
		}
	}
	


	return result;
}
void PhysicsManager::TestCollisions(){

	for (unsigned int i=0; i<physics.size(); i++){
		for (unsigned int j=i+1; j<physics.size(); j++){
			TestCollision(this->physics.at(i), this->physics.at(j));

		}
		
	}

}

GLboolean PhysicsManager::TestCollision(Physics* objectA, Physics* objectB){
	GLboolean result=false;
	Manifold manifold;
	manifold.objectA=objectA;
	manifold.objectB=objectB;

	glm::vec2 n = glm::vec2(objectA->GetX(), objectB->GetY())-glm::vec2(objectB->GetX(), objectB->GetY());

	GLfloat A_min_x = objectA->GetX()-objectA->GetWidth()/2;
	GLfloat A_max_x = objectA->GetX()+objectA->GetWidth()/2;
	GLfloat A_min_y = objectA->GetY()-objectA->GetHeight()/2;
	GLfloat A_max_y = objectA->GetY()+objectA->GetHeight()/2;

	GLfloat B_min_x = objectB->GetX()-objectB->GetWidth()/2;
	GLfloat B_max_x = objectB->GetX()+objectB->GetWidth()/2;
	GLfloat B_min_y = objectB->GetY()-objectB->GetHeight()/2;
	GLfloat B_max_y = objectB->GetY()+objectB->GetHeight()/2;

	result = collisionDetectorAABB(objectA->GetX(), objectA->GetY(), objectA->GetWidth(), objectA->GetHeight(),
		objectB->GetX(), objectB->GetY(), objectB->GetWidth(), objectB->GetHeight());

	GLfloat A_extent_x = (A_max_x - A_min_x)/ 2;
	GLfloat B_extent_x = (B_max_x - B_min_x)/ 2;

	GLfloat x_overlap = A_extent_x+B_extent_x-abs(n.x);

	if (x_overlap>0){	
		GLfloat A_extent_y = (A_max_y - A_min_y)/ 2;
		GLfloat B_extent_y = (B_max_y - B_min_y)/ 2;

		GLfloat y_overlap = A_extent_y+B_extent_y-abs(n.y);


		if (y_overlap>0){

			if (x_overlap>y_overlap){
				if (n.x<0){
					manifold.normal = glm::vec2(-1,0);
				} else {
					manifold.normal = glm::vec2(1,0);
				}
				manifold.penetration=x_overlap;
				
			} else {
				if (n.y<0){
					manifold.normal = glm::vec2(0,-1);
				} else {
					manifold.normal = glm::vec2(0, 1);
				}
				manifold.penetration=y_overlap;
				
			}

		
		
		
		
		
		}
	}

	if (result){
	//	std::cout << "Collision! " << manifold.normal.x << " " << manifold.normal.y<< std::endl;
		//trimit manifoldul la cele 2 obiecte
		manifold.objectA->onCollision(&manifold, true);
		manifold.objectB->onCollision(&manifold, false);
	}
	

	return result;
}
int PhysicsManager::Size(){
	return physics.size();
}

PhysicsManager::~PhysicsManager(){
	this->physics.clear();
	std::cout << "PhysicsManager terminated" << std::endl;
}