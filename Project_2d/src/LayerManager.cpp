#include "LayerManager.h"


LayerManager::LayerManager(Camera* cam, TextureManager* tm){
	this->cam = cam;
	this->textureManager = tm;
	this->visibileSize = 4.f;
	this->visibleSizeInt = 4;//static_cast<GLint>(this->visibileSize);

	//acum populez sectorul initial (0, 0)

	srand((unsigned)time(0));

	sector* s = PopulateSector(0,0);
	map[0]=s;
	this->visitedSectors.push_back(s);
	std::cout << "Layer manager initializes" << std::endl;

}


LayerManager::~LayerManager(){
	std::cout << "Destroying LayerManager" << std::endl;
	for (unsigned int i=0; i<visitedSectors.size(); i++){
		for (unsigned int j = 0; j<visitedSectors.at(i)->objects.size(); j++){			
			delete visitedSectors.at(i)->objects.at(j)->s;
			delete visitedSectors.at(i)->objects.at(j);
		}
		delete visitedSectors.at(i);
	}
}

void LayerManager::Update(){
	//std::cout << measure<>::execution( [&]() {  


	UpdateCurrent(); //updatez lista currentSectors
	for (unsigned int i=0; i<activeObjects.size(); i++){	
		activeObjects.at(i)->s->move(this->cam->getX()*activeObjects.at(i)->depth,this->cam->getY()*activeObjects.at(i)->depth);
		activeObjects.at(i)->s->getMatrix()->updateMatrix();
			
	

	}


	
//	}) << std::endl;

}

void LayerManager::Draw(){
	


	for (unsigned int i=0; i<activeObjects.size(); i++){		
			activeObjects.at(i)->s->draw();		

	}
		

}


sector* LayerManager::PopulateSector(GLint mx, GLint my){
	std::cout << "Populating " << mx << " " << my << std::endl;
	sector* s=new sector();

	s->x = mx;
	s->y = my;


	GLuint numPlanets = 1;//rand() %3+1;
	GLuint numAsteroids = 4; //rand() %10+1;

	
	
	for (GLuint i = 0; i<numPlanets; i++){
		
		GLfloat x =visibleSizeInt*mx + rand() % (this->visibleSizeInt*100)/100.0f - this->visibleSizeInt*0.5f;
		GLfloat y = visibleSizeInt*my + rand() % (this->visibleSizeInt*100)/100.0f - this->visibleSizeInt*0.5f;
		
		//GLfloat size = rand() % 9 *0.1f+0.1f;
		//GLfloat depth = rand() % 5 * 0.1f + 0.3f;	
		GLfloat size = rand() % 9 *0.1f+0.1f;
		GLfloat depth = rand() % 300 * 0.001f+0.3f;	
		GLint planet = rand() % 12;
		object* obj=new object();
		obj->s = new Sprite(x,y,size, size, static_cast<texture_id>(texture_id::PLANET_GREEN+planet), textureManager);
		obj->depth = depth;
		s->objects.push_back(obj);
	}
	for (GLuint i = 0; i<numAsteroids; i++){
		
		GLfloat x =visibleSizeInt*mx + (rand() % (this->visibleSizeInt*100))/100.0f - this->visibleSizeInt*0.5f;
		GLfloat y = visibleSizeInt*my + (rand() % (this->visibleSizeInt*100))/100.0f - this->visibleSizeInt*0.5f;
		
		GLfloat size = rand() % 4 *0.1f;
		GLfloat depth = rand() % 300 * 0.001f;	
		GLint meteor = rand() % 6;
		object* obj=new object();
		obj->s = new Sprite(x,y,size, size, static_cast<texture_id>(texture_id::METEOR_1+meteor), textureManager);
		obj->depth = depth;
		s->objects.push_back(obj);
	}

	


//	std::cout << "x: " << s->x << " y: "<<s->y << std::endl;

	return s;
}
void LayerManager::UpdateCurrent(){
	//std::cout << measure<>::execution( [&]() {  


	currentSectors.clear();
	/*
		mai jos sunt coordonatele sectorului in care se afla playerul
	*/

	GLfloat pX = cam->getX();
	GLfloat pY = cam->getY();

	GLint playerX = static_cast<int>(pX)/visibleSizeInt;  
	GLint playerY = static_cast<int>(pY)/visibleSizeInt;

	
	

	currentSectors.push_back(map[playerX*1000+playerY]);
	currentSectors.push_back(map[playerX*1000+playerY+1]);
	currentSectors.push_back(map[playerX*1000+playerY-1]);
	currentSectors.push_back(map[(playerX+1)*1000+playerY]);
	currentSectors.push_back(map[(playerX-1)*1000+playerY]);
	currentSectors.push_back(map[(playerX-1)*1000+playerY+1]);
	currentSectors.push_back(map[(playerX+1)*1000+playerY+1]);
	currentSectors.push_back(map[(playerX-1)*1000+playerY-1]);
	currentSectors.push_back(map[(playerX+1)*1000+playerY-1]);


	activeObjects.clear();
	glm::vec2 position;
	for (unsigned int i=0; i<currentSectors.size(); i++){
		for (unsigned int j=0; j<currentSectors.at(i)->objects.size(); j++){	
			
			
		
		
		//	position = currentSectors.at(i)->objects.at(j)->s->getPosition();
		//	if (glm::distance(position, glm::vec2(pX, pY))<4.f)
		/*	if (collisionDectectorAABB(
				pX, pY, 4.f, 4.f,
				position.x,
				position.y,
				2.f,
				2.f
				)
				) {*/
					activeObjects.push_back(currentSectors.at(i)->objects.at(j));
			//}
		}
		
	}
	std::sort(activeObjects.begin(),activeObjects.end(), &compareDepths);
	//std::cout << "Num elements drawn " << activeObjects.size() << std::endl;

	//	}) << std::endl;

}

