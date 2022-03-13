
#include <iostream>


class MyClass
{
public:
	MyClass();
	~MyClass();
	static int a;

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

int MyClass::a = 3;
int main()
{
	MyClass::a++;
    std::cout << MyClass::a;
}


