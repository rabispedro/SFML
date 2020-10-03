#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Pickup{
	private:
		//	Start value for Health Pickups
		const int HEALTH_START_VALUE = 50;
		const int AMMO_START_VALUE = 12;
		const int START_WAIT_TIME = 10;
		const int START_SECONDS_TO_LIVE = 5;
		
		//	The Sprite that represents this pickup
		Sprite m_Sprite;
		
		//	The Arena it exists in
		IntRect m_Arena;
		
		//	How much is this Pickup worth?
		int m_Value;
		
		//	What type of Pickup is this?
		//	1 = Health
		//	2 = Ammo
		
		int m_Type;
		
		//	Handle spawning and disappearing
		bool m_Spawned;
		float m_SecondsSinceSpawn;
		float m_SecondsSinceDeSpawn;
		float m_SecondsToLive;
		float m_SecondsToWait;
	
	public:
		Pickup(int type);
		
		//	Prepare a new Pickup
		void setArena(IntRect arena);
		
		void spawn();
		
		//	Check the Position of a Pickup
		FloatRect getPosition();
		
		//	Get the Sprite for Drawing
		Sprite getSprite();
		
		//	Let the Pickup Update Itself each frame
		void update(float elapsedTime);
		
		//	Is this Pickup currently spawned?
		bool isSpawned();
		
		//	Get the goodness from the Pickup
		int gotIt();
		
		//	Update the value of each Pickup
		void upgrade();
};
