#include "TextureManager.h"



TextureManager::TextureManager(){
	//first we generate the images array 

	fileId fid;
	fid.file="space_ship_up.png";
	fid.id = texture_id::PLAYER;
	images[0] = fid;
	fid.file="scout.png";
	fid.id = texture_id::SCOUT;			
	images[1] = fid;
	fid.file= "basic.png";
	fid.id = texture_id::BASIC;				
	images[2] = fid;
	fid.file="assault.png";
	fid.id = texture_id::ASSAULT;				
	images[3] = fid;
	fid.file="exp1.png";
	fid.id = texture_id::EXP1;				
	images[4] = fid;
	fid.file="exp2.png";
	fid.id = texture_id::EXP2;				
	images[5] = fid;
	fid.file="exp3.png";
	fid.id = texture_id::EXP3;				
	images[6] = fid;
	fid.file="exp4.png";
	fid.id = texture_id::EXP4;					
	images[7] = fid;
	fid.file="exp5.png";
	fid.id = texture_id::EXP5;				
	images[8]= fid;
	fid.file="exp6.png";
	fid.id = texture_id::EXP6;					
	images[9] = fid;
	fid.file="exp7.png";
	fid.id = texture_id::EXP7;				
	images[10] = fid;
	fid.file="exp8.png";
	fid.id = texture_id::EXP8;				
	images[11] = fid;
	fid.file="exp9.png";
	fid.id = texture_id::EXP9;					
	images[12] = fid;
	fid.file="exp10.png";
	fid.id = texture_id::EXP10;					
	images[13] = fid;
	fid.file="exp11.png";
	fid.id = texture_id::EXP11;					
	images[14] =fid;
	fid.file="exp12.png";
	fid.id = texture_id::EXP12;				
	images[15] = fid;
	fid.file="exp13.png";
	fid.id = texture_id::EXP13;					
	images[16] = fid;
	fid.file="exp14.png";
	fid.id = texture_id::EXP14;					
	images[17] = fid;
	fid.file="exp15.png";
	fid.id = texture_id::EXP15;					
	images[18] = fid;
	fid.file="exp16.png";
	fid.id = texture_id::EXP16;				
	images[18] = fid;
	fid.file="space2.jpg";
	fid.id = texture_id::SPACE;					
	images[19] = fid;
	fid.file="victory_screen.png";
	fid.id = texture_id::VIC_SCREEN;					
	images[20] = fid;
	fid.file="defeat_screen.png";
	fid.id = texture_id::DEF_SCREEN;					
	images[21] = fid;
	fid.file="text_score.png";
	fid.id = texture_id::TEXT_SCORE;					
	images[22] = fid;
	fid.file="text_enemies.png";
	fid.id = texture_id::TEXT_ENEMIES;					
	images[23] = fid;
	fid.file="num_0.png";
	fid.id = texture_id::NUM0;					
	images[24] =fid;
	fid.file="num_1.png";
	fid.id = texture_id::NUM1;					
	images[25] =fid;
	fid.file="num_2.png";
	fid.id = texture_id::NUM2;					
	images[26] = fid;
	fid.file="num_3.png";
	fid.id = texture_id::NUM3;					
	images[27] =fid;
	fid.file="num_4.png";
	fid.id = texture_id::NUM4;			
	images[28] = fid;
	fid.file="num_5.png";
	fid.id = texture_id::NUM5;					
	images[29] = fid;
	fid.file="num_6.png";
	fid.id = texture_id::NUM6;					
	images[30] = fid;
	fid.file="num_7.png";
	fid.id = texture_id::NUM7;				
	images[31] =fid;
	fid.file="num_8.png";
	fid.id = texture_id::NUM8;					
	images[32] = fid;
	fid.file="num_9.png";
	fid.id = texture_id::NUM9;					
	images[33] = fid;
	
	fid.file="green_planet.png";
	fid.id=texture_id::PLANET_GREEN;
	images[34] = fid;

	fid.file="jupiter.png";
	fid.id=texture_id::PLANET_JUPITER;
	images[35] = fid;

	fid.file="k_planet.png";
	fid.id=texture_id::PLANET_K;
	images[36] = fid;

	fid.file="lava_planet.png";
	fid.id=texture_id::PLANET_LAVA;
	images[37] = fid;

	fid.file= "planet_mars.png";
	fid.id=texture_id::PLANET_MARS;
	images[38] = fid;

	fid.file = "planet_pluto.png";
	fid.id=texture_id::PLANET_PLUTO;
	images[39]=fid;

	fid.file = "planet_neptune.png";
	fid.id=texture_id::PLANET_NEPTUNE;
	images[40]=fid;

	fid.file="planet1.png";
	fid.id=texture_id::PLANET_ONE;
	images[41]=fid;

	fid.file="meteor1.png";
	fid.id=texture_id::METEOR_1;
	images[42] = fid;

	fid.file="meteor2.png";
	fid.id=texture_id::METEOR_2;
	images[43] = fid;

	fid.file="meteor3.png";
	fid.id=texture_id::METEOR_3;
	images[44] = fid;

	fid.file="meteor4.png";
	fid.id=texture_id::METEOR_4;
	images[45] = fid;

	fid.file="meteor5.png";
	fid.id=texture_id::METEOR_5;
	images[46] = fid;

	fid.file="meteor6.png";
	fid.id=texture_id::METEOR_6;
	images[47] = fid;

	fid.file="venus.png";
	fid.id=texture_id::PLANET_VENUS;
	images[48] = fid;

	fid.file="star.png";
	fid.id=texture_id::PLANET_STAR;
	images[49] = fid;



	fid.file="rocket_light.png";
	fid.id = texture_id::ROCKET;										
	images[50] = fid;
	
	
	this->LoadTextures();
	this->getAtlas();
	this->mapIt();


	this->Bind();

	
}

