#pragma once
#include<vector>
#include"GameObject.h"
#include"GameObjectBlueprint.h"

using namespace std;
using namespace sf;

class GameObjectFactoryPlayMode{
	public:
		void buildGameObject(GameObjectBlueprint& bp, vector<GameObject>& mGameObjects);
};