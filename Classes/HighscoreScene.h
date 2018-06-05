#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__

#include <cocos2d.h>

class HighscoreScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	static void problemLoading(const std::string filename);
	CREATE_FUNC(HighscoreScene);

private:
	void _createTable();

};
#endif

