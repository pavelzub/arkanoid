#include <algorithm>
#include "GameMap.h"
#include "GameScene.h"
#define sqr(x) ((x)*(x))

USING_NS_CC;

GameMap::GameMap(cocos2d::Scene* scene, cocos2d::Size size, cocos2d::Point origin, std::function<void()> incScore)
{
	_scene = scene;
	_size = size;
	_origin = origin;
	_incScore = incScore;

	_genMap();
}

cocos2d::Vec2 GameMap::checkIntersection(cocos2d::Point point, float r)
{
	cocos2d::Vec2 result = { 1, 1 };
	point -= _origin;
	for (int i = std::max((float)0, (point.x - r) / _blockWidth); i <= std::min((float)width - 1, (point.x + r) / _blockWidth); i++)
		for (int j = std::max((float)0, (point.y - r) / _blockHeigth); j <= std::min((float)heigth - 1, (point.y + r) / _blockHeigth); j++) {
			if (!_map[i][j]->isVisible()) continue;

			Point x1(i * _blockWidth, (j + 1) * _blockHeigth);
			Point x2((i + 1) * _blockWidth, (j + 1) * _blockHeigth);
			Point x3((i + 1) * _blockWidth, j * _blockHeigth);
			Point x4(i * _blockWidth, j * _blockHeigth);

			float X = std::min(_short_way(x1, x2, point),  _short_way(x3, x4, point));
			float Y = std::min(_short_way(x2, x3, point), _short_way(x4, x1, point));
			
			if (std::min(X, Y) > r) continue;
			if (X <= Y)
				result.y = -1;
			if (Y <= X) 
				result.x = -1;
			
			_map[i][j]->setVisible(false);
			_incScore();

			return result;
		}

	return result;
}

float GameMap::_short_way(cocos2d::Point a, cocos2d::Point b, cocos2d::Point c)
{
	double A = a.getDistance(c), B = b.getDistance(c), C = a.getDistance(b);
	double x = (sqr(A) - sqr(B) + sqr(C)) / (2 * C);
	if (x < 0 || x > C) return std::min(A, B);
	return sqrt(sqr(A) - sqr(x));
}

void GameMap::_genMap()
{
	this->_blockWidth = _size.width / width;
	this->_blockHeigth = _size.height / heigth;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < heigth; j++) {
			_map[i][j] = Sprite::create("Block.png");
			_scene->addChild(_map[i][j]);
			_map[i][j]->setPosition(i * this->_blockWidth + this->_blockWidth / 2.0 + _origin.x, j * this->_blockHeigth + this->_blockHeigth / 2.0 + _origin.y);
			_map[i][j]->setScaleY(this->_blockHeigth / _map[i][j]->getContentSize().height);
			_map[i][j]->setScaleX(this->_blockWidth / _map[i][j]->getContentSize().width);
		}
}
