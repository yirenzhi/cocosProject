#include "Stone.h"

const string stonePic[14]={
	"rshuai.png", //(红色)帅
	"rshi.png",   //(红色)士
	"rxiang.png", //(红色)相
	"rma.png",    //(红色)马
	"rche.png",   //(红色)车
	"rpao.png",   //(红色)炮
	"rbing.png",  //(红色)兵

	"bjiang.png", //(黑色)将
	"bshi.png",   //(黑色)士
	"bxiang.png", //(黑色)相
	"bma.png",    //(黑色)马
	"bche.png",   //(黑色)车
	"bpao.png",   //(黑色)炮
	"bzu.png"     //(黑色)卒
};


Vec2 Stone::jiange = Vec2(61,61);
Vec2 Stone::initialPos = Vec2(83,46);

Stone::Stone(void)
{
}


Stone::~Stone(void)
{
}

Stone* Stone::create(int id)
{
	Stone* stone = new Stone();
	stone->init(id);
	stone->autorelease();
	return stone;
}

bool Stone::init(int id)
{
	if (id<16)
	{
		setColorT(Stone::RED);
	}
	else
	{
		setColorT(Stone::BLACK);
	}
	setId(id);
	
	int type_id = id<16?id:id-16;
	setX(_initAttribute[type_id].x);
	setY(_initAttribute[type_id].y);
	setType(_initAttribute[type_id].type);

	int p_id = id<16?getType():getType()+7;
	Sprite::initWithFile("stone/"+stonePic[p_id]);
	int pos_y = id<16?getY():9-getY();
	setPos(getX(),pos_y);
	setY(pos_y);
	setScale(0.9);
	return true;
}

void Stone::setPos(int x,int y)
{
	this->setPosition(initialPos.x+jiange.x*x,initialPos.y+jiange.y*y);
}


Stone::initAttribute Stone::_initAttribute[16]=
{
	//棋子类型  将，士，相，马，车，炮，兵
	{4,0,Stone::JIANG},
	{3,0,Stone::SHI},
	{5,0,Stone::SHI},
	{2,0,Stone::XINAG},
	{6,0,Stone::XINAG},
	{1,0,Stone::MA},
	{7,0,Stone::MA},
	{0,0,Stone::CHE},
	{8,0,Stone::CHE},
	{1,2,Stone::PAO},
	{7,2,Stone::PAO},
	{0,3,Stone::BING},
	{2,3,Stone::BING},
	{4,3,Stone::BING},
	{6,3,Stone::BING},
	{8,3,Stone::BING},
};