#include"BitmapStore.h"
#include<assert.h>

using namespace std;
using namespace sf;

BitmapStore* BitmapStore::m_s_Instance = nullptr;

BitmapStore::BitmapStore(){
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

void BitmapStore::addBitmap(string const& filename){
	//	Get a reference to m_Texture using m_s_Instance
	//	auto is the equivalent of map<string, Texture>
	auto& bitmapsMap = m_s_Instance->m_BitmapsMap;

	//	Create an iterator to hold a key-value-pair (kvp) and search for the required kvp using the passed in filename
	//	auto is the equivalent of map<string, Texture>::iterator
	auto keyValuePair = bitmapsMap.find(filename);

	//	No match found so save the texture in the map
	if(keyValuePair == bitmapsMap.end()){
		//	Create a new key value pair using the filename
		auto& texture = bitmapsMap[filename];

		//	Load the texture from the file in the usual way
		texture.loadFromFile(filename);
	}
}

Texture& BitmapStore::getBitmap(string const& filename){
	//	Get a reference to m_Texture using m_s_Instance
	//	auto is the equivalent of map<string, Texture>
	auto& m = m_s_Instance->m_BitmapsMap;

	//	Create an interactor to hold a key-value-pair (kvp) and search for the required kvp using the passed in filename
	//	auto is the equivalent of map<string, Texture>::iterator
	auto keyValuePair = m.find(filename);

	//	Did it find a match?
	if(keyValuePair != m.end()){
		return keyValuePair->second;
	}else{
		#ifdef debuggingOnConsole
		cout<<"BitmapStore::getBitmap() Texture not found!\n";
		#endif
		return keyValuePair->second;
	}
}
