#include"GameInputHandler.h"
#include"SoundEngine.h"
#include"GameScreen.h"

using namespace std;
using namespace sf;

class BulletSpawner;

void GameInputHandler::initialise(){

}

void GameInputHandler::handleGamepad(){

}

void GameInputHandler::handleKeyPressed(Event& event, RenderWindow& window){
	//	Handle key presses
	if(event.key.code == Keyboard::Escape){
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
	if(event.key.code == Keyboard::Left){
		m_PUC->moveLeft();
	}
	if(event.key.code == Keyboard::Right){
		m_PUC->moveRight();
	}
	if(event.key.code == Keyboard::Up){
		m_PUC->moveUp();
	}
	if(event.key.code == Keyboard::Down){
		m_PUC->moveDown();
	}

}

void GameInputHandler::handleKeyReleased(Event& event, RenderWindow& window){

}