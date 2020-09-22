#include"Bat.h"
#include"Ball.h"
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int WIDTH = 1920;
const int HEIGHT = 1080;
const string TITLE = "Pong";

int main(){
	//	Create a Video Mode Object (Resolution)
	VideoMode vm(1366, 768);
	
	//	Create and open a Window for the game
	RenderWindow window(vm, TITLE, Style::Default);
	
	//	Setting a Lower Resolution
	View view(FloatRect(0, 0, WIDTH, HEIGHT));
	window.setView(view);
	
	int score = 0;
	int lives = 3;
	
	//	Create a Bat at the bottom center of the screen
	Bat bat((WIDTH/2.0f), (HEIGHT-20));
	
	//	Create a Ball
	Ball ball((WIDTH/2.0f), 50);
	
	//	Create a Text Object called HUD
	Text hud;
	
	//	A cool Retro-Style Font
	Font font;
	font.loadFromFile("../fonts/game_over.ttf");
	
	//	Set the Font to our retro-style
	hud.setFont(font);
	
	//	Make it nice and big
	hud.setCharacterSize(100);
	
	//	Choose a color
	hud.setFillColor(Color::White);
	
	hud.setPosition(5, 5);
	
	//	Clock for timing everything
	Clock clock;
	
	while(window.isOpen()){
		/*
		*	HANDLE THE PLAYER INPUT
		*/
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				//	Quit the game when the window is closed
				window.close();
			}
		}//	while(window.pollEvent(event))
		
		//	Handle the Player quitting
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		
		//	Handle the pressing and releasing of the Directional Keys
		if(Keyboard::isKeyPressed(Keyboard::A)){
			bat.moveLeft();
		}else{
			bat.stopLeft();
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			bat.moveRight();
		}else{
			bat.stopRight();
		}
		
		
		
		/*
		*	UPDATE THE BAT, THE BALL AND THE HUD
		*/
		//	Update the DeltaTime
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		
		//	Update the HUD text
		stringstream ss;
		ss<<"Score: "<<score<<"\nLives: "<<lives;
		hud.setString(ss.str());
		
		//	Handle the Ball hitting the Bottom
		if(ball.getPosition().top > view.getSize().y){
			//	Reverse the Ball Direction
			ball.reboundBottom();
			
			//	Remove a Life
			lives--;
			
			//Check for zero Lives
			if(lives < 1){
				//	Reset the Score
				score = 0;
				
				//	Reset the Lives
				lives = 3;
			}
		}
		
		//	Handle Ball hitting Top
		if(ball.getPosition().top < 0){
			//	Reverse the Ball Direction
			ball.reboundBatOrTop();
			
			//	Add a point to the Player's Score
			score++;
		}
		
		//	Handle Ball hitting Sides
		if(ball.getPosition().left < 0 || (ball.getPosition().left+ball.getPosition().width) > view.getSize().x){
			//	Reverse the Ball Direction
			ball.reboundSides();
		}
		
		//	Has the Ball hit the Bat?
		if(ball.getPosition().intersects(bat.getPosition())){
			//	Hit detected so reverse the ball and add Score a point
			ball.reboundBatOrTop();
			score++;
		}
		
		
		/*
		*	DRAW THE BAT, THE BALL AND THE HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
		
	}//	while(window.isOpen())
	return 0;
}
