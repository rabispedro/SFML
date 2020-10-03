#include"Bullet.h"

using namespace sf;
using namespace std;

//	The Constructor
Bullet::Bullet(){
	m_BulletShape.setSize(Vector2f(2,2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY){
	//	Keep the track of the Bullet
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;
	
	//	Calculate the Gradient of the Flight Path
	float gradient = (startX-targetX)/(startY-targetY);
	
	//	Any Gradient less than 1 needs to be negative
	if(gradient < 0){
		gradient *= -1;
	}
	
	//	Calculate the ratio between X and Y
	float ratioXY = (m_BulletSpeed / (1+gradient));
	
	//	Set the "Speed" horinzontally and vertically
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = (ratioXY*gradient);
	
	//	Point the Bullet in the right direction
	if(targetX < startX){
		m_BulletDistanceX *= -1;
	}
	if(targetY < startY){
		m_BulletDistanceY *= -1;
	}
	
	//	Set a Max Range of 1000 Pixels
	float range = 1000;
	m_MinX = (startX - range);
	m_MaxX = (startX + range);
	m_MinY = (startY - range);
	m_MaxY = (startY + range);
	
	//	Position the Bullet ready to be Drawn
	m_BulletShape.setPosition(m_Position);
}

void Bullet::stop(){
	m_InFlight = false;
}

bool Bullet::isInFlight(){
	return m_InFlight;
}

FloatRect Bullet::getPosition(){
	return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape(){
	return m_BulletShape;
}

void Bullet::update(float elapsedTime){
	//	Update the Bullet position variables
	m_Position.x += (m_BulletDistanceX*elapsedTime);
	m_Position.y += (m_BulletDistanceY*elapsedTime);
	
	//	Move the Bullet
	m_BulletShape.setPosition(m_Position);
	
	//	Has the Bullet gone out of range?
	if((m_Position.x < m_MinX) || (m_Position.x > m_MaxX) || (m_Position.y < m_MinY) || (m_Position.y > m_MaxY)){
		m_InFlight = false;
	}
}
