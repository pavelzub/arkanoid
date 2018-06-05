#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <cocos2d.h>
#include <map>

class SceneManager 
{
public:
	enum Scenes{Menu, Game, GameOver, HighScores};
	static void startGame();
	static void setScene(Scenes name, int info = 0);

private:
	static cocos2d::Scene* _sceneNow;
	
};
#endif

