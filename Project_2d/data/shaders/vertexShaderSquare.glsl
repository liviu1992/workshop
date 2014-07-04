#version 400
in vec3 vertex_position;
uniform mat4 ProjMatrix;
uniform mat4 TransMatrix;
uniform mat4 RotMatrix;
in vec2 texCoord;
out vec2 texCoord0;

void main () 
{

	 gl_Position = RotMatrix * TransMatrix * vec4(vertex_position,1.0) ;
         texCoord0=texCoord;
}
