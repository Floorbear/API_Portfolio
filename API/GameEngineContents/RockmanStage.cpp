#include "RockmanStage.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "GameManager.h"
#include "HPBar.h"
#include "Scoreboard.h"
#include "RockManEnum.h"

RockmanStage::RockmanStage()
	:
	CurBackgroundIndex_(0),
	MaxBackgroundIndex_(0)
{
	AllMoveDOWNColPos_.resize(30);
	AllMoveDOWNColScale_.resize(30);
	AllMoveUPColPos_.resize(30);
	AllMoveUPColScale_.resize(30);
	//AllBackgroundImages_.reserve(30);
	// AllBackgroundColImages_.reserve(30);
	AllBackground_.reserve(30);
}

RockmanStage::~RockmanStage()
{
}

void RockmanStage::ChangeBackground(BackgroundDir _Dir, const float4& _MoveDir)
{
	if (_Dir == BackgroundDir::Next)
	{
		CurBackgroundIndex_++;
	}
	else if (_Dir == BackgroundDir::Prev)
	{
		CurBackgroundIndex_--;
	}

	//���� �ε����� �ƽ� �ε��� ���� ũ�ٸ� (�� ���� ��׶���� �̵��ߴٸ�), �ƽ� �ε����� �÷��ְ�, ��׶��带 ���� �������ش�.
	if (CurBackgroundIndex_ > MaxBackgroundIndex_)
	{
		MaxBackgroundIndex_ = CurBackgroundIndex_;
		BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), GetNameCopy()+"_" + std::to_string(CurBackgroundIndex_));
		float4 SetPos = GetCameraPos() + float4(0, _MoveDir.y * (BackGround_->GetScale().y)); //ī�޶� ��ǥ�� �̿��ؼ� �����ǥ�� ��׶��尡 ������ ��ġ�� ����Ѵ�.
		BackGround_->SetPosition(SetPos);


		AllBackground_.push_back(BackGround_);

		GameManager::GetInst()->SetCurrentBackGround(BackGround_);
	}
}

void RockmanStage::Loading()
{
}

void RockmanStage::Update()
{
}

void RockmanStage::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//Bgm ����
	Bgm_ = GameEngineSound::SoundPlayControl(GetNameConstRef()+".mp3", 30);

	//��� �浹ü 
	InitColPosNScale();


	//ó�� ��׶��� ����
	BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), GetNameCopy() + "_0");

	AllBackground_.push_back(BackGround_);

	//���� ��׶���� �̵��ϴ� �浹ü ����
	BackGround_->CreateCollision("MoveUP",AllMoveUPColScale_[CurBackgroundIndex_], AllMoveUPColPos_[CurBackgroundIndex_]);
	BackGround_->CreateCollision("MoveUP", AllMoveUPColScale_[1], AllMoveUPColPos_[1]);

	//���� �Ŵ����� ���� ��׶��� ���
	GameManager::GetInst()->SetCurrentBackGround(BackGround_);

	//UI ����
	CreateActor<HPBar>(static_cast<int>(GameLayer::UI), "HPBar");
	CreateActor<Scoreboard>(static_cast<int>(GameLayer::UI), "Scoreboard");

	Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");
}

void RockmanStage::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

