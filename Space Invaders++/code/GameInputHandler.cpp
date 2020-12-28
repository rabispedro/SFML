#include"GameInputHandler.h"
#include"SoundEngine.h"
#include"GameScreen.h"

using namespace std;
using namespace sf;

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
}

void GameInputHandler::handleKeyReleased(Event& event, RenderWindow& window){

}