#ifndef PHYSICS_H
#define PHYSICS_H
#include <stdio.h>
#include <GL\glew.h>
#include "Sprite.h"
#include <memory>
#include "SettingsManager.h"
#include "Combatant.h"
//#include "PhysicsManager.h"

class PhysicsManager;

struct Manifold;

enum physicsType{
	P_PLAYER, 
	P_SCOUT,
	P_BASIC,
	P_ASSAULT,
	P_POWERUP_1,
	P_POWERUP_2,
	P_POWERUP_3,
	P_ROCKET
};

enum movement{
	LEFTRIGHT, CIRC, SIN
};

enum stateAI{
	ROTATE_TO_PLAYER,
	ADVANCE_TO_PLAYER,
	FIRE_AT_PLAYER

};

class Physics{
public:
	//Physics();
	Physics(GLfloat x, GLfloat y, GLfloat width, GLfloat height, Sprite* sprite, physicsType type, GLboolean &isalive, GLfloat speedXY, Combatant* combatant, GLfloat mass) : alive(dummy){
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
		this->sprite = sprite;
		this->speedX=speedXY;
		this->speedY=speedXY;
		this->mspeedX=0;
		this->mspeedY=0;
		this->type=type;
		this->alive=alive;
		this->rotate=0;
		this->sprite = sprite;

		this->mass = mass;
		this->combatant=combatant;
		this->owner = false;

		SettingsManager settingsManager;
		this->sine_amplitude = settingsManager.get("sine_amplitude");
		this->circ_width = settingsManager.get("circ_width");
		this->circ_height = settingsManager.get("circ_height");
		this->limit_down = settingsManager.get("limit_down");
		this->limit_up = settingsManager.get("limit_up");
		this->limit_right = settingsManager.get("limit_right");
		this->limit_left =  settingsManager.get("limit_left");
		this->advanceStep = settingsManager.get("advance_step");
		this->fireDistance = settingsManager.get("fire_distance");
		this->distance_to_engage = settingsManager.get("distance_to_engage");
		this->rocketMaximumRange=settingsManager.get("rocket_maximum_range");

		GLfloat fire_limit=1;
		switch (this->type){
		case physicsType::P_PLAYER: 
				fire_limit = settingsManager.get("fire_limit");
			
				break;
		case physicsType::P_SCOUT:
				fire_limit = settingsManager.get("scout_fire_limit");
				fov = settingsManager.get("scout_fov");
				break;
		case physicsType::P_BASIC:
				fire_limit = settingsManager.get("basic_fire_limit");
				fov = settingsManager.get("basic_fov");
				break;
		case physicsType::P_ASSAULT:
				fire_limit = settingsManager.get("assault_fire_limit");
				fov = settingsManager.get("assault_fov");
				break;
				//fire_limit = settingsManager.get("enemy_fire_limit");
		}

		this->damage = static_cast<int>(settingsManager.get("attack_damage"));

		switch(type){
		case physicsType::P_ROCKET:
			this->left=true;
			this->right=false;
			this->fired=false;		
			break;

		case physicsType::P_SCOUT:
			this->left=true;
			this->right=false;
			this->mov=movement::SIN;
	
			break;

		case physicsType::P_BASIC:
			this->left=true;
			this->right=false;
			this->mov=movement::LEFTRIGHT;
	
			break;

		case physicsType::P_ASSAULT:
			this->left=true;
			this->right=false;
			this->mov=movement::SIN;	
	
			break;

		}

		this->fireTimer=0.f;
		this->fireLimit=fire_limit;
		this->m_fireLimit = fire_limit;
	
		this->fireCommand=false;
		this->speed=0;
		this->isExploding=false;

		this->setEnemyOrigin(x,y);
		
		AI_state = stateAI::ROTATE_TO_PLAYER; //starea initiala a AI-ului
		/*
			acum distribui pozitia pe o suprafata de 1.f x 1.f  
		*/
		//srand((unsigned) time(0));
		this->rotLeft = true;
		this->rotRight = false;
	
	};
	GLboolean fireCommandIssued();
	void issueFireCommand(GLboolean value);
	void setOwnerIfRocket(GLboolean owner);  //true for player, false for enemy
	GLboolean getOwner();
	Combatant* getCombatant();
	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetHeight();
	GLfloat GetWidth();
	void setPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat width, GLfloat height);
	
	GLfloat getSpeed();
	void setSpeed(GLfloat speed);
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	void Rotate(GLfloat rotate);
	GLfloat getRotate();
	void setRotate(GLfloat rotate);
	void fire();
	void Update();
	void SetX(GLfloat x);
	void SetY(GLfloat y);
	void onCollision(Manifold* manifold, GLboolean isA);
	physicsType getType();
	Sprite* getSprite();
	GLfloat getMass();
	GLfloat getFov();
	GLboolean canIFire();
	void setParentSpeed(GLfloat parentSpeedX, GLfloat parentSpeedY);
	GLfloat getSpeedX();
	GLfloat getSpeedY();
	void setEnemyOrigin(GLfloat originX, GLfloat originY);
	void advanceTowards(GLfloat x, GLfloat y, GLboolean fast);


	Physics* getParentsPhysics();
	void setParentsPhysics(Physics* physics);
	bool collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB );

	GLfloat getCurrentCamX();
	GLfloat getCurrentCamY();

	void AI_enemy();

	void setPlayer(Physics* player);
	void setPhysicsManager(PhysicsManager* physicsManager);
	GLboolean checkAngle();
	GLdouble getAngle();
	GLboolean checkDistance();

	void rotatingLeft();
	void rotatingRight();

