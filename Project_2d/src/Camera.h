#ifndef CAMERA_H
#define CAMERA_H
#include "Player.h"


class Camera{
public:
	Camera(Player* player);
	void updateCamera();
	GLfloat getX();
	GLfloat getY();
private:
	Player* player;
	GLfloat x;   //player x
	GLfloat y;   //player y
	GLfloat currentCamX;
	GLfloat currentCamY;
	GLfloat camBoundaryW;
	GLfloat camBoundaryH;
	GLboolean camFollowMode;
	GLfloat nextCamX;
	GLfloat nextCamY;
	GLfloat speedCam;
	GLboolean cam_left;
	GLboolean cam_right;
	GLboolean cam_up;
	GLboolean cam_down;



};

#endif