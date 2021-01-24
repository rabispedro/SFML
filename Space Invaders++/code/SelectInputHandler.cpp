#include"SelectInputHandler.h"
#include"SoundEngine.h"
#include"WorldState.h"
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

int WorldState::WAVE_NUMBER;

void SelectInputHandler::handleKeyPressed(Event& event, RenderWindow& window){
	//	Quit the game
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		//	DEBUG
		cout<<"Escado!\n";
		SoundEngine::playClick();
		//	DEGUB
		window.close();
	}
}

void SelectInputHandler::handleLeftClick(string& buttonInteractedWith, RenderWindow& window){
	cout<<"Clicado em algo!\n";
	if(buttonInteractedWith == "Play"){
		cout<<"Clicado em Play!\n";
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
	}

	if(buttonInteractedWith == "Quit"){
		cout<<"Clicado em Quit!\n";
		SoundEngine::playClick();
		window.close();
	}
}