#pragma once
#include<SFML/Graphics.hpp>
#include"InputHandler.h"
#include"PlayerUpdateComponent.h"
#include"TransformComponent.h"

using namespace std;
using namespace sf;

class GameScreen;

class GameInputHandler : public InputHandler{
	private:
		shared_ptr<PlayerUpdateComponent> m_PUC;
		shared_ptr<TransformComponent> m_PTC;
		bool m_ButtonPressed = false;

	public:
		void initialise();
		void handleGamepad() override;
		void handleKeyPressed(Event& event, RenderWindow& window) override;
		void handleKeyReleased(Event& event, RenderWindow& window) override;
};