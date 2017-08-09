#pragma once
#include "cocos2d.h"
#include <vector>
class Cell :
	public cocos2d::Sprite
{
public:
	//static Cell* create() {
	//	Cell* cell = new Cell();
	//	cell->initWithTexture(vecBatch[0]);
	//	cell->autorelease();
	//	return cell;
	//}
	Cell() :_id(9), _type(false) {
		initWithTexture(vecBatch[0]);
		autorelease();
	}

	CC_SYNTHESIZE(int, _id, Id);
	CC_SYNTHESIZE(bool, _type, Type);
	void changeImage();
	void changeImage(cocos2d::Texture2D* text1);

	static std::vector <cocos2d::Texture2D*> vecBatch;
private:
};

