#include<SFML/Graphics.hpp>
#include"Player.h"
#include"ZombieArena.h"
#include"TextureHolder.h"

#define TITLE "Zombie Arena"

using namespace std;
using namespace sf;

int main(){
	//	Here is the instance of TextureHolder
	TextureHolder holder;
	
	//	The Game will always be in one of four States
	enum class State{PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
	
	//	Start with the GAME_OVER State
	State state = State::GAME_OVER;
	
	//	Get the Screen Resolution and create a SFML Window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
	RenderWindow window(VideoMode(resolution.x, resolution.y), TITLE, Style::Default);
	
	//	Create a SFML View for the Main action
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));
	
	//	Here is our clock for timing everything
	Clock clock;
	
	//	How long has the PLAYING State been active
	Time gameTimeTotal;
	
	//	Where is the Mouse in relation to the World Coordinates
	Vector2f mouseWorldPosition;
	
	//	Where is the Mouse in relation to the Screen Coordinates
	Vector2i mouseScreenPosition;
	
	//	Create an Instance of the Player Class
	Player player;
	
	//	The Boundaries of the Arena
	IntRect arena;
	
	//	Create a Background
	VertexArray background;
	
	//	Load the Texture for our Background Vertex Array
	Texture textureBackground = TextureHolder::GetTexture("../graphics/background_sheet.png");
	
	
	//	Prepare for a Horde of Zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = nullptr;
	
	//	The Main Game Loop
	while(window.isOpen()){
		/*
		*	HANDLE PLAYER's INPUT
		*/
		//	Handle Events by Polling
		Event event;
		while(window.pollEvent(event)){
			//	Check Exit Window
			if(event.type == Event::Closed){
				window.close();
			}
			
			if(event.type == Event::KeyPressed){
				//	Pause the Game while Playing
				if(event.key.code == Keyboard::Return && state == State::PLAYING){
					state = State::PAUSED;
				}else if(event.key.code == Keyboard::Return && state == State::PAUSED){
					//	Restart while Paused
					state = State::PLAYING;
					//	Reset the Clock so there isn't a frame jump
					clock.restart();
				}else if(event.key.code == Keyboard::Return && state == State::GAME_OVER){
					//	Start a New Game while in GAME_OVER State
					state = State::LEVELING_UP;
				}
				if(state == State::PLAYING){
					//	stuff
					
					
					
				}
			}
		}//	while(window.pollEvent(event))
		
		//	Handle the Player's Quitting
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		
		//	Handle WASD while Playing
		if(state == State::PLAYING){
			//	Handle the pressing and releasing of the WASD keys
			if(Keyboard::isKeyPressed(Keyboard::W)){
				player.moveUp();
			}else{
				player.stopUp();
			}
			if(Keyboard::isKeyPressed(Keyboard::S)){
				player.moveDown();
			}else{
				player.stopDown();
			}
			if(Keyboard::isKeyPressed(Keyboard::A)){
				player.moveLeft();
			}else{
				player.stopLeft();
			}
			if(Keyboard::isKeyPressed(Keyboard::D)){
				player.moveRight();
			}else{
				player.stopRight();
			}
		}//	End WASD while Playing
		
		//	Handle the LEVELING_UP State
		if(state == State::LEVELING_UP){
			//	Handle the Player Leveling Up
			if(event.key.code == Keyboard::Num1){
				state = State::PLAYING;
			}
			if(event.key.code == Keyboard::Num2){
				state = State::PLAYING;
			}
			if(event.key.code == Keyboard::Num3){
				state = State::PLAYING;
			}
			if(event.key.code == Keyboard::Num4){
				state = State::PLAYING;
			}
			if(event.key.code == Keyboard::Num5){
				state = State::PLAYING;
			}
			if(event.key.code == Keyboard::Num6){
				state = State::PLAYING;
			}
			
			if(state == State::PLAYING){
				//	Prepare the Level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;
				
				//	Pass the Vertex Array by Reference to the createBackground function
				int tileSize = createBackground(background, arena);
				
				
				
				//	Spawn the Player in the middle of the Arena
				player.spawn(arena, resolution, tileSize);
				
				//	Create a Horde of Zombies
				numZombies = 10;
				
				//	Delete the previously allocated memory (if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;
				
				
				//	Reset the Clock so there ins't a frame jump
				clock.restart();
			}
		}//	End Leveling Up
		
		/*
		*	UPDATE THE FRAME
		*/
		
		if(state == State::PLAYING){
			//	Update the DeltaTime
			Time dt = clock.restart();
			
			//	Update the local Game Time
			gameTimeTotal += dt;
			
			//	Make a decimal fraction of 1 from the DeltaTime
			float dtAsSeconds = dt.asSeconds();
			
			//	Where is the Mouse Pointer
			mouseScreenPosition = Mouse::getPosition();
			
			//	Convert Mouse Position to World Coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
			
			//	Update the Player
			player.update(dtAsSeconds, Mouse::getPosition());
			
			//	Make a note of the Player New Position
			Vector2f playerPosition(player.getCenter());
			
			//	Make the View Centre around the Player
			mainView.setCenter(player.getCenter());
			
			//	Loop through each Zombie and Update them
			for(int i=0; i<numZombies; i++){
				if(zombies[i].isAlive()){
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}
			
		}//	if(state == State::PLAYING)
		
		
		
		/*
		*	DRAW THE SCENE
		*/
		
		if(state == State::PLAYING){
			window.clear();
			
			//	Set the mainView to be displayed in the Window and Draw everything related to it
			window.setView(mainView);
			
			//	Draw the Background
			window.draw(background, &textureBackground);
			
			//	Draw the Zombies
			for(int i=0; i<numZombies; i++){
				window.draw(zombies[i].getSprite());
			}
			
			//	Draw the player
			window.draw(player.getSprite());
		}
		if(state == State::LEVELING_UP){
			
		}
		if(state == State::PAUSED){
			
		}
		if(state == State::GAME_OVER){
			
		}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		window.display();
	}//	while(window.isOpen())
	
	//	Delete the previously allocated memory (if its exists)
	delete[] zombies;
	
	return 0;
}
