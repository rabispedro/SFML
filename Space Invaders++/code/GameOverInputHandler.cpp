#include"GameOverInputHandler.h"
#include"SoundEngine.h"
#include"WorldState.h"
#include<iostream>

using namespace std;
using namespace sf;

void GameOverInputHandler::handleKeyPressed(Event& event, RenderWindow& window){
	if(event.key.code == Keyboard::Escape){
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleLeftClick(string& buttonInteractedWith, RenderWindow& window){
	if(buttonInteractedWith == "Play"){
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
	}else if(buttonInteractedWith == "Home"){
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("Select");
	}
}