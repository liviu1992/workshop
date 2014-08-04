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
	if ((this->x >= this->currentCamX-0.3f && 
			this->x <= this->currentCamX+0.3f &&
			this->y >= this->currentCamY-0.3f &&
			this->y <= this->currentCamY+0.3f
			)){
				moving = false;
				
		} else {
			if (!moving){
				this->nextCamX= this->x;
				this->nextCamY = this->y;

				this->oldCamX = this->currentCamX;
				this->oldCamY = this->currentCamY;

				

				moving = true;
				time0=0.4;
				limit_time = 0.99;
			}
		
		
		}
		if (moving){
			if (time0>limit_time){
				moving = false;
			} 
			time0+=0.01;
			this->currentCamX = this->oldCamX + (this->nextCamX - this->oldCamX)*static_cast<GLfloat>(easingFunction(time0));//this->oldCamX + (this->nextCamX - this->oldCamX) * easingFunction(time0);
			this->currentCamY = this->oldCamY + (this->nextCamY- this->oldCamY)*static_cast<GLfloat>(easingFunction(time0));//this->oldCamY + (this->nextCamY - this->oldCamY) * easingFunction(time0);
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