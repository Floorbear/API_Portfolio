#pragma once
#include "GameEngineActor.h"

class GameEngineActorSubObject
{
	friend GameEngineActor;
public:
	GameEngineActorSubObject();
	~GameEngineActorSubObject();


	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(const GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Ohter) = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject&& _Other) noexcept = delete;

	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}

private:
	GameEngineActor* Actor_;

};

