#include "NetHander.h"


string NetHander::version = "1.0";
string NetHander::mac = "09-2015000-01";
string NetHander::bossId = "413"; //413  HNDX
string NetHander::gameId = "tvg200001";
string NetHander::serverUrl = "http://10.255.25.130/OTTGameHall_HNDX/Month2/";  //湖南电信
// string NetHander::serverUrl = "http://27.115.103.38/OTTGameHall_HNDX/Month2/";  //公网
//string NetHander::serverUrl = "http://api1.tvsdk.cn/OTTGameHall_Test/";
// string NetHander::serverUrl = "http://api1.tvsdk.cn/OTTGameHall_Test/Month2/";

const string hongBaoUrl = "http://10.255.25.130/OTTGameHall_hndx/FestivalActivity/";

string NetHander::key = "36DDA110-6F01-4C12-9840-33DAEC6A12FC";
int NetHander::playStatus = 0;
int NetHander::playTime = 0;
NetHander::NetHander():isClose(false),callback(NULL){
	getNetString = "";
	netTag =0;
}

NetHander::~NetHander(){
	callback = NULL;
}

void NetHander::getInfo(){
	string ver = Globe::callJava(Globe::makeJsonString("getVersion",""));
	if(ver!=""){
		version = ver;
	}

	string ma = Globe::callJava(Globe::makeJsonString("getMac",""));
	if(ma!=""){
		mac = ma;
	}
	CCLog("macdddd:%s",mac.c_str());
	string bosid = Globe::callJava(Globe::makeJsonString("getBossId",""));
	if(bosid!=""){
		bossId = bosid;
	}

	string pkgid = Globe::callJava(Globe::makeJsonString("getGameId",""));
	if(pkgid!=""){
		gameId = pkgid;
	}

	string url = Globe::callJava(Globe::makeJsonString("getServerUrl",""));
	if(url!=""){
		serverUrl = url;
	}

	string hkey = Globe::callJava(Globe::makeJsonString("getHttpKey",""));
	if(hkey!=""){
		key = hkey;
	}

	string userInfo = Globe::callJava(Globe::makeJsonString("getUserInfo",""));
	Reader reader;
	Value root;  
	//NetHander.userInfo:{"BalanceCommon":0,"BalanceInteraction":10.1,
	//"CustName":"test","OweTotalFee":0,
	//"Password":"123456","PlayStatus":1,"PlayTime":8,"TopupStatus":1}
	if (reader.parse(userInfo, root)){
		playStatus = root["PlayStatus"].asInt();
		playTime = root["PlayTime"].asInt();
		CCLog("playStatus:%s",Globe::intToString(playStatus).c_str());
		CCLog("playTime:%s",Globe::intToString(playTime).c_str());
	}
}



void NetHander::setCallBack(Callback *back,int tag){
	callback = back;
	netTag = tag;
}

