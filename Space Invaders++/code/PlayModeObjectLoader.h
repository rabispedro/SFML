#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include"GameObject.h"
#include"BlueprintObjectParser.h"
#include"GameObjectFactoryPlayMode.h"

using namespace std;
using namespace sf;

class PlayModeObjectLoader{
	private:
		BlueprintObjectParser m_BOP;
		GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;

	public:
		void loadGameObjectsForPlayMode(string pathToFile, vector<GameObject>& mGameObjects);
};