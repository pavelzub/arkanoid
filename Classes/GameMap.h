#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <cocos2d.h>

class GameMap
{
public:
	static const int heigth = 6;
	static const int width = 10;
	GameMap(cocos2d::Scene* scene, cocos2d::Size size, cocos2d::Point origin, std::function<void()> incScore);
	cocos2d::Vec2 checkIntersection(cocos2d::Point point, float r);

private:
	void _genMap();
	float _short_way(cocos2d::Point a, cocos2d::Point b, cocos2d::Point c);

	cocos2d::Sprite* _map[width][heigth];
	cocos2d::Scene* _scene;
	cocos2d::Size _size;
	cocos2d::Point _origin;
	float _blockWidth;
	float _blockHeigth;
	std::function<void()> _incScore;
};
#endif
