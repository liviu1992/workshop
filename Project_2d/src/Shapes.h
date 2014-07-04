#include <math.h>
#include <GL\glew.h>
#include <iostream>
namespace Shapes{


	static GLfloat* createCircle(GLfloat x, GLfloat y, int num_of_vertices, GLfloat radius){
	GLint num_of_triangles=num_of_vertices;
	GLint num_of_points = 3 * num_of_triangles+1;
           
    GLint buffer_size=num_of_points*2;
	const GLfloat PI = 3.141f;

   GLfloat *vertex_buffer = new GLfloat[buffer_size+12*2];
   vertex_buffer[0]=x;
   vertex_buffer[1]=y;

   float angle = PI*2*1/num_of_triangles;

   vertex_buffer[2]=x+radius*std::cos(angle);

   vertex_buffer[3]=y+radius*std::sin(angle);

   angle = PI*2*2/num_of_triangles;

   vertex_buffer[4]=x+radius*std::cos(angle);

   vertex_buffer[5]=y+radius*std::sin(angle);

	int c;
	for (int i=1; i<num_of_triangles; i++){
		angle = PI*2*(2+i)/num_of_triangles;

		vertex_buffer[i*6]=x;
		vertex_buffer[i*6+1]=y;
		vertex_buffer[i*6+2]=vertex_buffer[i*6-2];
		vertex_buffer[i*6+3]=vertex_buffer[i*6-1];
		vertex_buffer[i*6+4]=x+radius*std::cos(angle);
		vertex_buffer[i*6+5]=y+radius*std::sin(angle);
		c=i*6+5;
	}
	vertex_buffer[c-1]=vertex_buffer[2];
	vertex_buffer[c]=vertex_buffer[3];


		return vertex_buffer;


	}
};