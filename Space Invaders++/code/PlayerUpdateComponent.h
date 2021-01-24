#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include"UpdateComponent.h"
#include"TransformComponent.h"
#include"GameObject.h"
#include"GameObjectSharer.h"
#include"RectColliderComponent.h"

using namespace std;
using namespace sf;

class PlayerUpdateComponent : public UpdateComponent{
	private:
		string m_SpecificType = "player";

		shared_ptr<TransformComponent> m_TC;
		shared_ptr<RectColliderComponent> m_RCC;

		float m_Speed = 50.0f;
		float m_XExtend = 0;
		float m_YExtend = 0;

		bool m_IsHoldingLeft = false;
		bool m_IsHoldingRight = false;
		bool m_IsHoldingUp = false;
		bool m_IsHoldingDown = false;
	
	public:
		void updateShipTravelWithController(float x, float y);
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void stopLeft();
		void stopRight();
		void stopUp();
		void stopDown();

		/*
		*	From Component INTERFACE base class
		*/
		string Component::getSpecificType(){
			return m_SpecificType;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){
			m_TC = static_pointer_cast<TransformComponent>(self->getComponentByTypeAndSpecificType("transform", "transform"));
			m_RCC = static_pointer_cast<RectColliderComponent>(self->getComponentByTypeAndSpecificType("collider","rect"));	
		}

		/*
		*	From UpdateComponent
		*/
		void update(float fps) override;
};