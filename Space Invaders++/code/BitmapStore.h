#pragma once
#ifndef BITMAP_STORE_H
#define BITMAP_STORE_H

#include<SFML/Graphics.hpp>
#include<map>

using namespace std;
using namespace sf;

class BitmapStore{
	private:
		map<string,Texture> m_BitmapsMap;
		static BitmapStore* m_s_Instance;

	public:
		BitmapStore();
		static Texture& getBitmap(string const& filename);
		static void addBitmap(string const& filename);
};

#endif