#include"Engine.h"
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void Engine::draw(){
	//	Rub out the last frame
	m_Window.clear(Color::White);
	
	if(!m_SplitScreen){
		//	Switch to background view
		m_Window.setView(m_BGMainView);
		
		//	Draw the background
		m_Window.draw(m_BackgroundSprite);
		
		//	Switch to the main view
		m_Window.setView(m_MainView);
		
	}else{
		//	Split-Screen is active
		//	First draw Thomas's side of the screen
		//	Switch to the background view
		m_Window.setView(m_BGLeftView);
		
		//	Draw the background
		m_Window.draw(m_BackgroundSprite);
		
		//	Switch to the left view
		m_Window.setView(m_LeftView);
		
		//	Now draw the Bob's side of the screen
		//	Switch to the background view
		m_Window.setView(m_BGRightView);
		
		//	Draw the background
		m_Window.draw(m_BackgroundSprite);
		
		//	Switchto the right view
		m_Window.setView(m_RightView);
	}
	
	//	Draw the HUD
	//	Switch to the HUD view
	m_Window.setView(m_HudView);
	
	//	Show everything that have just draw
	m_Window.display();
}
