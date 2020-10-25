#include<iostream>

using namespace std;

class Strategy
{
public:
    virtual int doOperation(int num1, int num2) = 0;
    virtual ~Strategy() = default;
};

class OperationAdd :public Strategy
{
public:
    virtual int doOperation(int num1, int num2) override
    {
        return num1 + num2;
    }
};

class OperationSubstract :public Strategy
{
public:
    virtual int doOperation(int num1, int num2) override
    {
        return num1 - num2;
    }
};

class OperationMultiply :public Strategy
{
public:
    virtual int doOperation(int num1, int num2) override
    {
        return num1 * num2;
    }
};

class Context
{
public:
    Context(Strategy* strategy)
    {
        this->strategy = strategy;
    }
    int executeStrategy(int num1, int num2)
    {
        return strategy->doOperation(num1, num2);
    }
private:
    Strategy* strategy;
};

int main()
{

    Context* context = new Context(new OperationAdd);
    cout << "10 + 5 = " << context->executeStrategy(10, 5) << endl;

    context = new Context(new OperationSubstract);
    cout << "10 - 5 = " << context->executeStrategy(10, 5) << endl;

    context = new Context(new OperationMultiply);
    cout << "10 * 5 = " << context->executeStrategy(10, 5) << endl;
}