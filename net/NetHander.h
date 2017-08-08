#pragma once
#include "../common/Globe.h"
#include "cocos-ext.h"
#include "../utils/MD5.h"
#include "../json/json.h"
#include <string>
#include <locale.h> 
#include "Callback.h"

using namespace Json;



USING_NS_CC_EXT;  
#pragma comment(lib,"pthreadVCE2.lib")


class NetHander : public CCNode{
public:
	NetHander();
	~NetHander();
	
	Callback *callback;
	void setCallBack(Callback *back,int tag=0);
	void getUserLotHis(string id);
	void getLogo();
	void getHomePage();
	void getCategory();
	void getCategoryDetail(string id);
	void getAppDetail(string id);
	void getRecommendApp();
	void getApkDownloadUrl(string id);
	void getAllInstallApks(string allPkgName);
	void getNewVersion(string appId);
	void getAcitivity();
	void getAcitivityDetail(string id);
	void getZhuanquDetail(string id);
	void getUserPassword();
	void setUserPassword(string oldPassword,string passWord);
	void getXiaofeijilu(int index,int pagesize);

	void getGameCategory();					//获取游戏分类
	void getGameExist(string gameList);					//获取游戏存在
	void getUserInfo();						//获取用户信息
	void getSigninInfo(string id);					//获取签到信息
	void getSignResult(string id,string type);							//获取签到结果
	void getLotteryInfo(string lotteryID,string isMonth);					//抽奖
	void getLotteryResult(string lotteryID);			//抽奖结果
	void getWWJLotteryInfo(string lotteryID);						//娃娃机抽奖
	void getWWJLotteryResult(string lotteryID,int type);			//娃娃机抽奖结果
	void getWWJRewardNotice(string lotteryID);						//娃娃机中奖公告
	void getWWJLotteryHistory(string lotteryID);					//娃娃机中奖纪录
	void getRewardInfo();							//获取奖品列表
	void getActivityNotice();					//获取活动公告
	void getRewardNotice();						//获取兑换公告
	void getUserRewardHistory(string Ye,string num);					// 获取兑奖记录
	void saveUserContact(string strQQ);										// 获取QQ号绑定结果
	void getUserPsw();													// 获取用户密码
	void setUserPsw(string type,string OldPassword,string Password);													// 设置或修改监管密码

	void getLoadingInfo();						//打开应用时的信息
	void saveUserReward(string id,string type);						//保存兑奖结果

	void getHongbaoInfo();
	void getHongbaoResult();
	void saveHongbaoExchange(string propID);

	void unsubscribe();							// 退订处理
	/*
	*PageID					页面ID
	*PageContent			页面内容
	*RefPageID				跳转页面，具体定义请参见附录
	*RefPageContent			跳转页面内容，如游戏名称
	*ElementID				页面元素ID，具体定义请参见附录
	*ElementContent			页面元素内容，如跳转游戏的名称
	*IsSuccess				是否成功，如订购，兑换等  0：失败  1：成功
	*Extend1				扩展字段1
	*Extend2				扩展字段2
	*
	*/
	void saveLog(string pageID,string pageContent,string elementID="",string elementCon="",string refPageID="",string refPageCon="",string isSuccess="",string extend1="",string extend2="");							//保存日志
	
	void saveLogout(string sessionID);    //保存用户退出记录
	
	string getNetString;
	string name;

	static string version;
	static string mac;
	static string bossId;
	static string gameId;
	static string serverUrl;
	static string key;

	//NetHander.userInfo:{"BalanceCommon":0,"BalanceInteraction":10.1,
	//"CustName":"test","OweTotalFee":0,
	//"Password":"123456","PlayStatus":1,"PlayTime":8,"TopupStatus":1}
	
	//包月状态 1(包月),2(非包月)
	static int playStatus;
	//免费玩时间
	static int playTime;

	static void getInfo();
	void close();
	int netTag;

private:
	
	
	string sign;

	bool isClose;

	void doSend(string url);
	void callbackSend(CCNode *node,void *data);
	string put(string url,string key,string value);
	
};