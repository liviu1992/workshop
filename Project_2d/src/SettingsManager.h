#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <map>
#include <string>
#include <GL/glew.h>
#include <iostream>

extern std::map<std::string, GLfloat> settings;

class SettingsManager{
public:	
	SettingsManager();
	GLfloat get(std::string key);
	void printAll();

};

#endif