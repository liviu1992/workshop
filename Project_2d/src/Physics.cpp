#include "Physics.h"
#include "GL\glew.h"

GLfloat Physics::getMass(){
	return this->mass;
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
	if (fast){
		AdvanceStep = 60*advanceStep;
	} else {
		AdvanceStep = advanceStep;
	}
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
	} else if (y+fireDistance>this->y){
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


		//this->x=this->x+speedX*mspeedX*this->speed;
		//this->y=this->y+speedY*mspeedY*this->speed;
		this->sprite->move(this->x,this->y);
		

		this->getSprite()->getMatrix()->moveCamera(this->x, this->y);


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



	}
	if (type==physicsType::P_SCOUT || type==physicsType::P_BASIC || type==physicsType::P_ASSAULT){
	switch(this->mov){
		case movement::LEFTRIGHT:
		/*
			LEFT-RIGHT MOVE
		*/
			if (left){
				if (this->x<this->enemyOriginX + this->limit_left){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>enemyOriginX + this->limit_right){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
		
			this->sprite->move(this->x, this->y);
			break;
		case movement::CIRC:
		
		/*
			MISCARE CIRCULARA
		*/
			this->x=enemyOriginX +this->x +(float)this->speed*this->circ_width*(float)std::cos(glfwGetTime()*0.01);
			this->y=enemyOriginY-0.5f +this->y + (float)this->speed*this->circ_height*(float)std::sin(glfwGetTime()*0.01);
			this->sprite->move(this->x,this->y);		
			break;

		
		/*
			MISCARE SINUSOIDALA
		*/
		case movement::SIN:
			this->y=this->y + (float)this->speed*(float)std::sin(glfwGetTime()*this->sine_amplitude);
			if (left){
				if (this->x<enemyOriginX +this->limit_left){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>enemyOriginX + this->limit_right){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
			this->sprite->move(this->x, this->y);
		}
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