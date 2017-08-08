#pragma once
#include "string.h"
#include <string>
using namespace std;

class Callback{
public:
	Callback();
	~Callback();
	virtual void call(std::string receive,int calltag=0);
};