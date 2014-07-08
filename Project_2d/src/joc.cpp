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
	AICI SE AFLA TIPURILE DE SETARI PE CARE LE PUTEM 
	MODIFICA DIN FISIERUL settings.xml
*/

enum setting{
	SPEED_PLAYER,
	SPEED_SQUARE,
	WINDOW_WIDTH,
	WINDOW_HEIGHT,
	FULL_SCREEN
};

/*
	MAI JOS SUNT PARAMETRII JOCULUI(VARIABILE
	CORESPUNZATOARE TIPURILOR DE SETARI)

*/
float speedPlayer;
float speedSquare;

int g_gl_width = 640;
int g_gl_height = 480;
int g_gl_fullscreen = 0;

/*
	INCARCA SETARILE JOCULUI DIN FISIERUL settings.xml
	SE UTILIZEAZA LA INTRAREA IN JOC SAU LA APASAREA 
	TASTEI L
*/
void loadSettings(){
	
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
		switch(counter){
		case SPEED_PLAYER:
			speedPlayer = value;
			//std::cout << "speed circle " << speedCircle << std::endl;
			break;
		case SPEED_SQUARE:
			speedSquare = value;
			//std::cout << "speed square " << speedSquare << std::endl;
			break;
		case WINDOW_WIDTH:
			g_gl_width = (int)value;
			break;
		case WINDOW_HEIGHT:
			g_gl_height = (int)value;
			break;
		case FULL_SCREEN:
			g_gl_fullscreen = (int)value;
			
			break;

		default:
			std::cout << "Eroare citire setari" << std::endl;
			
		}
		counter++;

	}

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

				Sprite cifra(x+(c-1)*cifraWidth, y,cifraWidth, height, static_cast<texture_id>(texture_id::NUM0+num[c]-48), td);
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
	  window = glfwCreateWindow (g_gl_width, g_gl_height, "Workshop1", NULL, NULL);
  }

  // Se creeaza fereastra
 // GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop1", NULL, NULL);
  if (!window) {
    // nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
	printf ( "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  /*



  */

	
  //TODO fix this unhandled exception \/
 /* glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(openglDebugCallback, NULL);
  glEnable(GL_DEBUG_OUTPUT);*/
  
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



	/*
		Mai jos sunt variabilele pe care le voi folosi sa calculez 
		durata unui frame
	*/
	GLuint score=50;
	GLuint enemiesLeft=0;

	TextureManager textManager;
	SpriteManager spriteManager;
	
	std::vector<Enemy> enemies;
	EnemyFactory en(&textManager, &enemies, &spriteManager);
	en.Generate(enemiesLeft);
	std::cout << "Enemies left: " << enemiesLeft << std::endl;
	Sprite sky(0.f,0.f, 3.f,3.f,texture_id::SPACE, &textManager);
	
	Player player(&textManager);

	std::vector<Projectile> projectiles;


	
	

	spriteManager.Add(player.getSprite());


	GLboolean gamePlaying=true;
	GLboolean victory=false;

	Sprite victory_screen(0.f, 0.f, 3.f, 3.f, texture_id::VIC_SCREEN, &textManager);
	Sprite defeat_screen(0.f, 0.f, 3.f, 3.f, texture_id::DEF_SCREEN, &textManager);

	Sprite text_score(-1.f, 1.15f, 0.5f, 0.1f, texture_id::TEXT_SCORE, &textManager);
	Sprite text_enemies(0.5f, 1.15f, 0.5f, 0.15f, texture_id::TEXT_ENEMIES, &textManager);


	float lastTime = (float) glfwGetTime();
	float newTime;
	float frameTime;	
	glClearColor(0,0,0,0);
	while (!glfwWindowShouldClose(window)) {
		Utils::_update_fps_counter (window);

		/*
			Fac viteza de miscare sa fie independenta de framerate.
			Inmultesc viteza cu timpul dintre frameuri.

		*/
		newTime = (float) glfwGetTime();

		frameTime = newTime-lastTime;
		lastTime=newTime;

		/*
			######################################################
		*/

	  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glViewport (0, 0, g_gl_width, g_gl_height);

	  if (gamePlaying){
		  sky.draw();
		  spriteManager.Draw();

		  text_score.draw();
		  //draw score
		  drawNumber(score, -0.70f,1.15f,0.6f, 0.15f, &textManager);
		  
		

		  text_enemies.draw();

		   //draw enemies
		  drawNumber(enemiesLeft,0.8f,1.15f,0.6f, 0.15f, &textManager);
	  
		  for (unsigned int i=0; i<enemies.size(); i++){
			  if (!enemies.at(i).getSprite().get()->getDead()){
				  enemies.at(i).getPhysics().get()->setSpeed(speedPlayer*frameTime);
				  enemies.at(i).getPhysics().get()->Update();
			  } else {
				  													
				enemiesLeft=enemies.size()-1;
															
				if (enemies.at(i).getType()==enemyType::SCOUT_ENEMY){
					score+=20;
				} else if (enemies.at(i).getType()==enemyType::SCOUT_ENEMY){
					score+=10;
				} else if (enemies.at(i).getType()==enemyType::ASSAULT_ENEMY){
					score+=50;
				}
													 





				  spriteManager.Remove(enemies.at(i).getSprite());
				  enemies.erase(enemies.begin()+i);
			  }

		  }
		  for (unsigned int i=0; i<projectiles.size(); i++){
			  if (!projectiles.at(i).getSprite().get()->getDead() && projectiles.at(i).isAlive()){
				  projectiles.at(i).getPhysics().get()->setSpeed(speedPlayer*frameTime);
				  projectiles.at(i).getPhysics().get()->Update();
			  } else {

				  spriteManager.Remove(projectiles.at(i).getSprite());
				  projectiles.erase(projectiles.begin()+i);
		
			  }
		  
		  }

		  player.getPhysics().get()->Update();


		  //aici am facut sistemul de detectare a coliziunilor

		  for (unsigned int i =0; i<projectiles.size(); i++){
			  for (unsigned int j=0; j<enemies.size(); j++){
				

				  
			


					/* if (glm::distance(glm::vec2(projectiles.at(i).getPhysics().get()->GetX(), 
											 projectiles.at(i).getPhysics().get()->GetY()-0.6),
											 glm::vec2(enemies.at(j).getPhysics().get()->GetX(), 
											 enemies.at(j).getPhysics().get()->GetY())) < enemies.at(j).getPhysics().get()->GetHeight()/2+projectiles.at(i).getPhysics().get()->GetHeight()/2){*/
												  //projectiles.at(i).setAlive(false);
												  //pt explozii ale proiectilelor
				  GLfloat xP = projectiles.at(i).getPhysics().get()->GetX();
				  GLfloat yP = projectiles.at(i).getPhysics().get()->GetY();	
				  GLfloat wP = projectiles.at(i).getPhysics().get()->GetWidth();
				  GLfloat hP = projectiles.at(i).getPhysics().get()->GetHeight();	

				  GLfloat xE = enemies.at(j).getPhysics().get()->GetX();
				  GLfloat yE = enemies.at(j).getPhysics().get()->GetY();	
				  GLfloat wE = enemies.at(j).getPhysics().get()->GetWidth();
				  GLfloat hE = enemies.at(j).getPhysics().get()->GetHeight();	

				  if (collisionDetectorAABB(xP, yP, wP, hP, xE, yE, wE, hE)){			
													 projectiles.at(i).getSprite().get()->Explode();
													 enemies.at(j).damage(5);
													 

												

											//		enemies.at(j).getSprite().get()->Explode();		
													
														
											
					 }

				  }

			  }
		  
		  /*
			aici verific daca mai e vreun inamic viu, daca nu castig
		  */
		  GLboolean win=true;

		  for (unsigned int i =0; i<enemies.size(); i++){
			  if (enemies.at(i).getAlive()){
				  win = false;
			  }
		  }
		  if (win){

			  gamePlaying=false;
			  victory=true;
		}


		   if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)){
		  player.getPhysics().get()->setSpeed(speedPlayer*frameTime);
		  player.getPhysics().get()->setSpeedY(1);
		 
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)){
		  player.getPhysics().get()->setSpeed(speedPlayer*frameTime);
		  player.getPhysics().get()->setSpeedY(-1);
		
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)){
		 player.getPhysics().get()->setSpeed(speedPlayer*frameTime);
		 player.getPhysics().get()->setSpeedX(-1);

	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)){
		player.getPhysics().get()->setSpeed(speedPlayer*frameTime);
		player.getPhysics().get()->setSpeedX(1);

	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_L)){
		  loadSettings();
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_SPACE)){
		  if (player.fire()){
			  projectiles.push_back(Projectile(&textManager));		 
			  projectiles.at(projectiles.size()-1).Fire(player.getPhysics().get()->GetX(), player.getPhysics().get()->GetY(), player.getPhysics().get()->getRotate());
			  spriteManager.Add(projectiles.at(projectiles.size()-1).getSprite());
			  //penalizez jucatorul pentru consum excesiv de munitie
			  if (score>0){
				score-=1;
			  } else {
				  score = 0;
				  gamePlaying=false;
				  victory=false;
			  }
		  }
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q)){
		  player.getPhysics().get()->Rotate(0.1f);
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)){
		  player.getPhysics().get()->Rotate(-0.1f);
	  }

		
	} else {
			if (victory){
				victory_screen.draw();
				enemies.clear();
				enemies.shrink_to_fit();
  
				 projectiles.clear();
				 projectiles.shrink_to_fit();
		  
				Sprite text_final_score(-0.4f, -0.5f, 0.8f, 0.3f, texture_id::TEXT_SCORE, &textManager);
				text_final_score.draw();
				//Sprite text_enemies(0.5f, 1.15f, 0.6f, 0.3f, texture_id::TEXT_ENEMIES, &textManager);
				drawNumber(score, 0.f,-0.5,0.8f, 0.3f, &textManager);
	
		  
			} else {
				defeat_screen.draw();
				Sprite text_final_score(-0.4f, -0.5f, 0.8f, 0.3f, texture_id::TEXT_SCORE, &textManager);
				text_final_score.draw();
				//Sprite text_enemies(0.5f, 1.15f, 0.6f, 0.3f, texture_id::TEXT_ENEMIES, &textManager);
				drawNumber(score, 0.f,-0.5,0.8f, 0.3f, &textManager);

				
				Sprite text_final_enemies(-0.4f, -1.f, 0.8f, 0.25f, texture_id::TEXT_ENEMIES, &textManager);
				text_final_enemies.draw();
				drawNumber(enemiesLeft,0.f,-1.f,0.8f, 0.3f, &textManager);
			}

		}



		//  facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();


		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		 

		}
	 
	}
  
  glfwTerminate();

 
  enemies.clear();
  enemies.shrink_to_fit();
  
  projectiles.clear();
  projectiles.shrink_to_fit();
 // _CrtDumpMemoryLeaks();
  return 0;
}