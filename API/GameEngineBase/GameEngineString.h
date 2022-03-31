#pragma once
#include <string>
class GameEngineString
{
public:

	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = std::toupper(_Text[i]);
		}
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewString = _Text;
		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewString[i] = std::toupper(_Text[i]);
		}
		return NewString;
	}
private:
	GameEngineString();
	~GameEngineString();


	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(const GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Ohter) = delete;
	GameEngineString& operator=(const GameEngineString&& _Other) noexcept = delete;

};

