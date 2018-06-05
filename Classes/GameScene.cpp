#include "GameScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void GameScene::problemLoading(std::string filename)
{
	printf("Error while loading: %s\n", filename.c_str());
}

void GameScene::incScore()
{
	_score++;
	_ball->setSpeed(_score / 10.f);
}

void GameScene::update(float dt)
{
	_ball->move(dt);
	_platform->move(dt);
}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (!_ball->isMoving()) {
		_ball->start(touch->getLocation());
		return true;
	}

	_platform->setDirection(touch->getLocation().x < Director::getInstance()->getVisibleSize().width * 0.5f ? -1 : 1);

	return true;
}

bool GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	_platform->setDirection(0);
	return true;
}

void GameScene::_gameOver()
{
	SceneManager::setScene(SceneManager::GameOver, _score);
}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;
	
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("game.mpeg", true);

	scheduleUpdate();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_gameMap = new GameMap(this, { visibleSize.width * 0.7f, visibleSize.height * 0.4f }, { visibleSize.width * 0.15f, visibleSize.height * 0.5f }, [this]() {this->incScore(); });
	
	_platform = new Platform({ visibleSize.width * 0.5f, 0 }, visibleSize.width * 0.1f, visibleSize.height * 0.02f);
	addChild(_platform);
	
	_ball = new Ball({ visibleSize.width * 0.5f, visibleSize.height * 0.02f }, _gameMap, _platform, [this]{this->_gameOver(); });
	addChild(_ball);

	return true;
}