void TextureManager::getAtlas(){
	xml_document<> doc;
	std::ifstream file("../data/sprites.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);


	xml_node<> *pRoot = doc.first_node("TextureAtlas");

	for(xml_node<> *pNode=pRoot->first_node("SubTexture"); pNode; pNode=pNode->next_sibling())
	{
	
		
		std::string name =pNode->first_attribute("name")->value();
		//std::cout << name << std::endl;
		int x =atoi(pNode->first_attribute("x")->value());
		//std::cout << x << std::endl;
		int y =atoi(pNode->first_attribute("y")->value());
		//std::cout << y << std::endl;
		int width =atoi(pNode->first_attribute("width")->value());
		//std::cout << width << std::endl;
		int height =atoi(pNode->first_attribute("height")->value());
		//std::cout << height << std::endl;
		subtexture st;
		st.name=name;
		st.x=x;
		st.y=y;
		st.width=width;
		st.height=height;
		textureAtlas.push_back(st);
	}



}

TextureManager::~TextureManager(){

}

void TextureManager::LoadTextures(){
	Texture t;
	t.loadTexture("../data/sprites.png");
	
	this->texture = t.getTextureID();

}

void TextureManager::mapIt(){
	

		GLfloat x=0;
		GLfloat y=0;
		GLfloat width=0;
		GLfloat height=0;
	//incarc intr-un array de structuri un identificator si coordonatele fiecarei texturi
		int c=0;
		for (unsigned int i=0; i<this->textureAtlas.size(); i++){
		
				//asta e!
				x = static_cast<GLfloat>(textureAtlas.at(i).x);
				y = static_cast<GLfloat>(textureAtlas.at(i).y);
				width =  static_cast<GLfloat>(textureAtlas.at(i).width);
				height =  static_cast<GLfloat>(textureAtlas.at(i).height);

				

				//trecem x,y,width,height in spatiul UV
				x=x/4096;
				y=y/4096;
				width=width/4096;
				height=height/4096;
	
				//obtinem matricea cu coordonatele
				GLfloat coords[8] = {			
					x, y+height,
					x, y,
					x+width, y,
					x+width, y+height
				};
			
			
				for (unsigned int j =0; j<static_cast<unsigned int>(texture_id::ROCKET); j++){
					if (strcmp(images[j].file.c_str(), textureAtlas.at(i).name.c_str())==0){
						//adauga in noua lista 
						textureElement te;
						te.ID=images[j].id;
						for (int t=0; t<8; t++){
							te.uvs[t] = coords[t];

						}
						textureElements.push_back(te);
						
						c++;
						break;
					}
				}
				
			//now we test it
			/*	for (unsigned int v = 0; v<textureElements.size(); v++){
					std::cout<< textureElements.at(v).ID << std::endl;
					std::cout<< textureElements.at(v).uvs[0] <<" " <<  textureElements.at(v).uvs[1]  << std::endl;
					std::cout<< textureElements.at(v).uvs[2] <<" " <<  textureElements.at(v).uvs[3] << std::endl;
					std::cout<< textureElements.at(v).uvs[4] <<" " <<  textureElements.at(v).uvs[5] << std::endl;
					std::cout<< textureElements.at(v).uvs[6] <<" " <<  textureElements.at(v).uvs[7]  <<std::endl;
				}*/
				
		}
		std::cout << "Elements "<< c << std::endl;
		
	

}
/*
	incarc coordonatele asociate texturii cerute
*/
void TextureManager::getTexture(texture_id type, GLuint textureArray){
	

	for (unsigned int i=0; i<texture_id::ROCKET; i++){
		if (type == textureElements.at(i).ID){
				//asta e!
			
					
				for (int t=0; t<8; t++){
							uvCoords[t] = textureElements.at(i).uvs[t];

				}
				break;
			}

		}
		

		//activez bufferul
		glBindBuffer(GL_ARRAY_BUFFER,textureArray);

		//incarca bufferul pe GPU
		glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(uvCoords[0]), uvCoords, GL_STATIC_DRAW);

}

void TextureManager::Bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}


