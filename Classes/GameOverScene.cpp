#include "GameOverScene.h"
#include "SceneManager.h"

USING_NS_CC;

cocos2d::Scene * GameOverScene::createScene(int score)
{	
	auto scene = GameOverScene::create();
	scene->setScore(score);
	return scene;
}

bool GameOverScene::init()
{
	if (!Scene::init())
		return false;
	
	_visibleSize = Director::getInstance()->getVisibleSize();

	float height = _createLables();
	if (!height) return false;
	_createMenu(height);

	return true;
}

void GameOverScene::problemLoading(const std::string filename)
{
	printf("Error while loading: %s\n", filename.c_str());
}

void GameOverScene::setScore(int score)
{
	_score = score;
	_scoreLable->setString(_scoreLable->getString() + std::to_string(_score));
}

float GameOverScene::_createLables()
{
	float height = 0;
	_scoreLable = Label::createWithTTF("  Game over\nYour score:  ", "fonts/Marker Felt.ttf", 80);
	if (_scoreLable == nullptr) {
		problemLoading("fonts/Marker Felt.ttf");
		return 0;
	}
	
	height = _scoreLable->getContentSize().height;
	_scoreLable->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - height * 0.5f));
	this->addChild(_scoreLable);

	_nameLable = Label::createWithTTF("A", "fonts/Marker Felt.ttf", 100);
	height += _nameLable->getContentSize().height;
	_nameLable->setString("");
	
	_nameLable->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - height));
	this->addChild(_nameLable);

	return height;
}

void GameOverScene::_saveScore(cocos2d::Ref *)
{
	std::vector<std::pair<int, std::string>> scores;
	scores.push_back({_score, _nameLable->getString()});

	auto user = UserDefault::getInstance();
	for (int i = 0; i < 10; i++) {
		std::string nameStr = "name_" + std::to_string(i);
		std::string valueStr = "value_" + std::to_string(i);
		scores.push_back({ user->getIntegerForKey(valueStr.c_str(), 0), 
			user->getStringForKey(nameStr.c_str(), "") });
	}

	std::sort(scores.rbegin(), scores.rend());

	for (int i = 0; i < 10; i++) {
		std::string nameStr = "name_" + std::to_string(i);
		std::string valueStr = "value_" + std::to_string(i);
		user->setIntegerForKey(valueStr.c_str(), scores[i].first);
		user->setStringForKey(nameStr.c_str(), scores[i].second);
	}

	SceneManager::setScene(SceneManager::Menu);
}

void GameOverScene::_createMenu(float height)
{
	auto menu = Menu::create();
	menu->setPosition(0, -height * 0.5f);
	menu->setScale(0.6f, 1 - height / _visibleSize.height);
	auto q = menu->boundingBox().size;
	float btnWidth = _visibleSize.width / 7.f;
	float btnHeight = (_visibleSize.height - height) / 4.f;
	btnHeight += 0;
	btnWidth += 0;

	auto addItem = [menu, btnWidth, btnHeight](int index, std::string firstImagePath, std::string secondImagePath, const ccMenuCallback& callback) {
		auto item = cocos2d::MenuItemImage::create(firstImagePath, secondImagePath, callback);
		if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0) {
			problemLoading(firstImagePath + " and " + secondImagePath);
			return;
		}
		item->setScaleX((btnWidth * 0.9) / item->getContentSize().width);
		item->setScaleY((btnHeight * 0.9) / item->getContentSize().height);
		item->setPosition((index % 7 + 0.5f) * btnWidth, (4.f - index / 7) * btnHeight);
		menu->addChild(item);
	};

	for (char i = 'A'; i <= 'Z'; i++) 
		addItem(i - 'A', std::string(1, i) + ".png", std::string(1, i) + "p.png", [this, i](cocos2d::Ref * pSender) {
			if (this->_nameLable->getString().size() < 4) this->_nameLable->setString(this->_nameLable->getString() + i);
		});
	
	addItem(26, "Backspace.png", "Backspacep.png", [this](cocos2d::Ref * pSender) {
		if (this->_nameLable->getString().size() > 0) this->_nameLable->setString(this->_nameLable->getString().substr(0, 
																				  this->_nameLable->getString().size() - 1));
	});

	addItem(27, "OK.png", "OKp.png", CC_CALLBACK_1(GameOverScene::_saveScore, this));

	this->addChild(menu);
}
