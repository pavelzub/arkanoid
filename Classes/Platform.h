#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <cocos2d.h>

class Platform : public cocos2d::CCSprite
{
public:
	Platform(cocos2d::Point pos, float width, float height);
	void move(float dt);
	void setDirection(int d);
	cocos2d::Vec2 checkIntersection(cocos2d::Point point, float r, cocos2d::Vec2 direction);

private:
	float _speed = 10;
	int _direction = 0;
	cocos2d::Point _pos;
	float _height;
	float _width;
};
#endif

