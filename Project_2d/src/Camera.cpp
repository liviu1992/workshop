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
	
}

void Camera::updateCamera(){
	//std::cout << "Cam x " << currentCamX << "Cam y " << currentCamY << std::endl;
	this->x=player->getPhysics()->GetX();
	this->y=player->getPhysics()->GetY();
	//std::cout << "Player x " << x << "Player y " << y << std::endl;
	if ((this->x >= this->currentCamX-10.f*this->speedCam && 
			this->x <= this->currentCamX+10.f*this->speedCam &&
			this->y >= this->currentCamY-10.f*this->speedCam &&
			this->y <= this->currentCamY+10.f*this->speedCam
			)){
				
		} else {
			//advance towards this->x, this->y
			
		
		//	this->speedCam = 0.04f;
			
				GLfloat tempCX=(this->x - this->currentCamX)/20;
				GLfloat tempCY =(this->y - this->currentCamY)/20;


			if (glm::distance(glm::vec2(this->x, this->y), glm::vec2(this->currentCamX, this->currentCamY))>tempCX+tempCY ) {


				if (glm::abs(tempCX)>0.01f){
					
					this->currentCamX+=tempCX;
				//	 std::cout <<"x: " <<  glfwGetTime() << std::endl;
					
				//	std::cout << "X" << std::endl;
				} else {
					
				}

				if (glm::abs(tempCY)>0.01f){
					this->currentCamY+=tempCY;
			//		 std::cout <<"y: " << glfwGetTime() << std::endl;
					 
				//	std::cout << "Y" << std::endl;
				} else {
					//this->speedY=0;
				}
		/*	if (this->currentCamY<this->y+2*this->speedCam){
				this->currentCamY+=this->speedCam;
			} else if (this->currentCamY>this->y-2*this->speedCam){
				this->currentCamY-=this->speedCam;
			}*/
			
			} 
		}
		this->player->getSprite()->getMatrix()->moveCamera(this->currentCamX, this->currentCamY);
		
}

GLfloat Camera::getX(){
	return this->currentCamX;
}
GLfloat Camera::getY(){
	return this->currentCamY;
}