#include "Download.h"
#include "..\..\common\Screen.h"

Download::Download(string url,string name):clsCurDown(NULL){
	httpUrl = url;
	saveName = name;
	jindu = 0;
	string ablePath = MyFileUtils::getWritablePath();
	savePath = ablePath+saveName;
		MyFileUtils::openOrCreateFile_(savePath.c_str(),saveName);
}

Download::Download(){
	jindu = 0;
	string ablePath = MyFileUtils::getWritablePath();
	savePath = ablePath+saveName;
		MyFileUtils::openOrCreateFile_(savePath.c_str(),saveName);
}

Download::~Download(){
	
}



int Download::threadStart()
{
	//pthread_mutex_init(&g_downloadMutex, NULL);
	int errCode = 0;
	do {
		pthread_attr_t tAttr;
		errCode = pthread_attr_init(&tAttr);
		CC_BREAK_IF(errCode != 0);
		errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
		if (errCode != 0) {
			pthread_attr_destroy(&tAttr);
			break;
		}
		errCode = pthread_create(&th_curlDown, &tAttr, thread_download, this);
	} while (0);
	
	return errCode;
}

void* thread_download(void *arg) {
	Download *hw = (Download*)arg;
	hw->clsCurDown = new CurlDown(hw->httpUrl, hw->savePath);
	hw->clsCurDown->setDelegate(hw);
	hw->clsCurDown->downloadControler();
	//hw->autorelease();
	return NULL;
}
 
void Download::start()
{
	if(!Screen::getResDownTemplate(saveName)){
		threadStart();
	}
}


void Download::close(){
	if(clsCurDown){
		clsCurDown->isStop = true;
	}
}

void Download::pause(){
	clsCurDown->isPause = !clsCurDown->isPause;
}


void Download::onProgress(double percent, void *delegate, string filefullPath){ // 下载进度
	if (clsCurDown->isStop) {
		CurlDown * cd = (CurlDown *)delegate;
		//        pthread_mutex_lock(&g_downloadMutex);
		cd->setStopDown();
		//        pthread_mutex_unlock(&g_downloadMutex);
	}
	if(clsCurDown->isPause){
		CurlDown * cd = (CurlDown *)delegate;
		//        pthread_mutex_lock(&g_downloadMutex);
		cd->setPauseDown();
		//        pthread_mutex_unlock(&g_downloadMutex);
	}
	jindu = percent;
	//CCLog("current:%.2f",percent);
	//pthread_mutex_lock(&g_downloadMutex);
	
	//const char * per = CCString::createWithFormat("donw progress:%.2f%%", percent)->getCString();
	//updateStr = per;
	//downFilePath = filefullPath;
	//pthread_mutex_unlock(&g_downloadMutex);
}

void Download::onSuccess(string filefullPath){
	//pthread_mutex_lock(&g_downloadMutex);
	//Screen::removeDownloading(saveName);
	for(int i = 0;i<Screen::vecDownLoadRes.size();i++){//资源下载完成
		if(Screen::vecDownLoadRes[i]->fullPath==filefullPath){
			Screen::vecDownLoadRes[i]->isDownLoadSuccess = true;
			//break;
		}
	}
	delete clsCurDown;
	clsCurDown = NULL;
	delete this;
	//pthread_mutex_unlock(&g_downloadMutex);
	
}

void Download::onError(CurlDown::ErrorCode errorCode){
	//pthread_mutex_lock(&g_downloadMutex);
	for(int i = 0;i<Screen::vecDownLoadRes.size();i++){//资源下载完成
		if(Screen::vecDownLoadRes[i]->fullPath==saveName){
			Screen::vecDownLoadRes[i]->isDownLoadSuccess = false;
			break;
		}
	}
	//delete this;
	//pthread_mutex_unlock(&g_downloadMutex);
}
