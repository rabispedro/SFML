#pragma once
#include<string>
#include"Component.h"

using namespace std;
using namespace sf;

class UpdateComponent : public Component{
	private:
		string m_Type = "update";
		bool m_Enabled = false;

	public:
		virtual void update(float fps) = 0;

		/*
		*	From Component INTERFACE
		*/

		string Component::getType(){
			return m_Type;
		}

		void Component::disableComponent(){
			m_Enabled = false;
		}

		void Component::enableComponent(){
			m_Enabled = true;
		}

		bool Component::enabled(){
			return m_Enabled;
		}

		void Component::start(GameObjectSharer* gos, GameObject* self){
			
		}
};