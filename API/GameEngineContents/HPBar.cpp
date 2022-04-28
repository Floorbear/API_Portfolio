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

	//��� PerHP�� �� ä���ش�.
	for (int i = 0; i < 7; i++)
	{
		HPIndex_[i] = 4;
	}

	//��� ������ �ʱ�ȭ
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
	Player* CurPlayer = GameManager::GetInst()->GetPlayer();
	if (CurPlayer != nullptr)
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->On();

		}
		CurHP_ = CurPlayer->GetPlayerHP();
		//�Ʒ������� HPIndex�� ���� �ֽ�ȭ
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
	else //������ �������� �ʾҴٸ� HP�ٸ� �����
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->Off();

		}
	}

}

//HP�� ����
void HPBar::Render()
{
	Player* CurPlayer = GameManager::GetInst()->GetPlayer();
	if (CurPlayer != nullptr)
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->SetIndex(HPIndex_[i]);
		}
	}
	else //������ �������� �ʾҴٸ� HP�ٸ� �����
	{
		for (int i = 0; i < 7; i++)
		{
			PerHPRenderer_[i]->Off();

		}
	}

}
