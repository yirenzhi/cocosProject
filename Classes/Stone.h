#pragma once
#include "cocos2d.h"
#include <iostream>
using namespace std;
USING_NS_CC;
class Stone:public Sprite
{
public:
	Stone(void);
	~Stone(void);
	//棋子类型  将，士，相，马，车，炮，兵
	enum StoneType{ JIANG,SHI,XINAG,MA,CHE,PAO,BING };
	static Stone* create(int id);

	CC_SYNTHESIZE(StoneType,_type,Type);
	CC_SYNTHESIZE(int ,_id,Id);
	CC_SYNTHESIZE(int , _x,X);
	CC_SYNTHESIZE(int , _y,Y);

	static struct initAttribute
	{
		int x;
		int y;
		Stone::StoneType type;
	}_initAttribute[16];
	void setPos(int x,int y);
private:
	bool init(int id);
};

