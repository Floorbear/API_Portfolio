#include "HPBar.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"
#include "GameManager.h"
#include "Player.h"

HPBar::HPBar()
	:
	CurHP_(28)
{
}

HPBar::~HPBar()
{
}

void HPBar::Start()
{
	SetPosition({ 80,80 });

	//모든 PerHP를 꽉 채워준다.
	for (int i = 0; i < 7; i++)
	{
		HPIndex_[i] = 4;
	}

	//모든 렌더러 초기화
	for (int i = 0; i < 7; i++)
	{
		PerHPRenderer_[i] = CreateRenderer(static_cast<int>(GameLayer::UI), RenderPivot::LeftTop,{0,static_cast<float>(32*i)});
		PerHPRenderer_[i]->SetImage("PerHP.bmp");
		PerHPRenderer_[i]->SetIndex(4);
		PerHPRenderer_[i]->CameraEffectOff();
	}
}

void HPBar::Update()
{
	CurHP_ = GameManager::GetInst()->GetPlayer()->GetPlayerHP();

	//아래서부터 HPIndex의 값을 최신화
	int TempHP = CurHP_;
	for (int i = 6; i >= 0; i--)
	{
		if (TempHP >= 4)
		{
			HPIndex_[i] = 4;
			TempHP -= 4;
			continue;
		}
		else // 3,2,1,0
		{
			HPIndex_[i] = TempHP;
			TempHP -= TempHP;
			continue;
		}
	}
}

//HP바 렌더
void HPBar::Render()
{
	for (int i = 0; i < 7; i++)
	{
		PerHPRenderer_[i]->SetIndex(HPIndex_[i]);
	}
}
