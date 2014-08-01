#include "PhysicsManager.h"
#include "Physics.h"

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
			soundManager->Play(Sounds::ROCKET_LAUCHED);
		}

	}


}
void PhysicsManager::LaunchProjectile(Physics* parent){
	


		//std::cout << measure<>::execution( [&]() {  
	
		/*
		this->projectiles->push_back(new Projectile(this->tm ));
		this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setPosition(parent->GetX(), parent->GetY());
		if (parent->getType()==physicsType::P_PLAYER){
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setOwnerIfRocket(true);
			this->sm->Add(this->projectiles->at(this->projectiles->size()-1)->getSprite());
			this->Add(this->projectiles->at(this->projectiles->size()-1)->getPhysics());
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setParentSpeed(parent->getSpeedX(), parent->getSpeedY());
			this->projectiles->at(this->projectiles->size()-1)->Fire(parent->GetX(), parent->GetY(),parent->getRotate());
		} else {
			this->projectiles->at(this->projectiles->size()-1)->getPhysics()->setRotate(180);
			this->sm->Add(this->projectiles->at(this->projectiles->size()-1)->getSprite());
			this->Add(this->projectiles->at(this->projectiles->size()-1)->getPhysics());
			this->projectiles->at(this->projectiles->size()-1)->Fire(parent->GetX(), parent->GetY(),307.f * 3.14f/180.f);
		}
			

		*/
		
		if (parent->getType()==physicsType::P_PLAYER){
			this->projectiles->push_back(new Projectile(this->tm, true));
		} else {
			this->projectiles->push_back(new Projectile(this->tm, false));
		}
		
		Physics* physics=this->projectiles->at(this->projectiles->size()-1)->getPhysics();
		Projectile* projectile = this->projectiles->at(this->projectiles->size()-1);
		
		if (parent->getType()==physicsType::P_PLAYER){
			physics->setPosition(parent->GetX(), parent->GetY());
			physics->setOwnerIfRocket(true);
			this->sm->Add(projectile->getSprite());
			this->Add(physics);
			//physics->setParentSpeed(parent->getSpeedX(), parent->getSpeedY());
			projectile->getPhysics()->setParentsPhysics(parent);
			projectile->Fire(parent->GetX()+0.0025f, parent->GetY(),parent->getRotate()/*physics.at(i)->getRotate()*/);
		} else {
			physics->setPosition(parent->GetX(), parent->GetY());
			//physics->setRotate(180);
			this->sm->Add(projectile->getSprite());
			this->Add(physics);
			projectile->getPhysics()->setParentsPhysics(parent);
			projectile->Fire(parent->GetX()+0.0025f, parent->GetY(),parent->getRotate()+  3.141f/*physics.at(i)->getRotate()*/);
		}  
		
		//}) << std::endl;

}
/*
	tests if any enemy can fire at the player
*/
void PhysicsManager::TestAttacks(){
	//std::cout << measure<>::execution( [&]() {  


	/*for (unsigned int i=1; i<physics.size(); i++){
		if (!(physics.at(i)->getType()==physicsType::P_PLAYER || physics.at(i)->getType()==physicsType::P_ROCKET || physics.at(i)->getType()==physicsType::P_POWERUP_1 || physics.at(i)->getType()==physicsType::P_POWERUP_2 || physics.at(i)->getType()==physicsType::P_POWERUP_3 ) 			
			 &&  glm::distance(physics.at(i)->getSprite()->getPosition(), physics.at(0)->getSprite()->getPosition())<4.5f){
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
				if (physics.at(i)->canIFire()){
					physics.at(i)->issueFireCommand(true);
				}
				
			}
		
		
		



		}

	}*/
	//}) << std::endl;

}