void LayerManager::PopulateCurrent(){

//	std::cout << measure<>::execution( [&]() {  

	//aflu sectorul curent
	GLint x = static_cast<GLint>(cam->getX());//this->visibleSizeInt;
	GLint y = static_cast<GLint>(cam->getY());//this->visibleSizeInt;

	//verific daca sectoarele adiacente se afla in visitedSectors, daca nu le populez
	
	up = true;
	down = true;
	left = true;
	right = true;
	up_left=true;
	up_right=true;
	down_left=true;
	down_right=true;
	
	for (unsigned int i=0; i<this->visitedSectors.size(); i++){
		

		GLfloat visitedX=visitedSectors.at(i)->x;
		GLfloat visitedY=visitedSectors.at(i)->y;

		if (x/visibleSizeInt==visitedX && y/visibleSizeInt+1==visitedY){
			
			up = false;
		
			//break;
		}
		if (x/visibleSizeInt==visitedX && y/visibleSizeInt-1==visitedY){
			
			down = false;
		
		//	break;
		}
		if (x/visibleSizeInt-1==visitedX && y/visibleSizeInt==visitedY){
			
			left = false;
		
		//	break;
		}
		if (x/visibleSizeInt+1==visitedX && y/visibleSizeInt==visitedY){
			
			right = false;
		
	//		break;
		}
		if (x/visibleSizeInt-1==visitedX && y/visibleSizeInt+1==visitedY){
			
			up_left = false;
		
	//		break;
		}
		if (x/visibleSizeInt+1==visitedX && y/visibleSizeInt+1==visitedY){
			
			up_right = false;
		
	//		break;
		}
		if (x/visibleSizeInt-1==visitedX && y/visibleSizeInt-1==visitedY){
			
			down_left = false;
		
	//		break;
		}
		if (x/visibleSizeInt+1==visitedX && y/visibleSizeInt-1==visitedY){
			
			down_right = false;
		
	//		break;
		}

	}
	if (up){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt,y/visibleSizeInt+1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (down){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt,y/visibleSizeInt-1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (left){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt-1,y/visibleSizeInt);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (right){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt+1,y/visibleSizeInt);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (up_left){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt-1,y/visibleSizeInt+1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (up_right){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt+1,y/visibleSizeInt+1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (down_left){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt-1,y/visibleSizeInt-1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}
	if (down_right){
		//adaug un nou sector in lista de vizitate si il populez

		sector *s = PopulateSector(x/visibleSizeInt+1,y/visibleSizeInt-1);
		map[s->x*1000+s->y] = s;
		visitedSectors.push_back(s);
		
	}


	//	}) << std::endl;
	

}

bool LayerManager::collisionDetectorAABB(GLfloat cxA, GLfloat cyA, GLfloat wA, GLfloat hA, GLfloat cxB, GLfloat cyB, GLfloat wB, GLfloat hB ){
	GLfloat xA, yA, XA, YA, xB, yB, XB, YB;
	
	xA = cxA - wA/2;
	XA = cxA + wA/2;
	xB = cxB - wB/2;
	XB = cxB + wB/2;
	yA = cyA - wA/2;
	YA = cyA + wA/2;
	yB = cyB - hB/2;
	YB = cyB + hB/2;

	if (XA<xB || XB<xA || YA<yB || YB<yA){
		return false;
	}
	return true;

}

bool LayerManager::compareDepths(object* left, object* right){
		return left->depth > right->depth;
}
