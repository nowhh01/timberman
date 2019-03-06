#pragma once
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ContentHolder.h"
#include "Player.h"

class Game
{
public:
	Game();

	void Run();

private:
	enum class eTree
	{
		Green,
		Orange
	};

	enum class eSide
	{
		Right = -1,
		None,
		Left
	};

	const float SPEED_CHOPPED_LOG_X = 3.2f;
	const float SPEED_CHOPPED_LOG_Y = -1.4f;
	const float GRAVITY = .02f;

	const float PLAYER_LEFT_POSITION_X = 750;
	const float PLAYER_LEFT_POSITION_Y = 650;
	const float PLAYER_RIGHT_POSITION_X = 1140;
	const float PLAYER_RIGHT_POSITION_Y = 650;

	const float TREE_BOTTOM_X = 830;
	const float TREE_BOTTOM_Y = 800;
	const float LOG_WIDTH = 256;
	const float LOG_HEIGHT = 192;

	const float TIME_BAR_FULL_WIDTH = 250;
	const float AXE_LEFT = 700;
	const float AXE_RIGHT = 1075;
	const float ROTATION_RATE_CHOPPED_LOG = 1.5f;

	const int NUM_LOGS = 6;
	const int NUM_LOG_KINDS = 3;
	const int NUM_BACKGROUND_TREES = 2;

	void input();
	void update();
	void draw();
	void updateBranches();
	void loadSprite(const std::string& filePath, const float& x, const float& y, 
		sf::Sprite* const outSprite);
	void loadText(const sf::Font& font, const std::string& content, int size,
		const sf::Color& color, sf::Text* const outText);
	void loadSideLogBranch(int index);
	void loadTextureLog(int index);

	sf::Sprite* mSpriteLogs = new sf::Sprite[NUM_LOGS];
	eSide* mSideLogBranches = new eSide[NUM_LOGS];
	sf::Sprite* mSpriteBackgroundTrees = 
		new sf::Sprite[NUM_BACKGROUND_TREES];
	sf::Texture* mTextureLogs = new sf::Texture[NUM_LOG_KINDS];
	std::vector<sf::Sprite> mSpriteChoppedLogs;
	std::vector<float> mLogsChoppedSpeedX;
	std::vector<float> mLogsChoppedSpeedY;
	std::vector<float> mLogsChoppedRotation;

	sf::RenderWindow mWindow;
	sf::Sprite mSpriteBackground;
	sf::Sprite mSpriteTree;
	sf::Sprite mSpriteBee;
	sf::Sprite mSpriteSun;

	ContentHolder mContentHolder;
	Player mPlayer;

	std::stringstream mStringStream;
	sf::Time mGameTimeTotal;
	sf::Clock mClock;
	sf::RectangleShape mTimeBar;
	sf::RectangleShape mTimeBarGauge;
	sf::Text mTextMessage;
	sf::Text mTextScore;
	sf::Font mFont;
	sf::Sound mChopSound;
	sf::Sound mDeathSound;

	eSide mPlayerSide = eSide::Left;

	float mTimeBarHeight = 50.f;
	float mTimeRemaining = 1.5f;
	float mTimeBarWidthPerSecond = 
		TIME_BAR_FULL_WIDTH / (mTimeRemaining * 2);
	float mTimeSinceLogChopped;
	float mBeeSpeed;
	int mScore;

	bool mbBeeActive;
	bool mbChopping;
	bool mbLogActive;
	bool mbLogFlying;
	bool mbAcceptInput;
	bool mbPaused = true;
};