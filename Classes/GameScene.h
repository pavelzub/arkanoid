#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <cocos2d.h>
#include "Ball.h"
#include "GameMap.h"
#include "Platform.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	static void problemLoading(const std::string filename);
	int getScore() { return _score; };
	void incScore();
	CREATE_FUNC(GameScene);

protected:
	void update(float dt);

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void _gameOver();
	Ball* _ball;
	GameMap* _gameMap;
	Platform* _platform;
	int _score;

};
#endif

