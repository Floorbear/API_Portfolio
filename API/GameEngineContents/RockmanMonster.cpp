#include "RockmanMonster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"

RockmanMonster::RockmanMonster()
	:MonsterRenderer_(nullptr),
	CurState_(MonsterState::Chase),
	Player_(nullptr),
	CurHoriDir_(float4::ZERO),
	WantHoriDir_(float4::ZERO),
	Speed_(100.0f),
	AttackStartRange_(200.0f),
	AttCoolTime_(0.8f),
	CurAttTime_(0.0f)
{
	StateStr_[static_cast<int>(MonsterState::Chase)] = "Chase";
	StateStr_[static_cast<int>(MonsterState::Attack)] = "Attack";
}

RockmanMonster::~RockmanMonster()
{
}

void RockmanMonster::Start()
{
	//����׿� �׽�Ʈ ������
	SetPosition({ 3300,100 });

	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");

	Player_ = GameManager::GetInst()->GetPlayer();
}

void RockmanMonster::Update()
{
	UpdateState();

}

void RockmanMonster::Render()
{
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(StateStr_[static_cast<int>(CurState_)], GetCameraEffectPosition() + float4(0, 50));
	}

}

void RockmanMonster::ChangeState(MonsterState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case MonsterState::Chase:
		ChaseStart();
		break;
	case MonsterState::Attack:
		AttackStart();
		break;
	default:
		break;
	}

	CurState_ = _State;
}

void RockmanMonster::UpdateState()
{
	switch (CurState_)
	{
	case MonsterState::Chase:
		ChaseUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void RockmanMonster::ChaseStart()
{
	SetPosition(float4(GetPosition().x, AttackStartPos_.y));
}

void RockmanMonster::ChaseUpdate()
{
	WantHoriDir_= float4(Player_->GetPosition().x-GetPosition().x, 0);
	WantHoriDir_.Normal2D();

	//���� ��ȯ�� �Ͼ�ٸ� �ִϸ��̼��� �ٲ��
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
		CurHoriDir_ = WantHoriDir_;
	}

	//�����Ÿ� ���� �����ϸ� ������ �Ѵ�.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		ChangeState(MonsterState::Attack);
		return;
	}
	SetMove(CurHoriDir_ * Speed_*GameEngineTime::GetDeltaTime());
}

void RockmanMonster::AttackStart()
{
	AttackPos_ = Player_->GetPosition();
	AttackStartPos_ = GetPosition();

	InitVerDir_ = float4(0, Player_->GetPosition().y - GetPosition().y);
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // �ʱ� ���ǵ�

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;

}

void RockmanMonster::AttackUpdate()
{
	float Distance = float4(0, AttackPos_.y - GetPosition().y).Len2D();		//���ݸ�ǥ������ �Ÿ�

	//������ �������� �����ϸ� Vertical ������ȯ
	if (Distance < 20.0f)
	{
		CurVerDir_ = -CurVerDir_;
	}

	//Vertical ������ȯ�� �Ͼ ���¿��� ó�� ���� ������ ������ y��ǥ���� �����Ѵٸ�
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		float InitDistance = float4(0, AttackStartPos_.y - GetPosition().y).Len2D();
		if (InitDistance < 20.0f)
		{
			ChangeState(MonsterState::Chase);
			return;
		}
	}

	VerSpeed_ += 200.0f * GameEngineTime::GetDeltaTime();

	//���ӵ� �������ֱ�!!
	SetMove(float4(CurHoriDir_.x * Speed_*4.3f * GameEngineTime::GetDeltaTime(),CurVerDir_.y*VerSpeed_*GameEngineTime::GetDeltaTime()));
}
