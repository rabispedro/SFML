#include"Engine.h"
#include<SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;
using namespace sf;

void Engine::draw(){
	//	Rub out the last frame
	m_Window.clear(Color::White);
	
	//	Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());
	
	if(!m_SplitScreen){
		//	Switch to background view
		m_Window.setView(m_BGMainView);
		
		//	Draw the background
		//	m_Window.draw(m_BackgroundSprite);
		
		//	Draw the background, complete with shader effects
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		
		//	Switch to the main view
		m_Window.setView(m_MainView);
		
		//	Draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		
		//	Draw Thomas
		m_Window.draw(m_Thomas.getSprite());
		
		//	Draw Bob
		m_Window.draw(m_Bob.getSprite());
		
		//	Draw the particle system
		if(m_PS.running()){
			m_Window.draw(m_PS);
		}
	}else{
		//	Split-Screen is active
		//	First draw Thomas's side of the screen
		//	Switch to the background view
		m_Window.setView(m_BGLeftView);
		
		//	Draw the background
		//	m_Window.draw(m_BackgroundSprite);
		
		//	Draw the background, complete with shader effects
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		
		//	Switch to the left view
		m_Window.setView(m_LeftView);
		
		//	Draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		
		//	Draw Bob
		m_Window.draw(m_Bob.getSprite());
		
		//	Draw Thomas
		m_Window.draw(m_Thomas.getSprite());
		
		//	Draw the particle system
		if(m_PS.running()){
			m_Window.draw(m_PS);
		}
		
		//	Now draw the Bob's side of the screen
		//	Switch to the background view
		m_Window.setView(m_BGRightView);
		
		//	Draw the background
		//	m_Window.draw(m_BackgroundSprite);
		
		//	Draw the background, complete with shader effects
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		
		//	Switchto the right view
		m_Window.setView(m_RightView);
		
		m_Window.draw(m_VALevel, &m_TextureTiles);
		
		//	Draw Thomas
		m_Window.draw(m_Thomas.getSprite());
		
		//	Draw Bob
		m_Window.draw(m_Bob.getSprite());
		
		// Draw the particle system
		if(m_PS.running()){
			m_Window.draw(m_PS);
		}
	}
	
	//	Draw the HUD
	//	Switch to the HUD view
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());
	if(!m_Playing){
		m_Window.draw(m_Hud.getMessage());
	}
	
	//	Show everything that have just draw
	m_Window.display();
}
