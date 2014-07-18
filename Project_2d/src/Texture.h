/*
	Are rolul de a incarca o textura
	si de a oferi mai departe id-ul acesteia.
	Mai nou incarca o singura textura(sprites.png).
*/

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <iostream>
#include "stb_image.h"
#include <GL\glew.h>

/*
	in texture_id am texturile folosite

	!!! ROCKET trebuie sa fie intotdeauna ultima

*/
enum texture_id{
	PLAYER,
	SCOUT,
	BASIC,
	ASSAULT,
	EXP1,
	EXP2,
	EXP3,
	EXP4,
	EXP5,
	EXP6,
	EXP7,
	EXP8,
	EXP9,
	EXP10,
	EXP11,
	EXP12,
	EXP13,
	EXP14,
	EXP15,
	EXP16,
	SPACE,
	VIC_SCREEN,
	DEF_SCREEN,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	TEXT_SCORE,
	TEXT_ENEMIES,
	PLANET_GREEN,
	PLANET_JUPITER,
	PLANET_VENUS,
	PLANET_LAVA,
	PLANET_STAR,
	PLANET_K,
	PLANET_MARS,
	PLANET_PLUTO,
	PLANET_NEPTUNE,
	PLANET_ONE,
	PLANET_IO,
	PLANET_CERES,
	PLANET_WATER,
	METEOR_1,
	METEOR_2,
	METEOR_3,
	METEOR_4,
	METEOR_5,
	METEOR_6,
	POWERUP_1,
	POWERUP_2,
	POWERUP_3,
	ADV_1,
	ADV_2,
	ADV_3,
	ADV_4,
	ADV_5,
	ADV_6,
	ADV_7,
	ADV_8,
	ADV_9,
	ADV_10,
	ADV_11,
	ADV_12,
	ADV_13,
	LEFT_1,
	LEFT_2,
	LEFT_3,
	LEFT_4,
	LEFT_5,
	LEFT_6,
	LEFT_7,
	LEFT_8,
	LEFT_9,
	LEFT_10,
	LEFT_11,
	LEFT_12,
	LEFT_13,
	RIGHT_1,
	RIGHT_2,
	RIGHT_3,
	RIGHT_4,
	RIGHT_5,
	RIGHT_6,
	RIGHT_7,
	RIGHT_8,
	RIGHT_9,
	RIGHT_10,
	RIGHT_11,
	RIGHT_12,
	RIGHT_13,
	ROCKET
};
class Texture{

public:
	Texture(texture_id id);
	Texture();
	GLuint getTextureID();   //imi da id-ul texturii incarcate
	bool loadTexture(const std::string &filename);  // incarca o textura anume
	
private:
	GLuint texture;
};

#endif