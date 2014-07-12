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
#include <math.h>
#include <time.h>
#include "TextureManager.h"
#include "Painter.h"
#include <algorithm>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


struct element{
	GLfloat x;			//pozitia sprite-ului
	GLfloat y;          //pozitia sprite-ului
	GLboolean direction;  //spre dreapta
};





/*
	AICI SE AFLA TIPURILE DE SETARI PE CARE LE PUTEM 
	MODIFICA DIN FISIERUL settings.xml
*/
unsigned int num_sprites = 0;
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



	TextureManager tm;
	Painter p;

	GLuint num_sprites = 27000;

	//generez spriteurile(sub forma de pozitii)
	std::vector<GLfloat> spriteX;
	spriteX.reserve(50000);
	std::vector<GLfloat> spriteY;
	spriteX.reserve(50000);
	std::vector<GLshort> direction_right;
	spriteX.reserve(50000);

	/*
		Mai jos generez spriteurile initiale(si incerc sa le incadrez intre anumite limite(sa fie
		vizibile toate)

	*/
	std::srand((unsigned) time(0));
	for (unsigned int i=0; i<num_sprites; i++){	
		GLfloat x_off = static_cast<GLfloat>(rand()%1024)/1024*3-1.5f;
		GLfloat y_off = static_cast<GLfloat>(rand()%768)/768*3 -1.5f;
		if (y_off>0.4f ){
			y_off-=0.6f;//*static_cast<GLfloat>(rand()%6+1);
		}  else if (y_off<-0.4f ){
			y_off+=0.1f;//*static_cast<GLfloat>(rand()%6+1);
		}
		if (x_off>0.4f){
			x_off-=0.6f;//*static_cast<GLfloat>(rand()%6+1);
		} else if (x_off<-0.4f){
			x_off+=0.6f;//*static_cast<GLfloat>(rand()%6+1);
		}
		spriteX.push_back(x_off);
		spriteY.push_back(y_off);
		direction_right.push_back(1);


	}
	std::random_shuffle(spriteX.begin(), spriteX.end());
	std::random_shuffle(spriteY.begin(), spriteY.end());


	p.changeX(spriteX, num_sprites);
	p.changeY(spriteY, num_sprites);


	unsigned int count = 0;
	unsigned int step = 0;
	unsigned int batch = 100;
	unsigned int t = 0;
	unsigned int leftovers;
	unsigned int endPoint;

	GLshort* current_dir;
	GLfloat* current_x;

	float lastTime = (float) glfwGetTime();
	float newTime;
	float frameTime;	
	glClearColor(0,0,0,0);
	while (!glfwWindowShouldClose(window)) {
		Utils::_update_fps_counter (window, &num_sprites);	

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
	  


	  p.Render();                 //desenez spriteurile
	  p.changeX(spriteX, num_sprites);  //updatez pozitiile pe X
	  p.changeY(spriteY, num_sprites);  //updatez pozitiile pe Y(se schimba doar la incrementari, decrementari
									    //deci aceasta linie de cod ar putea fi mutata 

	  count++;  //variabila al carei unic rol e sa aiba alta valaore la urmatorul frame

	  t = count%(num_sprites/batch)+1;      //calculez la al catelea lot sunt cu miscarea
	      
	  leftovers = num_sprites - (num_sprites/batch * batch);  //calculez cate elemente sunt in plus in ultimul lot

	  endPoint = num_sprites-leftovers;          //calculez unde incepe partea supimentara a ultimului lot
	 /*
		MISC PE RAND FIECARE SPRITE IN LOTURI A CATE 100(ultimul va avea pana in 199 de elemente)
	 */
	
	  for (unsigned int i=(t-1)*batch; i<t*batch || (i>=endPoint && i<num_sprites); i++){
			current_dir = &direction_right.at(i);
			current_x = &spriteX.at(i);
			if ((*current_x)>0.8f){
				(*current_dir)=-1;
			} else if ((*current_x)<-0.8f){
				(*current_dir)=1;
			}
		
		  
		 
			 //spriteX.at(i)+=0.001f*(*current_dir);
			spriteX.at(i)+=0.01f*(*current_dir);


	  }



	


		//  facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();


		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		 

		}
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_KP_ADD)) {
			//cresc nr de sprite cu 1
			GLfloat x_off = static_cast<GLfloat>(rand()%1024)/1024*3-1.5f;
			GLfloat y_off = static_cast<GLfloat>(rand()%768)/768*3 -1.5f;
			if (y_off>0.4f ){
				y_off-=0.6f;//*static_cast<GLfloat>(rand()%6+1);
			}  else if (y_off<-0.4f ){
				y_off+=0.1f;//*static_cast<GLfloat>(rand()%6+1);
			}
			if (x_off>0.4f){
				x_off-=0.6f;//*static_cast<GLfloat>(rand()%6+1);
			} else if (x_off<-0.4f){
				x_off+=0.6f;//*static_cast<GLfloat>(rand()%6+1);
			}
			spriteX.push_back(x_off);
			spriteY.push_back(y_off);
			direction_right.push_back(1);
			num_sprites++;
		

		}
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_KP_SUBTRACT)) {
			//scad nr de sprite cu 1
			spriteX.pop_back();
			spriteY.pop_back();
			direction_right.pop_back();
			num_sprites--;
		}

	 
	}
  
  glfwTerminate();
 
 
 
 // _CrtDumpMemoryLeaks();
  return 0;
}