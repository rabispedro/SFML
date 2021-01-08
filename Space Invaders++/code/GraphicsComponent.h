#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Component.h"
#include"TransformComponent.h"
#include"GameObjectSharer.h"

using namespace std;
using namespace sf;

class GraphicsComponent : public Component{
	private:
		string m_Type = "graphics";
		bool m_Enabled = false;

	public:
		virtual void draw(RenderWindow& window, shared_ptr<TransformComponent> t) = 0;
		virtual void initialiseGraphics(string bitmapName, Vector2f objectSize) = 0;

		/*
		*	From Component INTERFACE
		*/
		string Component::getType(){
			return m_Type;
		}

		void Component::enableComponent(){
			m_Enabled = true;
		}

		void Component::disableComponent(){
			m_Enabled = false;
		}

		bool Component::enabled(){
			return m_Enabled;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){

		}
};