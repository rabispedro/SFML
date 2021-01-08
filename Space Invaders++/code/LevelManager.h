#pragma once
#include<vector>
#include<string>
#include"GameObject.h"
#include"GameObjectSharer.h"

using namespace std;
using namespace sf;

class LevelManager : public GameObjectSharer{
	private:
		vector<GameObject> m_GameObjects;
		const string WORLD_FOLDER = "../world";
		const string SLASH = "/";

		void runStartPhase();
		void activateAllGameObjects();

	public:
		vector<GameObject>& getGameObjects();
		void loadGameObjectsForPlayMode(string screenToLoad);

		/*
		*	From GameObjectSharer INTERFACE
		*/
		vector<GameObject>& GameObjectSharer::getGameObjectsWithGOS(){
			return m_GameObjects;
		}

		GameObject& GameObjectSharer::findFirstObjectWithTag(string tag){
			auto it = m_GameObjects.begin();
			auto end = m_GameObjects.end();

			for(it; it!=end; it++){
				if((*it).getTag() == tag){
					return (*it);
				}
			}
		}

		#ifdef debuggingErrors
		cout<<"LevelManager.h findFirstGameObjectWithTag() - TAG NOT FOUND ERROR!\n";
		#endif

		return m_GameObjects[0];
};