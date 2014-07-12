#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Utils{
	// 
	enum Color{
		RED,
		BLUE,
		GREEN,
		YELLOW
	};
	// ^^^^^ inutil
	

	/*
		incarc un shader din fisier, incerc sa il compilez si daca nu merge 
		afisez un mesaj care sa explice de ce a esuat
		
		returnez id-ul shaderului 
	*/
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
		GLint compileStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus = GL_FALSE){
			std::cout << "Error compiling shader at "<< filename << std::endl;
			GLint logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			GLchar *infoLog=new GLchar[logLength+1];

			glGetShaderInfoLog(shader, logLength, NULL, infoLog);

			std::cout << "Details regarding the compile error " << infoLog << std::endl;

		}
		
		

		return shader;
	}
	static void _update_fps_counter (GLFWwindow* window, unsigned int * num_sprites){
		static double previous_seconds = glfwGetTime ();
		static int frame_count;
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		if (elapsed_seconds > 0.25) {
			previous_seconds = current_seconds;
			double fps = (double)frame_count / elapsed_seconds;
			//char tmp[128];
		
			std::string tmp = "opengl @ fps: " + std::to_string(fps).substr(0,4) + " sprites: "+std::to_string(*num_sprites);
			glfwSetWindowTitle (window, tmp.c_str());
			frame_count = 0;
		}
		frame_count++;
	}

	//ataseaza shadere programului si il linkeaza
	static GLuint makeProgram(GLuint vertexShader, GLuint fragmentShader){
			GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glBindAttribLocation(program, 0, "vertex_position");
		glBindAttribLocation(program, 1, "texCoord");

		glLinkProgram(program);
		GLint programStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &programStatus);
		if (programStatus == GL_FALSE){
			std::cout << "Failed to link shader program "<< std::endl;
			GLint logLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
			GLchar *programLog=new GLchar[logLength+1];
			glGetProgramInfoLog(program, logLength, NULL, programLog);
			
			std::cout << "Link failure details "<<programLog << std::endl;


			free(programLog);

		}
		
		return program;
	}
	//ofera informatii legate de OpenGL
	static void showOpengGLInfo(){
		  const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
	 const GLubyte* version = glGetString (GL_VERSION); // version string
	 printf ("Renderer: %s\n", renderer);
	 printf ("OpenGL version supported %s\n", version);
	}
};

#endif