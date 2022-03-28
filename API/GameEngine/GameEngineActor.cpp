#include "GameEngineActor.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_,Scale_);


	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Image, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetImageScale();
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	
	return nullptr;
}
