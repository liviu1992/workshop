#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

// functie banala de incarcat continutul unui fisier intr-un buffer
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
	std::cout << size << std::endl;
	fclose(f);
	buffer[size] = 0;
	return buffer;
}


int main () {

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

  // Se creeaza fereastra
  GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop1", NULL, NULL);
  if (!window) {
    // nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
	printf ( "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  // Atasam contextul de fereastra
  glfwMakeContextCurrent (window);
                                  
  // Pornit extension handler-ul
  glewInit ();

  // Vedem versiunile
  const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version string
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);

  const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
  const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");


  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);

  delete[] vertex_shader;
  delete[] fragment_shader;

  

   GLint num_of_triangles=num_of_vertices-2;
   GLint num_of_points = 1+num_of_triangles;
   GLfloat radius = 1;
   GLint buffer_size=num_of_points*2;
   const GLfloat PI = 3.141;

   GLfloat *vertex_buffer = new GLfloat[buffer_size+2];

   vertex_buffer[0]=0;
   vertex_buffer[1]=0;
   int c=1;
   for (int i=1; i<num_of_triangles+1; i++){
	   float angle = PI*2*i/num_of_triangles;
	   //std::cout << angle << std::endl;
	   vertex_buffer[2*i]=radius*std::cos(angle);
	   vertex_buffer[2*i+1]=radius*std::sin(angle);
		c=2*i+2;   
   }
   vertex_buffer[c]=vertex_buffer[2];
   vertex_buffer[c+1]=vertex_buffer[3];

   



  // Generam un buffer in memoria video si scriem in el punctele din ram
  GLuint vbo = 0;
  glGenBuffers(1, &vbo); // generam un buffer 
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*(buffer_size+2), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

  // De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
  // 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
  // 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  while (!glfwWindowShouldClose(window)) {
	  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  // spunem ce shader vom folosi pentru desenare
	  glUseProgram(shader_programme);
	  // facem bind la vertex buffer
	  glBindBuffer(GL_ARRAY_BUFFER, vbo);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLE_FAN, 0, num_of_points+2);
	  // facem swap la buffere (Double buffer)
	  glfwSwapBuffers(window);

	  glfwPollEvents();
	}
  
  glfwTerminate();
  return 0;
}