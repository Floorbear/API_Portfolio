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

	//Dest의 이미지 Scale, 절대좌표(BackBuffer에 그려지기 때문)
	float4 RenderScale_;
	//Src의 이미지 Scale
	float4 RenderImageScale_;

	float4 RenderPivot_;
	float4 RenderImagePivot_;



};