void PhysicsManager::AllSearch(){
/*	playerX = physics.at(0)->GetX();
	playerY = physics.at(0)->GetY();
	if (this->strange==0){
		this->strange =  glfwGetTime();
	
		//obtin noi coordonate apropiate de cele dorite
		desiredX = playerX + (rand()%1000)/1000.f-0.5f;
		desiredY = playerY + (rand()%1000)/1000.f-0.5f;
	} else {
		if (this->strange+4 < glfwGetTime()){

		} else {
			this->strange=0;
		}


		
	}




	for (unsigned int i=0; i<physics.size(); i++){
		if (!(physics.at(i)->getType()==physicsType::P_PLAYER || physics.at(i)->getType()==physicsType::P_ROCKET || physics.at(i)->getType()==physicsType::P_POWERUP_1 || physics.at(i)->getType()==physicsType::P_POWERUP_2 ||  physics.at(i)->getType()==physicsType::P_POWERUP_3  )){

			//verific daca se afla playerul prin preajma
			//testez daca distanta player - inamic este mai mica de o anumita valoare
			//daca e asa, inamicul se va deplasa in pozitia de atac
			
					


					 //acum ma deplasez catre player
					 if (glm::distance(glm::vec2(physics.at(i)->GetX(), physics.at(i)->GetY()),
				 glm::vec2(playerX, playerY))< distance_to_engage){
					 this->physics.at(i)->advanceTowards(desiredX, desiredY, false);
					 } else {
						 this->physics.at(i)->advanceTowards(desiredX, desiredY, true);
					 }



			

		}
	}*/

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
	//nu rezolv coliziuni ce implica powerupuri si rachete
	if ((objectA->getType()==physicsType::P_POWERUP_1 || objectA->getType()==physicsType::P_POWERUP_2 || objectA->getType()==physicsType::P_POWERUP_3) && (objectB->getType()==physicsType::P_ROCKET)){
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

PhysicsManager::PhysicsManager(std::vector<Projectile*>* projectiles, TextureManager* tm, SpriteManager* sm, SoundManager* soundManager){
	this->projectiles = projectiles;
	this->soundManager = soundManager;
	this->tm = tm;
	this->sm = sm;
	this->strange = 0;
	SettingsManager settingsManager;
	
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
		if (glm::distance(physics.at(i)->getSprite()->getPosition(), physics.at(0)->getSprite()->getPosition())<1.8f){
			for (unsigned int j=i+1; j<physics.size(); j++){
			//	if (glm::distance(physics.at(j)->getSprite()->getPosition(), physics.at(0)->getSprite()->getPosition())<1.8f){
					TestCollision(this->physics.at(i), this->physics.at(j));
			//	}

			}
		}
		
	}


	
}

GLboolean PhysicsManager::TestCollision(Physics* objectA, Physics* objectB){
	GLboolean result=false;
	Manifold manifold;
	manifold.objectA=objectA;
	manifold.objectB=objectB;


	GLfloat objectAX=objectA->GetX();
	GLfloat objectAY=objectA->GetY();
	GLfloat objectAW = objectA->GetWidth();
	GLfloat objectAH=objectA->GetHeight();

	GLfloat objectBX=objectB->GetX();
	GLfloat objectBY=objectB->GetY();
	GLfloat objectBW = objectB->GetWidth();
	GLfloat objectBH=objectB->GetHeight();



	glm::vec2 n = glm::vec2(objectAX, objectAY)-glm::vec2(objectBX, objectBY);

	

	GLfloat A_min_x =objectAX-objectAW;
	GLfloat A_max_x = objectAX+objectAW;
	GLfloat A_min_y = objectAY-objectAH;
	GLfloat A_max_y = objectAY+objectAH;

	GLfloat B_min_x = objectBX-objectBW;
	GLfloat B_max_x = objectBX+objectBW;
	GLfloat B_min_y = objectBY-objectBH;
	GLfloat B_max_y = objectBY+objectBH;

	result = collisionDetectorAABB(objectAX, objectAY, objectAW, objectAH,
		objectBX, objectBY, objectBW, objectBH);

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
		//manifold.objectB->onCollision(&manifold, false);

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

SoundManager* PhysicsManager::getSoundManager(){
	return this->soundManager;
}