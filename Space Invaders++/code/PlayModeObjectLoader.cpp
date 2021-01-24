#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include"PlayModeObjectLoader.h"
#include"ObjectTags.h"

using namespace std;
using namespace sf;

void PlayModeObjectLoader::loadGameObjectsForPlayMode(string pathToFile, vector<GameObject>& mGameObjects){
	ifstream reader(pathToFile);
	string lineFromFile;

	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;

	string value = "";

	while(getline(reader, lineFromFile)){
		if(lineFromFile.find(ObjectTags::START_OF_OBJECT) != string::npos){
			GameObjectBlueprint bp;
			m_BOP.parseNextObjectForBlueprint(reader, bp);
			m_GameObjectFactoryPlayMode.buildGameObject(bp, mGameObjects);
		}
	}
}