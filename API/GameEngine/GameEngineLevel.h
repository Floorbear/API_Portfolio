#pragma once
#include <GameEngineBase/GameEngineNameObject.h>


class GameEngineLevel : public GameEngineNameObject
{
public:
	GameEngineLevel();

	//이거 짱중요함 
	virtual ~GameEngineLevel();


	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(const GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Ohter) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _Other) noexcept = delete;
protected:
	// 만들어지면서 리소스나 액터를 만드는 함수....
	virtual void Loading() = 0;

};

