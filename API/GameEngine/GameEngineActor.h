#pragma once
#include <GameEngineBase/GameEngineNameObject.h>

class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
	friend GameEngineLevel;
public:
	GameEngineActor();
	~GameEngineActor();


	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(const GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Ohter) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0;

private:
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}
	GameEngineLevel* Level_;

};

