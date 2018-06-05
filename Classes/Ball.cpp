#include "Ball.h"
#include <algorithm>

USING_NS_CC;

Ball::Ball(cocos2d::Point pos, GameMap* gameMap, Platform* platform, std::function<void()> lose) :
	Sprite()
{
	_gameMap = gameMap;
	_pos = pos;
	_platform = platform;
	_lose = lose;
	initWithFile("Ball.png");

	setScaleX(30 / getContentSize().width);
	setScaleY(30 / getContentSize().height);
	_pos.y += getBoundingBox().size.height * 0.5f;
	setPosition(_pos);
}

void Ball::start(cocos2d::Point directionPoint)
{
	_isMoving = true;
	directionPoint.y = std::max(_pos.y + 10, directionPoint.y);
	_direction = directionPoint - _pos;
	_direction.normalize();
}

void Ball::move(float dt)
{
	if (!_isMoving) return;
	_pos += _direction * _speed;

	cocos2d::Vec2 direction = _gameMap->checkIntersection(_pos, getBoundingBox().size.height / 2.0);
	_direction.x *= direction.x;
	_direction.y *= direction.y;
	_direction = _platform->checkIntersection(_pos, getBoundingBox().size.height / 2.0, _direction);

	_checkBorderIntersection();
	setPosition(_pos);
}

void Ball::setSpeed(float speed)
{
	_speed = speed + STARTSPEED;
}

void Ball::_checkBorderIntersection()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (_pos.y - getBoundingBox().size.height / 2 < 0) {
		_lose();
		return;
	}

	if (_pos.x + getBoundingBox().size.width / 2 > visibleSize.width ||
		_pos.x - getBoundingBox().size.width / 2 < 0)
		_direction.x *= -1;
	if (_pos.y + getBoundingBox().size.height / 2 > visibleSize.height)
		_direction.y *= -1;
}
