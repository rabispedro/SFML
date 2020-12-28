#pragma once
#include"InputHandler.h"

using namespace std;
using namespace sf;

class GameScreen;

class GameInputHandler : public InputHandler{
	public:
		void initialise();
		void handleGamepad() override;
		void handleKeyPressed(Event& event, RenderWindow& window) override;
		void handleKeyReleased(Event& event, RenderWindow& window) override;
};