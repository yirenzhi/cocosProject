#pragma once
#include "cocos2d.h"
class Cell :
	public cocos2d::Sprite
{
public:
	static Cell* create(cocos2d::Texture2D* texture) {
		Cell* cell = new Cell();
		cell->initWithTexture(texture);
		cell->autorelease();
		return cell;
	}
	Cell();
	~Cell();
};

