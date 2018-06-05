#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "HighscoreScene.h"

cocos2d::Scene* SceneManager::_sceneNow;

void SceneManager::startGame()
{
	_sceneNow = MenuScene::createScene();
	cocos2d::Director::getInstance()->runWithScene(_sceneNow);
}

void SceneManager::setScene(Scenes name, int info)
{
	auto tmp = _sceneNow;
	switch (name)
	{
	case SceneManager::Menu:
		_sceneNow = MenuScene::createScene();
		break;
	case SceneManager::Game:
		_sceneNow = GameScene::createScene();
		break;
	case SceneManager::GameOver:
		_sceneNow = GameOverScene::createScene(info);
		break;
	case SceneManager::HighScores:
		_sceneNow = HighscoreScene::createScene();
		break;
	default:
		break;
	}
	cocos2d::Director::getInstance()->replaceScene(_sceneNow);
	//delete tmp;
}
