#pragma once
#include"InputHandler.h"

using namespace std;
using namespace sf;

class SelectInputHandler : public InputHandler{
	public:
		void handleKeyPressed(Event& event, RenderWindow& window) override;
		void handleLeftClick(string& buttonInteractedWith, RenderWindow& window) override;
};