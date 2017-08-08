#pragma once
#include "cocos-ext.h"
#include "../../utils/MyFileUtils.h"
#include "CurDown.h"
#define USING_STD using namespace std;
USING_STD;

USING_NS_CC_EXT;  
#pragma comment(lib,"pthreadVCE2.lib")

void* thread_download(void *arg);
class Download : public CurlDownDelegate,public CCNode{
public:
	//pthread_mutex_t g_downloadMutex;
	CurlDown *clsCurDown;
	Download(string url,string name);
	Download();
	~Download();
	int jindu;
	pthread_t th_curlDown; // 线程初始化
	void close();
	void pause();

	// 断点续传 回调方法
	virtual void onError(CurlDown::ErrorCode errorCode);
	virtual void onProgress(double percent, void *delegate, string filefullPath);
	virtual void onSuccess(string filefullPath);
	void start();
	int threadStart();
	string savePath;
	string httpUrl;
	string saveName;
};