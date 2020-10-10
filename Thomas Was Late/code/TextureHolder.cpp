#include"TextureHolder.h"
#include<assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder(){
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename){
	//	Get a reference to m_Textures using m_s_Instance
	//	auto is equivalent to map<string, Texture>
	auto& m = m_s_Instance->m_Textures;
	
	//	Create an iterator to hold a key-value-pair (kvp) and search for the required kvp using the passed filename
	//	auto is equivalent to map<string, Texture>::iterator
	auto keyValuePair = m.find(filename);
	
	//	Did the match was find?
	if(keyValuePair != m.end()){
		//	Yes. Return the texture, the second part of the kvp, the texture itself
		return keyValuePair->second;
	}else{
		//	Filename not found
		//	Create a new key-value-pair using the filename
		auto& texture = m[filename];
		
		//	Load the texture from file in the usual way
		texture.loadFromFile(filename);
		
		//	Return the texture to the calling code
		return texture;
	}
}
