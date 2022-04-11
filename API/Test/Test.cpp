#include <stdio.h>
#include <stdlib.h>


int* func2()
{
	int* a = new int();
	*(a) = 3;
	return a;
}

int func1()
{
	return *func2();
}


int main()
{

}

