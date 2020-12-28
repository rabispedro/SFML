#include"SelectUIPanel.h"
#include<iostream>

#define TITLE "Space Invaders++"

using namespace std;
using namespace sf;

//	Create a new UIPanel by calling the super-class constructor
SelectUIPanel::SelectUIPanel(Vector2i res) : UIPanel(res, ((res.x/10)*2), (res.y/3), ((res.x/10)*6), (res.y/3), 50, 255, 255, 255){
		m_ButtonWidth = (res.x/20);
		m_ButtonHeight = (res.y/20);
		m_ButtonPadding = (res.x/100);

		m_Text.setFillColor(Color(0,255,0,255));
		m_Text.setString(TITLE);

		m_Font.loadFromFile("../fonts/Roboto-Light.ttf");
		m_Text.setFont(m_Font);

		m_Text.setPosition(Vector2f(m_ButtonPadding, (m_ButtonHeight+(m_ButtonPadding*2))));
		m_Text.setCharacterSize(100);
		initialiseButtons();
}

void SelectUIPanel::initialiseButtons(){
	//	Buttons are positioned relative to the top left corner of the UI Panel (m_View in UIPanel)
	addButton(m_ButtonPadding, m_ButtonPadding, m_ButtonWidth, m_ButtonHeight, 0, 255, 0, "Play");
	addButton((m_ButtonWidth+(m_ButtonPadding*2)), m_ButtonPadding, m_ButtonWidth, m_ButtonHeight, 255, 0, 0, "Quit");
}

void SelectUIPanel::draw(RenderWindow& window){
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}

