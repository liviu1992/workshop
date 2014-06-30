#version 400
in vec3 vertex_position;
uniform mat4 Matrix;
in vec2 texCoord;
out vec2 texCoord0;

void main () 
{

	 gl_Position = Matrix * vec4(vertex_position,1.0) ;
         texCoord0=texCoord;
}
