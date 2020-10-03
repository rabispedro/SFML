#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Bullet{
	private:
		//	Where is the Bullet?
		Vector2f m_Position;
		
		//	What each Bullet looks like
		RectangleShape m_BulletShape;
		
		//	Is this Bullet currently whizzing through the air
		bool m_InFlight = false;
		
		//	How fast does a Bullet travels?
		float m_BulletSpeed = 1000;
		
		//	What fraction of 1 Pixel does the Bullet travel, Horizontally and Vertically each frame?
		//	These values will be derived from m_BulletSpeed
		float m_BulletDistanceX;
		float m_BulletDistanceY;
		
		//	Some boundaries so the Bullet doesn't fly forever
		float m_MaxX;
		float m_MinX;
		float m_MaxY;
		float m_MinY;
	
	public:
		//	The Constructor
		Bullet();
		
		//	Stop the bullet
		void stop();
		
		//	Returns the value of m_InFlight
		bool isInFlight();
		
		//	Launch a New Bullet
		void shoot(float startX, float startY, float targetX, float targetY);
		
		//	Tell the Calling Code where the Bullet is in the World
		FloatRect getPosition();
		
		//	Return the actual Shape (for Drawing)
		RectangleShape getShape();
		
		//	Update the Bullet Each Frame
		void update(float elapsedTime);
};

