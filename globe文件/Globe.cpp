#include "Globe.h"

bool Globe::isPlaySound = false;
string Globe::gameSoSavePath = "soPath";//游戏so的保存目录
string Globe::gameInfoSavePath = "gameInfo";//游戏详情页面的目录
string Globe::homePageSavaPath = "homePage";//首页图片保存目录
string Globe::gameVariousSavaPath = "gameVarious";//首页图片保存目录
string Globe::gameIconSavePath = "gameIcon";
string Globe::huodongSavaPath = "huodong";//活动界面图片保存目录
string Globe::zhuantiSavaPath = "zhuanti";//专题界面图片保存目录
string Globe::chouJiangSavaPath = "chouJiang";
string Globe::loadingSavaPath = "loading";
string Globe::payMentSavaPath = "pay";
Globe::Globe(void){

}

Globe::~Globe(void){

}
std::vector<std::string> Globe::split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

//std::wstring Globe::StringToWString(const std::string& s)
//  {
//    setlocale(LC_ALL, "chs");   
//    const char* _Source = s.c_str();  
//    size_t _Dsize = s.size() + 1;  
//    wchar_t *_Dest = new wchar_t[_Dsize];  
//    wmemset(_Dest, 0, _Dsize);  
//    mbstowcs(_Dest,_Source,_Dsize);  
//    std::wstring result = _Dest;  
//    delete []_Dest;  
//    setlocale(LC_ALL, "C");  
//    return result;  
//  }
//  
//  //只拷贝低字节至string中
//std::string Globe::WStringToString(const std::wstring& ws)
//{
//    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";  
//	setlocale(LC_ALL, "chs");  
//	const wchar_t* _Source = ws.c_str();  
//	size_t _Dsize = 2 * ws.size() + 1;  
//	char *_Dest = new char[_Dsize];  
//	memset(_Dest,0,_Dsize);  
//	wcstombs(_Dest,_Source,_Dsize);  
//	std::string result = _Dest;  
//	delete []_Dest;  
//	setlocale(LC_ALL, curLocale.c_str());  
//	return result;  
//
//}

string Globe::intToString(int a){
	stringstream s;    
	s<<a;
	return (s.str());
}

string Globe::floatToString(float f){
	ostringstream oss;
	oss<<f;
	string str(oss.str());
	return str;
}
float Globe::StringTofloat(string f)
{
	float number = std::atof(f.c_str());
	return number;
}

int Globe::stringToInt(string a){
	int number = std::atoi( a.c_str() ); 
	return number;
}

float Globe::get02Float(float a){
	return int((a+0.5)*100)/100.0;
}

string Globe::intArrayToString(int *a,int lenght){

	int arrayLength=lenght;  

	string strs;  

	for(int i=0;i<arrayLength;i++)  
	{  
		int &temp=a[i];  
		strs+=intToString(temp)+",";  
	} 
	return strs;
}


float Globe::abs(float a){
	return (a>=0?a:-a);
}

CCActionInterval *Globe::moveForBeser(CCPoint p1,CCPoint p2,CCPoint air,float time){
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1=p1;//控制点1
	bezierCon.controlPoint_2=p2;//控制点2
	bezierCon.endPosition =air;// 结束位置
	// CCBezierTo
	//    创建一个贝塞尔曲线运动的动作
	//    参数1：贝塞尔曲线运动的时间
	//    参数2 ：ccBezierConfig结构体   
	CCActionInterval * action = CCBezierTo::create(time, bezierCon);
	//CCActionInterval * action = CCBezierBy::create(3, bezierCon);//支持反向
	//CCActionInterval * action1 = action->reverse();
	return action;
}

int Globe::getRandom(int end)
{
	int time = getCurrentTime()%100000;
	float ra = CCRANDOM_0_1();
	int rand_ = (time*ra);
	int ret = (rand_%end);
	if(ret<0){
		ret = ret+end;
	}
	return ret;
}

long Globe::getCurrentTime()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
} 

bool Globe::rectContainsPoint(CCRect rect,CCPoint p){
	if(p.x>=rect.origin.x&&p.x<=rect.origin.x+rect.size.width&&
		p.y>=rect.origin.y&&p.y<=rect.origin.y+rect.size.height){
			playEffect("button.mp3");
			return true;
	}else{
		return false;
	}
}

bool Globe::rectContainsTiles(CCRect rect,CCPoint p){
	if(p.x>=rect.origin.x&&p.x<=rect.origin.x+rect.size.width&&
		p.y>=rect.origin.y&&p.y<=rect.origin.y+rect.size.height){
			return true;
	}else{
		return false;
	}
}

void Globe::playBgSound(string sddr,bool isLoop){
	if(!isPlaySound){
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(sddr.c_str(),isLoop);
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		return;
	}else{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(sddr.c_str(),isLoop);
	}
}
void Globe::playEffect(string sddr){
	if(!isPlaySound){
		return;
	}else{
		SimpleAudioEngine::sharedEngine()->playEffect(sddr.c_str(),false);
	}
}

