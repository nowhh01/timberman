#include "pch.h"
#include "Player.h"
#include "ContentHolder.h"

Player::Player()
{
	for (int i = 0; i <= FRAME_NUM_CHOP; i++)
	{
		mFrames[i] = sf::IntRect((0 + FRAME_WIDTH * i), 0,
			FRAME_WIDTH, FRAME_HEIGHT);
	}

	mSpriteSheet.setTexture(
		ContentHolder::FindTexture("graphics/player_sprite.png"));
	mSpriteSheet.setTextureRect(mFrames[FRAME_STAND]);
	mSpriteSheet.setPosition(750, 650);
	mSpriteSheet.setOrigin(FRAME_WIDTH / 2.f, 0);
}

void Player::Update(const float& deltaTime)
{
	if (!mbChopping)
	{
		mbChopping = true;
	}

	mCollapsedTimeSinceFrameChanged += deltaTime;

	if (mCollapsedTimeSinceFrameChanged > .02f)
	{
		mCollapsedTimeSinceFrameChanged = 0;

		if (mCurrentFrame == FRAME_NUM_CHOP)
		{
			mCurrentFrame = FRAME_STAND;
			mbChopping = false;
		}
		else
		{
			mCurrentFrame++;
		}
	}

	mSpriteSheet.setTextureRect(mFrames[mCurrentFrame]);
}

void Player::ChangeDirection(int direction)
{
	mSpriteSheet.setScale((float)direction, 1.f);
}

bool Player::IsChopping()
{
	return mbChopping;
}

const sf::Sprite& Player::GetSprite() const
{
	return mSpriteSheet;
}

void Player::SetPosition(const float& x, const float& y)
{
	mSpriteSheet.setPosition(x, y);
}