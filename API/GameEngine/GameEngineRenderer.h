#pragma once
#include "GameEngineActorSubObject.h"
#include <string>
#include <GameEngine/GameEngineEnum.h>

class GameEngineImage;
class  GameEngineRenderer : public GameEngineActorSubObject
{
public:
	GameEngineRenderer();
	~GameEngineRenderer();


	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(const GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Ohter) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

public:
	void SetImage(const std::string& _Name);
	void SetImageScale();

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;

	//Dest�� �̹��� Scale, ������ǥ(BackBuffer�� �׷����� ����)
	float4 RenderScale_;
	//Src�� �̹��� Scale
	float4 RenderImageScale_;

	float4 RenderPivot_;
	float4 RenderImagePivot_;



};