void Globe::setSound(bool is){
	isPlaySound = is;
	if(!isPlaySound){
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
	}else{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

void Globe::closeBgSound(){
	SimpleAudioEngine::sharedEngine()->end();
}


//CCSpriteBatchNode* Globe::creatNumSprite(int num,string ddr){
//	CCSpriteBatchNode * cbn = CCSpriteBatchNode::create(ddr.c_str());
//	string the = Globe::intToString(num);
//	int weishu = the.length();
//	for(int i = 0;i<weishu;i++){
//		int yu = 1;
//		for(int j = 0;j<i+1;j++){
//			yu = yu*10;
//		}
//		int a = ((num%yu)/(yu/10));
//		
//		CCSprite *sp = CCSprite::createWithTexture(cbn->getTexture());
//		int w = (int)(sp->boundingBox().size.width/13);
//		int h = sp->boundingBox().size.height;
//		sp->setTextureRect(CCRectMake((3+a)*w, 0, w, h));
//		sp->setAnchorPoint(ccp(0,0));
//		sp->setPositionX((weishu-1-i)*w);
//		cbn->addChild(sp);
//		cbn->setContentSize(CCSize(weishu*w,h));
//	}
//	return cbn;
//}




string Globe::callJava(string inr)
{
	string get = "";
	//非静态函数示例
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	JniMethodInfo method;
	//
	bool b=JniHelper::getStaticMethodInfo(method,"com/holyblade/platform/monthly/CocosMethods",
		"cocosCall","(Ljava/lang/String;)Ljava/lang/String;");
	if (b)
	{
		jstring tojava = method.env->NewStringUTF(inr.c_str());
		jstring jstr=(jstring)method.env->CallStaticObjectMethod(method.classID,method.methodID,tojava);
		std::string str = JniHelper::jstring2string(jstr);
		get = str;
	}
#endif
	return get;
}

string Globe::makeJsonString(string order,string info){
	Json::Value root;
	root["order"] = Json::Value(order);
	root["info"] = Json::Value(info);
	Json::FastWriter fw;
	string send = fw.write(root);
	return send;
}

void Globe::sleep(long time){
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32) 
	float slepTime = time/100;
Sleep(slepTime);
#else
string get= Globe::makeJsonString("sleep","");
callJava(get);
#endif
}

void Globe::showMemoryLog(){
	string get= Globe::makeJsonString("getMemory","");
	CCLog("memory:%s",Globe::callJava(get).c_str());
}

int Globe::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	memset(outbuf, 0, outlen);
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
	iconv_close(cd);
	return 0;
}

/*UTF8תΪGB2312*/
std::string Globe::UTFToGBK(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}

/*GB2312תΪUTF8*/
std::string Globe::GBKToUTF(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}


/* 
 horizontalSpacing： 水平间距 
 verticalSpacing：   垂直间距 
 lineWidth：         一行的最大宽度 
 */  
CCLabelTTF* Globe::horizontalSpacingANDverticalSpacing(string _string, const char *fontName, float fontSize, float horizontalSpacing, float verticalSpacing, float lineWidth,ccColor3B color)  
{ 
    CCArray* labelTTF_arr = CCArray::create();  
    int index = 0;  
    int index_max = strlen(_string.c_str());  
    bool is_end = true;  
    while (is_end) {
        if (_string[index] >= 0 && _string[index] <= 127) {  
            string englishStr =_string.substr(index,1).c_str();  
			CCLabelTTF *te = CCLabelTTF::create(englishStr.c_str(), fontName, fontSize);
			te->setColor(color);
            labelTTF_arr->addObject(te);  
            index+= 1;  
        }  
        else{  
            string chineseStr =_string.substr(index,3).c_str();  
			CCLabelTTF *te = CCLabelTTF::create(chineseStr.c_str(), fontName, fontSize);
			te->setColor(color);
            labelTTF_arr->addObject(te);  
            index+= 3;  
        }  
        if (index>=index_max) {  
            is_end=false;  
        }  
    }  
    //以上步骤是根据ASCII码找出中英文字符，并创建成一个CCLabelTTF对象存入labelTTF_arr数组中。  
      
      
    //下面创建的原理是在CCLabelTTF对象上添加子对象CCLabelTTF，以此组合成一句话，以左上角第一个字为锚点。。  
    CCLabelTTF* returnTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(0);  
    float nowWidth = returnTTF->getContentSize().width;  
    CCLabelTTF* dangqiangTTF = returnTTF;  
    CCLabelTTF* lineBeginTTF = returnTTF;  
      
    int arr_count = labelTTF_arr->count();  
    for (int i=1; i < arr_count; i++) {  
        CCLabelTTF* beforeTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(i);  
        beforeTTF->setAnchorPoint(ccp(0, 0.5));  
        nowWidth+=beforeTTF->getContentSize().width;  
        if (nowWidth >= lineWidth) {  
            nowWidth = returnTTF->getContentSize().width;  
            dangqiangTTF = lineBeginTTF;  
            beforeTTF->setPosition(ccp(0, -dangqiangTTF->getContentSize().height*0.5-verticalSpacing));  
            lineBeginTTF = beforeTTF;  
		}else{  
            beforeTTF->setPosition(ccp(dangqiangTTF->getContentSize().width+horizontalSpacing, dangqiangTTF->getContentSize().height*0.5));  
        }  
        dangqiangTTF->addChild(beforeTTF);  
        dangqiangTTF = beforeTTF;  
    }  
      
    return returnTTF;  
} 

CCLabelTTF* Globe::getLabelTTF(string str,CCPoint point,CCPoint anchor,ccColor3B color,int fontSize){
	CCLabelTTF *temp = CCLabelTTF::create("type","Marker Felt",fontSize);
	temp->setAnchorPoint(anchor);
	temp->setColor(color);
	temp->setString(str.c_str());
	temp->setPosition(point);
	return temp;
}

string Globe::replaceStr(string s){//去掉末尾的\n
	string get = s.substr(0,s.rfind('\n'));
	return get;
}

