#pragma once
#include<SFML/Graphics.hpp>
#include"ScreenManager.h"
#include"SoundEngine.h"

using namespace std;
using namespace sf;

class GameEngine{
	private:
		Clock m_Clock;
		Time m_DT;
		RenderWindow m_Window;

		unique_ptr<ScreenManager> m_ScreenManager;

		float m_FPS = 0.0f;
		Vector2f m_Resolution;

		void handleInput();
		void update();
		void draw();

	public:
		SoundEngine m_SoundEngine;

		GameEngine();
		void run();
};