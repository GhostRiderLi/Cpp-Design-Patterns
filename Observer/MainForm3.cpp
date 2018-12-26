#include <iostream>
#include <list>
using namespace std;

class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};

//进度条
class IProgressBar{
public:
	//virtual void setValue(folat)=0;
	virtual void display(float)=0;
	virtual ~IProgressBar(){}
};

class ConsoleBar: public IProgressBar{
public:
	void display(float value) override{
		//控制台输出方式
		string str;
		int n = static_cast<int>(50*value);
		for(int i = 0; i < 50; ++i){
			if(i < n)
				str += ".";
			else
				str += " ";
		}

		cout <<'\r'<< str << value*100 << "%";
	}
};


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
			onProgress(progressValue);// 更新状态
			_sleep(125);
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



// class MainForm : public Form, public IProgress{
class MainForm : public IProgress{

	// TextBox* txtFilePath;
	// TextBox* txtFileNumber;
	string txtFilePath;
	int txtFileNumber;


	IProgressBar* bar;  //进度条

public:
	MainForm(const string& path, int num, IProgressBar* Bar): txtFilePath(path), txtFileNumber(num), bar(Bar){ }

	void Button1_Click(){

		// string filePath = txtFilePath->getText();
		// int number = atoi(txtFileNumber->getText().c_str());

		//ConsoleNotifier cn;

		FileSplitter splitter(txtFilePath, txtFileNumber);

		splitter.addIProgress(this); //¶©ÔÄÍ¨Öª
		//splitter.addIProgress(&cn); //¶©ÔÄÍ¨Öª

		splitter.split();

		splitter.removeIProgress(this);

	}

	virtual void DoProgress(float value){
		//progressBar->setValue(value);
		bar->display(value);
	}
};

// class ConsoleNotifier : public IProgress {
// public:
// 	virtual void DoProgress(float value){
// 		cout << ".";
// 	}
// };
// 
// 
int main(){
	IProgressBar* bar = new ConsoleBar;
	MainForm form("text",100,bar);
	form.Button1_Click();

	delete bar;
	return 0;
}

