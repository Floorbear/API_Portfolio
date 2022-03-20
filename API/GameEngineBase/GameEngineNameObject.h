#pragma once
#include <string>

class GameEngineNameObject
{
public:
	GameEngineNameObject();
	virtual ~GameEngineNameObject();


	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(const GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Ohter) = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject&& _Other) noexcept = delete;

public:
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}
	inline std::string GetNameCopy()
	{
		return Name_;
	}
	const inline std::string& GetNameConstRef() 
	{
		return Name_;
	}
	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}
protected:

private:
	std::string Name_;
};

