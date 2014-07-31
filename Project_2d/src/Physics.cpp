#include "Physics.h"
#include "PhysicsManager.h"
#include <cmath>
#include "GL\glew.h"

Physics* Physics::player;
PhysicsManager* Physics::physicsManager;

GLfloat Physics::getMass(){
	return this->mass;
}

void Physics::setPlayer(Physics* player){
	this->player=player;
}
void Physics::onCollision(Manifold* manifold, GLboolean isA){
	
	

	//intotdeauna din A se va face totul pentru a pastra simplitatea 
	if (isA){
		if (manifold->objectB->getType()==physicsType::P_POWERUP_1){
			//player will get the powerup
			std::cout << "Increasing health!" << std::endl;
			manifold->objectA->getCombatant()->increaseHealth(10);
			//manifold->objectB->getCombatant()->increaseHealth(10);
			manifold->objectB->getSprite()->setDead(true);
		}
		if (manifold->objectB->getType()==physicsType::P_POWERUP_2){
			//player will get the powerup
			std::cout << "Increasing speed!" << std::endl;


			manifold->objectA->getCombatant()->addModifier(modifier::HIGH_SPEED);
		
			manifold->objectB->getSprite()->setDead(true);
		}
		if (manifold->objectB->getType()==physicsType::P_POWERUP_3){
			//player will get the powerup
			std::cout << "Instagib!" << std::endl;

			manifold->objectA->getCombatant()->addModifier(modifier::INSTAGIB);
			
			manifold->objectB->getSprite()->setDead(true);
		}


		if (this->type!=physicsType::P_ROCKET && (manifold->objectA->getType()==physicsType::P_PLAYER) && manifold->objectB->getType()==physicsType::P_ROCKET && !manifold->objectB->getOwner()){
			combatant->damage(damage);
			manifold->objectB->getSprite()->Explode();
			
			manifold->objectB->isExploding=true;
			//manifold->objectB->Rotate(-manifold->objectB->getRotate());
			
		}
		else if (this->type!=physicsType::P_ROCKET && manifold->objectA->getType()!=physicsType::P_PLAYER && manifold->objectB->getType()==physicsType::P_ROCKET && manifold->objectB->getOwner()){
				if (!manifold->objectA->getSprite()->getExplode() && !manifold->objectA->getSprite()->getDead()){
					manifold->objectB->getSprite()->Explode();
					
					if (manifold->objectB->getParentsPhysics()->getCombatant()->hasModifier(modifier::INSTAGIB)){
						std::cout << "Instagibbed!" << std::endl;
						combatant->damage(9999);
						
					} else {
						combatant->damage(damage);
					}

					manifold->objectB->isExploding=true;
				}
			
		
			
		}
	

	} 

}

void Physics::setEnemyOrigin(GLfloat originX, GLfloat originY){
	this->enemyOriginX=originX;
	this->enemyOriginY=originY;
}


Combatant* Physics::getCombatant(){
	return this->combatant;
}
physicsType Physics::getType(){
	return this->type;
}
void Physics::setParentSpeed(GLfloat parentSpeedX, GLfloat parentSpeedY){
	this->parentSpeedX=parentSpeedX;
	this->parentSpeedY=parentSpeedY;
}
GLfloat Physics::getSpeedX(){
	return this->speedX*this->speed*0.05f;
}
GLfloat Physics::getSpeedY(){
	return this->speedY*this->speed*0.05f;
}
GLfloat Physics::GetX(){
	return this->x;
}
GLfloat Physics::GetY(){
	return this->y;
}

void Physics::advanceTowards(GLfloat x, GLfloat y, GLboolean fast){
	GLfloat AdvanceStep=0;

		AdvanceStep = 0.005f;
	
	if (x<this->x){
		this->x-= AdvanceStep;
		this->enemyOriginX-=AdvanceStep;
	} else if (x>this->x){
		this->x+= AdvanceStep;
		this->enemyOriginX+=AdvanceStep;
	}

	if (y+fireDistance<this->y){
		this->y-= AdvanceStep;
		this->enemyOriginY-=AdvanceStep;
	} else if (y>this->y){
		this->y+= AdvanceStep;
		this->enemyOriginY+=AdvanceStep;
	}
}

void Physics::SetX(GLfloat x){
	this->x=x;
}
void Physics::SetY(GLfloat y){
	this->y=y;
}

