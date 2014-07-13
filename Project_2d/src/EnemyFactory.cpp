#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(TextureManager* tm, std::vector<Enemy*>* enemies, SpriteManager* sm, PhysicsManager* pm){
		this->enemies=enemies;
		this->tm = tm;
		this->sm = sm;
		this->pm = pm;
	}

	void EnemyFactory::Generate(GLint &numEnemies){
		SettingsManager settingsManager;
		GLint scout_seed = static_cast<GLint>(settingsManager.get("scout_seed"));
		GLint basic_seed = static_cast<GLint>(settingsManager.get("basic_seed"));
		GLint assault_seed = static_cast<GLint>(settingsManager.get("assault_seed"));
		GLfloat scout_limit_up = settingsManager.get("scout_limit_up");
		GLfloat scout_limit_down = settingsManager.get("scout_limit_down");
		GLfloat scout_limit_left = settingsManager.get("scout_limit_left");
		GLfloat scout_limit_right = settingsManager.get("scout_limit_right");
		GLfloat scout_bounce = settingsManager.get("scout_bounce");

		GLfloat basic_limit_up = settingsManager.get(" basic_limit_up");
		GLfloat  basic_limit_down = settingsManager.get(" basic_limit_down");
		GLfloat  basic_limit_left = settingsManager.get(" basic_limit_left");
		GLfloat  basic_limit_right = settingsManager.get(" basic_limit_right");
		GLfloat basic_bounce = settingsManager.get("basic_bounce");

		GLfloat assault_limit_up = settingsManager.get("assault_limit_up");
		GLfloat assault_limit_down = settingsManager.get("assault_limit_down");
		GLfloat assault_limit_left = settingsManager.get("assault_limit_left");
		GLfloat assault_limit_right = settingsManager.get("assault_limit_right");
		GLfloat assault_bounce = settingsManager.get("assault_bounce");

		std::srand((unsigned) time(0));
		//how many units of type A

		int seed1 = scout_seed+ std::rand()%3;
		
		GLfloat x, y;  //positions
		for (int i=0; i<seed1; i++){
			enemies->push_back(new Enemy(tm, enemyType::SCOUT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			pm->Add(enemies->at(enemies->size()-1)->getPhysics());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (x<scout_limit_left){
				x+=scout_bounce;
			} else if (x>scout_limit_right){
				x-=scout_bounce;
			}
			if (y<scout_limit_down){
				y+=scout_bounce;
			} else if (y>scout_limit_up){
				y-=scout_bounce;
			}
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Scout generated  at " <<x << "  " << y <<  std::endl;
		}

	
		//how many units of type B

		int seed2 = basic_seed + std::rand()%4;

		for (int i=0; i<seed2; i++){
			enemies->push_back(new Enemy(tm, enemyType::BASIC_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			pm->Add(enemies->at(enemies->size()-1)->getPhysics());
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<basic_limit_down){
				y+=basic_bounce;
			} else if (y>basic_limit_up){
				y-=basic_bounce;
			}
			
			
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Basic generated " << std::endl;

		}
		
		
		//how many units of type C

		int seed3 = assault_seed +std::rand()%3;
		

		for (int i=0; i<seed3; i++){
			enemies->push_back(new Enemy(tm, enemyType::ASSAULT_ENEMY));
			sm->Add(enemies->at(enemies->size()-1)->getSprite());
			pm->Add(enemies->at(enemies->size()-1)->getPhysics());
			
			x = 1.0f*(100 -(rand()% 200))/100;
			y = 1.0f*(100 -(rand()% 200))/100;
			if (y<assault_limit_down){
				y+=assault_bounce;
			} else if (y>assault_limit_up){
				y-=assault_bounce;
			}
			if (x<assault_limit_left){
				x+=assault_bounce;
			} else if (x>assault_limit_right){
				x-=assault_bounce;
			}
			enemies->at(enemies->size()-1)->getPhysics()->setPosition(x, y);
			std::cout << "Assault generated " << std::endl;

		}

	/*	sm->Remove(enemies->at(0)->getSprite());
		pm->Remove(enemies->at(0)->getPhysics());
		delete enemies->at(0);
		enemies->erase(enemies->begin());   //altfel genereaza o unitate in plus care nu este afisata pe ecran
*/

		numEnemies=seed1+seed2+seed3;
		std::cout << numEnemies << " generated" << std::endl;
	}
