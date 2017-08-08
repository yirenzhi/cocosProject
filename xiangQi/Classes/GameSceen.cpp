#include "GameSceen.h"
#include "FirstScene.h"
#include <functional>
#include <algorithm>
const string GameSceenPath="gameScreen/";

bool GameSceen::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize=Director::getInstance()->getWinSize();

	auto bg = Sprite::create(GameSceenPath+"bg0.jpg");
	bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(bg);

	ADD_TOUCH_ONE(GameSceen);
	ADD_TOUCH_KEY(GameSceen);


	_stoneOffset=Vec2(83,46);
	_plateOffset=Vec2(20,10);
	_stoneSpace=61;
	_isSelected=false;
	focus=NULL;
	//桌子
	auto zhuozi = Sprite::create(GameSceenPath+"floor.jpg");
	zhuozi->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(zhuozi);
	zhuozi->setScaleX(winSize.width/zhuozi->getContentSize().width);
	zhuozi->setScaleY(winSize.height/zhuozi->getContentSize().height);

	//棋盘
	auto qipan = Sprite::create(GameSceenPath+"background.png");
	//设置棋盘的偏移值
	qipan->setAnchorPoint(Vec2(0,0));
	qipan->setPosition(_plateOffset);
	qipan->setScale((winSize.height-2*_plateOffset.y)/qipan->getContentSize().height);
	addChild(qipan);

	//菜单
	//新局   //开始  //悔棋   //暂停  //难度
	auto menu = Menu::create();
	addChild(menu);

	string menusImage[] = {"new","start","regret","pause","difficulty"};
	int len = sizeof(menusImage)/sizeof(menusImage[0]);


//	std::function<void(Ref*)> bind_func = CC_CALLBACK_1(GameSceen::start,this);
	//vector<const ccMenuCallback&>  callbackFuc;
	vector<std::function<void(Ref*)>>  callbackFuc;

	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::newGame,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::start,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::regret,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::pause ,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::difficulty,this));
	for (int i=0;i<len;i++)
	{
		auto newGame = MenuItemImage::create(GameSceenPath+menusImage[i]+".jpg",GameSceenPath+menusImage[i]+".jpg",callbackFuc[i]);
		menu->addChild(newGame);
		newGame->setPosition(Vec2(280,220-i*80));
	}

	//棋子
	for(int i=0;i<32;i++)
	{
		auto stone = Stone::create(i);
		addChild(stone);
		vecStone.push_back(stone);
	}

	curMoveType=Stone::RED;
	return true;
}


bool GameSceen::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos= touch->getLocation();

	int x,y;		//用来存储触摸点对应的棋盘x,y值
	if (!getClickPos(pos,x,y))
	{
		return false;
	}
	
	int selectId = getStoneID(x,y);
// 	if ()
// 	{
// 	}
	if (selectId==focusId)
	{
		return false;
	}
	if (_isSelected)//已经有棋子选中
	{
		moveStone(focusId,x,y);
	}
	else//没有棋子选中
	{
		if (selectId!=-1)
		{
			//如果选中的棋子不是要走的那一家则无法行动
			if (vecStone[selectId]->getColorT()!=curMoveType)
			{
				return true;
			}
			focusId=selectId;
			changeFocus(x,y);
		}
	}

	return true;
}

Vec2 GameSceen::getPlatePos(int x,int y)
{

	int xx = x*61;
	int yy = y*61;
	return Vec2(xx,yy)+_stoneOffset;
}

int GameSceen::getStoneID(int x,int y)
{
	for (unsigned int i=0;i<vecStone.size();i++)
	{
		if (x==vecStone[i]->getX()&&y==vecStone[i]->getY())
		{
			return vecStone[i]->getId();
		}
	}
	return -1;

}

void GameSceen::changeFocus(int x,int y)
{
	if(focus==NULL)
	{
		focus=Sprite::create(GameSceenPath+"selected.png");
		addChild(focus);
	}

	focus->setPosition(getPlatePos(x,y));
	_isSelected=true;
}

