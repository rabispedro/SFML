#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Player{
	private:
		const float START_SPEED = 200.0f;
		const float START_HEALTH = 100.0f;
		//	Where is the Player
		Vector2f m_Position;
		
		//	Player Sprite
		Sprite m_Sprite;
		
		//	Player Texture
		//	Changes soon
		Texture m_Texture;
		
		//	What is Screen Resolution
		Vector2f m_Resolution;
		
		//	What size is the current Arena
		IntRect m_Arena;
		
		//	How big is each tile of the arena
		int m_TileSize;
		
		//	Which direction(s) is the Player currently moving in
		bool m_UpPressed;
		bool m_DownPressed;
		bool m_LeftPressed;
		bool m_RightPressed;
		
		//	How much Health has the Player got?
		int m_Health;
		
		//	What is the maximum Health the Player can have
		int m_MaxHealth;
		
		//	When was the Player Last Hit
		Time m_LastHit;
		
		//	Speed in pixels per second
		float m_Speed;
	
	public:
		Player();
		
		void spawn(IntRect arena, Vector2f resolution, int tileSize);
		
		//	Call this at the End of every game
		void resetPlayerStats();
		
		//	Handle the PLayer getting hit by a zombie
		bool hit(Time timeHit);
		
		//	How long ago was the Player Last Hit
		Time getLastHitTime();
		
		//	Where is the Player
		FloatRect getPosition();
		
		//	Where is the center of the Player
		Vector2f getCenter();
		
		//	What angle is the Player facing
		float getRotation();
		
		//	Send a copy of the Sprite to the Main function
		Sprite getSprite();
		
		//	Move the Player
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		
		//	Stop the Player Moving in a specific direction
		void stopLeft();
		void stopRight();
		void stopUp();
		void stopDown();
		
		//	Update Every Frame
		void update(float elapsedTime, Vector2i mousePosition);
		
		//	Give the Player a Speed Boost
		void upgradeSpeed();
		
		//	Give the Player a Health Boost
		void upgradeHealth();
		
		//	Increase the maximum amount of Health the Player can have
		void increaseHealthLevel(int amount);
		
		//	How much health has the Player Currenctly got?
		int getHealth();
};
