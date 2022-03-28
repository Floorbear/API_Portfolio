#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineEnum.h>
#include <list>

class GameEngineRenderer;
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

	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}
	inline void SetPosition(float4 _Position)
	{
		Position_ = _Position;
	}
	inline void SetScale(float4 _Scale)
	{
		Scale_= _Scale;
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

protected:
	virtual void Start() = 0;
	virtual void Update() {}
	virtual void Render() {}
	void DebugRectRender();


private:
	float4 Position_;
	float4 Scale_;
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}
	GameEngineLevel* Level_;

	std::list<GameEngineRenderer*> RenderList_;
};

