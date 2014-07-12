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
GLuint num_sprites = 100;
enum setting{	
	NUM_SPRITES,
	WINDOW_WIDTH,
	WINDOW_HEIGHT,
	FULL_SCREEN
};


int g_gl_width = 640;
int g_gl_height = 480;
int g_gl_fullscreen = 0;

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
		
		
		case NUM_SPRITES:
			num_sprites = static_cast<GLuint>(value);
			//std::cout << "speed square " << speedSquare << std::endl;
			break;
		case WINDOW_WIDTH:
			g_gl_width = static_cast<GLint>(value);
			break;
		case WINDOW_HEIGHT:
			g_gl_height = static_cast<GLint>(value);
			break;
		case FULL_SCREEN:
			g_gl_fullscreen = (int)value;
			
			break;

		default:
			std::cout << "Eroare la citirea setarilor din 'data/settings.xml'" << std::endl;			
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

	TextureManager tm;  //incarca si aplica textura
	Painter p;			//se ocupa de randare

	

	//generez spriteurile(sub forma de pozitii)
	std::vector<GLfloat> spriteX;     //aici pun offseturile pe X
	spriteX.reserve(50000);
	std::vector<GLfloat> spriteY;	  //aici pun offseturile pe Y
	spriteX.reserve(50000);
	std::vector<GLshort> direction_right;   //aici tin directia in care se misca (daca e 1 e in dreapta, -1 in stanga)
	spriteX.reserve(50000);

	/*
		Mai jos generez spriteurile initiale(si incerc sa le incadrez intre anumite limite(sa fie
		vizibile toate)

	*/
	std::srand((unsigned) time(0));     //pun un seed unic la functia rand
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

	/*
		Amestec cele 2 siruri pentru(sper) o distributie mai uniforma
	*/
	std::random_shuffle(spriteX.begin(), spriteX.end());
	std::random_shuffle(spriteY.begin(), spriteY.end());


	//incarc pe GPU offseturile 
	p.changeX(spriteX, num_sprites);
	p.changeY(spriteY, num_sprites);


	unsigned int count = 0;			//cu asta numar
	unsigned int batch = 100;		//cat de multe spriteuri misc pe frame(dimensiunea unui lot)
	unsigned int t = 0;				//la al catele lot sunt
	unsigned int leftovers;			//cate elemente peste dimensiunea standard(batch) are ultimul lot
	unsigned int endPoint;			//de unde incep elementele suplimentare ale ultimului lot

	GLshort* current_dir;   //pointer la element din vectorul cu directii
	GLfloat* current_x;		//pointer la element din vectorul cu offsetul x

	GLboolean first = true;    //are loc daca sunt la primul frame


	glClearColor(0,0,0,0);  //setez culoarea de fundal a ecranului(cu ce culoare "curat" ecranul)
	while (!glfwWindowShouldClose(window)) {
		Utils::_update_fps_counter (window, &num_sprites);	//pentru afisaj fps(si nr_spriteuri)
			  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glViewport (0, 0, g_gl_width, g_gl_height);
	  


	  p.Render();                 //desenez spriteurile
	  p.changeX(spriteX, num_sprites);  //updatez pozitiile pe X
	 
									    //deci aceasta linie de cod ar putea fi mutata 

	  count++;  //variabila al carei unic rol e sa aiba alta valaore la urmatorul frame

	  t = count%(num_sprites/batch)+1;      //calculez la al catelea lot sunt cu miscarea

	  /*
		codul de mai jos se executa doar la primul frame(si ulterior la fiecare modificare a nr de elemente
	  */

	  if (first){    
		   p.changeY(spriteY, num_sprites);  //updatez pozitiile pe Y(se schimba doar la incrementari, decrementari

		  leftovers = num_sprites - (num_sprites/batch * batch);  //calculez cate elemente sunt in plus in ultimul lot

		  endPoint = num_sprites-leftovers;          //calculez unde incepe partea supimentara a ultimului lot

		  first = false; //nu mai sunt la primul frame
	  }
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

			leftovers = num_sprites - (num_sprites/batch * batch);  //calculez cate elemente sunt in plus in ultimul lot

			endPoint = num_sprites-leftovers;
		
			 p.changeY(spriteY, num_sprites);  //updatez pozitiile pe Y(se schimba doar la incrementari, decrementari
		}
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_KP_SUBTRACT)) {
			//scad nr de sprite cu 1
			
			if (num_sprites>(batch+1)){
				spriteX.pop_back();
				spriteY.pop_back();
				direction_right.pop_back();
				num_sprites--;
				leftovers = num_sprites - (num_sprites/batch * batch);  //calculez cate elemente sunt in plus in ultimul lot

			    endPoint = num_sprites-leftovers;

				 p.changeY(spriteY, num_sprites);  //updatez pozitiile pe Y(se schimba doar la incrementari, decrementari

			} else {
				std::cout << "Nu pot fi mai putin de " << batch << " de elemente!";  
			}
		}

	 
	}
  
  glfwTerminate();

  return 0;
}