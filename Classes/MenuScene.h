#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include <cocos2d.h>

class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	static void problemLoading(const std::string filename);
	CREATE_FUNC(MenuScene);

private:
	int _createTitle();
	void _createMenu(int offset);
	void _menuNewGameCallback(cocos2d::Ref* pSender);
	void _menuHighScoresCallback(cocos2d::Ref* pSender);
	void _menuExitCallback(cocos2d::Ref* pSender);

	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;
};
#endif

