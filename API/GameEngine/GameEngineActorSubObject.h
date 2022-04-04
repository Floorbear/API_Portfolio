#pragma once
#include "GameEngineActor.h"

class GameEngineActorSubObject : public GameEngineUpdateObject
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

	inline bool IsUpdate() override
	{
		//SubObject가 비활성화 되거나 부모가 비활성화 되면 false 반환
		return GameEngineUpdateObject::IsUpdate() && Actor_->IsUpdate();
	}

	inline bool IsDeath() override
	{
		return GameEngineUpdateObject::IsDeath() || Actor_->IsDeath();
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}

private:
	GameEngineActor* Actor_;

};

