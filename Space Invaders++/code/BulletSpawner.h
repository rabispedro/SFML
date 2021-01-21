#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class BulletSpawner{
	public:
		virtual void spawnBullet(Vector2f spawnLocation, bool forPlayer) = 0;
};