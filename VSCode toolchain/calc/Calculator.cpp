#include <iostream>

class Calculator
{
    public:
        Calculator(int, int, char);

    public:
        static int m_nRetValue;
};

int main()
{
    std::cout << "Hello, I'am calculator!" << std::endl;
    std::cout << "Please input 2 integer:" << std::flush;
    int x = 0;
    int y = 0;
    char oper = '+';
    // std::cin >> x >> y >> oper;
    std::cin >> x >> oper >> y;
    Calculator calc(x, y, oper);
    std::cout << "\t" << calc.m_nRetValue << std::endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}

int Calculator::m_nRetValue = 0;
Calculator::Calculator(int x, int y, char oper)
{
    switch (oper)
    {
        case '+': m_nRetValue = x + y;
            break;
        case '-': m_nRetValue = x - y;
            break;
        case '*': m_nRetValue = x * y;
            break;
        case '/': m_nRetValue = y ? x/y : 0;
            break;
    }
}