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
  const char * fragment_shader_red = LoadFileInMemory("../data/fragmentShaderRed.glsl");
  const char * fragment_shader_green = LoadFileInMemory("../data/fragmentShaderGreen.glsl");

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fs_red = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_red, 1, &fragment_shader_red, NULL);
  glCompileShader(fs_red);

  GLuint shader_programme_red = glCreateProgram();
  glAttachShader(shader_programme_red, fs_red);
  glAttachShader(shader_programme_red, vs);
  glLinkProgram(shader_programme_red);


  GLuint fs_green = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_red, 1, &fragment_shader_green, NULL);
  glCompileShader(fs_green);

  GLuint shader_programme_green = glCreateProgram();
  glAttachShader(shader_programme_green, fs_green);
  glAttachShader(shader_programme_green, vs);
  glLinkProgram(shader_programme_green);

  delete[] vertex_shader;
  delete[] fragment_shader_red;
  delete[] fragment_shader_green;

  

  

   GLfloat vertex_buffer_red[]={
	   0.1, 0.0,
	   0.2, 0.5,
	   0.3, 0.0

   };
     GLfloat vertex_buffer_green[]={
	   -0.1, 0.0,
	   -0.2, -0.5,
	   -0.3, 0.0

   };

  
   



  // Generam un buffer in memoria video si scriem in el punctele din ram
  GLuint vbo_red;
  glGenBuffers(1, &vbo_red); // generam un buffer 
  glBindBuffer(GL_ARRAY_BUFFER, vbo_red); // setam bufferul generat ca bufferul curent 
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6, vertex_buffer_red, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  



  GLuint vbo_green;
  glGenBuffers(1, &vbo_green); // generam un buffer 
  glBindBuffer(GL_ARRAY_BUFFER, vbo_green); // setam bufferul generat ca bufferul curent 
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6, vertex_buffer_green, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

  // De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
  // 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
  // 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);



  while (!glfwWindowShouldClose(window)) {
	  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  // spunem ce shader vom folosi pentru desenare
	  glUseProgram(shader_programme_red);
	  // facem bind la vertex buffer
	  glBindBuffer(GL_ARRAY_BUFFER, vbo_red);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, 3);

	  //glUseProgram(NULL);

	  //glBindBuffer(GL_ARRAY_BUFFER, NULL);

	  

	  glUseProgram(shader_programme_green);

	  glBindBuffer(GL_ARRAY_BUFFER, vbo_green);

	  glDrawArrays(GL_TRIANGLES,0,3);
	  // facem swap la buffere (Double buffer)
	  glfwSwapBuffers(window);

	  glfwPollEvents();
	}
  
  glfwTerminate();
  return 0;
}