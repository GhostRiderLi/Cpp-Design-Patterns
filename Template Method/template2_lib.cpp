#include <iostream>

using namespace std;

// 程序库开发人员
class Library
{
  public:
    //ÎÈ¶¨ template method
    void Run()
    {
        Step1();

        if (Step2())
        { 
            Step3();  //支持变化 ==> 虚函数多态调用
        }

        for (int i = 0; i < 4; i++)
        {
            Step4(); //支持变化 ==> 虚函数多态调用
        }

        Step5();
    }
    virtual ~Library() {} // 虚析构

  protected:
    void Step1()
    { //稳定
        cout << "Step1" << endl;
    }
    void Step3()
    { //稳定
        cout << "Step3" << endl;
    }
    void Step5()
    {   //稳定
        cout << "Step5" << endl;
    }

    virtual bool Step2() =0; //变化
    virtual void Step4() =0;//变化
};
