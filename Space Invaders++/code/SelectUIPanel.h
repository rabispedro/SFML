#pragma once
#include"UIPanel.h"

using namespace std;
using namespace sf;

class SelectUIPanel : public UIPanel{
	private:
		void initialiseButtons();

	public:
		SelectUIPanel(Vector2i res);
		void virtual draw(RenderWindow& window);
};