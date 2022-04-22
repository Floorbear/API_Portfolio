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

	//현재 인덱스가 맥스 인덱스 보다 크다면 (즉 다음 백그라운드로 이동했다면), 맥스 인덱스를 늘려주고, 백그라운드를 동적 생성해준다.
	if (CurBackgroundIndex_ > MaxBackgroundIndex_)
	{
		MaxBackgroundIndex_ = CurBackgroundIndex_;
		BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), GetNameCopy()+"_" + std::to_string(CurBackgroundIndex_));
		float4 SetPos = GetCameraPos() + float4(0, _MoveDir.y * (BackGround_->GetScale().y)); //카메라 좌표를 이용해서 상대좌표로 백그라운드가 생성될 위치를 계산한다.
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
	//Bgm 셋팅
	Bgm_ = GameEngineSound::SoundPlayControl(GetNameConstRef()+".mp3", 30);

	//모든 충돌체 
	InitColPosNScale();


	//처음 백그라운드 셋팅
	BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), GetNameCopy() + "_0");

	AllBackground_.push_back(BackGround_);

	//다음 백그라운드로 이동하는 충돌체 생성
	BackGround_->CreateCollision("MoveUP",AllMoveUPColScale_[CurBackgroundIndex_], AllMoveUPColPos_[CurBackgroundIndex_]);
	BackGround_->CreateCollision("MoveUP", AllMoveUPColScale_[1], AllMoveUPColPos_[1]);

	//게임 매니저에 현재 백그라운드 등록
	GameManager::GetInst()->SetCurrentBackGround(BackGround_);

	//UI 셋팅
	CreateActor<HPBar>(static_cast<int>(GameLayer::UI), "HPBar");
	CreateActor<Scoreboard>(static_cast<int>(GameLayer::UI), "Scoreboard");

	Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");
}

void RockmanStage::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

