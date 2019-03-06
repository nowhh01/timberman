#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ContentHolder
{
public:
	ContentHolder();
	ContentHolder(ContentHolder const&) = delete;
	ContentHolder& operator = (ContentHolder const&) = delete;
	
	static sf::Texture& FindTexture(const std::string& filePath);
	static sf::SoundBuffer& FindSoundBuffer(const std::string& filePath);
	static sf::Font& FindFont(const std::string& filePath);

	template <class T>
	T& findContent(const std::string& filePath,
		std::map<std::string, T>* const outContents)
	{
		auto keyValuePair = outContents->find(filePath);

		if (keyValuePair != outContents->end())
		{
			return keyValuePair->second;
		}
		else
		{
			T& content = (*outContents)[filePath];
			content.loadFromFile(filePath);

			return content;
		}
	}
	
private:
	static ContentHolder* msInstance;
	std::map<std::string, sf::Texture> mTextures;
	std::map<std::string, sf::SoundBuffer> mSoundBuffers;
	std::map<std::string, sf::Font> mFonts;
};