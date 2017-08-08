#pragma once
#include "cocos2d.h"
#define USING_STD using namespace std;
USING_STD;
class DownloadObject
{
public:
	DownloadObject();
	~DownloadObject();
	virtual void downloadEnd(string path);
	string fromUrl;
	string saveDir;
	string inTheFolder;
	double showTime;
};