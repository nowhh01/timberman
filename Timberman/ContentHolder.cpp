#include "pch.h"
#include "ContentHolder.h"
#include <assert.h>

ContentHolder* ContentHolder::msInstance = nullptr;

ContentHolder::ContentHolder()
{
	assert(msInstance == nullptr);
	msInstance = this;
}

sf::Texture& ContentHolder::FindTexture(const std::string& filePath)
{
	auto& textures = ContentHolder::msInstance->mTextures;

	return ContentHolder::msInstance->findContent<sf::Texture>(filePath, &textures);
}

sf::SoundBuffer& ContentHolder::FindSoundBuffer(const std::string& filePath)
{
	auto& soundBuffers = ContentHolder::msInstance->mSoundBuffers;

	return ContentHolder::msInstance->findContent<sf::SoundBuffer>(filePath, &soundBuffers);
}

sf::Font& ContentHolder::FindFont(const std::string& filePath)
{
	auto& fonts = ContentHolder::msInstance->mFonts;

	return ContentHolder::msInstance->findContent<sf::Font>(filePath, &fonts);
}