GLfloat Physics::GetHeight(){
	return this->height;

}
GLfloat Physics::GetWidth(){
	return this->width;

}
void Physics::setPosition(GLfloat x, GLfloat y){
	this->x=x;
	this->y=y;
	this->sprite->move(this->x,this->y);
	

}
void Physics::setSize(GLfloat width, GLfloat height){
	this->width=width;
	this->height=height;
	
}
GLfloat Physics::getSpeed(){
	return this->speed;
}
void  Physics::setSpeed(GLfloat speed){
	this->speed=speed;
}
void  Physics::setSpeedX(GLfloat speedX){
	this->speedX+=speedX;
}
void  Physics::setSpeedY(GLfloat speedY){
	this->speedY+=speedY;
}
void  Physics::Rotate(GLfloat rotate){
	this->rotate += rotate;
	this->sprite->Rotate(this->rotate, this->GetX(), this->GetY());
}
GLfloat  Physics::getRotate(){
	return this->rotate;
	
}

void Physics::setRotate(GLfloat rotate){
	this->rotate=rotate;
	this->sprite->Rotate(this->rotate, this->GetX(), this->GetY());
}
Sprite* Physics::getSprite(){
	return this->sprite;
}

void Physics::Update(){
	if (isExploding){
		this->Rotate(-this->getRotate());
		return;
	}
	switch(this->type){
	case physicsType::P_PLAYER:
		
		this->getCombatant()->checkModifierLifetime();    //verific ca dupa un interval de timp modifier-ul se dispara

	

		this->y+=cos(rotate)*speedY*speed*0.05f;
		this->x+=-sin(rotate)*speedX*speed*0.05f;
		
		speedX*=0.98f;
		speedY*=0.98f;
				
		this->sprite->move(this->x,this->y);
		
		
		

		break;
	case physicsType::P_ROCKET:
		if (this->fired){
			this->sprite->Rotate(this->rotate, this->GetX(), this->GetY());
			this->speedX=2;
			this->speedY=2;
			//if (this->owner){
		//	speed*=1.5f;
			//}
			if (this->owner){
				if (this->getParentsPhysics()->getCombatant()->hasModifier(modifier::HIGH_SPEED)){
					m_speed =2.f*speed;
					m_fireLimit = fireLimit/4;
				} else {
					m_speed = speed;
					m_fireLimit = fireLimit;
				}
			} else {
				m_speed = speed;
				m_fireLimit = fireLimit;
			}

			if (this->fired){
				this->y+=cos(rotate)*speedY*m_speed;
				this->x+=-sin(rotate)*speedX*m_speed;
				this->sprite->move(this->x, this->y);
			}
			if ( this->y>this->rocketOriginY + this->rocketMaximumRange){
				this->sprite->setDead(true);		
				this->alive=false;

			
			}
			if ( this->y<this->rocketOriginY - rocketMaximumRange){
				this->sprite->setDead(true);		
				this->alive=false;

			}

			if ( this->x>this->rocketOriginX  + this->rocketMaximumRange){
				this->sprite->setDead(true);
				this->alive=false;
			
			}
			if ( this->x<this->rocketOriginX - this->rocketMaximumRange){
				this->sprite->setDead(true);	
				this->alive=false;

			}
		}
		break;
	default:
		AI_enemy();
		break;

	}
	
			
	this->getSprite()->getMatrix()->updateMatrix();
	}

	



//doar pentru proiectile
void Physics::fire(){
	this->fired=true;
	this->rocketOriginX=this->x;
	this->rocketOriginY=this->y;
	

}

GLboolean Physics::getOwner(){
	return this->owner;
}
GLboolean Physics::fireCommandIssued(){
	return this->fireCommand;
}
void Physics::issueFireCommand(GLboolean value){
	this->fireCommand=value;
}
void Physics::setOwnerIfRocket(GLboolean owner){
	this->owner = owner;  //true for player, false for enemy
}

GLboolean Physics::canIFire(){
	if (glfwGetTime()>=fireTimer+m_fireLimit){
			fireTimer = (float)glfwGetTime();
			return true;
		}
		else {
			return false;
		}
}

GLfloat Physics::getFov(){
	return static_cast<GLfloat>(this->fov);
}

Physics* Physics::getParentsPhysics(){
	return this->parentsPhysics;
}
void Physics::setParentsPhysics(Physics* physics){
	this->parentsPhysics=physics;
	
}

