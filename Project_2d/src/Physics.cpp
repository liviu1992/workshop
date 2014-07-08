#include "Physics.h"




/*Physics::Physics(){
	this->x=0;
	this->y=0;
	this->width=0.2;
	this->height=0.2;
	this->speedX=0;
	this->speedY=0;
	this->type=physicsType::P_PLAYER;


}*/
/*Physics::Physics(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::shared_ptr<Sprite> sprite, physicsType type, GLboolean &alive) : alive(dummy){
	
	
	
}*/
GLfloat Physics::GetX(){
	return this->x;
}
GLfloat Physics::GetY(){
	return this->y;
}
GLfloat Physics::GetHeight(){
	return this->height;

}
GLfloat Physics::GetWidth(){
	return this->width;

}
void Physics::setPosition(GLfloat x, GLfloat y){
	this->sprite.get()->move(x,y);
	this->x=x;
	this->y=y;

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
	this->speedX=speedX;
}
void  Physics::setSpeedY(GLfloat speedY){
	this->speedY=speedY;
}
void  Physics::Rotate(GLfloat rotate){
	this->rotate += rotate;
	this->sprite.get()->Rotate(this->rotate, this->GetX(), this->GetY());
}
GLfloat  Physics::getRotate(){
	return this->rotate;
}

void Physics::setRotate(GLfloat rotate){
	this->rotate=rotate;
}

void Physics::Update(){
	switch(this->type){
	case physicsType::P_PLAYER:
		this->x=this->x+speedX*this->speed;
		this->y=this->y+speedY*this->speed;

		this->sprite.get()->move(this->x,this->y);


		this->speedX=0;
		this->speedY=0;

		break;
	case physicsType::P_ROCKET:
		this->sprite.get()->Rotate(this->rotate, this->GetX(), this->GetY());
		this->speedX=2;
		this->speedY=2;
	

		if (this->fired){
			std::cout << "a" << std::endl;
			this->y+=cos(rotate)*speedY*speed;
			this->x+=-sin(rotate)*speedX*speed;
			this->sprite.get()->move(this->x, this->y);
		}
		if ( this->y>1.5){
			this->sprite.get()->setDead(true);		
			this->alive=false;

			
		}
		if ( this->y<-1.5){
			this->sprite.get()->setDead(true);		
			this->alive=false;

		}

		if ( this->x>1.5){
			this->sprite.get()->setDead(true);
			this->alive=false;
			
		}
		if ( this->x<-1.5){
			this->sprite.get()->setDead(true);	
			this->alive=false;

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
				if (this->x<-0.8f){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8f){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
		
			this->sprite.get()->move(this->x, this->y);
			break;
		case movement::CIRC:
		
		/*
			MISCARE CIRCULARA
		*/
			this->x=this->x + (float)this->speed*1.8f*(float)std::cos(glfwGetTime());
			this->y=this->y + (float)this->speed*0.25f*(float)std::sin(glfwGetTime());
			this->sprite.get()->move(this->x+0.4f,this->y+0.5f);		
			break;

		
		/*
			MISCARE SINUSOIDALA
		*/
		case movement::SIN:
			this->y=this->y + (float)2.f*this->speed*(float)std::sin(glfwGetTime()*4);
			if (left){
				if (this->x<-0.8f){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8f){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
			this->sprite.get()->move(this->x, this->y);
		}
	}

}
//doar pentru proiectile
void Physics::fire(){
	this->fired=true;
	std::cout << "Fired!" << std::endl;
}