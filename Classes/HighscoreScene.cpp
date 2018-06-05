#include "GameScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
#include "HighscoreScene.h"

USING_NS_CC;

void HighscoreScene::problemLoading(std::string filename)
{
	printf("Error while loading: %s\n", filename.c_str());
}

void HighscoreScene::_createTable()
{
	auto user = UserDefault::getInstance();

	for (int i = 0; i < 10; i++) {
		std::string nameStr = "name_" + std::to_string(i);
		std::string valueStr = "value_" + std::to_string(i);
		std::string text = std::to_string(i + 1) + ".   \"" +  user->getStringForKey(nameStr.c_str(), "") + "\"   "
			+ std::to_string(user->getIntegerForKey(valueStr.c_str(), 0));
		auto titleItem = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 50);

		titleItem->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f,
			Director::getInstance()->getVisibleSize().height - titleItem->getContentSize().height * (i + 1));
		this->addChild(titleItem);
	}

	auto BtnBack = cocos2d::MenuItemImage::create("Back.png", "Backp.png", [](cocos2d::Ref * pSender) {
		SceneManager::setScene(SceneManager::Menu);
	});
	if (BtnBack == nullptr || BtnBack->getContentSize().width <= 0 || BtnBack->getContentSize().height <= 0) {
		problemLoading("Back.png and Backp.png");
		return;
	}

	auto menu = Menu::create();
	BtnBack->setPositionY(-Director::getInstance()->getVisibleSize().height * 0.5f + BtnBack->getContentSize().height);
	menu->addChild(BtnBack);
	this->addChild(menu);
}

cocos2d::Scene * HighscoreScene::createScene()
{
	return HighscoreScene::create();
}

bool HighscoreScene::init()
{
	if (!Scene::init())
		return false;
	_createTable();
	return true;
}
