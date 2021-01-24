#pragma once
#include<SFML/Graphics.hpp>
#include"UIPanel.h"

using namespace std;
using namespace sf;

class GameOverUIPanel : public UIPanel{
	private:
		void initialiseButtons();
	
	public:
		GameOverUIPanel(Vector2i res);
		void virtual draw(RenderWindow& window);
};