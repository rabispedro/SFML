//	Libraries
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<sstream>

//	Constants
#define WIDTH 1366
#define HEIGHT 768
#define TITLE "Timber!!!"

//	Abreviations
using namespace std;
using namespace sf;

//	Functions
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//	Where is the player/branch?
//	Left or Right
enum class side{ LEFT, RIGHT, NONE};
side branchesPositions[NUM_BRANCHES];

//	Where the game starts from
int main(){
	//	Create a Video Mode Object (Resolution Screen)
	VideoMode vm(WIDTH, HEIGHT);
	//	Create and open a Window for the game
	RenderWindow window(vm, TITLE, Style::Default);
	
	View view(FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	
	//	Create a Texture to hold a graphic on the GPU
	Texture textureBackground;
	
	//	Load a Graphic into de Texture
	textureBackground.loadFromFile("../graphics/background.png");
	
	//	Creat a Sprite
	Sprite spriteBackground;
	
	//	Attach the texture to the Sprite
	spriteBackground.setTexture(textureBackground);
	
	//	Set the Background to cover the screen
	spriteBackground.setPosition(0,0);
	
	//	Make a Tree Sprite
	Texture textureTree;
	textureTree.loadFromFile("../graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);
	
	//	Make a Bee Sprite
	Texture textureBee;
	textureBee.loadFromFile("../graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 100);
	
	//	Is the Bee currently moving?
	bool beeActive = false;
	
	//	How fast can the Bee fly
	float beeSpeed = 0.0f;
	
	//	Make 3 Clouds Sprite from 1 Texture
	Texture textureCloud;
	
	//	Load 1 new Texture
	textureCloud.loadFromFile("../graphics/cloud.png");
	
	//	3 New Sprites with the same Texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	
	//	Position the Clouds on the Left of the screen at diferent heights
	spriteCloud1.setPosition(0,0);
	spriteCloud2.setPosition(0,250);
	spriteCloud3.setPosition(0,500);
	
	//	Are the Clouds currently on the screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	
	//	How fast is each Cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	
	//	Variables to control time itself
	Clock clock;
	
	//	Time-Bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 800;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition(((WIDTH/2.0f)-(timeBarStartWidth/2.0f)), 980);
	
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = (timeBarStartWidth/timeRemaining);
	
	//	Track whether the game is running
	bool paused = true;
	
	//	Draw some text
	int score = 0;
	Text messageText, scoreText;
	
	//	Choose a font
	Font font;
	font.loadFromFile("../fonts/KOMIKAP_.ttf");
	
	//	Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	
	//	Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	
	//	Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	
	//	Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	
	//	Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left+(textRect.width/2.0f), textRect.top+(textRect.height/2.0f));
	messageText.setPosition((WIDTH/2.0f), (HEIGHT/2.0f));
	scoreText.setPosition(20, 20);
	
	//	Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("../graphics/branch.png");
	
	//	Set the texture for each branch sprite
	for(int i=0; i<NUM_BRANCHES; i++){
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		
		//	Set the sprite's origin to dead centre
		//	It's possible can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}
	//	Prepare the Player
	Texture texturePlayer;
	texturePlayer.loadFromFile("../graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	
	//	The Player starts of the LEFT
	side playerSide = side::LEFT;
	
	//	Prepare the Gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("../graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);
	
	//	Prepare the Axe
	Texture textureAxe;
	textureAxe.loadFromFile("../graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	
	//	Line the Axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	
	//	Prepare the Flying Log
	Texture textureLog;
	textureLog.loadFromFile("../graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	
	//	Some other useful Log Related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
	//	Control the Player Input
	bool acceptInput = false;
	
	//	Prepare the sounds
	//	The Player Choppig sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("../sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	
	//	The Player has met his end under a branch
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("../sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	
	//	Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("../sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);
	
	//	Main game loop
	while(window.isOpen()){
		/*
		* 	HANDLE PLAYER'S INPUT
		*/
		
		Event event;
		while(window.pollEvent(event)){
			//	Closing the window
			if(event.type == Event::Closed){
				window.close();
			}
			
			if(event.type == Event::KeyReleased && !paused){
				//	Listen for key presses again
				acceptInput = true;
				
				//	Hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}//	while(window.pollEvent(event))
		
		//	Exit the game
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		
		//	Start the game
		if(Keyboard::isKeyPressed(Keyboard::Return)){
			paused = false;
			
			//	Reset the time and the score
			score = 0;
			timeRemaining = 6.0f;
			
			//	Make all the branches disappear - starting in the second position
			for(int i=1; i<NUM_BRANCHES; i++){
				branchesPositions[i] = side::NONE;
			}
			
			//	Make sure the Gravestone is hidden
			spriteRIP.setPosition(675, 2000);
			
			//	Move the Player into position
			acceptInput = true;
		}
		//	Wrap the Player controls to make sure it is accept input if(acceptInput)
		if(acceptInput){
			//	First handle pressing the right cursor key
			if(Keyboard::isKeyPressed(Keyboard::D)){
				//	Make sure the player is on the Right
				playerSide = side::RIGHT;
				score++;
				
				//	Add to the amount of time remaining
				timeRemaining += (2/score) + 0.15;
				
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				
				spritePlayer.setPosition(1200, 720);
				
				//	Update the branches
				updateBranches(score);
				
				//	Set the Log Flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				
				acceptInput = false;
				
				//	Play a Chop sound
				chop.play();
			}
			//	Handle the Left cursor key
			else if(Keyboard::isKeyPressed(Keyboard::A)){
				//	Make sure the Player is on the Left
				playerSide = side::LEFT;
				score++;
				
				//	Add to the amount of time remaining
				timeRemaining += ((2/score) + 0.15);
				
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				
				spritePlayer.setPosition(580, 720);
				
				//	Update the Branches
				updateBranches(score);
				
				//	Set the Log Flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;
				
				acceptInput = false;
				
				//	Play a Chop sound
				chop.play();
			}
		}
		/*
		* 	UPDATE THE SCENE
		*/
		//	Verify if the game is paused
		if(!paused){
			//	Measure time
			Time dt = clock.restart();
			
			//	Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			
			//	Resize up the Time-Bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));
			
			if(timeRemaining <= 0.0f){
				//	Pause the game
				paused = true;
				
				//	Change the message shown to the player
				messageText.setString("Out of time!!!");
				
				//	Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left+(textRect.width/2.0f), textRect.top+(textRect.height/2.0f));
				messageText.setPosition((WIDTH/2.0f), (HEIGHT/2.0f));
				
				//	Play the Out Of Time sound
				outOfTime.play();
			}
			//	Setup the Bee
			if(!beeActive){
				//	How fast is the Bee
				srand((int)time(0));
				beeSpeed = (rand()%200)+200;
				
				//	How high is the Bee
				srand((int)time(0)*100);
				float height = (rand()%500)+500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}else{
				//	Move the Bee
				spriteBee.setPosition((spriteBee.getPosition().x-(beeSpeed*dt.asSeconds())), spriteBee.getPosition().y);
				
				//	Has the Bee reached the left-hand edge of the screen?
				if(spriteBee.getPosition().x < -100){
					//	Set it up ready to be a whole new Bee next frame
					beeActive = false;
				}
			}
			//	Manage the Clouds
			//	Cloud 1
			if(!cloud1Active){
				//	How fast is the Cloud 1
				srand((int)time(0)*10);
				cloud1Speed = (rand()%200);
				
				//	How high is the Cloud 1
				srand((int)time(0)*10);
				float height = (rand()%150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}else{
				//	Move the Cloud 1
				spriteCloud1.setPosition(spriteCloud1.getPosition().x+(cloud1Speed*dt.asSeconds()), spriteCloud1.getPosition().y);
				
				//	Has the Cloud 1 reached the right hand edge of the screen?
				if(spriteCloud1.getPosition().x > 1920){
					//	Set it up ready to be a whole new cloud next frame
					cloud1Active = false;
				}
			}
			//	Cloud 2
			if(!cloud2Active){
				//	How fast is the Cloud 2
				srand((int)time(0)*20);
				cloud2Speed = (rand()%200);
				
				//	How high is the Cloud 2
				srand((int)time(0)*20);
				float height = ((rand()%300)-150);
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}else{
				//	Move the Cloud 2
				spriteCloud2.setPosition(spriteCloud2.getPosition().x+(cloud2Speed*dt.asSeconds()), spriteCloud2.getPosition().y);
				
				//	Has the Cloud 2 reached the right hand edge of the screen?
				if(spriteCloud2.getPosition().x > 1920){
					//	Set it up ready to be a whole new cloud next frame
					cloud2Active = false;
				}
			}
			//	Cloud 3
			if(!cloud3Active){
				//	How fast is the Cloud 3
				srand((int)time(0)*30);
				cloud3Speed = (rand()%200);
				
				//	How high is the Cloud 3
				srand((int)time(0)*30);
				float height = ((rand()%450)-150);
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}else{
				//	Move the Cloud 2
				spriteCloud3.setPosition(spriteCloud3.getPosition().x+(cloud3Speed*dt.asSeconds()), spriteCloud3.getPosition().y);
				
				//	Has the Cloud 2 reached the right hand edge of the screen?
				if(spriteCloud3.getPosition().x > 1920){
					//	Set it up ready to be a whole new cloud next frame
					cloud3Active = false;
				}
			}
			//	Update the score text
			stringstream ss;
			ss<<"Score = "<<score;
			scoreText.setString(ss.str());
			
			//	Update the Branches Sprites
			for(int i=0; i<NUM_BRANCHES; i++){
				float height = (i*150);
				if(branchesPositions[i] == side::LEFT){
					//	Move the Sprite to the LEFT side
					branches[i].setPosition(610, height);
					
					//	Flip the Sprite round the other way
					branches[i].setRotation(180);
				}else if(branchesPositions[i] == side::RIGHT){
					//	Move the Sprite to the RIGHT side
					branches[i].setPosition(1330, height);
					
					//	Set the Sprite rotation to normal
					branches[i].setRotation(0);
				}else{
					//	Hide the Branch
					branches[i].setPosition(3000, height);
				}
			}
			//	Handle a Flying Log
			if(logActive){
				spriteLog.setPosition(spriteLog.getPosition().x+(logSpeedX*dt.asSeconds()), spriteLog.getPosition().y+(logSpeedY*dt.asSeconds()));
				
				//	Has the Log reached the right hand edge?
				if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().y > 2000){
					//	Set it up ready to be a whole new Log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}
			//	Has the Player been squished by a Branch?
			if(branchesPositions[5] == playerSide){
				//	Death
				paused = true;
				acceptInput = false;
				
				//	Draw the Gravestone
				spriteRIP.setPosition(525, 760);
				
				//	Hide the Player
				spritePlayer.setPosition(2000, 660);
				
				//	Change the Text of the Message
				messageText.setString("SQUISHED!!!");
				
				//	Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();
				
				messageText.setOrigin((textRect.left + (textRect.width/2.0f)),(textRect.top+(textRect.height/2.0f)));
				messageText.setPosition((WIDTH/2.0f), (HEIGHT/2.0f));
				
				//	Play the Death Sound
				death.play();
			}
		}//	if(!paused)
		/*
		* 	DRAW THE SCENE
		*/
		
		//	Clear everything from the last frame
		window.clear();
		
		//	Draw our game scene here
		window.draw(spriteBackground);
		
		//	Draw the Clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		
		//	Draw the Branches
		for(int i=0; i<NUM_BRANCHES; i++){
			window.draw(branches[i]);
		}
		
		//	Draw the Tree
		window.draw(spriteTree);
		
		//	Draw the Player
		window.draw(spritePlayer);
		
		//	Draw Axe
		window.draw(spriteAxe);
		
		//	Draw the Flying Log
		window.draw(spriteLog);
		
		//	Draw the Gravestone
		window.draw(spriteRIP);
		
		//	Draw the Bee
		window.draw(spriteBee);
		
		//	Draw the Score
		window.draw(scoreText);
		
		//	Draw the Time-Bar
		window.draw(timeBar);
		
		if(paused){
			//	Draw the Message
			window.draw(messageText);
		}
		
		//	Show everything just drew
		window.display();
	}	//	while(window.isOpen())
	return 0;
}

void updateBranches(int seed){
	//	Move all the branches down one place
	for(int i=NUM_BRANCHES; i>0; i--){
		branchesPositions[i] = branchesPositions[(i-1)];
	}
	//	Spawn a new Branch at position 0
	//	LEFT, RIGHT, NONE
	srand((int)time(0)+seed);
	int r = (rand()%5);
	switch(r){
		case 0:
			branchesPositions[0] = side::LEFT;
			break;
		case 1:
			branchesPositions[0] = side::RIGHT;
			break;
		default:
			branchesPositions[0] = side::NONE;
			break;
	}
}
