#include "Physics.h"




void Physics::onCollision(Manifold* manifold, GLboolean isA){
	//aici pun pentru coliziune racheta inamic

	/*if (this->type==physicsType::P_ROCKET && !manifold->objectA->type==physicsType::P_PLAYER && !manifold->objectB->type==physicsType::P_PLAYER){
		sprite->Explode();
		
	
	} */

	//intotdeauna din A se va face totul pentru a pastra simplitatea 
	if (isA){
		if (this->type==physicsType::P_ROCKET && !(manifold->objectA->getType()==physicsType::P_PLAYER)){
		/*	if (!sprite->getExplode()){
				sprite->Explode();	
			}
			*/
			
		}
		else {
			if (this->type!=physicsType::P_ROCKET && manifold->objectA->getType()!=physicsType::P_PLAYER && manifold->objectB->getType()==physicsType::P_ROCKET){
				if (!manifold->objectA->getSprite()->getExplode() && !manifold->objectA->getSprite()->getDead()){
					std::cout << "Damaging!" <<std::endl;
					combatant->damage(5);
					manifold->objectB->getSprite()->Explode();

				}
			
		
			}
		}
	

	} 

	

	

	//aici pun pentru intersectia cu o racheta

}
Combatant* Physics::getCombatant(){
	return this->combatant;
}
physicsType Physics::getType(){
	return this->type;
}

GLfloat Physics::GetX(){
	return this->x;
}
GLfloat Physics::GetY(){
	return this->y;
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
	this->mspeedX=speedX;
}
void  Physics::setSpeedY(GLfloat speedY){
	this->mspeedY=speedY;
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
	switch(this->type){
	case physicsType::P_PLAYER:
		this->x=this->x+speedX*mspeedX*this->speed;
		this->y=this->y+speedY*mspeedY*this->speed;
		this->sprite->move(this->x,this->y);
		this->mspeedX=0;
		this->mspeedY=0;

		break;
	case physicsType::P_ROCKET:
		if (this->fired){
			this->sprite->Rotate(this->rotate, this->GetX(), this->GetY());
			this->speedX=2;
			this->speedY=2;
	

			if (this->fired){
				this->y+=cos(rotate)*speedY*speed;
				this->x+=-sin(rotate)*speedX*speed;
				this->sprite->move(this->x, this->y);
			}
			if ( this->y>1.8){
				this->sprite->setDead(true);		
				this->alive=false;

			
			}
			if ( this->y<-1.8){
				this->sprite->setDead(true);		
				this->alive=false;

			}

			if ( this->x>1.8){
				this->sprite->setDead(true);
				this->alive=false;
			
			}
			if ( this->x<-1.8){
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
				if (this->x<this->limit_left){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>this->limit_right){
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
			this->x=this->x + (float)this->speed*this->circ_width*(float)std::cos(glfwGetTime());
			this->y=this->y + (float)this->speed*this->circ_height*(float)std::sin(glfwGetTime());
			this->sprite->move(this->x,this->y);		
			break;

		
		/*
			MISCARE SINUSOIDALA
		*/
		case movement::SIN:
			this->y=this->y + (float)this->speed*(float)std::sin(glfwGetTime()*this->sine_amplitude);
			if (left){
				if (this->x<this->limit_left){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>this->limit_right){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
			this->sprite->move(this->x, this->y);
		}
	}

}
//doar pentru proiectile
void Physics::fire(){
	this->fired=true;

}