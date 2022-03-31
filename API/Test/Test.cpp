#include <iostream>
#include <string>

static void ToUpper(std::string& _Text)
{
	for (size_t i = 0; i < _Text.size(); i++)
	{
		_Text[i] = std::toupper(_Text[i]);
	}
}



int main()
{
	std::string a("hi");
	ToUpper(a);
	std::cout << a << std::endl;
}


