#include "GameScene.h"
#include "HelloWorldScene.h"
#include <stdio.h>
#include<iostream>
USING_NS_CC;
const int numX = 16;
const int numY = 16;
const int numCell = 40;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	//初始化雷的分布
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


	for (size_t i = 0; i < numX; i++)
	{
		for (size_t j = 0; j < numY; j++)
		{	
			if (cells[i][j]==-1)
			{
				continue;
			}
			int count = 0;
			//计算每个格子应该显示的数字的算法
			int kuangNums[8][2] = { { i - 1 ,j - 1},{ i - 1 ,j},{ i - 1 ,j + 1 },{ i ,j - 1 },{ i ,j + 1 },{ i + 1 ,j - 1 },{ i + 1 ,j },{ i + 1 ,j + 1 } };
			for (size_t m = 0; m < 8; m++)
			{
				if (kuangNums[m][0] == -1 || kuangNums[m][0] == 16 || kuangNums[m][1] == -1 || kuangNums[m][1] == 16)
				{
					continue;
				}
				count += (cells[kuangNums[m][0]][kuangNums[m][1]]);
			}
			cells[i][j] = -count;
		}
	}

	auto lay1 = Layer::create();
	addChild(lay1);
	lay1->setPosition(100, 100);

	//给精灵帧赋值
	for (size_t i = 0; i < 11; i++)
	{
		char buffer[128];
		if (i<9)
		{
			sprintf(buffer, "game/%d.jpg", i);
		}
		else if (i==9)
		{
			sprintf(buffer, "game/%c.jpg", 's');
		}
		else if(i==10)
		{
			sprintf(buffer, "game/%s.jpg", 'bomb');
		}
		SpriteBatchNode* bNode = SpriteBatchNode::create(buffer);
		addChild(bNode);
		Cell::vecBatch.push_back(bNode->getTexture());
	}
	SpriteBatchNode* bNode = SpriteBatchNode::create("game/0.jpg");
	addChild(bNode);
	//创建所有的雷
	//

	for (size_t i = 0; i < numY; i++)
	{
		std::vector<Cell*> vec1;
		vectorCe.push_back(vec1);
		for (size_t j = 0; j < numX; j++)
		{
			//auto p = Sprite::createWithTexture(bNode->getTexture());
			//auto p = Sprite::create("game/0.jpg");
			auto p = new Cell;
			lay1->addChild(p);
			p->setPosition(21*j, 21*i);
			vectorCe[i].push_back(p);
		}
	}
	//增加返回到上一个界面的菜单
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

	//增加触摸机制
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create(); 
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this); 
		listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this); 
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	//触摸判断
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			auto pos = touch->getLocationInView();
			pos = Director::getInstance()->convertToGL(pos);

			pos = vectorCe[i][j]->convertToNodeSpace(pos);
			Size sz = vectorCe[i][j]->getTexture()->getContentSizeInPixels();
			Rect rect = Rect(0, 0, sz.width, sz.height);
			if (rect.containsPoint(pos))
			{
				log("ok");
				vectorCe[i][j]->changeImage();
			}
		}
	}

	return true;
}
void GameScene::onTouchEnded(Touch *touch, Event *event)
{


}
