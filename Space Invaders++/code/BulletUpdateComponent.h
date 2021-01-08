#pragma once
#include<string>
#include"UpdateComponent.h"
#include"TransformComponent.h"
#include"GameObject.h"
#include"GameObjectSharer.h"
#include"RectColliderComponent.h"

using namespace std;
using namespace sf;

class BulletUpdateComponent : public UpdateComponent{
	private:
		string m_SpecificType = "bullet";
		shared_ptr<TransformComponent> m_TC;
		shared_ptr<RectColliderComponent> m_RCC;
	
		float m_Speed = 75.0f;

		int m_AlienBulletSpeedModifier;
		int m_ModifierRandomComponent = 5;
		int m_MininumAdditionalModifier = 5;

		bool m_MovingUp = true;

	public:
		bool m_BelongsToPlayer = false;
		bool m_IsSpawned = false;

		void spawnForPlayer(Vector2f spawnPosition);
		void spawnForInvader(Vector2f spawnPosition);
		void deSpawn();
		bool isMovingUp();

		/*
		*	From Component INTERFACE base class
		*/
		string Component::getSpecificType(){
			return m_SpecificType;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){
			//	Where is this specific invader
			m_TC = static_pointer_cast<TransformComponent>(self->getComponentByTypeAndSpecificType("transform","transform"));
			m_RCC = static_pointer_cast<RectColliderComponent>(self->getComponentByTypeAndSpecificType("collider","rect"));
		}

		/*
		*	From UpdateComponent
		*/
		void update(float fps) override;
};