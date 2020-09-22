#include"Bat.h"
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
	RenderWindow(vm, TITLE, Style::Default);
	
	//	Setting a Lower Resolution
	View view(FloatRect(0, 0, WIDTH, HEIGHT));
	window.setView(view);
	
	int score = 0;
	int lives = 3;
	
	//	Create a Bat at the bottom center of the screen
	Bat bat((WIDTH/2.0f), (HEIGHT-20));
	
	//	Add a ball in the next chapter
	
	
	//	Create a Text Object called HUD
	Text hud;
	
	//	A cool Retro-Style Font
	Font font;
	font.loadFromFile("../fonts/ka1.ttf");
	
	//	Set the Font to our retro-style
	hud.setFont(font);
	
	//	Make it nice and big
	hud.setCharacterSize(75);
	
	//	Choose a color
	hud.setFillColor(Color::White);
	
	hud.setPosition(20, 20);
	
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
		
		//	Update the HUD text
		stringstream ss;
		ss<<"Score: "<<score<<"\nLives: "<<lives;
		hud.setString(ss.str());
		
		/*
		*	DRAW THE BAT, THE BALL AND THE HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.display();
		
	}//	while(window.isOpen())
	return 0;
}
