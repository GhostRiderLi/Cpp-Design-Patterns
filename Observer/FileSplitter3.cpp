#include <iostream>
#include <list>
using namespace std;

class FileSplitter
{
	string m_filePath;
	int m_fileNumber;

	list<IProgress*>  m_iprogressList; 
	
public:
	FileSplitter(const string& filePath, int fileNumber) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber){
	}

	void split(){

		//1. 读入文件

		//2. 分批次分割文件
		for (int i = 0; i < m_fileNumber; i++){
			//...

			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			onProgress(progressValue);//·¢ËÍÍ¨Öª
		}

	}


	void addIProgress(IProgress* iprogress){
		m_iprogressList.push_back(iprogress);
	}

	void removeIProgress(IProgress* iprogress){
		m_iprogressList.remove(iprogress);
	}

protected:
	virtual void onProgress(float value){
		
		list<IProgress*>::iterator itor=m_iprogressList.begin();

		while (itor != m_iprogressList.end() ){
			(*itor)->DoProgress(value); //¸üÐÂ½ø¶ÈÌõ
			itor++;
		}
	}
};