#pragma once
#include"UIPanel.h"

using namespace std;
using namespace sf;

class GameUIPanel : public UIPanel{
	public:
		GameUIPanel(Vector2i res);
		void draw(RenderWindow& window) override;
};