#include "RockmanItem.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "BackGround.h"
#include "Player.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

RockmanItem::RockmanItem()
	:ItemRenderer_(nullptr),
	Gravity_(-600.0f),
	CurItemType_(ItemType::SmallEnergy),
	DeathTimer_(4.0f)
{
	ItemName_[static_cast<int>(ItemType::BigEnergy)] = "BigEnergy";
	ItemName_[static_cast<int>(ItemType::SmallEnergy)] = "SmallEnergy";
	ItemName_[static_cast<int>(ItemType::RedBonusBall)] = "RedBonusBall";
}

RockmanItem::~RockmanItem()
{
}

void RockmanItem::SetItem(const float4& _Pos)
{


	//���⿡ ������
	switch (CurItemType_)
	{
	case ItemType::SmallEnergy:
		SetScale({ 64,64 });
		break;
	case ItemType::BigEnergy:
		SetScale({ 64,64 });
		break;
	case ItemType::RedBonusBall:
		SetScale({ 32,32 });
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}

	ItemCol_ = CreateCollision("ItemCol", GetScale());

	float4 MovePos = _Pos+float4(0,-15);
	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	if (CurrentBackground->IsBlocked(_Pos) == true) //���� �����ϴ� �������� �� �ȼ��̸�
	{

		while (CurrentBackground->IsBlocked(MovePos) == true)
		{
			MovePos += float4::RIGHT;
		}
	}
	SetPosition(MovePos);
}

void RockmanItem::Start()
{
	//���⿡ Ȯ�� ����
	GameEngineRandom NewRandom;
	int RandomValue = NewRandom.RandomInt(0, 100);
	if (RandomValue < 70)
	{
		CurItemType_ = ItemType::RedBonusBall;

	}
	else if (RandomValue >= 70 && RandomValue < 90)
	{
		CurItemType_ = ItemType::SmallEnergy;
	}
	else
	{
		CurItemType_ = ItemType::BigEnergy;
	}

	ItemRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object));

	ItemRenderer_->SetTransColor(TransColor);
	ItemRenderer_->CreateAnimation("BonusBall.bmp", "RedBonusBall", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "SmallEnergy", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "BigEnergy", 1, 2, 1, true);


	//������Ÿ�Կ� ���� �̹��� ����
	switch (CurItemType_)
	{
	case ItemType::SmallEnergy:
		ItemRenderer_->ChangeAnimation("SmallEnergy");
		break;
	case ItemType::BigEnergy:
		ItemRenderer_->ChangeAnimation("BigEnergy");
		break;
	case ItemType::RedBonusBall:
		ItemRenderer_->ChangeAnimation("RedBonusBall");
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}
	
	

}

void RockmanItem::Update()
{
	DeathTimer_ -= GameEngineTime::GetDeltaTime();
	if (DeathTimer_ <= 0)
	{
		Death();
	}

	Gravity_ += 1500*GameEngineTime::GetDeltaTime();



	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	float4 CheckUpPos = GetPosition() + float4(0, -GetScale().Half().y);
	float4 CheckDownPos = GetPosition() + float4(0, GetScale().Half().y);
	//���� �ȼ� �浹 �˻�
	if (CurrentBackground->IsBlocked(CheckUpPos) == true)
	{
		Gravity_ = 0;
		SetMove(float4::DOWN);//1�ȼ� �Ʒ���
	}

	//�Ʒ���

	if (CurrentBackground->IsBlocked(CheckDownPos) == false)
	{
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}

	if (ItemCol_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
	{
		Player* CurPlayer = GameManager::GetInst()->GetPlayer();
		
		//�������� ������ ȿ��
		switch (CurItemType_)
		{
		case ItemType::SmallEnergy:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			CurPlayer->AddPlayerHP(2);

			break;
		case ItemType::BigEnergy:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			CurPlayer->AddPlayerHP(10);
			break;
		case ItemType::RedBonusBall:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			GameManager::GetInst()->AddScore(1000);
			break;
		case ItemType::Max:
			break;
		default:
			break;
		}
		
		Death();
	}
}
