#include "EnemyFactory.h"


	EnemyFactory::EnemyFactory(TextureManager* tm, std::vector<Enemy*>* enemies, SpriteManager* sm){
		this->enemies=enemies;
		this->tm = tm;
		this->sm = sm;
	}

	void EnemyFactory::Generate(GLint &numEnemies){
		SettingsManager settingsManager;
		GLint scout_seed = static_cast<GLint>(settingsManager.get("scout_seed"));
		GLint basic_seed = static_cast<GLint>(settingsManager.get("basic_seed"));
		GLint assault_seed = static_cast<GLint>(settingsManager.get("assault_seed"));

		std::srand((unsigned) time(0));
		//how many units of type A

		int seed1 = scout_seed+ std::rand()%3;

		GLfloat x, y;  //positions
		for (int i=0; i<seed1; i++){
			enemies->push_back(new Enemy(tm, enemyType::SCOUT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Scout generated " << std::endl;
		}

		//how many units of type B

		int seed2 = basic_seed + std::rand()%4;

		for (int i=0; i<seed2; i++){
			enemies->push_back(new Enemy(tm, enemyType::BASIC_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Basic generated " << std::endl;

		}
		//how many units of type C

		int seed3 = assault_seed +std::rand()%3;
		

		for (int i=0; i<seed3; i++){
			enemies->push_back(new Enemy(tm, enemyType::ASSAULT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<0.f){
				y+=0.5f;
			}
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Assault generated " << std::endl;

		}

		numEnemies=seed1+seed2+seed3;
		std::cout << numEnemies << " generated" << std::endl;
	}
