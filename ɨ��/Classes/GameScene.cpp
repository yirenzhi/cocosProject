#include "GameScene.h"
#include "HelloWorldScene.h"
#include <stdio.h>
#include<iostream>
USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{

	const int numCell = 40;

	int changeNum = 0;
	while (changeNum<numCell)
	{
		int x = rand()%16;
		int y = rand()%16;
		CCLOG("%d,%d", x,y);
		if (cells[x][y] == 0)
		{
			cells[x][y] = -1;
			changeNum++;
		}
	}

	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			std::cout << cells[j][i]<<"\t";
		}
		std::cout << std::endl;
	}
	auto lay1 = Layer::create();
	addChild(lay1);
	lay1->setPosition(100, 100);
	//创建所有的雷
	//
	SpriteBatchNode* bNode = SpriteBatchNode::create("game/0.jpg");
	addChild(bNode);
	const int numX = 16;
	const int numY = 16;
	for (size_t i = 0; i < numY; i++)
	{
		std::vector<Cell*> vec1;
		vectorCe.push_back(vec1);
		for (size_t j = 0; j < numX; j++)
		{
			//auto p = Sprite::createWithTexture(bNode->getTexture());
			//auto p = Sprite::create("game/0.jpg");
			auto p = Cell::create(bNode->getTexture());
			lay1->addChild(p);
			p->setPosition(21*j, 21*i);
			vectorCe[i].push_back(p);
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuBackCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//auto p = Sprite::create("game/s.jpg");
	//addChild(p);
	//p->setPosition(300, 300);
	return true;
}


void GameScene::menuBackCallback(Ref* pSender)
{
	CCLOG("start");
	if (Scene *pScene = TransitionFade::create(0.3f, HelloWorld::createScene()))
	{
		CCDirector::getInstance()->replaceScene(pScene);
	}
}

