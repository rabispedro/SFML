#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include"Component.h"
#include"GraphicsComponent.h"

using namespace std;
using namespace sf;

class Component;

class StandardGraphicsComponent : public GraphicsComponent{
	private:
		Sprite m_Sprite;
		string m_SpecificType = "standard";
	
	public:
		/*
		*	From Component INTERFACE base class
		*/
		string Component::start(GameObjectSharer* gos, GameObject* self){

		}

		/*
		*	From Graphics Component
		*/
		void draw(RenderWindow& window, shared_ptr<TransformComponent> t) override;
		void initialiseGraphics(string bitmapName, Vector2f objectSize) override;
};