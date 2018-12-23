#include <iostream>

// 表示计算税率需要的数据结构
struct Context{
    float tax;
    Context(float t = 0.0):tax(t){}
};
/*****************************工厂模式****************************************/
// 策略
class TaxStrategy{
public:
    virtual double Calculate(const Context& context)=0;
    virtual ~TaxStrategy(){}
};


class CNTax : public TaxStrategy{
public:
    double Calculate(const Context& context) override{
        //***********
        float val = context.tax + 1.0;
        std::cout << "CNTax: " << val << std::endl;
        return val;
    }
};

class USTax : public TaxStrategy{
public:
    double Calculate(const Context& context) override{
        //***********
        float val = context.tax + 2.0;
        std::cout << "USTax: " << val << std::endl;
        return val;
    }
};

class DETax : public TaxStrategy{
public:
    double Calculate(const Context& context) override{
        //***********
        float val = context.tax + 3.0;
        std::cout << "DETax: " << val << std::endl;
        return val;

    }
};

// 策略工厂
class StrategyFactory{
public:
    virtual TaxStrategy* newStrategy()=0;
};

class StrategyCNTax: public StrategyFactory{
public:
    TaxStrategy* newStrategy() override { return new CNTax;}
};

class StrategyUSTax: public StrategyFactory{
public:
    TaxStrategy* newStrategy() override { return new USTax;}
};

class StrategyDETax: public StrategyFactory{
public:
    TaxStrategy* newStrategy() override { return new DETax;}
};

/*****************************工厂模式结束*************************************/

//扩展内容
//*********************************
class FRTax : public TaxStrategy{
public:
	double Calculate(const Context& context) override{
		//.........
        float val = context.tax + 4.0;
        std::cout << "FRTax: " << val << std::endl;
        return val;
	}
};

class StrategyFRTax: public StrategyFactory{
public:
    TaxStrategy* newStrategy() override { return new FRTax;}
};


// 策略模式调用工厂模式
class SalesOrder{
private:
    TaxStrategy* strategy;

public:
    // ¹¤³§Ä£Ê½
    SalesOrder(StrategyFactory* strategyFactory){
        this->strategy = strategyFactory->newStrategy();
    }
    ~SalesOrder(){
        delete this->strategy;
    }

    double CalculateTax(){
        //...
        Context context;
        
        double val = strategy->Calculate(context); //多态调用
        //...
        return val;
    }
    
};


int main(){
    StrategyFactory* pf = new StrategyDETax;
    SalesOrder Sales(pf);
    std::cout << Sales.CalculateTax() << std::endl;
    return 0;
}