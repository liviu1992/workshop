#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include "Camera.h"

/*
	pentru masurarea performantei
*/
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F>
    static typename TimeT::rep execution(F const &func)
    {
        auto start = std::chrono::system_clock::now();
        func();
        auto duration = std::chrono::duration_cast< TimeT>(
            std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

//obiect din mediul inconjurator, definit de un sprite si de o adancime(care
//permite realizarea unui efect de 2.5D 
struct object{
	Sprite* s;				//ce sprite folosesc pentru a reprezenta obiectul
	GLfloat depth;			//"adancimea" relativa la pozitia playerului la care se afla obiectul
							//preferabil intre 0(infinit de departe de player, adica stationar in
							//urma miscarilor acestuia) si 1(pe acelasi nivel de adancime cu playerul)
							
};

//defineste un sector al hartii (un patrat de anumite dimensiuni folosit
//pentru a reduce numarul de obiecte din mediul inconjurator(planete, asteroizi)
//cu care trebuie sa lucrez. 
struct sector{
	GLint x;
	GLint y;
	std::vector<object*> objects;  //contine obiectele care se afla in acel sector
	
};



class LayerManager{
public:
	LayerManager(Camera* cam, TextureManager* tm);
	~LayerManager();
	void Update();		//updateaza pozitiile obiectelor din currentSectors(pentru a simula efectul de 2.5D
	void Draw();		//deseneaza pozitiile obiectelor vizibile in acest moment pe ecran
						//voi folosi algoritmul pentru detectia coliziunilor pentru a ma asigura ca 
						//exista o coliziune intre obiectele din sectoarele active si un patrat cu originea
						//in pozitia playerului si o lungime si o inaltime suficienta pentru a depasi ecranul.
						//in cazul in care conditiile sunt satisfacute obiectele vor fi desenate.
	sector* PopulateSector(GLint x, GLint y);  //populeaza sectorul de coordonate x si y
	void PopulateCurrent();  //populeaza toate sectoarele din jurul playerului care nu au fost populate deja
	void UpdateCurrent();    //updatez currentSectors
	bool LayerManager::collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB );
	static bool compareDepths(object* left, object* right);
private:
	std::map<GLint, sector*> map;
	std::vector<sector*> currentSectors;  //aici pun sectoarele curente, pe care le voi desena si updata
	std::vector<sector*> visitedSectors; //aici pun sectoarele deja populate
	std::vector<object*> activeObjects;
	TextureManager* textureManager; //util pentru a creea un nou sprite
	Camera* cam; //de aici aflam ce sectoare sunt vizibile
	GLfloat visibileSize;
	GLint visibleSizeInt;
	GLboolean first;

	GLboolean up;
	GLboolean down;
	GLboolean left;
	GLboolean right ;
	GLboolean up_left;
	GLboolean up_right;
	GLboolean down_left;
	GLboolean down_right;
	
};

#endif