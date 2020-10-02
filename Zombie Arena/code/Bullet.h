#pragma once
#include<SFML/Graphics.hpp>

using namespace std;
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
		float ;
		float ;
		
	
	public:
		
};

