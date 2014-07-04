#version 400
uniform sampler2D diffuse;
in vec2 texCoord0;
out vec4 frag_colour;
void main () {
	frag_colour = texture2D(diffuse, texCoord0); 
}