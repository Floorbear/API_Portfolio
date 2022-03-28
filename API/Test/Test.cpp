#include <iostream>
#include <string>

class Test
{
public:

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewString = _Text;
		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewString[i] = std::toupper(_Text[i]);
		}
		return NewString;
	}
};



int main()
{
	std::cout << Test::ToUpperReturn("MyNameIsMuMu") << std::endl;
}


