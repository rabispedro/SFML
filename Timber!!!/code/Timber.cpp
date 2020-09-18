//	Libraries
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>


//	Constants
#define WIDTH 1920
#define HEIGHT 1080
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
	
	
	
	//	Main game loop
	while(window.isOpen()){
		/*
		* 	HANDLE the player's Input
		*/
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
		}
		
		/*
		* 	UPDATE the scene
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
			
			
			
		//	End if(!paused)
		}
		
		/*
		* 	DRAW the scene
		*/
		
		//	Clear everything from the last frame
		window.clear();
		
		//	Draw our game scene here
		window.draw(spriteBackground);
		
		//	Draw the Clouds
		
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		
		//	Draw the Tree
		window.draw(spriteTree);
		
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
	}
	return 0;
}

void updateBranches(int seed){
	
}
