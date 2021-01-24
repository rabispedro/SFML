#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

using namespace std;
using namespace sf;

class GameObject;

class GameObjectSharer{
	public:
		virtual vector<GameObject>& getGameObjectsWithGOS() = 0;
		virtual GameObject& findFirstObjectWithTag(string tag) = 0;
};