#include "PhysicsManager.h"
#define MIN(X,Y) ( (X) < (Y) ? (X) : (Y)) 

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
void PhysicsManager::AllAttack(){
	for (unsigned int i=0; i<this->physics.size(); i++){
		if (this->physics.at(i)->fireCommandIssued()){
			//std::cout << "Fire" << std::endl;
			LaunchProjectile(this->physics.at(i));
			physics.at(i)->issueFireCommand(false);

		}

	}


}
void PhysicsManager::LaunchProjectile(Physics* parent){
	
		this->projectiles->push_back(new Projectile(this->tm ));
		this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setPosition(parent->GetX(), parent->GetY());
		if (parent->getType()==physicsType::P_PLAYER){
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setOwnerIfRocket(true);
			this->sm->Add(this->projectiles->at(this->projectiles->size()-1)->getSprite());
			this->Add(this->projectiles->at(this->projectiles->size()-1)->getPhysics());
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setParentSpeed(parent->getSpeedX(), parent->getSpeedY());
			this->projectiles->at(this->projectiles->size()-1)->Fire(parent->GetX(), parent->GetY(),parent->getRotate()/*physics.at(i)->getRotate()*/);
		} else {
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setRotate(180);
			this->sm->Add(this->projectiles->at(this->projectiles->size()-1)->getSprite());
			this->Add(this->projectiles->at(this->projectiles->size()-1)->getPhysics());
			this->projectiles->at(this->projectiles->size()-1)->Fire(parent->GetX(), parent->GetY(),307.f * 3.14f/180.f/*physics.at(i)->getRotate()*/);
		}
		
	

}
/*
	tests if any enemy can fire at the player
*/
void PhysicsManager::TestAttacks(){
	for (unsigned int i=1; i<physics.size(); i++){
		if (!(physics.at(i)->getType()==physicsType::P_PLAYER || physics.at(i)->getType()==physicsType::P_ROCKET)){
			//then we have an enemy
			// * stiu ca playerul este primul adaugat in PhysicsManager(de aia incep si de la 1 for-ul)
			// acum testez daca inamicul poate "vedea" playerul
			glm::vec2 enemyPosition = glm::vec2(physics.at(i)->GetX(), physics.at(i)->GetY());
			glm::vec2 enemyFacing = glm::normalize(glm::vec2(0, -1)); //directia in care se uita inamicul, adica in jos 
			glm::vec2 playerPosition = glm::vec2(physics.at(0)->GetX(), physics.at(0)->GetY()); // stiu ca e la pozitia 0

			glm::vec2 enemyToPlayer = glm::normalize(playerPosition - enemyPosition);

			GLfloat angle = static_cast<GLfloat>(glm::acos(glm::dot(enemyFacing, enemyToPlayer))*180/3.141);
			GLfloat fov = this->physics.at(i)->getFov();
			if (angle < fov/2){    //testez daca playerul e in raza vizuala a inamicului
				//si daca e trag pe directia (0, -1) 
				if (physics.at(i)->canIFire()){
					//LaunchProjectile(physics.at(i));
					//std::cout << "Fire command issued " << std::endl;
					physics.at(i)->issueFireCommand(true);
				}
				
			}
		





		}

	}

}

void PhysicsManager::AllSearch(){
	
	for (unsigned int i=0; i<physics.size(); i++){
		if (!(physics.at(i)->getType()==physicsType::P_PLAYER || physics.at(i)->getType()==physicsType::P_ROCKET)){

			//verific daca se afla playerul prin preajma
			//testez daca distanta player - inamic este mai mica de o anumita valoare
			//daca e asa, inamicul se va deplasa in pozitia de atac
			if (glm::distance(glm::vec2(physics.at(i)->GetX(), physics.at(i)->GetY()),
				 glm::vec2(physics.at(0)->GetX(), physics.at(i)->GetY()))< distance_to_engage){

					 //acum ma deplasez catre player

					 this->physics.at(i)->advanceTowards(physics.at(0)->GetX(), physics.at(0)->GetY());




			}

		}
	}

}

/*
	din manifold o sa iau viteza pe normala
*/
void solveCollision(Physics* objectA, Physics* objectB, Manifold* manifold){
	//nu rezolv coliziuni intre racheta trasa de player si player
	if (((objectA->getType()==physicsType::P_ROCKET) && (objectB->getType()==physicsType::P_PLAYER) && objectB->getOwner())) { 
			return;
	}
	//nu rezolv coliziuni intre racheta trasa de inamici si acestia
	if (((objectA->getType()==physicsType::P_ROCKET) && (objectB->getType()!=physicsType::P_PLAYER) && !objectB->getOwner())  ){
			return;
	}




	GLfloat velAlongNormal = manifold->penetration;
	GLfloat e = 0.1f;// 0.01f;

	GLfloat j = -(1+e) * velAlongNormal;
	j /= objectA->getMass() + objectB->getMass();
	j = j/10;
	glm::vec2 impulse = j * manifold->normal;

	glm::vec2 velocityA = -objectA->getMass() * impulse;
	glm::vec2 velocityB = objectB->getMass() * impulse;
	
	
	objectA->setPosition(objectA->GetX()+velocityA.x, objectA->GetY()+velocityA.y);
	objectB->setPosition(objectB->GetX()+velocityB.x, objectB->GetY()+velocityB.y);

}

PhysicsManager::PhysicsManager(std::vector<Projectile*>* projectiles, TextureManager* tm, SpriteManager* sm){
	this->projectiles = projectiles;
	this->tm = tm;
	this->sm = sm;
	SettingsManager settingsManager;
	distance_to_engage = settingsManager.get("distance_to_engage");
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

		solveCollision(objectA, objectB, &manifold);
		
		
	
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