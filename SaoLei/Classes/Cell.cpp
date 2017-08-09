#include "Cell.h"

std::vector <cocos2d::Texture2D*> Cell::vecBatch;


void Cell::changeImage()
{
	if (!_type)
	{
		_type = true;
		setTexture(vecBatch[_id]);
	}
}

void Cell::changeImage(cocos2d::Texture2D* text1)
{
	setTexture(text1);
}
