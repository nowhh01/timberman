#include "pch.h"
#include "Game.h"

void Game::draw()
{
	mWindow.clear();
	mWindow.draw(mSpriteBackground);

	for (int i = 0; i < NUM_BACKGROUND_TREES; i++)
	{
		mWindow.draw(mSpriteBackgroundTrees[i]);
	}

	for (int i = 0; i < NUM_LOGS; i++)
	{
		if (i == 0 && mbLogFlying)
		{
			continue;
		}
		mWindow.draw(mSpriteLogs[i]);
	}

	
	mWindow.draw(mSpriteTree);
	mWindow.draw(mPlayer.GetSprite());
	mWindow.draw(mSpriteBee);
	mWindow.draw(mSpriteSun);
	mWindow.draw(mTextScore);
	mWindow.draw(mTimeBar);
	mWindow.draw(mTimeBarGauge);

	if (mbPaused)
	{
		mWindow.draw(mTextMessage);
	}

	if (mSpriteChoppedLogs.size() != 0)
	{
		for (int i = 0; i < mSpriteChoppedLogs.size(); i++)
		{
			mWindow.draw(mSpriteChoppedLogs[i]);
		}
	}

	mWindow.display();
}