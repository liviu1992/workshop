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
GLint Combatant::getHealth(){
	return this->health;
}