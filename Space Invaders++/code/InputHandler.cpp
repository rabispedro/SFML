#include<iostream>
#include<sstream>
#include"InputHandler.h"

using namespace std;
using namespace sf;

void InputHandler::initialiseInputHandler(ScreenManagerRemoteControl* sw, vector<shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen){
	m_ScreenManagerRemoteControl = sw;
	m_Buttons = buttons;
	m_PointerToUIPanelView = pointerToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(RenderWindow& window, Event& event){
	//	Handle any key presses
	if(event.type == Event::KeyPressed){
		handleKeyPressed(event, window);
	}

	if(event.type == Event::KeyReleased){
		handleKeyReleased(event, window);
	}

	//	Handle any left mouse click released
	if(event.type == Event::MouseButtonReleased){
		cout<<"Click detected!\n";
		cout<<"Mouse position X: "<<Mouse::getPosition().x<<"\n";
		cout<<"Mouse position Y: "<<Mouse::getPosition().y<<"\n\n";

		Vector2f m_Mouse = window.mapPixelToCoords(Mouse::getPosition(), (*getPointerToUIView()));
		cout<<"Mouse relative X: "<<m_Mouse.x<<"\n";
		cout<<"Mouse relative Y: "<<m_Mouse.y<<"\n";
		auto end = m_Buttons.end();

		for(auto i = m_Buttons.begin(); i != end; i++){
			cout<<"Text: "<<(*i)->m_Text<<"\n";
			if((*i)->m_Collider.contains(window.mapPixelToCoords(Mouse::getPosition(), (*getPointerToUIView())))){
				//	Capture the text of the button that was interacted with and pass it to the specialized version of this class if implemented
				cout<<"Text Found: "<<(*i)->m_Text<<"\n";
				handleLeftClick((*i)->m_Text, window);
				break;
			}
		}
		cout<<"\n";
	}

	handleGamepad();
}

//	Do nothing unless handled by derived class
void InputHandler::handleGamepad(){}

//	Do nothing unless handled by derived class
void InputHandler::handleKeyPressed(Event& event, RenderWindow& window){}

//	Do nothing unless handled by derived class
void InputHandler::handleKeyReleased(Event& event, RenderWindow& window){}

//	Do nothing unless handled by derived class
void InputHandler::handleLeftClick(string& buttonInteractedWith, RenderWindow& window){}

View* InputHandler::getPointerToUIView(){
	return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::getPointerToScreenManagerRemoteControl(){
	return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::getmParentScreen(){
	return m_ParentScreen;
}