private:
	stateAI AI_state;

	static Physics* player;
	static PhysicsManager* physicsManager;

	GLboolean canFire;
	GLdouble fireTimer;
	GLdouble fireLimit;
	GLdouble fov;
	GLboolean fireCommand;

	GLboolean owner;
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	GLfloat rotate;
	GLfloat speed;
	GLfloat speedX;
	GLfloat m_speed;
	GLdouble m_fireLimit;
	GLfloat speedY;
	Sprite *sprite;
	Combatant *combatant;
	physicsType type;
	GLboolean fired;
	GLboolean &alive;
	GLboolean dummy;
	GLboolean left;
	GLboolean right;
	GLfloat mspeedX;
	GLfloat mspeedY;
	movement mov;
	GLfloat sine_amplitude;
	GLfloat circ_width;
	GLfloat circ_height;
	GLfloat limit_left;
	GLfloat limit_right;
	GLfloat limit_up;
	GLfloat limit_down;
	GLint damage;
	GLfloat mass;
	
	GLfloat rocketMaximumRange;
	GLfloat rocketOriginX;
	GLfloat rocketOriginY;
	GLfloat enemyOriginX;
	GLfloat enemyOriginY;

	GLboolean isExploding;


	GLfloat parentSpeedX;
	GLfloat parentSpeedY;


	GLfloat advanceStep;
	GLfloat fireDistance;

	Physics* parentsPhysics;

	GLfloat desiredOffsetX;
	GLfloat desiredOffsetY;

	GLfloat currentCamX;
	GLfloat currentCamY;
	GLfloat nextCamX;
	GLfloat nextCamY;
	GLfloat camBoundaryW;
	GLfloat camBoundaryH;
	GLfloat speedCam;
	GLboolean camFollowMode;

	GLboolean cam_left;
	GLboolean cam_right;
	GLboolean cam_down;
	GLboolean cam_up;

	GLfloat distance_to_engage;
	GLdouble angle;

	GLboolean rotLeft;
	GLboolean rotRight;


};

struct Manifold{
	Physics* objectA;
	Physics* objectB;
	GLfloat penetration;   
	glm::vec2 normal;
	

};
#endif