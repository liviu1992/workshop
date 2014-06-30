#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

int main(){
	//initialize the glfw

	if (!glfwInit()){
		glfwTerminate();
		std::cout << "Error!" << std::endl;
		int i;
		std::cin >> i;
		return -1;
	}



	GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL Test",NULL, NULL);
	if (window == NULL){
		std::cout << "Can't create window!" << std::endl;
		int i;
		std::cin >> i;
	}

	glfwMakeContextCurrent(window);

	std::cout << glGetString(GL_VERSION) << std::endl;

	/*
		NOW WE WILL PREPARE THE BUFFERS TO DRAW SOMETHING
	*/
	//first we define the pointer to the buffer
	GLuint vbo;
	//then we assign an id to the pointer
	glGenBuffers(1, &vbo);
	//then we bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	//we create the data for our buffer
	GLfloat bufferData[]={
		0.0, 0.5, 
		0.5, -0.5,
		-0.5, -0.5
	};
	//we send the data to the GPU at the location indicated by the vbo pointer
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);







	glClearColor(0.0, 1.0, 0.0, 0.0);
	while (!glfwWindowShouldClose(window)){
		
		GLint width, height;

		glfwGetWindowSize(window, &width, &height);

		glViewport(0,0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}



	
	glfwDestroyWindow(window);
	glfwTerminate();




	return 0;
}
