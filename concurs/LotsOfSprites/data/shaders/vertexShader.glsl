#version 400
in layout(location=0) vec2 position;
in layout(location=1) float Xoffset;
in layout(location=2) float Yoffset;

in layout(location=3) vec2 texCoord;
out vec2 texCoord0;
out vec3 theColor;
void main () 
{

	 gl_Position =  vec4(position.x+Xoffset, position.y+Yoffset, 0, 1);
         texCoord0=texCoord;
}