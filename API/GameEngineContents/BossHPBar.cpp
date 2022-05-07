#include "BossHPBar.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"
#include "GameManager.h"
#include "Cutman.h"
BossHPBar::BossHPBar() :
	CurHP_(0)
{
}

BossHPBar::~BossHPBar()
{
}

void BossHPBar::Start()
{
	SetPosition({ 160,80 });

	//모든 PerHP를 꽉 채워준다.
	for (int i = 0; i < 7; i++)
	{
		HPIndex_[i] = 4;
	}

	//모든 렌더러 초기화
	for (int i = 0; i < 7; i++)
	{
		PerHPRenderer_[i] = CreateRenderer(static_cast<int>(GameLayer::UI), RenderPivot::LeftTop, { 0,static_cast<float>(32 * i) });
		PerHPRenderer_[i]->SetImage("BossPerHP.bmp");
		PerHPRenderer_[i]->SetIndex(4);
		PerHPRenderer_[i]->CameraEffectOff();
	}
}

void BossHPBar::Update()
{
	if (Cutman_ != nullptr)
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->On();

		}
		CurHP_ = Cutman_->GetHP();
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
				if (TempHP <= 0)
				{
					TempHP = 0;
				}
				HPIndex_[i] = TempHP;
				TempHP -= TempHP;
				continue;
			}
		}
	}
	else //게임이 시작하지 않았다면 HP바를 감춘다
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->Off();

		}
	}
}

void BossHPBar::Render()
{
	if (Cutman_ != nullptr)
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->SetIndex(HPIndex_[i]);
		}
	}
	else //게임이 시작하지 않았다면 HP바를 감춘다
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->Off();
		}
	}
}
