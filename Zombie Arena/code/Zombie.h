#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;

class Zombie{
	private:
		//	How fast is each zombie type?
		const float BLOATER_SPEED = 40;
		const float CHASER_SPEED = 80;
		const float CRAWLER_SPEED = 20;
		
		//	How tough is each zombie type
		const float BLOATER_HEALTH = 5;
		const float CHASER_HEALTH = 1;
		const float CRAWLER_HEALTH = 3;
		
		//	Make each Zombie vary its Speed slightly
		const int MAX_VARIANCE = 30;
		const int OFFSET = (101-MAX_VARIANCE);
		
		//	Where is the Zombie
		Vector2f m_Position;
		
		//	A Sprite for the Zombie
		Sprite m_Sprite;
		
		//	How Fast can this one Run/Crawl
		float m_Speed;
		
		//	How much Health has it got?
		float m_Health;
		
		//	Is it still alive?
		bool m_Alive;
	
	public:
		//	Handle when a Bullet Hits a Zombie
		bool hit();
		
		//	Find out if the Zombie is Alive
		bool isAlive();
		
		//	Spawn a new Zombie
		void spawn(float startX, float startY, int type, int seed);
		
		//	Return a Rectangle that is the Position in the World
		FloatRect getPosition();
		
		//	Get a copy of the Sprite to Draw
		Sprite getSprite();
		
		//	Update the Zombie Each Frame
		void update(float elapsedTime, Vector2f playerLocation);
};

