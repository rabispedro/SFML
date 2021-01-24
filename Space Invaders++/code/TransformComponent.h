#pragma once
#include<string>
#include<SFML/Graphics.hpp>
#include"Component.h"

using namespace std;
using namespace sf;

class Component;

class TransformComponent : public Component{
	private:
		const string m_Type = "transform";
		Vector2f m_Location;
		float m_Height;
		float m_Width;
	
	public:
		TransformComponent(float width, float height, Vector2f location);
		Vector2f& getLocation();
		Vector2f getSize();

		/*
		*	From Component INTERFACE
		*/
		string Component::getType(){
			return m_Type;
		}

		string Component::getSpecificType(){
			//	Only one type of Transform, so just return m_Type
			return m_Type;
		}

		void Component::disableComponent(){
			
		}

		void Component::enableComponent(){

		}

		bool Component::enabled(){
			return false;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){
			
		}
};