bool Physics::collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB ){
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

GLfloat Physics::getCurrentCamX(){
	return this->currentCamX;
}
GLfloat Physics::getCurrentCamY(){
	return this->currentCamY;
}

void Physics::AI_enemy(){

	GLboolean nearPlayer = checkDistance();
	GLboolean aimingPlayer = checkAngle();
//	std::cout << "Position " << x << "  " << y << " State " << AI_state << std::endl;
	
		//angle=0;
	
	
	switch(AI_state){
	case stateAI::ROTATE_TO_PLAYER:
		//actions 

	
		angle = getAngle();
	
		if (abs(angle)>0.27){
			angle = 0.27 * angle/abs(angle);
		}
		
		 

	//	 angle = -angle;

		// std::cout << static_cast<int>(this->rotate * 180/3.14) %360 << std::endl;
		// if ( abs(angle*180/3.141)>15){			 
		this->Rotate(angle);
		// }		
		
		//transitions
	//	if (aimingPlayer){



		if (nearPlayer){
			AI_state = stateAI::FIRE_AT_PLAYER;
		} else {
			AI_state = stateAI::ADVANCE_TO_PLAYER;
		}

		/*} else {
			AI_state =  stateAI::ROTATE_TO_PLAYER;
		}*/
	

		break;

	case stateAI::ADVANCE_TO_PLAYER:
		//actions
	//	std::cout << "Advancing " << y << std::endl;
		//advanceTowards(player->GetX(),player->GetY() , false);
		this->y-=cos(this->rotate)*0.02f;
		this->x+=sin(this->rotate)*0.02f;
		this->sprite->move(this->x,this->y);
		//transitions
		if (!aimingPlayer){
			AI_state = stateAI::ROTATE_TO_PLAYER;
			break;
		}
		if (nearPlayer){
			AI_state = stateAI::FIRE_AT_PLAYER;
		} else {
			AI_state = stateAI::ADVANCE_TO_PLAYER;
		}

	

		break;

	case stateAI::FIRE_AT_PLAYER:
		//actions
		//physicsManager->LaunchProjectile(this);
		if (this->canIFire()){
			this->issueFireCommand(true);
		}
		
	//	std::cout << "Fire "<< y << std::endl;
		//transitions
		if (!nearPlayer){
			AI_state = stateAI::ADVANCE_TO_PLAYER;;
			break;
		}


		if (!aimingPlayer){
			AI_state = stateAI::ROTATE_TO_PLAYER;
		} else {
			AI_state = stateAI::FIRE_AT_PLAYER;
		}		

		break;


	}
}

void Physics::setPhysicsManager(PhysicsManager* physicsManager){
	this->physicsManager = physicsManager;
}
GLboolean Physics::checkAngle(){
	
	glm::vec2 enemyPosition = glm::vec2(this->x,this->y); //aflu pozitia inamicului
	//glm::vec2 enemyFacing = glm::normalize(glm::vec2(0, -1)); //directia in care se uita inamicul, adica in jos 

	glm::vec2 enemyFacing = glm::vec2(sin(this->rotate), -cos(this->rotate));
	glm::vec2 playerPosition = glm::vec2(this->player->GetX(),this->player->GetY()); // stiu ca e playerul e la pozitia 0 in physics din 
														   //physicsManager


	glm::vec2 enemyToPlayer = glm::normalize(playerPosition - enemyPosition);

	GLfloat angle = static_cast<GLfloat>(glm::acos(glm::dot(enemyFacing, enemyToPlayer))*180/3.141);
	GLfloat fov = 30;

	if (angle<fov/2){		
		return true;
	} else {
		return false;
	}
	

	

}

GLboolean Physics::checkDistance(){
	GLfloat distance = glm::distance(glm::vec2(player->GetX(),player->GetY()), glm::vec2(this->x, this->y));
	if (distance<1.f){//distance_to_engage){
		return true;
	} else {
		return false;
	}
	
}

GLdouble Physics::getAngle(){
	
	/*glm::vec2 enemyPosition = glm::vec2(this->x,this->y); //aflu pozitia inamicului
	//glm::vec2 enemyFacing = glm::normalize(glm::vec2(0, -1)); //directia in care se uita inamicul, adica in jos 

	glm::vec2 enemyFacing = glm::vec2(sin(this->rotate), -cos(this->rotate));
	glm::vec2 playerPosition = glm::vec2(this->player->GetX(),this->player->GetY()); // stiu ca e playerul e la pozitia 0 in physics din 
														   //physicsManager


	glm::vec2 enemyToPlayer = glm::normalize(playerPosition - enemyPosition);
	GLfloat rad_angle = glm::acos(glm::dot(enemyFacing, enemyToPlayer));
	GLfloat m_angle = static_cast<GLfloat>(rad_angle*180/3.141f);

	GLfloat fov = 90;

	if (angle<fov/2){
		return rad_angle;
	} else  {
		return -rad_angle;
		std::cout << "neg" << std::endl;
	}
	*/

	return atan2(this->x, this->y) -  atan2(this->player->GetX() , this->player->GetY());
	



}

void Physics::rotatingLeft(){
	this->rotLeft=true;
	this->rotRight=false;
}
void Physics::rotatingRight(){
	this->rotLeft=false;
	this->rotRight=true;
}
