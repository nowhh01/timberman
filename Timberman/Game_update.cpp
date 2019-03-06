#include "pch.h"
#include "Game.h"

void Game::update()
{
	sf::Time dt = mClock.restart();
	float dtAsMilliSeconds = (float)dt.asMilliseconds();
	float dtAsSeconds = dt.asSeconds();
	if (!mbPaused)
	{
		mTimeRemaining -= dtAsSeconds / 2;
		float timeLength = mTimeBarWidthPerSecond * mTimeRemaining;

		mTimeBarGauge.setSize(sf::Vector2f(timeLength, mTimeBarHeight));

		if (mTimeRemaining <= 0.0f)
		{
			mbPaused = true;
			mTextMessage.setString("Game Over");

			sf::FloatRect textRect = mTextMessage.getLocalBounds();
			mTextMessage.setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
			mTextMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);

			mDeathSound.play();
		}
		else
		{
			if (!mbBeeActive)
			{
				srand((int)time(0) * 10);
				mBeeSpeed = (float)(rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (float)(rand() % 500) + 500;
				mSpriteBee.setPosition(2000, height);
				mbBeeActive = true;
			}
			else
			{
				mSpriteBee.setPosition(
					mSpriteBee.getPosition().x - (mBeeSpeed * dt.asSeconds()),
					mSpriteBee.getPosition().y);

				if (mSpriteBee.getPosition().x < -100)
				{
					mbBeeActive = false;
				}
			}

			mStringStream << mScore;
			mTextScore.setString(mStringStream.str());
			mTextScore.setPosition(1920 / 2 - mTextScore.getLocalBounds().width / 2, 200);
			mStringStream.str("");

			if (mbChopping)
			{
				mPlayer.Update(dtAsSeconds);

				if (!mPlayer.IsChopping())
				{
					mbChopping = false;
				}
			}

			if (mbLogActive)
			{
				if (mSideLogBranches[0] == mPlayerSide)
				{
					mPlayer.SetPosition(2000, 650);

					mTextMessage.setString("SQUISHED!!");

					sf::FloatRect textRect = mTextMessage.getLocalBounds();

					mTextMessage.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);

					mTextMessage.setPosition(1920 / 2.0f, 1080 / 2.0f);

					mDeathSound.play();
					mbPaused = true;
					mbAcceptInput = false;
				}
				else
				{
					srand((int)time(0) * mScore);

					float speedX = SPEED_CHOPPED_LOG_X * (int)mPlayerSide;
					float speedY = SPEED_CHOPPED_LOG_Y * (rand() % 4 + 1);
					float rotation = 
						ROTATION_RATE_CHOPPED_LOG * (int)mPlayerSide;

					mSpriteChoppedLogs.push_back(mSpriteLogs[0]);
					mLogsChoppedSpeedX.push_back(speedX);
					mLogsChoppedSpeedY.push_back(speedY);
					mLogsChoppedRotation.push_back(rotation);

					
					loadTextureLog(NUM_LOGS - 1);
					mbLogFlying = true;
				}

				mbLogActive = false;
			}

			if (mbLogFlying)
			{
				mTimeSinceLogChopped += dtAsSeconds;
				if (mTimeSinceLogChopped > .1f)
				{
					updateBranches();
					mTimeSinceLogChopped = 0;
					mbLogFlying = false;
				}
			}
		}
	}
	else
	{
		mbChopping = false;
	}

	if (mSpriteChoppedLogs.size() != 0)
	{
		srand((int)time(0) * mScore);

		for (int i = 0; i < mSpriteChoppedLogs.size(); i++)
		{
			mSpriteChoppedLogs[i].move(sf::Vector2f(
				mLogsChoppedSpeedX[i] * dtAsMilliSeconds,
				mLogsChoppedSpeedY[i] * dtAsMilliSeconds));
			mLogsChoppedSpeedY[i] += GRAVITY * dtAsMilliSeconds;
			mSpriteChoppedLogs[i].rotate(mLogsChoppedRotation[i]);

			if (mSpriteChoppedLogs[0].getPosition().x < 0 
				|| mSpriteChoppedLogs[0].getPosition().x > 1920)
			{
				mSpriteChoppedLogs.erase(mSpriteChoppedLogs.begin());
				mLogsChoppedSpeedX.erase(mLogsChoppedSpeedX.begin());
				mLogsChoppedSpeedY.erase(mLogsChoppedSpeedY.begin());
				mLogsChoppedRotation.erase(mLogsChoppedRotation.begin());
				i--;
			}
		}
	}
}
