#include<sstream>
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"ZombieArena.h"
#include"TextureHolder.h"
#include"Bullet.h"
#include"Pickup.h"

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
	
	//	100 Bullets Should do
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1.0f;
	
	//	When was the fire button last pressed?
	Time lastPressed;
	
	//	Hide the mouse pointer and replace it with Crosshair
	window.setMouseCursorVisible(false);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("../graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);
	
	//	Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);
	
	//	About the game
	int score = 0;
	int hiScore = 0;
	
	//	For the Home/Game Over Screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("../graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.scale((resolution.x/1920), (resolution.y/1080));
	spriteGameOver.setPosition(0,0);
	
	//	Create a view for the HUD
	View hudView(FloatRect(0, 0, resolution.x, resolution.y));
	
	//	Create a Sprite for the Ammo Icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("../graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(10, 698);
	
	//	Load the Font
	Font font;
	font.loadFromFile("../fonts/zombiecontrol.ttf");
	
	//	Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(75);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(291, 344);
	pausedText.setString("Press Enter to continue!");
	
	//	Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(286, 304);
	gameOverText.setString("Press Enter to play");
	
	//	Leveling Up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(75);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(60, 145);
	stringstream levelUpStream;
	levelUpStream<<"1- Increase rate of fire\n"<<"2- Increase clip size (next reload)\n"<<"3- Increase max health\n"<<"4- Increase run speed\n"<<"5- More and better health pickups\n"<<"6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());
	
	//	Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(35);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(60, 713);
	
	//	Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 10);
	
	//	Hi Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(35);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1145, 10);
	stringstream hiScoreStream;
	hiScoreStream<<"Hi Score: "<<hiScore;
	hiScoreText.setString(hiScoreStream.str());
	
	//	Zombie remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(35);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(915, 713);
	zombiesRemainingText.setString("Zombies: 100");
	
	//	Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(35);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(1165, 713);
	waveNumberText.setString("Waves: 0");
	
	//	Health Bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(384, 698);
	
	//	Debug HUD
	Text debugText;
	debugText.setFont(font);
	debugText.setCharacterSize(25);
	debugText.setFillColor(Color::White);
	debugText.setPosition(20, 220);
	ostringstream ss;
	
	//	When did the last update the HUD happen?
	int framesSinceLastHUDUpdate = 0;
	
	//	How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;
	
	
	
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
					//	Reloading
					if(event.key.code == Keyboard::R){
						if(bulletsSpare >= clipSize){
							//	Plenty of Bullets. Reload
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
						}else if(bulletsSpare > 0){
							//	Only few Bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
						}else{
							//	MORE HERE SOON?!
						}
					}
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
			
			//Fire a Bullet
			if(Mouse::isButtonPressed(Mouse::Left)){
				if(((gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds()) > (1000/fireRate)) && (bulletsInClip > 0)){
					//	Pass the center of the Player and the center of the Cross-Hair to the Shoot function
					bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
					currentBullet++;
					if(currentBullet > 99){
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					bulletsInClip--;
				}
			}//	if(Mouse::isButtonPressed(Mouse::Left))
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
				
				//	Configure the Pickups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);
				
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
			
			//	Set the Crosshair to the Mouse World Location
			spriteCrosshair.setPosition(mouseWorldPosition);
			
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
			
			//	Update any Bullets that are in-flight
			for(int i=0; i<100; i++){
				if(bullets[i].isInFlight()){
					bullets[i].update(dtAsSeconds);
				}
			}
			
			//	Update the Pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);
			
			//	COLLISION DETECTION
			//	Have any zombies been shot?
			for(int i=0; i<100; i++){
				for(int j=0; j<numZombies; j++){
					if((bullets[i].isInFlight()) && (zombies[j].isAlive())){
						if(bullets[i].getPosition().intersects(zombies[j].getPosition())){
							//	Stop the bullet
							bullets[i].stop();
							
							//	Register the Hit and see if it was a kill
							if(zombies[j].hit()){
								//	Not just a hit but a kill too
								score += 10;
								
								if(score > hiScore){
									hiScore = score;
								}
								
								numZombiesAlive--;
								
								//	When all the zombies are dead (again)
								if(numZombiesAlive == 0){
									state = State::LEVELING_UP;
								}
							}
						}
					}
				}
			}//	for(int i=0; i<100; i++)
			
			//	Have any zombies touched the Player?
			for(int i=0; i<numZombies; i++){
				if(player.getPosition().intersects(zombies[i].getPosition()) && zombies[i].isAlive()){
					if(player.hit(gameTimeTotal)){
						//	More here later
						
					}
					
					if(player.getHealth() <= 0){
						state = State::GAME_OVER;
					}
				}
			}//	for(int i=0; i<numZombies; i++)
			
			//	Has the Player touched health pickup?
			if((player.getPosition().intersects(healthPickup.getPosition())) && (healthPickup.isSpawned())){
				player.increaseHealthLevel(healthPickup.gotIt());
			}
			
			//	Has the Player touched ammo pickup?
			if((player.getPosition().intersects(ammoPickup.getPosition())) && (ammoPickup.isSpawned())){
				bulletsSpare += ammoPickup.gotIt();
			}
			
			//	Size up the Health Bar
			healthBar.setSize(Vector2f((player.getHealth()*3), 50));
			
			//	Increment the number of frames since the previous update
			framesSinceLastHUDUpdate++;
			
			//	Re-Calculate every fpsMeasurementFrameInterval frames
			if(framesSinceLastHUDUpdate > fpsMeasurementFrameInterval){
				//	Update the Game HUD Text
				stringstream ssAmmo;
				stringstream ssScore;
				stringstream ssHiScore;
				stringstream ssWave;
				stringstream ssZombiesAlive;
				
				//	Update the Ammo Text
				ssAmmo<<bulletsInClip<<"/"<<bulletsSpare;
				ammoText.setString(ssAmmo.str());
				
				//	Update the Score Text
				ssScore<<"Score: "<<score;
				scoreText.setString(ssScore.str());
				
				//	Update the High Score Text
				ssHiScore<<"Hi Score: "<<hiScore;
				hiScoreText.setString(ssHiScore.str());
				
				//	Update the Wave
				ssWave<<"Wave: "<<wave;
				waveNumberText.setString(ssWave.str());
				
				//	Update the Zombie Remaining Text
				ssZombiesAlive<<"Zombies: "<<numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());
				
				framesSinceLastHUDUpdate = 0;
			}//	if(framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
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
			
			//	Draw the Bullets
			for(int i=0; i<100; i++){
				if(bullets[i].isInFlight()){
					window.draw(bullets[i].getShape());
				}
			}
			
			//	Draw the player
			window.draw(player.getSprite());
			
			//	Draw the Pickups, if currently spawned
			if(ammoPickup.isSpawned()){
				window.draw(ammoPickup.getSprite());
			}
			if(healthPickup.isSpawned()){
				window.draw(healthPickup.getSprite());
			}
			
			//	Draw the Crosshair
			window.draw(spriteCrosshair);
			
			//	Switch to the HUD View
			window.setView(hudView);
			
			//	Draw all the HUD Elements
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
		}
		
		if(state == State::LEVELING_UP){
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}
		
		if(state == State::PAUSED){
			window.draw(pausedText);
		}
		
		if(state == State::GAME_OVER){
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		window.display();
	}//	while(window.isOpen())
	
	//	Delete the previously allocated memory (if its exists)
	delete[] zombies;
	
	return 0;
}
