#include "pch.h"
#include "Game.h"

Game::Game()
{
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	mWindow.create(sf::VideoMode(resolution.x, resolution.y), "Timberman",
		sf::Style::Fullscreen);
	
	mSpriteBackground.setScale(4, 2.2f);
	mWindow.setMouseCursorVisible(false);

	loadSprite("graphics/background.png", 0, 0, &mSpriteBackground);
	loadSprite("graphics/tree_bottom.png", TREE_BOTTOM_X + 3, 
		TREE_BOTTOM_Y, &mSpriteTree);
	loadSprite("graphics/bee.png", 0, 800, &mSpriteBee);
	loadSprite("graphics/green_tree.png", 250, 200, mSpriteBackgroundTrees);
	loadSprite("graphics/half_green_tree.png", 1300, 300,
		mSpriteBackgroundTrees + 1);
	loadSprite("graphics/sun.png", 1700, 70, &mSpriteSun);

	mTimeBar.setFillColor(sf::Color::White);
	mTimeBar.setOutlineColor(sf::Color::Color(0, 115, 204));
	mTimeBar.setSize(sf::Vector2f(TIME_BAR_FULL_WIDTH + 12,
		mTimeBarHeight + 12));
	mTimeBar.setOutlineThickness(5.f);
	mTimeBar.setPosition((1920 / 2) - TIME_BAR_FULL_WIDTH / 2 - 6, 120 - 6);

	mTimeBarGauge.setSize(sf::Vector2f(TIME_BAR_FULL_WIDTH / 2,
		mTimeBarHeight));
	mTimeBarGauge.setFillColor(sf::Color::Color(0, 153, 204));
	mTimeBarGauge.setPosition((1920 / 2) - TIME_BAR_FULL_WIDTH / 2, 120);

	mFont = ContentHolder::FindFont("fonts/KOMIKAP_.ttf");

	loadText(mFont, "Press Enter to start", 75, sf::Color::White, &mTextMessage);
	loadText(mFont, "0", 100, sf::Color::White, &mTextScore);

	sf::FloatRect textRect = mTextMessage.getLocalBounds();
	mTextMessage.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mTextMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);
	mTextMessage.setOutlineColor(sf::Color::Color(0, 153, 204));
	mTextMessage.setOutlineThickness(5.f);

	mTextScore.setPosition(1920 / 2 - mTextScore.getLocalBounds().width / 2, 200);
	mTextScore.setOutlineColor(sf::Color::Color(0, 153, 204));
	mTextScore.setOutlineThickness(5.f);
	
	mTextureLogs[0] = ContentHolder::FindTexture("graphics/log_with_green.png");
	mTextureLogs[1] = ContentHolder::FindTexture("graphics/log_with_orange.png");
	mTextureLogs[2] = ContentHolder::FindTexture("graphics/log.png");

	for (int i = 0; i < NUM_LOGS; i++)
	{
		loadSideLogBranch(i);
		loadTextureLog(i);
		(mSpriteLogs + i)->setOrigin(128, 96);
	}
	mChopSound.setBuffer(ContentHolder::FindSoundBuffer("sounds/chop.wav"));
	mDeathSound.setBuffer(ContentHolder::FindSoundBuffer("sounds/death.wav"));
}

void Game::Run()
{
	while (mWindow.isOpen())
	{
		input();
		update();
		draw();
	}
}

void Game::updateBranches()
{
	sf::Vector2f position;
	sf::Sprite* sprite = 0;
	for (int i = 0; i < NUM_LOGS - 1; i++)
	{
		mSideLogBranches[i] = mSideLogBranches[i + 1];
		sprite = &mSpriteLogs[i];
		position = sprite->getPosition();
		*(sprite) = mSpriteLogs[i + 1];
		sprite->setPosition(position);
	}

	loadSideLogBranch(5);
	loadTextureLog(5);
}

void Game::loadSprite(const std::string& filePath, const float& x, const float& y, 
	sf::Sprite* const outSprite)
{
	outSprite->setTexture(ContentHolder::FindTexture(filePath));
	outSprite->setPosition(x, y);
}

void Game::loadText(const sf::Font& font, const std::string& content, int size,
	const sf::Color& color, sf::Text* const outText)
{
	outText->setFont(font);
	outText->setString(content);
	outText->setCharacterSize(size);
	outText->setFillColor(color);
}

void Game::loadSideLogBranch(int index)
{
	srand((int)time(0) * (mScore + 1) * index);
	switch (rand() % (NUM_LOG_KINDS))
	{
	case 0:
		mSideLogBranches[index] = eSide::Left;
		break;
	case 1:
		mSideLogBranches[index] = eSide::Right;
		break;
	default:
		mSideLogBranches[index] = eSide::None;
		break;
	}
}

void Game::loadTextureLog(int index)
{
	float height = 
		TREE_BOTTOM_Y - LOG_HEIGHT * (index + 1) + LOG_HEIGHT / 2;
	srand((int)time(0) * (mScore + 1) * index);

	if (mSideLogBranches[index] == eSide::Left)
	{
		mSpriteLogs[index].setTexture(
			mTextureLogs[rand() % (NUM_LOG_KINDS - 1)]);
		mSpriteLogs[index].setScale(-1.f, 1.f);
	}
	else if (mSideLogBranches[index] == eSide::Right)
	{
		mSpriteLogs[index].setTexture(
			mTextureLogs[rand() % (NUM_LOG_KINDS - 1)]);
		mSpriteLogs[index].setScale(1.f, 1.f);
	}
	else
	{
		sf::IntRect rect(0, 0, 512, 192);
		mSpriteLogs[index].setTexture(mTextureLogs[2]);
		mSpriteLogs[index].setTextureRect(rect);
	}

	mSpriteLogs[index].setPosition(TREE_BOTTOM_X + LOG_WIDTH / 2, height);
}