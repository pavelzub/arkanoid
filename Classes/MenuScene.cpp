#include "MenuScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void MenuScene::problemLoading(std::string filename)
{
	printf("Error while loading: %s\n", filename.c_str());
}

cocos2d::Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
		return false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("menu.mpeg", true);

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	
	int offset = _createTitle();
	_createMenu(offset);

	return true;
}

int MenuScene::_createTitle()
{
	auto titleItem = Label::createWithTTF("Arkanoid", "fonts/Marker Felt.ttf", 150);
	if (titleItem == nullptr) {
		problemLoading("fonts/Marker Felt.ttf");
		return 0;
	}
	titleItem->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
		_origin.y + _visibleSize.height - titleItem->getContentSize().height));

	this->addChild(titleItem, 1);
	return titleItem->getContentSize().height * 2;
}

void MenuScene::_createMenu(int offset)
{
	auto menu = Menu::create();
	menu->setPositionY(_origin.y + _visibleSize.height - offset);

	auto addItem = [menu](int index, std::string firstImagePath, std::string secondImagePath, const ccMenuCallback& callback) {
		auto item = cocos2d::MenuItemImage::create(firstImagePath, secondImagePath, callback);
		if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0) {
			problemLoading(firstImagePath + " and " + secondImagePath);
			return;
		}
		item->setScale(3);
		item->setPositionY(-index * item->getContentSize().height * 3);
		menu->addChild(item);
	};

	addItem(0, "NewGameNormal.png", "NewGameSelected.png", CC_CALLBACK_1(MenuScene::_menuNewGameCallback, this));
	addItem(1, "HighScoresNormal.png", "HighScoresSelected.png", CC_CALLBACK_1(MenuScene::_menuHighScoresCallback, this));
	addItem(2, "ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(MenuScene::_menuExitCallback, this));

	this->addChild(menu);
}

void MenuScene::_menuNewGameCallback(cocos2d::Ref * pSender)
{
	SceneManager::setScene(SceneManager::Game);
}

void MenuScene::_menuHighScoresCallback(cocos2d::Ref * pSender)
{
	SceneManager::setScene(SceneManager::HighScores);
}

void MenuScene::_menuExitCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}
