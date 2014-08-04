#include "TextureManager.h"
/*
	dureaza mai mult pana incarca texturile dar pe parcurs pentru a ajunge la o textura
	nu e necesara decat parcurgerea unui vector de aproximativ 50 de elemente.

*/


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
	fid.file="t_score.png";
	fid.id = texture_id::TEXT_SCORE;					
	images[22] = fid;
	fid.file="t_kills.png";
	fid.id = texture_id::TEXT_KILLS;		
	images[23] = fid;
	fid.file="t_hp.png";
	fid.id = texture_id::TEXT_HP;		
	images[24] = fid;
	fid.file="num_0.png";
	fid.id = texture_id::NUM0;					
	images[25] =fid;
	fid.file="num_1.png";
	fid.id = texture_id::NUM1;					
	images[26] =fid;
	fid.file="num_2.png";
	fid.id = texture_id::NUM2;					
	images[27] = fid;
	fid.file="num_3.png";
	fid.id = texture_id::NUM3;					
	images[28] =fid;
	fid.file="num_4.png";
	fid.id = texture_id::NUM4;			
	images[29] = fid;
	fid.file="num_5.png";
	fid.id = texture_id::NUM5;					
	images[30] = fid;
	fid.file="num_6.png";
	fid.id = texture_id::NUM6;					
	images[31] = fid;
	fid.file="num_7.png";
	fid.id = texture_id::NUM7;				
	images[32] =fid;
	fid.file="num_8.png";
	fid.id = texture_id::NUM8;					
	images[33] = fid;
	fid.file="num_9.png";
	fid.id = texture_id::NUM9;					
	images[34] = fid;
	
	fid.file="green_planet.png";
	fid.id=texture_id::PLANET_GREEN;
	images[35] = fid;

	fid.file="jupiter.png";
	fid.id=texture_id::PLANET_JUPITER;
	images[36] = fid;

	fid.file="k_planet.png";
	fid.id=texture_id::PLANET_K;
	images[37] = fid;

	fid.file="lava_planet.png";
	fid.id=texture_id::PLANET_LAVA;
	images[38] = fid;

	fid.file= "planet_mars.png";
	fid.id=texture_id::PLANET_MARS;
	images[39] = fid;

	fid.file = "planet_pluto.png";
	fid.id=texture_id::PLANET_PLUTO;
	images[40]=fid;

	fid.file = "planet_neptune.png";
	fid.id=texture_id::PLANET_NEPTUNE;
	images[41]=fid;

	fid.file="planet1.png";
	fid.id=texture_id::PLANET_ONE;
	images[42]=fid;

	fid.file="planet_io.png";
	fid.id=texture_id::PLANET_IO;
	images[43]=fid;

	fid.file="planet_ceres.png";
	fid.id=texture_id::PLANET_CERES;
	images[44]=fid;

	fid.file="planet_water.png";
	fid.id=texture_id::PLANET_WATER;
	images[45]=fid;

	fid.file="meteor1.png";
	fid.id=texture_id::METEOR_1;
	images[46] = fid;

	fid.file="meteor2.png";
	fid.id=texture_id::METEOR_2;
	images[47] = fid;

	fid.file="meteor3.png";
	fid.id=texture_id::METEOR_3;
	images[48] = fid;

	fid.file="meteor4.png";
	fid.id=texture_id::METEOR_4;
	images[49] = fid;

	fid.file="meteor5.png";
	fid.id=texture_id::METEOR_5;
	images[50] = fid;

	fid.file="meteor6.png";
	fid.id=texture_id::METEOR_6;
	images[51] = fid;

	fid.file="venus.png";
	fid.id=texture_id::PLANET_VENUS;
	images[52] = fid;

	fid.file="star.png";
	fid.id=texture_id::PLANET_STAR;
	images[53] = fid;

	fid.file="powerup1.png";
	fid.id=texture_id::POWERUP_1;
	images[54] = fid;

	fid.file="powerup2.png";
	fid.id=texture_id::POWERUP_2;
	images[55] = fid;

	fid.file="powerup3.png";
	fid.id=texture_id::POWERUP_3;
	images[56] = fid;

	fid.file="space_ship_up_1.png";
	fid.id=texture_id::ADV_1;
	images[57] = fid;

	fid.file="space_ship_up_2.png";
	fid.id=texture_id::ADV_2;
	images[58] = fid;

	fid.file="space_ship_up_3.png";
	fid.id=texture_id::ADV_3;
	images[59] = fid;

	fid.file="space_ship_up_4.png";
	fid.id=texture_id::ADV_4;
	images[60] = fid;

	fid.file="space_ship_up_5.png";
	fid.id=texture_id::ADV_5;
	images[61] = fid;

	fid.file="space_ship_up_6.png";
	fid.id=texture_id::ADV_6;
	images[62] = fid;

	fid.file="space_ship_up_7.png";
	fid.id=texture_id::ADV_7;
	images[63] = fid;

	fid.file="space_ship_up_8.png";
	fid.id=texture_id::ADV_8;
	images[64] = fid;

	


	fid.file="space_ship_left_1.png";
	fid.id=texture_id::LEFT_1;
	images[65] = fid;

	fid.file="space_ship_left_2.png";
	fid.id=texture_id::LEFT_2;
	images[66] = fid;

	fid.file="space_ship_left_3.png";
	fid.id=texture_id::LEFT_3;
	images[67] = fid;

	fid.file="space_ship_left_4.png";
	fid.id=texture_id::LEFT_4;
	images[68] = fid;

	fid.file="space_ship_left_5.png";
	fid.id=texture_id::LEFT_5;
	images[69] = fid;

	fid.file="space_ship_left_6.png";
	fid.id=texture_id::LEFT_6;
	images[70] = fid;

	fid.file="space_ship_left_7.png";
	fid.id=texture_id::LEFT_7;
	images[71] = fid;

	fid.file="space_ship_left_8.png";
	fid.id=texture_id::LEFT_8;
	images[72] = fid;

	



	fid.file="space_ship_right_1.png";
	fid.id=texture_id::RIGHT_1;
	images[73] = fid;

	fid.file="space_ship_right_2.png";
	fid.id=texture_id::RIGHT_2;
	images[74] = fid;

	fid.file="space_ship_right_3.png";
	fid.id=texture_id::RIGHT_3;
	images[75] = fid;

	fid.file="space_ship_right_4.png";
	fid.id=texture_id::RIGHT_4;
	images[76] = fid;

	fid.file="space_ship_right_5.png";
	fid.id=texture_id::RIGHT_5;
	images[77] = fid;

	fid.file="space_ship_right_6.png";
	fid.id=texture_id::RIGHT_6;
	images[78] = fid;

	fid.file="space_ship_right_7.png";
	fid.id=texture_id::RIGHT_7;
	images[79] = fid;

	fid.file="space_ship_right_8.png";
	fid.id=texture_id::RIGHT_8;
	images[80] = fid;

	fid.file="powerup_speed_active.png";
	fid.id=texture_id::PWUP_1;
	images[81] = fid;

	fid.file="powerup_instagib_active.png";
	fid.id=texture_id::PWUP_2;
	images[82] = fid;

	fid.file = "rocket3.png";
	fid.id = texture_id::ROCKET_2;
	images[83] = fid;

	fid.file = "rocket4.png";
	fid.id = texture_id::ROCKET_3;
	images[84] = fid;

	fid.file = "rocket5.png";
	fid.id = texture_id::ROCKET_4;
	images[85] = fid;

	fid.file = "help70.png";
	fid.id = texture_id::HELP;
	images[86] = fid;


	fid.file="rocket_light.png";
	fid.id = texture_id::ROCKET;										
	images[87] = fid;
	
	
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
						textureElements[te.ID] = te;
						
						c++;
						break;
					}
				}
		
				
		}

		
	

}
/*
	incarc coordonatele asociate texturii cerute
*/
void TextureManager::getTexture(texture_id type, GLuint textureArray){
	
	
	//o abordare mai rapida
	textureElement e=textureElements[type];   
	for (int t=0; t<8; t++){
		uvCoords[t] = e.uvs[t];

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


