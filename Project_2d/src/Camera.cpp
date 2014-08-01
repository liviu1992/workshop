#include "Camera.h"

Camera::Camera(Player* player){
	currentCamX=0.f;
	currentCamY=0.f;
	nextCamX=0.f;
	nextCamY=0.f;
	camBoundaryW = 0.45f;
	camBoundaryH = 0.3f;
	camFollowMode = false;
	this->speedCam = 0.02f;

	cam_left = false;
	cam_right = false;
	cam_up = false;
	cam_down = false;
	this->player=player;
	this->moving = false;
}

void Camera::updateCamera(){
	//std::cout << "Cam x " << currentCamX << "Cam y " << currentCamY << std::endl;
	this->x=player->getPhysics()->GetX();
	this->y=player->getPhysics()->GetY();
	//std::cout << "Player x " << x << "Player y " << y << std::endl;
	if ((this->x >= this->currentCamX-0.3f && 
			this->x <= this->currentCamX+0.3f &&
			this->y >= this->currentCamY-0.3f &&
			this->y <= this->currentCamY+0.3f
			)){
				moving = false;
				std::cout << "Moving is false" << std::endl;
				
		} else {
			if (!moving){
				std::cout << "Movement initiated!" << std::endl;
				this->nextCamX= this->x;
				this->nextCamY = this->y;

				this->oldCamX = this->currentCamX;
				this->oldCamY = this->currentCamY;

				
			//	std::cout << "From: " << oldCamX << " " << oldCamY << " To: " << nextCamX << " " << nextCamY << std::endl;

				moving = true;
				time0=0.4;
				limit_time = 0.99;
			}
			/*if (moving && (abs(this->x)> abs(nextCamX)+0.001f ||abs(this->y)> abs(nextCamY)+0.001f)){
				std::cout << "Movement continued" << std::endl;
				this->nextCamX = this->x;
				this->nextCamY = this->y;

				limit_time+=time0;

			//	limit_time+=time0;
				
			}*/
		
		}
		if (moving){
			if (time0>limit_time){
				moving = false;
			} 
			time0+=0.01;
			this->currentCamX = this->oldCamX + (this->nextCamX - this->oldCamX)*easingFunction(time0);//this->oldCamX + (this->nextCamX - this->oldCamX) * easingFunction(time0);
			this->currentCamY = this->oldCamY + (this->nextCamY- this->oldCamY)*easingFunction(time0);//this->oldCamY + (this->nextCamY - this->oldCamY) * easingFunction(time0);
		//	std::cout << "X: " << currentCamX << " Y: " << currentCamY << std::endl;
			
		}
		this->player->getSprite()->getMatrix()->moveCamera(this->currentCamX, this->currentCamY);
}

GLfloat Camera::getX(){
	return this->currentCamX;
}
GLfloat Camera::getY(){
	return this->currentCamY;
}

GLdouble Camera::easingFunction(GLdouble time){
	return time * time*time*time*time;
}