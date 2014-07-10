#include "Combatant.h"


void Combatant::damage(GLint damage){

	if (damageTimer == 0){
		damageTimer = glfwGetTime();
		std::cout << health << std::endl;
		health-=damage;
	} else if (glfwGetTime()-damageTimer>1.5){
		std::cout << "Resetting timer" << std::endl;
		damageTimer = 0;
	}
	if (health<0){
		std::cout << "Exterminated!" << std::endl;
		sprite->Explode();
	}

}