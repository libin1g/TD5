#include <iostream>

int main(int argc, char **argv)
{
    int a = 1000000000;
    int b = 1000000000;
    long long c = a * b; //ERROR
    long long c2 = (long long)(a * b); // ERROR
    long long c1 = (long long)a * b; // OK
    long long c3 = 1LL * a * b;//OK
    long long c4 = a * b * 1LL;//ERROR
    std::cout << a << "*" << a <<":\t"<< c << "\t" << c1 << "\t" << c2 << "\t" << c3 << "\t"<< c4 << std::endl;

    return 0;
}
