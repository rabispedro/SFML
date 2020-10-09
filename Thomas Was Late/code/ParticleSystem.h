#pragma once
#include<SFML/Graphics.hpp>
#include"Particle.h"

using namespace std;
using namespace sf;

class ParticleSystem : public Drawable{
	private:
		vector<Particle> m_Particles;
		VertexArray m_Vertices;
		float m_Duration;
		bool m_IsRunning = false;
	
	public:
		void init(int numParticles);
		
		virtual void draw(RenderTarget& target, RenderStates states) const;
		
		void emitParticles(Vector2f startPosition);
		
		void update(float dt);
		
		bool running();
};
