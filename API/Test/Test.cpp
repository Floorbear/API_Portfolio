#include <iostream>


class Test
{
public:
	void Func();
};

void Test::Func()
{
	std::cout << "Call Func" << std::endl;
}

int main()
{
	void(Test::*VPtr)();
	VPtr = &Test::Func;
	Test t;
	(t.*VPtr)();

}


