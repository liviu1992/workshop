#include "LayerManager.h"
	LayerManager::LayerManager(Player* player){
		this->player = player;

	}
	void LayerManager::Add(Sprite* sprite, GLfloat depth){
		layerComponent component;
		component.sprite=sprite;
		component.depth=depth;
		layer.push_back(component);

		//acum sortam noua lista
		std::sort(layer.begin(), layer.end(), &LayerManager::compareDepths);

	}
	void LayerManager::Update(){
		//the close layer
		for (unsigned int i=0; i<layer.size(); i++){
			if (glm::distance(this->player->getSprite()->getPosition(), layer.at(i).sprite->getPosition())<8.f){
				layer.at(i).sprite->move(this->player->getPhysics()->GetX()*layer.at(i).depth, this->player->getPhysics()->GetY()*layer.at(i).depth);
				layer.at(i).sprite->getMatrix()->updateMatrix();
			}
	
		}
		
		

	}
	bool LayerManager::compareDepths(layerComponent left, layerComponent right){
		return left.depth > right.depth;
	}

	void LayerManager::Draw(){
		for (unsigned int i=0; i<layer.size(); i++){

			if (glm::distance(this->player->getSprite()->getPosition(), layer.at(i).sprite->getPosition())<8.f){
				layer.at(i).sprite->draw();
			}
		}
	}

	LayerManager::~LayerManager(){
		for (unsigned int i=0; i<this->layer.size(); i++){
			delete layer.at(i).sprite;
			
		}
		
	}