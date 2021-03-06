#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Matrix.h"
#include "RAPIDXML\rapidxml_utils.hpp"
#include "RAPIDXML\rapidxml.hpp"
#include "Utils.h"
#include "Shapes.h"
#include "Sprite.h"
#include "SpriteTriangle.h"
#include "SpriteCircle.h"
#include "GLM\glm.hpp"
#include "SpriteManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <stack>
#include "EnemyFactory.h"
#include <map>
#include "SettingsManager.h"
#include "PhysicsManager.h"
#include "LayerManager.h"
#include "Camera.h"
//#include "MapGenerator.h"
#include "Powerup.h"
#include "SoundManager.h"

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>









/*
	MAI JOS SUNT PARAMETRII JOCULUI(VARIABILE
	CORESPUNZATOARE TIPURILOR DE SETARI)

*/
GLfloat speedPlayer;
GLfloat speedSquare;

GLfloat rotationSpeed;

GLfloat attack_damage;

GLfloat background_x;
GLfloat background_y;
GLfloat background_width;
GLfloat background_height;

GLint initial_score;
GLint defeat_score;
GLint rocket_penalty;
GLint scout_bounty;
GLint basic_bounty;
GLint assault_bounty;


GLfloat score_x;
GLfloat score_y;
GLfloat score_width;
GLfloat score_height;

GLfloat enemies_x;
GLfloat enemies_y;
GLfloat enemies_width;
GLfloat enemies_height;


GLfloat final_score_x;
GLfloat final_score_y;
GLfloat final_score_width;
GLfloat final_score_height;

GLfloat final_enemies_x;
GLfloat final_enemies_y;
GLfloat final_enemies_width;
GLfloat final_enemies_height;

GLfloat text_score_x;
GLfloat text_score_y;
GLfloat text_score_width;
GLfloat text_score_height;

GLfloat text_enemies_x;
GLfloat text_enemies_y;
GLfloat text_enemies_width;
GLfloat text_enemies_height;

GLfloat text_hp_x;
GLfloat text_hp_y;
GLfloat text_hp_width;
GLfloat text_hp_height;


GLfloat final_text_score_x;
GLfloat final_text_score_y;
GLfloat final_text_score_width;
GLfloat final_text_score_height;

GLfloat final_text_enemies_x;
GLfloat final_text_enemies_y;
GLfloat final_text_enemies_width;
GLfloat final_text_enemies_height;


GLfloat victory_screen_x;
GLfloat victory_screen_y;
GLfloat victory_screen_width;
GLfloat victory_screen_height;

GLfloat defeat_screen_x;
GLfloat defeat_screen_y;
GLfloat defeat_screen_width;
GLfloat defeat_screen_height;

GLfloat health_x;
GLfloat health_y;
GLfloat health_width;
GLfloat health_height;

GLint g_gl_width = 640;
GLint g_gl_height = 480;
GLint g_gl_fullscreen = 0;


/*
	INCARCA SETARILE JOCULUI DIN FISIERUL settings.xml
	SE UTILIZEAZA LA INTRAREA IN JOC SAU LA APASAREA 
	TASTEI L
*/
void loadSettings(){
	std::cout << "Loading settings from '../data/settings.xml'..." << std::endl;
	rapidxml::xml_document<> doc;
	std::ifstream file("../data/settings.xml");
	std::stringstream ss;
	ss << file.rdbuf();
	std::string content(ss.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node("Settings");

	int counter=0;
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("Item"); pNode; pNode =pNode->next_sibling()){
		//std::string name = pNode->first_attribute("name")->value();
		float value = (float) atof(pNode->first_attribute("value")->value());
		std::string name = pNode->first_attribute("name")->value();

		settings[name]=value;
	}
	std::cout << "Settings loaded" << std::endl;

}


void drawNumber(GLuint number, GLfloat x, GLfloat y, GLfloat width, GLfloat height, TextureManager *td){		
		char num[7];
		sprintf_s(num, "%5dk", number);
		GLfloat cifraWidth = width/5;
		for (char c = 1; c<7; c++){
			if (num[c]=='k'){
				break;
			} else if (num[c]>='0' && num[c]<='9') {
				//deseneaza cifra
				Sprite cifra(x+(c-1)*(cifraWidth+0.01f), y,cifraWidth, height, static_cast<texture_id>(texture_id::NUM0+num[c]-48), td);
				cifra.draw();
			}

		}		
	}

