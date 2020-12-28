#pragma once
#include<SFML/Graphics.hpp>
#include<memory>

using namespace std;
using namespace sf;

class Button{
	private:
		RectangleShape m_Button;
		Text m_ButtonText;
		Font m_Font;

	public:
		string m_Text;
		FloatRect m_Collider;

		Button(Vector2f position, float width, float height, int red, int green, int blue, string text);
		void draw(RenderWindow& window);
};