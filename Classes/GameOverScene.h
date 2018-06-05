#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include <cocos2d.h>

class GameOverScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int score);
	virtual bool init();
	static void problemLoading(const std::string filename);
	void setScore(int score);
	CREATE_FUNC(GameOverScene);

private:
	float _createLables();
	void _saveScore(cocos2d::Ref *);
	void _createMenu(float height);
	int _score = 0;
	cocos2d::Label* _nameLable;
	cocos2d::Label* _scoreLable;

	cocos2d::Size _visibleSize;
};
#endif

