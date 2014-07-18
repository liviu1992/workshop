#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(TextureManager* tm, std::vector<Enemy*>* enemies, SpriteManager* sm, PhysicsManager* pm){
		this->enemies=enemies;
		this->tm = tm;
		this->sm = sm;
		this->pm = pm;
		SettingsManager settingsManager;
		scout_seed = static_cast<GLint>(settingsManager.get("scout_seed"));
		basic_seed = static_cast<GLint>(settingsManager.get("basic_seed"));
		assault_seed = static_cast<GLint>(settingsManager.get("assault_seed"));
		scout_limit_up = settingsManager.get("scout_limit_up");
		scout_limit_down = settingsManager.get("scout_limit_down");
		scout_limit_left = settingsManager.get("scout_limit_left");
		scout_limit_right = settingsManager.get("scout_limit_right");
		scout_bounce = settingsManager.get("scout_bounce");

		basic_limit_up = settingsManager.get(" basic_limit_up");
		basic_limit_down = settingsManager.get(" basic_limit_down");
		basic_limit_left = settingsManager.get(" basic_limit_left");
		basic_limit_right = settingsManager.get(" basic_limit_right");
		basic_bounce = settingsManager.get("basic_bounce");

		assault_limit_up = settingsManager.get("assault_limit_up");
		assault_limit_down = settingsManager.get("assault_limit_down");
		assault_limit_left = settingsManager.get("assault_limit_left");
		assault_limit_right = settingsManager.get("assault_limit_right");
		assault_bounce = settingsManager.get("assault_bounce");


	}

	void EnemyFactory::Generate(GLint &numEnemies){
		

		std::srand((unsigned) time(0));
		//how many units of type A

		int seed1 = scout_seed+ std::rand()%3;
		
		GLfloat x, y;  //positions
		x=0;
		y=0;
		for (int i=0; i<seed1; i++){
			addRandomEnemyOfGivenType(enemyType::SCOUT_ENEMY);
			
		}

	
		//how many units of type B

		int seed2 = basic_seed + std::rand()%4;

		for (int i=0; i<seed2; i++){
			addRandomEnemyOfGivenType(enemyType::BASIC_ENEMY);

		}
		
		
		//how many units of type C

		int seed3 = assault_seed +std::rand()%3;
		

		for (int i=0; i<seed3; i++){
			addRandomEnemyOfGivenType(enemyType::ASSAULT_ENEMY);

		}

	/*	sm->Remove(enemies->at(0)->getSprite());
		pm->Remove(enemies->at(0)->getPhysics());
		delete enemies->at(0);
		enemies->erase(enemies->begin());   //altfel genereaza o unitate in plus care nu este afisata pe ecran
*/

		numEnemies=seed1+seed2+seed3;
	//	std::cout << numEnemies << " generated" << std::endl;
	}
	void EnemyFactory::addRandomEnemyOfGivenType(enemyType type){
		enemies->push_back(new Enemy(tm, type));
		sm->Add(enemies->at(enemies->size()-1)->getSprite());
		pm->Add(enemies->at(enemies->size()-1)->getPhysics());
			
		GLfloat x, y;
		x = 1.0f*((rand()% 3000-1500))/100;
		y = 1.0f*((rand()% 3000-1500))/100;
			
		enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
	}

	void EnemyFactory::addRandomEnemy(){
		enemyType type = static_cast<enemyType>(enemyType::SCOUT_ENEMY+ (rand() % 3));
		enemies->push_back(new Enemy(tm, type));
		sm->Add(enemies->at(enemies->size()-1)->getSprite());
		pm->Add(enemies->at(enemies->size()-1)->getPhysics());
			
		GLfloat x, y;
		x = 1.0f*(4000 -(rand()% 2000))/100;
		y = 1.0f*(4000 -(rand()% 2000))/100;
			
		enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);

	}