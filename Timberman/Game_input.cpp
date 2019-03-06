#include "pch.h"
#include "Game.h"

void Game::input()
{
	sf::Event event;

	while (mWindow.pollEvent(event)) 
	{
		if (event.type == sf::Event::KeyReleased && !mbPaused) 
		{
			mbAcceptInput = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
	{
		mWindow.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) 
	{
		if (mbPaused)
		{
			mPlayer.SetPosition(PLAYER_LEFT_POSITION_X, 
				PLAYER_LEFT_POSITION_Y);
			mPlayer.ChangeDirection(1);
			mTimeRemaining = 1.5f;
			mScore = 0;

			mbAcceptInput = true;
			mbPaused = false;
		}
	}

	if (mbAcceptInput) 
	{
		auto right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		auto left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

		if (right || left)
		{
			if (right)
			{
				mbChopping = true;
				mPlayer.SetPosition(PLAYER_RIGHT_POSITION_X, 
					PLAYER_RIGHT_POSITION_Y);
				mPlayerSide = eSide::Right;
			}
			else
			{
				mbChopping = true;
				mPlayer.SetPosition(PLAYER_LEFT_POSITION_X, 
					PLAYER_LEFT_POSITION_Y);
				mPlayerSide = eSide::Left;
			}

			mTimeRemaining += 1 / ((mScore / 30) / 2 + 1.0f) * .2f;
			
			if (mTimeRemaining > 3.0f)
			{
				mTimeRemaining = 3.f;
			}

			mPlayer.ChangeDirection((int)mPlayerSide);
			mScore++;

			mChopSound.play();

			mbLogActive = true;
			mbAcceptInput = false;
		}
	}
}
