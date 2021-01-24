#pragma once
#include<SFML/Graphics.hpp>
#include"Screen.h"
#include"GameInputHandler.h"
#include"GameOverInputHandler.h"
#include"BulletSpawner.h"
#include"PhysicsEnginePlayMode.h"

using namespace std;
using namespace sf;

class GameScreen : public Screen, public BulletSpawner{
	private:
		ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
		shared_ptr<GameInputHandler> m_GIH;
		PhysicsEnginePlayMode m_PhysicsEnginePlayMode;

		Texture m_BackgroundTexture;
		Sprite m_BackgroundSprite;

		int m_NumberInvadersInWorldFile = 0;
		vector<int> m_BulletObjectLocations;
		int m_NextBullet = 0;
		bool m_WaitingToSpawnBulletForPlayer = false;
		bool m_WaitingToSpawnBulletForInvader = false;
		Vector2f m_PlayerBulletSpawnLocation;
		Vector2f m_InvaderBulletSpawnLocation;
		Clock m_BulletClock;

	public:
		static bool m_GameOver;

		GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
		void initialise() override;
		void virtual update(float fps);
		void virtual draw(RenderWindow& window);

		BulletSpawner* getBulletSpawner();

		/*
		*	From BulletSpawner INTERFACE
		*/
		void BulletSpawner::spawnBullet(Vector2f spawnLocation, bool forPlayer){
			if(forPlayer){
				Time elapsedTime = m_BulletClock.getElapsedTime();
				if(elapsedTime.asMilliseconds() > 500){
					m_PlayerBulletSpawnLocation.x = spawnLocation.x;
					m_PlayerBulletSpawnLocation.y = spawnLocation.y;
					m_WaitingToSpawnBulletForPlayer = true;
					m_BulletClock.restart();
				}
			}else{
					m_InvaderBulletSpawnLocation.x = spawnLocation.x;
					m_InvaderBulletSpawnLocation.y = spawnLocation.y;
					m_WaitingToSpawnBulletForInvader = true;
			}
		}


};