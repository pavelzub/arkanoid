#include "Ball.h"
#include <algorithm>
#include "Platform.h"
#define sqr(x) ((x)*(x))

USING_NS_CC;

Platform::Platform(cocos2d::Point pos, float width, float height)
{
	_pos = pos;
	_height = height;
	_width = width;

	_pos.y += height * 0.5f;
	setPosition(_pos);
	initWithFile("Platform.png");

	setScaleX(width / getContentSize().width);
	setScaleY(height / getContentSize().height);
}

void Platform::move(float dt)
{
	_pos.x = std::min(_pos.x + _direction * _speed, Director::getInstance()->getVisibleSize().width - _width / 2.f);
	_pos.x = std::max(_pos.x, _width / 2.f);
	setPositionX(_pos.x);
}

void Platform::setDirection(int d)
{
	_direction = d;
}

cocos2d::Vec2 Platform::checkIntersection(cocos2d::Point point, float r, cocos2d::Vec2 direction)
{
	Point x1(_pos.x - _width * 0.5f, _pos.y + _height * 0.5f);
	Point x2(_pos.x + _width * 0.5f, _pos.y + _height * 0.5f);

	cocos2d::Vec2 result(1, 1);

	double A = x1.getDistance(point), B = x2.getDistance(point), C = x1.getDistance(x2);
	double x = (sqr(A) - sqr(B) + sqr(C)) / (2 * C);

	if (x < 0 || x > C) {
		if (A > r && B > r) return direction;
		if (x < 0 && direction.x <= 0 || x > C && direction.x >= 0)direction.x *= -1;
		direction.y *= -1;
	}
	else if (sqrt(sqr(A) - sqr(x)) < r) {
		if (x < C * 0.2f && direction.x <= 0) {
			float tmp = direction.x;
			direction.x = -std::sin(- M_PI / 6.f) * direction.y + std::cos(- M_PI / 6.f) * direction.x;
			direction.y = -std::sin(- M_PI / 6.f) * tmp - std::cos(- M_PI / 6.f) * direction.y;
		}
		else if (x > C * 0.8f && direction.x >= 0) {
			float tmp = direction.x;
			direction.x = -std::sin(M_PI / 6.f) * direction.y + std::cos(M_PI / 6.f) * direction.x;
			direction.y = -std::sin(M_PI / 6.f) * tmp - std::cos(M_PI / 6.f) * direction.y;
		}
		else direction.y *= -1;
		if (direction.y < 0) direction.y *= -1;
	}
		

	return direction;
}
