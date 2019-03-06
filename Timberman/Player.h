#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void Update(const float& deltaTime);
	void ChangeDirection(int direction);
	bool IsChopping();
	const sf::Sprite& GetSprite() const;
	void SetPosition(const float& x, const float& y);
	
private:
	const int FRAME_WIDTH = 371;
	const int FRAME_HEIGHT = 371;
	const int FRAME_STAND = 0;
	const int FRAME_FIRST_CHOP = 1;
	const int FRAME_NUM_CHOP = 5;
	
	std::map<int, sf::IntRect> mFrames;
	sf::Sprite mSpriteSheet;
	float mCurrentDirection;
	float mCollapsedTimeSinceFrameChanged;
	int mCurrentFrame = FRAME_STAND;
	bool mbChopping;
};