/*
	A aparut din necesitatea de a incarca fiecare textura
	o singura data. Stocheaza id-urile texturilor intr-un
	array egal in dimensiune cu numarul texturilor(ma bazez
	pe faptul ca intotdeauna in enumeratie texture_id ROCKET
	va fi ultimul element. Apeland functia Bind a acestui obiect
	pot activa o anumita textura.

*/

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"

class TextureManager{
public:
	TextureManager();
	~TextureManager();
	void LoadTextures();        //asta incarca toate texturile(pas necesar O SINGURA DATA la inceputul jocului)
	void Bind(texture_id type); //asta activeaza o textura anume
private:
	GLuint textures[texture_id::ROCKET+1];  //aici o sa tin id-urile texturilor
											//codul functioneaza corect cat timp
											//ROCKET e ultimul elemenet al enumeratiei 
											//texture_id

};

#endif