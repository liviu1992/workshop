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
/*
	AICI SE AFLA TIPURILE DE SETARI PE CARE LE PUTEM 
	MODIFICA DIN FISIERUL settings.xml
*/

enum setting{
	SPEED_CIRCLE,
	SPEED_SQUARE,
	WINDOW_WIDTH,
	WINDOW_HEIGHT,
	FULL_SCREEN
};

/*
	MAI JOS SUNT PARAMETRII JOCULUI(VARIABILE
	CORESPUNZATOARE TIPURILOR DE SETARI)

*/
float speedCircle;
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
		float value = atof(pNode->first_attribute("value")->value());
		switch(counter){
		case SPEED_CIRCLE:
			speedCircle = value;
			//std::cout << "speed circle " << speedCircle << std::endl;
			break;
		case SPEED_SQUARE:
			speedSquare = value;
			//std::cout << "speed square " << speedSquare << std::endl;
			break;
		case WINDOW_WIDTH:
			g_gl_width = value;
			break;
		case WINDOW_HEIGHT:
			g_gl_height = value;
			break;
		case FULL_SCREEN:
			g_gl_fullscreen = value;
			
			break;

		default:
			std::cout << "Eroare citire setari" << std::endl;
			
		}
		counter++;

	}

}

 

void glfw_error_callback (int error, const char* description) {
  std::cout << "GLFW ERROR: code "<<error <<" msg: "<<description << std::endl;
}

void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
  g_gl_width = width;
  g_gl_height = height;
  
  /* putem modifica aici matricile de perspectiva */
}

int main () {
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
		Variabile pe care le voi folosi pentru a pastra 
		starea obiectelor

	*/
	//float circleX=0.5;
	//float circleY=0;
	float squareX1=0.5;
	float squareY1=0.5;

	float squareX2=-0.5;
	float squareY2=0.5;

	float shipX=0;
	float shipY=0.2;

	


	Sprite square1(0.5, 0.5, 0.3, 0.3, "../data/textures/spaceshipS.png");
	Sprite square2(-0.5, 0.5, 0.3, 0.3, "../data/textures/spaceshipS.png");

	Sprite ship(0, 0.4, 0.6, 0.5, "../data/textures/ship/space_ship_up.png");

	//SpriteTriangle str1(-0.8,-0.9, 0.2,0.3, Utils::Color::BLUE);

	//SpriteTriangle str2(-0.6,-0.9, 0.2,0.3, Utils::Color::RED);



	//int sprite_number=3000;
	/*std::vector<Sprite> sprites;
	sprites.reserve(sprite_number);

	for (int i=0; i<sprite_number; i++){
		sprites.push_back(Sprite(0,0,0.1,0.1,Utils::Color::BLUE));
	}
	*/


	//SpriteCircle sc1(0,0, 0.1, Utils::Color::RED);


//	sc1.move(0.0, 0.2);

	/*
		Mai jos sunt variabilele pe care le voi folosi sa calculez 
		durata unui frame
	*/

	float lastTime = glfwGetTime();
	float newTime;
	float frameTime;	
	glClearColor(0,0,0,0);
	while (!glfwWindowShouldClose(window)) {
		Utils::_update_fps_counter (window);

		/*
			Fac viteza de miscare sa fie independenta de framerate.
			Inmultesc viteza cu timpul dintre frameuri.

		*/
		newTime = glfwGetTime();

		frameTime = newTime-lastTime;
		lastTime=newTime;

		/*
			######################################################
		*/

	  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glViewport (0, 0, g_gl_width, g_gl_height);

	//  sc1.move(circleX, circleY);

///	  sc1.draw();

	//  str1.draw();

	//  str2.draw();	  
	

	  ship.move(shipX, shipY);
	  ship.draw();



	/*  for (int i=0; i<sprites.size(); i++){
		sprites.at(i).draw();
	}*/

	  /*
		VITEZA PATRATULUI DEPINDE DE TIMP DECI E INDEPENDENTA DE FRAMERATE

	  */
	  float time =glfwGetTime();

	  squareX1 = 0.4 * std::cos(time*speedSquare);   
	  squareY1= 0.4 * std::sin(time*speedSquare);

	  squareX2 = 0.4 * std::sin(time*speedSquare);   
	  squareY2= 0.4 * std::cos(time*speedSquare);


	  square1.move(squareX1, squareY1);
	  square2.move(squareX2, squareY2);


	  square1.draw();
	  square2.draw();

	 //  facem swap la buffere (Double buffer)
	  glfwSwapBuffers(window);

	  glfwPollEvents();
	  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (window, 1);
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)){
		 // circleY+=speedCircle*frameTime;   //scalez distanta cu timpul parcurs intre frameuri
											//pentru a obtine o viteza constanta indiferent de
											//durata dintre frameuri

		//  sc1.moveY(circleY);
		   shipY+=speedCircle*frameTime;

	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)){
		//  circleY-=speedCircle*frameTime;
		  shipY-=speedCircle*frameTime;
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)){
		//  circleX-=speedCircle*frameTime;
		  shipX-=speedCircle*frameTime;

	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)){
		//  circleX+=speedCircle*frameTime;
		  shipX+=speedCircle*frameTime;

	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_L)){
		  loadSettings();
	  }
	}
  
  glfwTerminate();
  return 0;
}