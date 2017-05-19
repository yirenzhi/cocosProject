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

	void getGameCategory();					//��ȡ��Ϸ����
	void getGameExist(string gameList);					//��ȡ��Ϸ����
	void getUserInfo();						//��ȡ�û���Ϣ
	void getSigninInfo(string id);					//��ȡǩ����Ϣ
	void getSignResult(string id,string type);							//��ȡǩ�����
	void getLotteryInfo(string lotteryID,string isMonth);					//�齱
	void getLotteryResult(string lotteryID);			//�齱���
	void getWWJLotteryInfo(string lotteryID);						//���޻��齱
	void getWWJLotteryResult(string lotteryID,int type);			//���޻��齱���
	void getWWJRewardNotice(string lotteryID);						//���޻��н�����
	void getWWJLotteryHistory(string lotteryID);					//���޻��н���¼
	void getRewardInfo();							//��ȡ��Ʒ�б�
	void getActivityNotice();					//��ȡ�����
	void getRewardNotice();						//��ȡ�һ�����
	void getUserRewardHistory(string Ye,string num);					// ��ȡ�ҽ���¼
	void saveUserContact(string strQQ);										// ��ȡQQ�Ű󶨽��
	void getUserPsw();													// ��ȡ�û�����
	void setUserPsw(string type,string OldPassword,string Password);													// ���û��޸ļ������

	void getLoadingInfo();						//��Ӧ��ʱ����Ϣ
	void saveUserReward(string id,string type);						//����ҽ����

	void getHongbaoInfo();
	void getHongbaoResult();
	void saveHongbaoExchange(string propID);

	void unsubscribe();							// �˶�����
	/*
	*PageID					ҳ��ID
	*PageContent			ҳ������
	*RefPageID				��תҳ�棬���嶨����μ���¼
	*RefPageContent			��תҳ�����ݣ�����Ϸ����
	*ElementID				ҳ��Ԫ��ID�����嶨����μ���¼
	*ElementContent			ҳ��Ԫ�����ݣ�����ת��Ϸ������
	*IsSuccess				�Ƿ�ɹ����綩�����һ���  0��ʧ��  1���ɹ�
	*Extend1				��չ�ֶ�1
	*Extend2				��չ�ֶ�2
	*
	*/
	void saveLog(string pageID,string pageContent,string elementID="",string elementCon="",string refPageID="",string refPageCon="",string isSuccess="",string extend1="",string extend2="");							//������־
	
	void saveLogout(string sessionID);    //�����û��˳���¼
	
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
	
	//����״̬ 1(����),2(�ǰ���)
	static int playStatus;
	//�����ʱ��
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