void NetHander::getGameCategory()
{
	name = "GetCategory.ashx";
	string url = serverUrl + name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getUserInfo()						//获取用户信息
{
	name = "GetUserInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);

}

void NetHander::getLogo(){
	name = "GetLogo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getHongbaoInfo()
{
	name = "GetRewardInfo.ashx";
	string url = hongBaoUrl+name;

	url = put(url, "MacAddress", mac);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getHongbaoResult()
{
	name = "GetLotteryResult.ashx";
	string url = hongBaoUrl+name;

	url = put(url, "MacAddress", mac);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::saveHongbaoExchange(string propID)
{
	name = "SaveUserReward.ashx";
	string url = hongBaoUrl+name;

	url = put(url, "MacAddress", mac);
	url = put(url, "PropID", propID);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getHomePage(){
	name = "GetHomePage.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getCategory(){
	name = "getCategory.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getCategoryDetail(string id){
	name = "GetNewCategoryDetail.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "CategoryID", id);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getGameExist(string gameList)					//获取游戏存在
{
	name = "GetGameExist.ashx";
	string url = serverUrl+name;
	url = put(url, "AppIDs", gameList);
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getActivityNotice()					//获取活动公告
{

	name = "GetActivityNotice.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "Count", "10");
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);

}

void NetHander::getRewardNotice()					//获取兑换公告
{
	name = "GetRewardNotice.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "Count", "10");
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);

}

void NetHander::saveUserReward(string id,string type)						//保存兑奖结果
{
	name = "SaveUserReward.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "PropID",id);
	url = put(url, "Type", type);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getLoadingInfo()						//打开应用时的信息
{
	name = "GetLoadingInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getAppDetail(string id){
	name = "GetAppDetail.ashx";
	string url = serverUrl+name;
	url = put(url, "AppID", id);
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getApkDownloadUrl(string id){
	name = "GetDownloadUrl.ashx";
	string url = serverUrl+name;
	url = put(url, "AppID", id);
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getRecommendApp(){
	name = "GetRecommendApp.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getAllInstallApks(string allPkgName){
	name = "GetSJAppInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "PackageNames", allPkgName);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getNewVersion(string appId){
	name = "GetAppUpdate.ashx";
	string url = serverUrl+name;
	url = put(url, "AppIDs", appId);
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getAcitivity(){
	name = "GetActivity.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getRewardInfo()							//获取奖品列表
{
	name = "GetRewardInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getAcitivityDetail(string id){
	name = "GetActivityDetail.ashx";
	string url = serverUrl+name;
	url = put(url, "ActivityID", id);
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}


void NetHander::getSigninInfo(string id)					//获取签到信息
{
	name = "GetSigninInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "SigninID", id);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);

}
void NetHander::getUserLotHis(string id)
{
	name = "GetUserLotteryHistory.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "Count", "6");
	url = put(url, "LotteryID", id);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);

}

void NetHander::getLotteryInfo(string lotteryID,string isMonth){

	name = "GetLotteryInfo.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "IsMonth", isMonth);
	url = put(url, "LotteryID", lotteryID);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getLotteryResult(string lotteryID){

	name = "GetLotteryResult.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "IsMonth",Globe::intToString(playStatus) );
	url = put(url, "LotteryID", lotteryID);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getWWJLotteryInfo(string lotteryID)
{
	name = "GetWWJLotteryInfo.ashx";
	string url = hongBaoUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "LotteryID", lotteryID);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getWWJLotteryResult(string lotteryID,int type)
{
	name = "GetWWJLotteryResult.ashx";
	string url = hongBaoUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "IsMonth",Globe::intToString(playStatus) );
	url = put(url, "LotteryID", lotteryID);
	url = put(url, "LotteryType", Globe::intToString(type));
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getWWJRewardNotice(string lotteryID)
{
	name = "GetWWJLotteryNotice.ashx";
	string url = hongBaoUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "Count","50");
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getWWJLotteryHistory(string lotteryID)
{
	name = "GetWWJLotteryHistory.ashx";
	string url = hongBaoUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "Count","4");
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getSignResult(string id,string type)							//获取签到结果
{
	name = "GetSigninResult.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "SigninID", id);
	url = put(url, "UserType", type);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::getZhuanquDetail(string id){
	name = "GetZoneDetail.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);
	url = put(url, "ZoneID", id);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getUserPassword(){
	name = "GetUserPassword.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "ManySDK_UserID", mac);
	

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getXiaofeijilu(int index,int pageSize){
	name = "GetUserOrders.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "C_3rd_UserID", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "page", Globe::intToString(index));
	url = put(url, "pagesize", Globe::intToString(pageSize));
	

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::setUserPassword(string oldPassword,string passWord){
	name = "SetUserPassword.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "ManySDK_UserID", mac);
	url = put(url, "OldPassword", oldPassword);
	url = put(url, "Password", passWord);
	

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getUserRewardHistory(string Ye,string num)					// 获取兑奖记录
{
	name = "GetUserRewardHistory.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Page", Ye);
	url = put(url, "PageSize", num);
	url = put(url, "Version", version);


	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::saveUserContact(string strQQ)										// 获取QQ号绑定结果
{
	name = "SaveUserContact.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "QQ", strQQ);
	url = put(url, "Version", version);


	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::getUserPsw()
{
	name = "GetUserPsw.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::setUserPsw(string type,string OldPassword,string Password)												// 设置或修改监管密码
{
	name = "SetUserPsw.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "OpType", type);
	url = put(url, "OldPassword", OldPassword);
	url = put(url, "Password", Password);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}

void NetHander::unsubscribe()							// 退订处理
{
	name = "Unsubscribe.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::saveLogout(string sessionID)    //保存用户退出记录
{
	name = "SaveLogout.ashx";
	string url = serverUrl+name;
	url = put(url, "BossID", bossId);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "SessionID", sessionID);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}
void NetHander::saveLog(string pageID,string pageContent,string elementID,string elementCon,string refPageID,string refPageCon,string isSuccess,string extend1,string extend2)							//保存日志
{
	name = "SaveLog.ashx";
	string url = serverUrl+name;
	pageContent = Globe::GBKToUTF(pageContent.c_str());
	refPageCon = Globe::GBKToUTF(refPageCon.c_str());
	elementCon = Globe::GBKToUTF(elementCon.c_str());

	url = put(url, "BossID", bossId);
	url = put(url, "ElementContent",elementCon);
	url = put(url, "ElementID",elementID);
	url = put(url, "Extend1",extend1);
	url = put(url, "Extend2",extend2);
	url = put(url, "IsSuccess",isSuccess);
	url = put(url, "MacAddress", mac);
	url = put(url, "ManySDK_GameID", gameId);
	url = put(url, "PageContent",pageContent);
	url = put(url, "PageID",pageID);
	url = put(url, "RefPageContent",refPageCon);
	url = put(url, "RefPageID",refPageID);
	url = put(url, "Version", version);

	sign += key;
	sign = md5(sign);
	url+="&sign="+sign;
	CCLog("httpUrl:%s",url.c_str());
	doSend(url);
}



void NetHander::doSend(string url){
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl((url+"&sj=0").c_str());//设置请求地址  
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(NetHander::callbackSend));//请求完的回调函数  
    //request->setRequestData("HelloWorld",strlen("HelloWorld"));//请求的数据
	request->setTag(name.c_str());
	CCHttpClient::getInstance()->setTimeoutForConnect(20);
	CCHttpClient::getInstance()->setTimeoutForRead(20);
	CCHttpClient::getInstance()->send(request);//发送请求 
    request->release();//释放
	getNetString = "";
}

void NetHander::close(){
	this->autorelease();
	isClose = true;
}

void NetHander::callbackSend(CCNode *node,void *data){
	CCLog("callbackSend:%x",this);
	CCHttpResponse *response = (CCHttpResponse*)data;  
	if (!response)  
    {  
        return;  
    }
	if(isClose){
		return;
	}
	//获取一些其他参数
	if(true){
		int s=response->getHttpRequest()->getRequestType();
		if(s!=0){
			CCLog("request type %d",s); 
		}
		
		int statusCode = response->getResponseCode();
		if(statusCode!=200){
			CCLog("response code: %d", statusCode);  
		}
		
		if (!response->isSucceed())
		{  
			CCLog("response failed");  
			CCLog("error buffer: %s", response->getErrorBuffer());  
			if(callback){
				callback->call("",netTag);
			}
			return;  
		}  
	}

    std::vector<char> *buffer = response->getResponseData(); 

	std::string temp(buffer->begin(),buffer->end());
    CCLog("httpReceived:[%s]|%s",response->getHttpRequest()->getTag(),temp.c_str());
	getNetString = temp;
	if(callback){
		callback->call(temp,netTag);
	}
}

string NetHander::put(string url,string key,string value){
	if(url.find("?")==-1){
		sign = "";
		sign = sign + value;
		url = url + ("?" + key + "=" +  value);
	}else{
		sign = sign + value;
		url = url + ("&" + key + "=" +  value);
	}
	return url;
}









