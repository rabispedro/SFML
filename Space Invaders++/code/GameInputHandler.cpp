#include<SFML/Graphics.hpp>
#include"GameInputHandler.h"
#include"SoundEngine.h"
#include"GameScreen.h"

using namespace std;
using namespace sf;

class BulletSpawner;

void GameInputHandler::initialise(){

}

void GameInputHandler::handleGamepad(){
	float deadZone = 10.0f;
	float x = Joystick::getAxisPosition(0, Joystick::X);
	float y = Joystick::getAxisPosition(0, Joystick::Y);

	if(x < deadZone && x > -deadZone){
		x = 0;
	}
	if(y < deadZone && y > -deadZone){
		y = 0;
	}

	m_PUC->updateShipTravelWithController(x, y);

	//	Has the player pressed the B button?
	if(Joystick::isButtonPressed(0, 1)){
		m_ButtonPressed = true;
		
	}

	//	Has the player just released the B button?
	if(!Joystick::isButtonPressed(0, 1)){
		m_ButtonPressed = false;

		//	Shoot a bullet
		SoundEngine::playShoot();
		Vector2f spawnLocation;
		spawnLocation.x = (m_PTC->getLocation().x + m_PTC->getSize().x/2.0f);
		spawnLocation.y = m_PTC->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->spawnBullet(spawnLocation, true);
	}

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
	if(event.key.code == Keyboard::Left){
		m_PUC->stopLeft();
	}
	if(event.key.code == Keyboard::Right){
		m_PUC->stopRight();
	}
	if(event.key.code == Keyboard::Up){
		m_PUC->stopUp();
	}
	if(event.key.code == Keyboard::Down){
		m_PUC->stopDown();
	}
	if(event.key.code == Keyboard::Space){
		//	Shoot a bullet
		SoundEngine::playShoot();
		Vector2f spawnLocation;
		spawnLocation.x = (m_PTC->getLocation().x + m_PTC->getSize().x/2.0f);
		spawnLocation.y = m_PTC->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->spawnBullet(spawnLocation, true);
	}
}