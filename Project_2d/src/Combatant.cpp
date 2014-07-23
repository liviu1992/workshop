#include "Combatant.h"


void Combatant::damage(GLint damage){

	if (damageTimer == 0){
		damageTimer = glfwGetTime();
	
		health-=damage;
	} else if (glfwGetTime()-damageTimer>1.5){
	
		damageTimer = 0;
	}
	if (health<0){
		std::cout << "Killed!" << std::endl;
		sprite->Explode();
	}

}
void Combatant::increaseHealth(GLint amount){
	
	this->health+=amount;
	std::cout << "Health increased" << std::endl;
}
GLint Combatant::getHealth(){
	return this->health;
}

void Combatant::addModifier(modifier mod){
	if (mod == modifier::HIGH_SPEED){
		modifier_speed = true;
		this->timer_speed=glfwGetTime();
	}
	if (mod == modifier::INSTAGIB){
		modifier_instagib = true;
		this->timer_instagib = glfwGetTime();
	}
}

void Combatant::removeModifier(modifier mod){
	if (mod == modifier::HIGH_SPEED){
		modifier_speed = false;
	}
	if (mod == modifier::INSTAGIB){
		modifier_instagib = false;
	}
}

bool Combatant::hasModifier(modifier mod){
	if (mod == modifier::HIGH_SPEED){
		return modifier_speed;


	} else if (mod == modifier::INSTAGIB){
		return modifier_instagib;

	}
	std::cout << "Something went wrong with the modifier" << std::endl;
	return false;
}
/*
	aceasta functie asigura faptul ca durata de viata 
	a modifierelor este limitata 
*/
void Combatant::checkModifierLifetime(){
	if (this->timer_speed <= glfwGetTime()-10){
		this->modifier_speed = false;
	}
	if (this->timer_instagib <= glfwGetTime()-10){
		this->modifier_instagib = false;
	}


}