bool GameSceen::getClickPos(Vec2 point, int &x, int &y)
{
	for (x=0;x<9;x++)
	{
		for (y=0;y<10;y++)
		{
			Vec2 platePos = getPlatePos(x,y);
			if (point.getDistance(platePos)<30)
			{
				return true;
			}
		}
	}
	return false;
}

void GameSceen::moveStone(int selectId,int x,int y)
{
	if (canMove(vecStone[selectId],x,y))
	{
		//吃子
		int moveId = getStoneID(x,y);
		if (moveId!=-1)
		{
			reMove(moveId);
		}
		//移动棋子
		vecStone[selectId]->setX(x);
		vecStone[selectId]->setY(y);
		vecStone[selectId]->setPosition(getPlatePos(x,y));
		focusId = getStoneID(x,y);
		focus->setPosition(getPlatePos(x,y));
		_isSelected=false;
		if (curMoveType==Stone::RED)
		{
			curMoveType=Stone::BLACK;
		}
		else
		{
			curMoveType=Stone::RED;
		}
	}
}
bool	GameSceen::canMove(Stone* sto,int x,int y)
{
	//判断目标没有自己家的棋子
	int moveId = getStoneID(x,y);
	if (moveId!=-1)
	{
		if (sto->getColorT()==vecStone[moveId]->getColorT())
		{
			//将光标移动过来
			focusId=moveId;
			changeFocus(x,y);

			return false;
		}
	}
	int stoX=sto->getX();
	int stoY=sto->getY();
	switch (sto->getType())
	{
	case Stone::JIANG:
		{
			if (sto->getColorT()==Stone::RED)
			{
				//帅要在中间区域内行动
				if (x>=3&&x<=5&&y>=0&&y<=2)
				{
					//帅只能移动一步，将要移动的位置只能是他四周的点
					if ((stoX==x&&abs(stoY-y)==1)||(stoY==y&&abs(stoX-x)==1))
					{
						return true;
					}
				}
			}
			else
			{
				//将要在中间区域内行动
				if (x>=3&&x<=5&&y>=7&&y<=9)
				{
					//将只能移动一步，将要移动的位置只能是他四周的点
					if ((stoX==x&&abs(stoY-y)==1)||(stoY==y&&abs(stoX-x)==1))
					{
						return true;
					}
				}
			}
		}
		break;
	case Stone::SHI:
		{ 
			if (sto->getColorT()==Stone::RED)
			{
				//红士要在中间区域内行动
				if (x>=3&&x<=5&&y>=0&&y<=2)
				{
					//士只能移动一步，将要移动的位置只能是他四周的点
					if (abs(stoX-x)==1&&abs(stoY-y)==1)
					{
						return true;
					}
				}
			}
			else
			{
				//黑士要在中间区域内行动
				if (x>=3&&x<=5&&y>=7&&y<=9)
				{
					//士只能移动一步，将要移动的位置只能是他四周的点
					if (abs(stoX-x)==1&&abs(stoY-y)==1)
					{
						return true;
					}
				}
			}
		}
		break;
	case Stone::XINAG:
		{
			if (sto->getColorT()==Stone::RED)
			{
				//红象要在中间区域内行动
				if (x>=0&&x<=8&&y>=0&&y<=4)
				{
					//象只能移动一步，将要移动的位置只能是他四周的点
					if (abs(stoX-x)==2&&abs(stoY-y)==2)
					{
						return true;
					}
				}
			}
			else
			{
				//黑象要在中间区域内行动
				if (x>=0&&x<=8&&y>=5&&y<=9)
				{
					//象只能移动一步，将要移动的位置只能是他四周的点
					if (abs(stoX-x)==2&&abs(stoY-y)==2)
					{
						return true;
					}
				}
			}
		}
		break;
	case Stone::MA:
		{
			//马飞日，且不能憋马腿
			if (stoY+2==y&&abs(stoX-x)==1&&getStoneID(stoX,stoY+1)==-1)//向上飞
			{
				return true;
			}
			else if (stoY-2==y&&abs(stoX-x)==1&&getStoneID(stoX,stoY-1)==-1)//向下飞
			{
				return true;
			}
			else if (stoX-2==x&&abs(stoY-y)==1&&getStoneID(stoX-1,stoY)==-1)//向左飞
			{
				return true;
			}
			else if (stoX+2==x&&abs(stoY-y)==1&&getStoneID(stoX+1,stoY)==-1)//向右飞
			{
				return true;
			}
		}
		break;
	case Stone::CHE:
		{
			if (stoY==y&&stoX!=x)//水平移动
			{
				if (x>stoX)
				{
					for (int i=stoX+1;i<x;i++)
					{
						if (getStoneID(i,stoY)!=-1)
						{
							return false;
						}
					}
				}
				else
				{
					for (int i=stoX-1;i>x;i--)
					{
						if (getStoneID(i,stoY)!=-1)
						{
							return false;
						}
					}
				}
				return true;
			}
			else if(stoX==x&&stoY!=y)
			{
				if (y>stoY)
				{
					for (int i=stoY+1;i<y;i++)
					{
						if (getStoneID(stoX,i)!=-1)
						{
							return false;
						}
					}
				}
				else
				{
					for (int i=stoY-1;i>y;i--)
					{
						if (getStoneID(stoX,i)!=-1)
						{
							return false;
						}
					}
				}
				return true;
			}
		}
		break;
	case Stone::PAO:
		{
			if (stoY==y&&stoX!=x)//水平移动
			{
				int num=0;
				if (x>stoX)
				{
					for (int i=stoX+1;i<x;i++)
					{
						if (getStoneID(i,stoY)!=-1)
						{
							num++;
						}
					}
				}
				else
				{
					for (int i=stoX-1;i>x;i--)
					{
						if (getStoneID(i,stoY)!=-1)
						{
							num++;
						}
					}
				}
				if (num==0)
				{
					return true;
				}
				else if (num==1)
				{
					//炮打间隔的棋子
					if (getStoneID(x,y)!=-1)
					{
						return true;
					}
				}
			}
			else if(stoX==x&&stoY!=y)
			{
				int num=0;
				if (y>stoY)
				{
					for (int i=stoY+1;i<y;i++)
					{
						if (getStoneID(stoX,i)!=-1)
						{
							num++;
						}
					}
				}
				else
				{
					for (int i=stoY-1;i>y;i--)
					{
						if (getStoneID(stoX,i)!=-1)
						{
							num++;
						}
					}
				}
				if (num==0)
				{
					return true;
				}
				else if (num==1)
				{
					//炮打间隔的棋子
					if (getStoneID(x,y)!=-1)
					{
						return true;
					}
				}
			}
		}
		break;
	case Stone::BING:
		{
			if (sto->getColorT()==Stone::RED)
			{
				if (stoY==y-1&&stoX==x)
				{
					return true;
				}
				else if (stoY>4)
				{
					if (stoY==y&&abs(stoX-x)==1)
					{
						return true;
					}
				}
			}
			else
			{
				if (stoY==y+1&&stoX==x)
				{
					return true;
				}
				else if (stoY<=4)
				{
					if (stoY==y&&abs(stoX-x)==1)
					{
						return true;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return false;
}

void GameSceen::reMove(int removeId)
{
	vecStone[removeId]->removeFromParent();
	//在vector中删除吃掉的子
	std::vector<Stone *>::iterator iter=std::find(vecStone.begin(),vecStone.end(),vecStone[removeId]);
	vecStone.erase(iter);
}

void GameSceen::onTouchEnded(Touch *touch, Event *unused_event)
{

}


void GameSceen::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACK==keyCode)
	{
		REPLACE_SCENE(FirstScene);
	}
}
void GameSceen::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}
void GameSceen::update(float delta)
{

}

void GameSceen::start(Ref*)
{
	log("start");
}

void GameSceen::newGame(Ref*)
{
	log("newGame");
}
void GameSceen::regret(Ref*)
{
	log("regret");
}
void GameSceen::pause(Ref*)
{
	log("pause");
}
void GameSceen::difficulty(Ref*)
{
	log("difficulty");
}
