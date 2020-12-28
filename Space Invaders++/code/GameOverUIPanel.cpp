#include"GameOverUIPanel.h"
#include"GameScreen.h"

#define MESSAGE "GAME OVER!!!"

using namespace std;
using namespace sf;

bool GameScreen::m_GameOver;

GameOverUIPanel::GameOverUIPanel(Vector2i res) : UIPanel(res, ((res.x/10)*3), (res.y/2), ((res.x/10)*3), (res.y/6), 50, 255, 255, 255){
	m_ButtonWidth = (res.x/20);
	m_ButtonHeight = (res.y/20);
	m_ButtonPadding = (res.x/100);

	m_Text.setFillColor(Color(0,255,0,255));
	m_Text.setString(MESSAGE);

	m_Font.loadFromFile("../fonts/Roboto-Light.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(Vector2f((m_ButtonPadding), ((m_ButtonPadding*2)+m_ButtonHeight)));
	m_Text.setCharacterSize(60);
	initialiseButtons();
}

void GameOverUIPanel::initialiseButtons(){
	addButton(m_ButtonPadding, m_ButtonPadding, m_ButtonWidth, m_ButtonHeight, 0, 255, 0, "Play");
	addButton((m_ButtonWidth+(m_ButtonPadding*2)), m_ButtonPadding, m_ButtonWidth*1.4f, m_ButtonHeight, 255, 0, 0, "Home");
}

void GameOverUIPanel::draw(RenderWindow& window){
	if(GameScreen::m_GameOver){
		show();
		UIPanel::draw(window);
		window.draw(m_Text);
	}else{
		hide();
	}
}