#pragma once
#include"cocos2d.h"
#include"Cell.h"
#include <vector>
class GameScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();


private:
	void menuBackCallback(Ref* pSender);
	virtual bool init();
	CREATE_FUNC(GameScene);

	std::vector<std::vector <Cell*> > vectorCe;
	int cells[16][16] = { 0 };

};

