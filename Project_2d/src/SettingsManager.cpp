#include "SettingsManager.h"
std::map<std::string, GLfloat> settings;


SettingsManager::SettingsManager(){
}

GLfloat SettingsManager::get(std::string key){
	return settings[key];
}

void SettingsManager::printAll(){
	std::map<std::string, GLfloat>::iterator map_iterator;

	for (map_iterator = settings.begin(); map_iterator!=settings.end(); ++map_iterator){
		std::cout << map_iterator->first << "   " << map_iterator->second << std::endl;
	}
}