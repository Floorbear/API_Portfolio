#include "Cutman.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "BackGround.h"
#include "GameManager.h"
#include <GameEngineBase/GameEngineRandom.h>

Cutman::Cutman()
{
}

Cutman::~Cutman()
{
}

void Cutman::InitMonster()
{
	SetScale({ 60,80 });
	//�������ͽ�
	AttackDamage_ = 3;//Default 3

	DropScore_ = 500;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 250.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;

	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 20;
	CurHP_ = MaxHP_;

	//�ð�����
	CurIdleTime_ = 0;
	MaxIdleTime_ = 1.0f;

	//�߷°���
	Gravity_ = 0;

}

void Cutman::InitRenderer()
{
	//������ �ִϸ��̼� ����
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER,float4(0,40));
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Idle_HaveWeaponRight", 0, 1, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Idle_HaveWeaponLeft", 0, 1, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Move_HaveWeaponRight", 2, 4, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Move_HaveWeaponLeft", 2, 4, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Jump_HaveWeaponLeft", 5, 5, 0.1f,false);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Jump_HaveWeaponRight", 5, 5, 0.1f, false);


	//��� �ִϸ��̼�
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("Cutman_Idle_HaveWeaponLeft");
}

void Cutman::ChangeIdleAni()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("Cutman_Idle_HaveWeapon"+ RockmanUtility::DirToStr(CurHoriDir_));
}

void Cutman::SetMonster()
{
	//�ݸ��� ����
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());
}

void Cutman::IdleStart()
{
	ChangeIdleAni();
	CurIdleTime_ = 0;
}

void Cutman::IdleUpdate()
{
	CurIdleTime_ += GameEngineTime::GetDeltaTime();
	std::cout << CurIdleTime_ << std::endl;
	if (CurIdleTime_ >= MaxIdleTime_)
	{
		ChangeState(MonsterState::Move);
		return;
	}
}

void Cutman::MoveStart()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	Speed_ = Default_Speed_;
	MonsterRenderer_->ChangeAnimation("Cutman_Move_HaveWeapon" + RockmanUtility::DirToStr(CurHoriDir_));
}

void Cutman::MoveUpdate()
{
	//�Ƹ��� �÷��̾ �ִ� �������� ������Ʈ�ϰ�, �ִϸ��̼��� �ֽ�ȭ �մϴ�
	float4 WantPos = float4(Player_->GetPosition().x - GetPosition().x, 0);
	float4 WantDir = WantPos;
	WantDir.Normal2D();
	if (CurHoriDir_.CompareInt2D(WantDir) == false)
	{
		CurHoriDir_ = WantDir;
		MonsterRenderer_->ChangeAnimation("Cutman_Move_HaveWeapon" + RockmanUtility::DirToStr(CurHoriDir_));
	}

	if (WantPos.Len2D() < AttackStartRange_)
	{
		GameEngineRandom NewRandom;	
		Gravity_ = NewRandom.RandomFloat(-2100, -1500);;
		ChangeState(MonsterState::Jump);
		return;
	}

	//�Ʒ� �ٴ��� ���°�� ���� ���·�
	if (CheckPixelCol(float4::DOWN, WallColor, false) == false)
	{
		Gravity_ = 0;
		ChangeState(MonsterState::Jump);
		return;
	}

	//�տ� ���� ������  �������·�
	if (CheckPixelCol(CurHoriDir_, WallColor, false) == true)
	{
		GameEngineRandom NewRandom;
		Gravity_ = NewRandom.RandomFloat(-2100, -1500);;
		ChangeState(MonsterState::Jump);
		return;
	}

	Move(CurHoriDir_, Speed_,WallColor,false);
}

void Cutman::JumpStart()
{
	MonsterRenderer_->ChangeAnimation("Cutman_Jump_HaveWeapon" + RockmanUtility::DirToStr(CurHoriDir_));
}

void Cutman::JumpUpdate()
{
	Gravity_ += 5000 * GameEngineTime::GetDeltaTime();
	Speed_ -= Speed_ * 0.5f * GameEngineTime::GetDeltaTime();

	//���� �̵�
	Move(CurHoriDir_, Speed_, WallColor, false);

	//�����̵�
	if (Gravity_ >= 0) //�������� �ִ� ���¶��
	{
		if (CheckPixelCol(float4::DOWN, WallColor, false) == true)//�������� ���¿����� ����üũ
		{
			//���� ���� ����
			if (CheckPixelCol(float4::DOWN, WallColor,false) == true)
			{
				BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

				float4 NextPos = float4(0, (GetScale().Half().y + 1));
				float4 CheckPos_Mid = GetPosition() + float4(0, (GetScale().Half().y + 1));
				float Len = NextPos.Len2D();

				while (
					true == CurBackGround->IsBlocked(CheckPos_Mid, WallColor))
				{
					NextPos.Normal2D();
					Len -= 1.0f;
					NextPos *= Len;
					CheckPos_Mid = GetPosition() += NextPos;

					//���ѷ��� Ż���� ���� ������ġ
					if (1.0f >= NextPos.Len2D())
					{
						break;
					}
				}
				float4 WantMovePos = NextPos - float4(0, GetScale().Half().y);
				SetMove(WantMovePos);
			}
			ChangeState(MonsterState::Move);
			return;
		}

		Move(float4::DOWN, Gravity_, WallColor, false);
	}
	else //����ϰ� �ִ� ���¸�
	{
		Move(float4::UP, -Gravity_, WallColor, false);
	}
}

bool Cutman::CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid)
{
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, GetScale().Half().y - 10);

		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}

		if (CurBackGround->IsBlocked(CheckPos_Top, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Bottom, _RGB)
			)
		{
			return true;
		}
	}

	//_Dir == Up or Down
	else if (_Dir.CompareInt2D(float4::DOWN) == true || _Dir.CompareInt2D(float4::UP) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();


		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20, _Dir.y * (GetScale().Half().y + 1));//�׷���Ƽ�� ������ float4::down�� ���� (�ӷ��� �ƴ� �ӵ���) Gravity�� ��ȣ�� üũ�ؾ��Ѵ�
		float4 CheckPos_Mid = GetPosition() + float4(0, _Dir.y * (GetScale().Half().y + 1));
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20, _Dir.y * (GetScale().Half().y + 1));


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right, _RGB)
			)
		{
			return true;
		}
	}
	else if (_Dir.CompareInt2D(float4::ZERO) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20, 0);
		float4 CheckPos_Mid = GetPosition() + float4(0, 0);
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20, 0);


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right, _RGB)
			)
		{
			return true;
		}
	}
	return false;
}

void Cutman::Move(float4 _Dir, float _Speed, unsigned long _RGB, bool _CheckOnlyMid)
{
	if (CheckPixelCol(_Dir, _RGB, _CheckOnlyMid) == true)
	{
		return;
	}

	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
}
