#include"TextureHolder.h"

#include<assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder(){
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename){
	//	Get a reference to m_Texture using m_s_Instance
	//	Auto is the equivalent of map<string, Texture>
	auto& m = m_s_Instance->m_Textures;
	
	//	Create a iterator to hold a key-value-pair (KVP) and search for the require KVP using the passed in the File Name
	//	Auto is equivalent of map<string, Texture>::iterator
	auto keyValuePair = m.find(filename);
	
	//	Did it found a match?
	if(keyValuePair != m.end()){
		//	Yes, return the Texture (the second part of the KVP, the Texture)
		return keyValuePair->second;
	}else{
		//	File name not found: Create a new key value pair using the Filename 
		auto& texture = m[filename];
		
		//	Load the Texture from file in the usual way
		texture.loadFromFile(filename);
		
		//	Return the Texture to the Calling Code
		return texture;
	}
}
