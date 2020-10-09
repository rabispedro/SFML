#include"Engine.h"
#include <SFML/OpenGL.hpp>
#define TITLE "Thomas Was Late"

using namespace std;
using namespace sf;

Engine::Engine(){
	//	Get the screen resolution and create a SFML window and view
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
	m_Window.create(VideoMode(resolution.x, resolution.y), TITLE, Style::Default);
	
	//	Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	
	//	Initialize the split-screen views
	m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	
	m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	
	//	Can this graphics card use shaders?
	if(!Shader::isAvailable()){
		//	Time to get a new PC or remove all the shader related code
		m_Window.close();
	}else{
		//	Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("../shaders/vertShader.vert", "../shaders/rippleShader.frag");
	}
	
	m_BackgroundTexture = TextureHolder::GetTexture("../graphics/background.png");
	
	//	Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	
	//	Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture("../graphics/tiles_sheet.png");
	
	//	Initialize the particle system
	m_PS.init(1000);
}

void Engine::run(){
	//	Timing
	Clock clock;
	
	while(m_Window.isOpen()){
		Time dt = clock.restart();
		
		//	Update the total game time
		m_GameTimeTotal += dt;
		
		//	Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		
		//	Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}
