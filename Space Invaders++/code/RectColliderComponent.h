#pragma once
#include"ColliderComponent.h"
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class RectColliderComponent : public ColliderComponent{
	private:
		string m_SpecificType = "rect";
		FloatRect m_Collider;
		string m_Tag = "";
	
	public:
		RectColliderComponent(string name);
		string getColliderTag();
		void setOrMoveCollider(float x, float y, float width, float height);
		FloatRect& getColliderRectF();

		/*
		*	From Component INTERFACE base class
		*/
		string getSpecificType(){
			return m_SpecificType;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){
			
		}
};