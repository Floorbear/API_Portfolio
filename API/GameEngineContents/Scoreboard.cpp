#include "Scoreboard.h"
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameManager.h"

Scoreboard::Scoreboard()
{
	for (int i = 0; i < 7; i++)
	{
		ScoreNumberRenderer_[i] = nullptr;
		NumberIndex[i] = 0;
	}

}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()-float4(70,420));

	for (int i = 0; i < 7; i++)
	{
		ScoreNumberRenderer_[i] = CreateRenderer(static_cast<int>(GameLayer::UI),RenderPivot::LeftTop,{static_cast<float>(32*i),0});
		ScoreNumberRenderer_[i]->SetImage("Numbers.bmp");
		ScoreNumberRenderer_[i]->SetIndex(0);
		ScoreNumberRenderer_[i]->CameraEffectOff();
		ScoreNumberRenderer_[i]->SetTransColor(RGB(128, 0, 128));
	}

}

void Scoreboard::Update()
{
	int CurScore = GameManager::GetInst()->GetScore();

	for (int i = 0; CurScore != 0; i++)
	{
		NumberIndex[6 - i] = CurScore % 10;
		CurScore /= 10;
	}
}

void Scoreboard::Render()
{
	for (int i = 0; i < 7; i++)
	{
		ScoreNumberRenderer_[i]->SetIndex(NumberIndex[i]);
	}
}
