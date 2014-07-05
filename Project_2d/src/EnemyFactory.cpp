#include "EnemyFactory.h"


	EnemyFactory::EnemyFactory(TextureManager* tm, std::vector<Enemy>* enemies, SpriteManager* sm){
		this->enemies=enemies;
		this->tm = tm;
		this->sm = sm;
	}

	void EnemyFactory::Generate(){
		std::srand((unsigned) time(0));
		//how many units of type A

		int seed1 = 1+ std::rand()%3;
		std::cout << seed1 << std::endl;

		GLfloat x, y;  //positions
		for (int i=0; i<seed1; i++){
			enemies->push_back(Enemy(tm, enemyType::SCOUT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1).getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			enemies->at(enemies->size()-1).setPosition(x, y);
			std::cout << "Scout generated " << std::endl;
		}

		//how many units of type B

		int seed2 = 1 + std::rand()%4;
		std::cout << seed2 << std::endl;

		for (int i=0; i<seed2; i++){
			enemies->push_back(Enemy(tm, enemyType::BASIC_ENEMY));
			sm->Add(enemies->at(enemies->size()-1).getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			
			enemies->at(enemies->size()-1).setPosition(x, y);
			std::cout << "Basic generated " << std::endl;

		}
		//how many units of type C

		int seed3 = 1+ std::rand()%3;
		std::cout << seed3 << std::endl;

		for (int i=0; i<seed3; i++){
			enemies->push_back(Enemy(tm, enemyType::ASSAULT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1).getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			
			enemies->at(enemies->size()-1).setPosition(x, y);
			std::cout << "Assault generated " << std::endl;

		}
	}
	