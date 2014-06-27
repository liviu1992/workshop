#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
namespace Utils{
	enum Color{
		RED,
		BLUE,
		GREEN,
		YELLOW
	};

	static GLuint loadShader(const char* filename, GLenum type){
		std::ifstream file;
		file.open(filename);
		if (!file.is_open()){
			std::cout << "Couldn't open the file " << filename << std::endl;
			
		}
		std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		const char *shaderSource = content.c_str();

		GLuint shader;
		shader= glCreateShader(type);			
		
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		//delete[] shaderSource;

		return shader;
	}
	static void _update_fps_counter (GLFWwindow* window){
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
	static GLuint makeProgram(GLuint vertexShader, GLuint fragmentShader){
			GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		return program;
	}
	static void showOpengGLInfo(){
		  const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
	 const GLubyte* version = glGetString (GL_VERSION); // version string
	 printf ("Renderer: %s\n", renderer);
	 printf ("OpenGL version supported %s\n", version);
	}
};

#endif