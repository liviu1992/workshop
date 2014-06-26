#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Matrix.cpp"
#include "RAPIDXML\rapidxml_utils.hpp"
#include "RAPIDXML\rapidxml.hpp"



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


		//std::cout << "Nume: " << name << " Valoare: " << value << std::endl;
	}

}

 // ....................Calculam FPS-ul si il afisam in titlul ferestrei.................
 void _update_fps_counter (GLFWwindow* window) {
  static double previous_seconds = glfwGetTime ();
  static int frame_count;
  double current_seconds = glfwGetTime ();
  double elapsed_seconds = current_seconds - previous_seconds;
  if (elapsed_seconds > 0.25) {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    char tmp[128];
    sprintf (tmp, "opengl @ fps: %.2f", fps);
    glfwSetWindowTitle (window, tmp);
    frame_count = 0;
  }
  frame_count++;
}

void glfw_error_callback (int error, const char* description) {
  //gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);   <<< nu functioneaza
  std::cout << "GLFW ERROR: code "<<error <<" msg: "<<description << std::endl;
}

void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
  g_gl_width = width;
  g_gl_height = height;
  
  /* putem modifica aici matricile de perspectiva */
}

char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}


int main () {
	loadSettings();

	Matrix m;
	std::cout << "Matrix element " << m.getData()[0] << std::endl;

	GLint num_of_vertices=0;
	std::cout << "Din cati vertecsi sa fie facut cercul?" << std::endl;
	while (num_of_vertices<3){
		std::cin >> num_of_vertices;
	}

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
  const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version string
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);

  /*
	MAI JOS INCARC SHADERELE, LE COMPILEZ SI LE ALOC PROGRAMELOR
  */

  const char * vertex_shader = LoadFileInMemory("../data/vertexShaderT.glsl");
  const char * fragment_shaderGreen = LoadFileInMemory("../data/fragmentShaderGreen.glsl");
  const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fsg = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fsg, 1, &fragment_shaderGreen, NULL);
  glCompileShader(fsg);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, vs);
  glAttachShader(shader_programme, fs);
  glLinkProgram(shader_programme);

  GLuint shader_programmeGreen = glCreateProgram();
  glAttachShader(shader_programmeGreen, vs);
  glAttachShader(shader_programmeGreen, fsg);
  glLinkProgram(shader_programmeGreen);

  delete[] vertex_shader;
  delete[] fragment_shader;
  delete[] fragment_shaderGreen;

  /*
	VARIABILE NECESARE DESENARII CERCULUI
  */

   GLint num_of_triangles=num_of_vertices;
   GLint num_of_points = 3 * num_of_triangles+1;
   GLfloat radius = 0.3;
   GLint buffer_size=num_of_points*2;
   const GLfloat PI = 3.141;

   GLfloat *vertex_buffer = new GLfloat[buffer_size+12*2];
	/*
		MAI JOS POPULEZ BUFFERUL CU TRIUNGHIURILE CARE VOR COMPUNE CERCUL
	*/
   
   vertex_buffer[0]=0;
   vertex_buffer[1]=0;

  float angle = PI*2*1/num_of_triangles;

   vertex_buffer[2]=radius*std::cos(angle);

   vertex_buffer[3]=radius*std::sin(angle);

   angle = PI*2*2/num_of_triangles;

   vertex_buffer[4]=radius*std::cos(angle);

   vertex_buffer[5]=radius*std::sin(angle);

	int c;
	for (int i=1; i<num_of_triangles; i++){
		angle = PI*2*(2+i)/num_of_triangles;

		vertex_buffer[i*6]=0;
		vertex_buffer[i*6+1]=0;
		vertex_buffer[i*6+2]=vertex_buffer[i*6-2];
		vertex_buffer[i*6+3]=vertex_buffer[i*6-1];
		vertex_buffer[i*6+4]=radius*std::cos(angle);
		vertex_buffer[i*6+5]=radius*std::sin(angle);
		c=i*6+5;
	}
	vertex_buffer[c-1]=vertex_buffer[2];
	vertex_buffer[c]=vertex_buffer[3];

	/*
		PREGATESC CELELALTE CORPURI
	*/

	GLfloat shapes_buffer[] = {
	  0.2f, 0.3f,    
	  0.3f, 0.f,		//primul triunghi
	  0.1f, 0.f,     

	 -0.2f, 0.3f, 	 
	 -0.1f, 0.f,		//al doilea triunghi
	 -0.3f, 0.f, 


	 -0.1f, 0.1f, 
	  0.1f, 0.1f, 
	  0.1f, -0.1f,     //patratul
	 -0.1f, 0.1f, 
	  0.1f, -0.1f, 
	 -0.1f, -0.1f, 

  };


  /*
		INCARC CELELALTE CORPURI IN BUFFER
  */
  
  for (int i=0; i<24; i++){
	  vertex_buffer[c+1+i] = shapes_buffer[i];
  }

  // Generam un buffer in memoria video si scriem in el punctele din ram
  GLuint vbo = 0;
  glGenBuffers(1, &vbo); // generam un buffer 
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
  glBufferData(GL_ARRAY_BUFFER, (buffer_size+2 * 12) * sizeof (float), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

  delete[] vertex_buffer;
  //delete[] shapes_buffer;

  // De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
  // 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
  // 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  


	//............Antialiasing...............
	glfwWindowHint (GLFW_SAMPLES, 4);

	/*
		Variabile pe care le voi folosi pentru a pastra 
		starea obiectelor

	*/

	float circleX=0.5;
	float circleY=0;

	float squareX=0;
	float squareY=-0.8;


	/*
		Mai jos sunt variabilele pe care le voi folosi sa calculez 
		durata unui frame
	*/

	float lastTime = glfwGetTime();
	float newTime;
	float frameTime;



	GLint mat =glGetUniformLocation(shader_programme, "Matrix");


	

	

	while (!glfwWindowShouldClose(window)) {
		_update_fps_counter (window);

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


	  // spunem ce shader vom folosi pentru desenare
	  glUseProgram(shader_programme);
	  //move(translationMatrix, circleX, circleY, 0);
	  m.translateTo(circleX, circleY);
	  glUniformMatrix4fv(mat, 1, GL_FALSE, m.getData()); 

	  // facem bind la vertex buffer
	  glBindBuffer(GL_ARRAY_BUFFER, vbo);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, num_of_triangles*3);

	 // glUseProgram(NULL);

	  glUseProgram(shader_programme);
	 // move(translationMatrix, -0.8, -0.9, 0);

	  m.translateTo(-0.8, -0.9);
	  glUniformMatrix4fv(mat, 1, GL_FALSE, m.getData()); 
	  glDrawArrays(GL_TRIANGLES, num_of_triangles*3, 3);

	  glUseProgram(shader_programmeGreen);

	  //move(translationMatrix, -0.7, -0.9, 0);
	  
	  m.translateTo(-0.7, -0.9);
	  glUniformMatrix4fv(mat, 1, GL_FALSE, m.getData()); 

	  glDrawArrays(GL_TRIANGLES, num_of_triangles*3+3, 3);	
	  float time =glfwGetTime();

	  /*
		VITEZA PATRATULUI DEPINDE DE TIMP DECI E INDEPENDENTA DE FRAMERATE

	  */
	  squareX = 0.4 * std::cos(time*speedSquare);   
	  squareY= 0.4 * std::sin(time*speedSquare);

	  //move(translationMatrix, squareX, squareY, 0);
	  m.translateTo(squareX, squareY);

	  glUniformMatrix4fv(mat, 1, GL_FALSE, m.getData()); 


	  glDrawArrays(GL_TRIANGLES, num_of_triangles*3+6, 6);
	 //  facem swap la buffere (Double buffer)
	  glfwSwapBuffers(window);

	  glfwPollEvents();
	  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (window, 1);
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)){
		  circleY+=speedCircle*frameTime;   //scalez distanta cu timpul parcurs intre frameuri
											//pentru a obtine o viteza constanta indiferent de
											//durata dintre frameuri
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)){
		  circleY-=speedCircle*frameTime;
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)){
		  circleX-=speedCircle*frameTime;
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)){
		  circleX+=speedCircle*frameTime;
	  }
	  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_L)){
		  loadSettings();
	  }
	}
  
  glfwTerminate();
  return 0;
}