/*
	testam prin metoda AABB daca are loc o coliziune
*/
bool collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB ){
	GLfloat xA, yA, XA, YA, xB, yB, XB, YB;
	
	xA = cxA - wA/2;
	XA = cxA + wA/2;
	xB = cxB - wB/2;
	XB = cxB + wB/2;
	yA = cyA - wA/2;
	YA = cyA + wA/2;
	yB = cyB - hB/2;
	YB = cyB + hB/2;

	if (XA<xB || XB<xA || YA<yB || YB<yA){
		return false;
	}
	return true;

}
/*
void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam){
	//std::cout << "Crap! " << std::endl;
}
*/
void glfw_error_callback (int error, const char* description) {
  std::cout << "GLFW ERROR: code "<<error <<" msg: "<<description << std::endl;
}

void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
  g_gl_width = width;
  g_gl_height = height;
  
  /* putem modifica aici matricile de perspectiva */
}

int main () {
	
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );


	loadSettings();
	

	SettingsManager settingsManager;
	speedPlayer=settingsManager.get("player_speed");
	speedSquare=settingsManager.get("square_speed");
	rotationSpeed = settingsManager.get("rotation_speed");
	attack_damage = settingsManager.get("attack_damage");
	background_x=settingsManager.get("background_x");
	background_y = settingsManager.get("background_y");
	background_width = settingsManager.get("background_width");
	background_height = settingsManager.get("background_height");	
	score_x = settingsManager.get("score_x");
	score_y = settingsManager.get("score_y");
	score_width = settingsManager.get("score_width");
	score_height = settingsManager.get("score_height");
	enemies_x = settingsManager.get("enemies_x");
	enemies_y = settingsManager.get("enemies_y");
	enemies_width = settingsManager.get("enemies_width");
	enemies_height = settingsManager.get("enemies_height");
	final_score_x = settingsManager.get("final_score_x");
	final_score_y = settingsManager.get("final_score_y");
	final_score_width = settingsManager.get("final_score_width");
	final_score_height = settingsManager.get("final_score_height");
	final_enemies_x = settingsManager.get("final_enemies_x");
	final_enemies_y = settingsManager.get("final_enemies_y");
	final_enemies_width = settingsManager.get("final_enemies_width");
	final_enemies_height = settingsManager.get("final_enemies_height");
	text_score_x = settingsManager.get("text_score_x");
	text_score_y = settingsManager.get("text_score_y");
	text_score_width = settingsManager.get("text_score_width");
	text_score_height = settingsManager.get("text_score_height");
	text_enemies_x = settingsManager.get("text_enemies_x");
	text_enemies_y = settingsManager.get("text_enemies_y");
	text_enemies_width = settingsManager.get("text_enemies_width");
	text_enemies_height = settingsManager.get("text_enemies_height");
	final_text_score_x = settingsManager.get("final_text_score_x");
	final_text_score_y = settingsManager.get("final_text_score_y");
	final_text_score_width = settingsManager.get("final_text_score_width");
	final_text_score_height = settingsManager.get("final_text_score_height");
	final_text_enemies_x = settingsManager.get("final_text_enemies_x");
	final_text_enemies_y = settingsManager.get("final_text_enemies_y");
	final_text_enemies_width = settingsManager.get("final_text_enemies_width");
	final_text_enemies_height = settingsManager.get("final_text_enemies_height");
	victory_screen_x = settingsManager.get("victory_screen_x");
	victory_screen_y = settingsManager.get("victory_screen_y");
	victory_screen_width = settingsManager.get("victory_screen_width");
	victory_screen_height = settingsManager.get("victory_screen_height");
	defeat_screen_x = settingsManager.get("defeat_screen_x");
	defeat_screen_y = settingsManager.get("defeat_screen_y");
	defeat_screen_width = settingsManager.get("defeat_screen_width");
	defeat_screen_height = settingsManager.get("defeat_screen_height");
	health_x = settingsManager.get("health_x");
	health_y = settingsManager.get("health_y");
	health_width = settingsManager.get("health_width");
	health_height = settingsManager.get("health_height");


	text_hp_x = settingsManager.get("text_hp_x");
	text_hp_y = settingsManager.get("text_hp_y");
	text_hp_width = settingsManager.get("text_hp_width");
	text_hp_height = settingsManager.get("text_hp_height");



	
	initial_score = static_cast<GLint>(settingsManager.get("initial_score"));
    defeat_score = static_cast<GLint>(settingsManager.get("defeat_score"));
	rocket_penalty  = static_cast<GLint>(settingsManager.get("rocket_penalty"));

	scout_bounty  = static_cast<GLint>(settingsManager.get("scout_bounty"));
	basic_bounty  = static_cast<GLint>(settingsManager.get("basic_bounty"));
	assault_bounty  = static_cast<GLint>(settingsManager.get("assault_bounty"));




	
	g_gl_width = static_cast<int>(settingsManager.get("window_width"));
	g_gl_height =static_cast<int>(settingsManager.get("window_height"));
	g_gl_fullscreen = static_cast<int>(settingsManager.get("fullscreen"));
	

  // Initializare (se creeaza contextul)
  if (!glfwInit ()) {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 
  GLFWwindow* window=NULL;
  // ........Resolution si Fullscreen..........
  if (g_gl_fullscreen){
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	g_gl_width=vmode->width;
	g_gl_height=vmode->height;
	window = glfwCreateWindow (
	vmode->width, vmode->height, "Extended GL Init", mon, NULL
	);
  } else {
	  window = glfwCreateWindow (g_gl_width, g_gl_height, "Space Warfare", NULL, NULL);
  }

  // Se creeaza fereastra
 // GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop1", NULL, NULL);
  if (!window) {
    // nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
	printf ( "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }




	glfwSetErrorCallback (glfw_error_callback);
	glfwSetWindowSizeCallback (window, glfw_window_size_callback);   
	// Atasam contextul de fereastra
	glfwMakeContextCurrent (window);                                  
	// Pornit extension handler-ul
	glewInit ();
	// Vedem versiunile 
	Utils::showOpengGLInfo();
  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );


	//............Antialiasing...............
	glfwWindowHint (GLFW_SAMPLES, 4);


	GLboolean hintscreen=true;
	GLdouble hintscreen_timer;
	GLdouble hintscreen_limit=0.5;

	GLdouble musicswitch_timer;
	GLdouble musicswitch_limit=1;

	GLdouble cheat_timer;
	GLdouble cheat_limit=0.5;

	/*
		Mai jos sunt variabilele pe care le voi folosi sa calculez 
		durata unui frame
	*/
	GLint score=initial_score;
	GLint enemiesKilled=0;
	GLint enemiesTotal=1;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projectiles;
	std::vector<Powerup*> powerups;
	SoundManager soundManager;

	TextureManager textManager;
	Player player(&textManager);
	
	Physics* playerPhysics = player.getPhysics();
	playerPhysics->setPlayer(playerPhysics);
	Camera cam(&player);
	SpriteManager spriteManager(&cam);
	//SpriteManager worldSpriteManager;
	PhysicsManager physicsManager(&projectiles, &textManager, &spriteManager, &soundManager);
	playerPhysics->setPhysicsManager(&physicsManager);
	
	
	LayerManager layerManager(&cam, &textManager);

	//generez primul sector
	//MapGenerator mapGenerator(&layerManager, &textManager);

   // mapGenerator.Generate();

	physicsManager.Add(player.getPhysics());

	
	EnemyFactory enemyFactory(&textManager, &enemies, &spriteManager, &physicsManager, &player);
	enemyFactory.Generate(enemiesTotal);

	

	
	Sprite sky(background_x, background_y, background_width,background_height,texture_id::SPACE, &textManager);
	
	

	spriteManager.Add(player.getSprite());

	srand((unsigned) time(0));


	GLboolean gamePlaying=true;
	GLboolean victory=false;

	Sprite victory_screen(victory_screen_x, victory_screen_y, victory_screen_width, victory_screen_height, texture_id::VIC_SCREEN, &textManager);
	Sprite defeat_screen(defeat_screen_x, defeat_screen_y, defeat_screen_width, defeat_screen_height, texture_id::DEF_SCREEN, &textManager);

	Sprite text_score(text_score_x, text_score_y, text_score_width, text_score_height, texture_id::TEXT_SCORE, &textManager);
	Sprite text_enemies(text_enemies_x, text_enemies_y, text_enemies_width, text_enemies_height, texture_id::TEXT_KILLS, &textManager);
	Sprite text_hp(text_hp_x, text_hp_y, text_hp_width, text_hp_height, texture_id::TEXT_HP, &textManager);

	Sprite modifier_speed(1.1f, 0.2f, 0.2f,0.24f, texture_id::PWUP_1, &textManager);
	Sprite modifier_instagib(1.1f, 0.6f, 0.2f,0.24f, texture_id::PWUP_2, &textManager);

	Sprite help_screen(0.f, 0.f, 2.5f, 2.5f, texture_id::HELP, &textManager);
	
	
	/*float lastTime = (float) glfwGetTime();
	float newTime;
	float frameTime;	*/
	double t = 0.0;
	const double dt = 0.016;

	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	hintscreen_timer = glfwGetTime();
	musicswitch_timer = glfwGetTime();
	cheat_timer = glfwGetTime();

	soundManager.Play(Sounds::MUSIC);
	soundManager.PauseMusic();
	glClearColor(0,0,0,0);


	

	while (!glfwWindowShouldClose(window)) {
		Utils::_update_fps_counter (window);


	

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while ( accumulator >= dt )
		{

			//AICI PUN FIZICA
			if (gamePlaying){

				layerManager.PopulateCurrent();
				layerManager.Update();
				if (hintscreen==GL_TRUE){
					
					

					 if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ENTER)){
						 if (glfwGetTime()-hintscreen_timer >hintscreen_limit){
							hintscreen_timer = glfwGetTime();
							hintscreen = GL_FALSE;
							soundManager.ResumeMusic();
						 }
					 }


				
				} else {
				
					player.getPhysics()->Update();

		 
					soundManager.Update();

				  //populez sectoarele din jur
		  

				  
				  physicsManager.TestCollisions();		
				  physicsManager.AllAttack();


				  for (unsigned int i=0; i<enemies.size(); i++){
					  Physics* enemyPhysics = enemies.at(i)->getPhysics();
			

					  if (!enemies.at(i)->getSprite()->getDead()){
						  enemyPhysics->setSpeed(speedPlayer*static_cast<GLfloat>(frameTime));
						  enemyPhysics->Update();
					  } else {
				  													
						enemiesKilled++;
						enemyFactory.addRandomEnemy();


						//mai jos o sa pun codul necesar aparitiei unui powerup in locul 
						//inamicului distrus
					//	std::cout << "Preparing powerup" << std::endl;
						powerupType PowerupType;
						GLshort t;
						t = rand()% 10;  
						if (t<7){
							PowerupType = powerupType::PW1_1;
						} else if (t<9){
							PowerupType = powerupType::PW1_2;
						} else {
							PowerupType = powerupType::PW1_3;
						}
				


						powerups.push_back(new Powerup(enemyPhysics->GetX(), enemyPhysics->GetY(), &textManager, PowerupType));
						spriteManager.Add(powerups.at(powerups.size()-1)->getSprite());
						physicsManager.Add(powerups.at(powerups.size()-1)->getPhysics());				
					//	std::cout << "Powerup deployed" << std::endl;
						//std::cout << "Number of powerups " << powerups.size() << std::endl;

						//
															
						if (enemies.at(i)->getType()==enemyType::BASIC_ENEMY){
							score+=basic_bounty;
						} else if (enemies.at(i)->getType()==enemyType::SCOUT_ENEMY){
							score+=scout_bounty;
						} else if (enemies.at(i)->getType()==enemyType::ASSAULT_ENEMY){
							score+=assault_bounty;
						}
													 



						  spriteManager.Remove(enemies.at(i)->getSprite());
						  physicsManager.Remove(enemyPhysics);

						  delete enemies.at(i);
						  enemies.erase(enemies.begin()+i);
					  }

					  }
					  for (unsigned int i=0; i<projectiles.size(); i++){
						  Physics* projectilePhysics=projectiles.at(i)->getPhysics();
						  if (!projectiles.at(i)->getSprite()->getDead() && projectiles.at(i)->isAlive()){
							  projectilePhysics->setSpeed(speedPlayer*static_cast<GLfloat>(frameTime));
							  projectilePhysics->Update();
						  } else {
							  spriteManager.Remove(projectiles.at(i)->getSprite());
							  physicsManager.Remove(projectilePhysics);
							  delete projectiles.at(i);
							  projectiles.erase(projectiles.begin()+i);
		
						  }
		  
					  }
					  /*
						verific daca exista powerups-uri luate de player, daca da le elimin 
					  */
					  for (unsigned int i=0; i<powerups.size(); i++){
			  
						  if (!powerups.at(i)->getSprite()->getDead()){
							  /*   
								sterg powerup-ul dupa 10 secunde de viata pentru a preveni umplerea hartii cu prea 
								multe sprite-uri
							  */
								if (powerups.at(i)->getCreationTime() <= glfwGetTime()-10){
									spriteManager.Remove(powerups.at(i)->getSprite());
									physicsManager.Remove(powerups.at(i)->getPhysics());
									delete powerups.at(i);
									powerups.erase(powerups.begin()+i);
								}


						  } else {
							 spriteManager.Remove(powerups.at(i)->getSprite());
							 physicsManager.Remove(powerups.at(i)->getPhysics());
							 delete powerups.at(i);
							 powerups.erase(powerups.begin()+i);
				  
						  }
			
					  }

					  GLboolean no_enemies=true;
					  GLboolean no_health=true;
					  if (100 != enemiesKilled){
						 no_enemies=false;
					  } 
					  if (player.getCombatant()->getHealth()>0){
						  no_health=false;
					  }
		
					  if (no_enemies || no_health){

						  gamePlaying=false;
						  if (player.getCombatant()->getHealth()>0){
							   victory=true;
						  } else {
							  victory= false;
						  }
			 
					}


				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)){
					  playerPhysics->setSpeed(static_cast<GLfloat>(frameTime));
					  playerPhysics->setSpeedY(speedPlayer);
					  playerPhysics->setSpeedX(speedPlayer);
					  player.getSprite()->setLeft(false);
					  player.getSprite()->setRight(false);		
					  player.getSprite()->setAdvance(true);
			 
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)){
					  playerPhysics->setSpeed(static_cast<GLfloat>(frameTime));
					  playerPhysics->setSpeedY(-speedPlayer);
					  playerPhysics->setSpeedX(-speedPlayer);
					  player.getSprite()->setLeft(false);
					  player.getSprite()->setRight(false);		
					  player.getSprite()->setAdvance(true);
		
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)){
					 playerPhysics->Rotate(rotationSpeed);
					 player.getSprite()->setLeft(true);
					 player.getSprite()->setRight(false);		
					 player.getSprite()->setAdvance(false);
					// playerPhysics->rotatingLeft();
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)){
					 playerPhysics->Rotate(-rotationSpeed);
					 player.getSprite()->setLeft(false);
					 player.getSprite()->setRight(true);		
					 player.getSprite()->setAdvance(false);
					// playerPhysics->rotatingRight();
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_L)){
					  loadSettings();
				  }


				  // instagib cheat
				   if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_I)){
					   if (glfwGetTime()-cheat_timer>cheat_limit){
						   if (!player.getCombatant()->hasModifier(modifier::INSTAGIB)){
								player.getCombatant()->addModifier(modifier::INSTAGIB);
								std::cout << "IG" << std::endl;
						   } else {
							   player.getCombatant()->removeModifier(modifier::INSTAGIB);
							   std::cout << "NIG" << std::endl;
						   }
						   cheat_timer = glfwGetTime();
					   }
				  }
					// instagib cheat
				   if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_H)){
					   if (glfwGetTime()-cheat_timer>cheat_limit){
						   if (!player.getCombatant()->hasModifier(modifier::HIGH_SPEED)){
								player.getCombatant()->addModifier(modifier::HIGH_SPEED);
								std::cout << "HS" << std::endl;
						   } else {
							   player.getCombatant()->removeModifier(modifier::HIGH_SPEED);
							   std::cout << "NHS" << std::endl;
						   }
						   cheat_timer = glfwGetTime();
					   }
				  }


				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_SPACE)){
					  if (playerPhysics->canIFire()){
			
						 playerPhysics->issueFireCommand(true);
						// soundManager.Play(Sounds::ROCKET_LAUCHED);
						  //penalizez jucatorul pentru consum excesiv de munitie
						  if (score>defeat_score){
							  score-=rocket_penalty;
						  } else {
							  score = defeat_score;
							  gamePlaying=false;
							  victory=false;
						  }
					  }
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_N)){
					  if (glfwGetTime()-musicswitch_timer >musicswitch_limit){
						  soundManager.NextSong(false);
						  std::cout << "Next song " << std::endl;
						  musicswitch_timer = glfwGetTime();
					  }
				  }
				  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ENTER)){
					  if (glfwGetTime()-hintscreen_timer >hintscreen_limit){
						  hintscreen_timer = glfwGetTime();
						  hintscreen = GL_TRUE;
						  soundManager.PauseMusic();
					  } 
					  
				  }
		  
		  

				}

			}
			//
			//integrate( state, t, dt );
			accumulator -= dt;
			t += dt;
		}

		//AICI MISC CAMERA SI DESENEZ! 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);


		if (gamePlaying){
			cam.updateCamera(); 


			sky.move(cam.getX(), cam.getY());
			sky.getMatrix()->updateMatrix();
		
			sky.draw();
	
		
			layerManager.Draw();
			spriteManager.Draw();	 
			//draw score
			drawNumber(score, score_x, score_y, score_width, score_height, &textManager);
			text_enemies.draw();
			text_score.draw();
			text_hp.draw();
			//draw enemies
			drawNumber(enemiesKilled,enemies_x, enemies_y, enemies_width, enemies_height, &textManager);
			//player health
			drawNumber(player.getCombatant()->getHealth(), health_x,health_y, health_width,health_height, &textManager);

			if (player.getCombatant()->hasModifier(modifier::HIGH_SPEED)){
				modifier_speed.draw();
			}
			if (player.getCombatant()->hasModifier(modifier::INSTAGIB)){
				modifier_instagib.draw();
			}
			if (hintscreen==GL_TRUE){
				//deseneaza ecranul cu hints
				help_screen.draw();
			}

		
		} else {
			if (victory){
				victory_screen.draw();

				for (unsigned int i=0; i<enemies.size(); i++){
					delete enemies.at(i);
  
				}
				for (unsigned int i=0; i<projectiles.size(); i++){
					delete projectiles.at(i);
				}
				for (unsigned int i=0; i<powerups.size(); i++){
					delete powerups.at(i);
				}

				enemies.clear();
  
				projectiles.clear();
		  
				Sprite text_final_score(final_text_score_x, final_text_score_y, final_text_score_width, final_text_score_height, texture_id::TEXT_SCORE, &textManager);
				text_final_score.draw();
				//Sprite text_enemies(0.5f, 1.15f, 0.6f, 0.3f, texture_id::TEXT_ENEMIES, &textManager);
				drawNumber(score,final_score_x,final_score_y,final_score_width, final_score_height, &textManager);
	
		  
			} else {
				defeat_screen.draw();
				Sprite text_final_score(final_text_score_x, final_text_score_y, final_text_score_width, final_text_score_height, texture_id::TEXT_SCORE, &textManager);
				text_final_score.draw();
				//Sprite text_enemies(0.5f, 1.15f, 0.6f, 0.3f, texture_id::TEXT_ENEMIES, &textManager);
				drawNumber(score,final_score_x,final_score_y,final_score_width, final_score_height, &textManager);

				
				Sprite text_final_enemies(final_text_enemies_x, final_text_enemies_y, final_text_enemies_width, final_text_enemies_height, texture_id::TEXT_KILLS, &textManager);
				text_final_enemies.draw();
				drawNumber(enemiesKilled,final_enemies_x, final_enemies_y, final_enemies_width, final_enemies_height, &textManager);
			}

		}

	

		//  facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();


		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_M)) {
			if (!soundManager.MusicPause()){
				soundManager.PauseMusic();
				std::cout << "Music paused" << std::endl;
			} else {
				std::cout << "Music resumed" << std::endl;
				soundManager.ResumeMusic();
			}
		
		 

		}

		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		 

		}

}
	 
	
  
  glfwTerminate();

  for (unsigned int i=0; i<enemies.size(); i++){
	  delete enemies.at(i);
  
  }
  for (unsigned int i=0; i<projectiles.size(); i++){
	  delete projectiles.at(i);
  }

  for (unsigned int i=0; i<powerups.size(); i++){
	  delete powerups.at(i);
  }

  enemies.clear();
  
  projectiles.clear();
 // _CrtDumpMemoryLeaks();
  return 0;
}