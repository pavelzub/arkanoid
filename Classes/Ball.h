#ifndef __BALL_H__
#define __BALL_H__

#include <cocos2d.h>
#include "GameMap.h"
#include "Platform.h"

class Ball : public cocos2d::CCSprite
{
public:
	Ball (cocos2d::Point pos, GameMap* gameMap, Platform* platform, std::function<void()> lose);
	void start(cocos2d::Point directionPoint);
	void move(float dt);
	void setSpeed(float speed);
	bool isMoving() { return _isMoving; };

private:
	void _checkBorderIntersection();
	std::function<void()> _lose;

	const float STARTSPEED = 6;

	GameMap* _gameMap;
	Platform* _platform;
	cocos2d::Point _pos;
	bool _isMoving = false;
	float _speed = STARTSPEED;
	cocos2d::Vec2 _direction;
};
#endif

