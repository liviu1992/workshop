#version 400
 in vec3 vertex_position;
uniform mat4 Matrix;
void main () 
{

	 gl_Position = Matrix * vec4(vertex_position,1.0) ;
	
}
