
#include <rapidxml-1.13\rapidxml.hpp>
#include <rapidxml-1.13\rapidxml_utils.hpp>
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace rapidxml;

struct subtexture{
	std::string name;
	int x;
	int y;
	int width;
	int height;
};

int main(){
	std::vector<struct subtexture> textureAtlas;

	/*std::ifstream fin;
	fin.open("../data/texture.xml");
	if (!fin.is_open()){
		fin.close();
		std::cout << "Eroare la deschidere" << std::endl;
		return 1;
	}
	std::string source((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	fin.close();
	const char* shaderSource = source.c_str();

	std::cout << shaderSource << source.c_str();

	int i;
	std::cin >> i;
	*/
	xml_document<> doc;
	std::ifstream file("../data/texture.xml");
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
	std::cout << "Texture Atlas\n###################" << std::endl;
	for (int j=0; j<textureAtlas.size(); j++){
		subtexture s = textureAtlas.at(j);
		std::cout << s.name << std::endl;
		std::cout << s.x << std::endl;
		std::cout << s.y << std::endl;
		std::cout << s.width << std::endl;
		std::cout << s.height << std::endl;
	}


	int i;
	std::cin >> i;
	return 0;
}