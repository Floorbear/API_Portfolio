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
#include "ReadyUI.h"
RockmanStage::RockmanStage()
	:
	StartBackground_(nullptr),
	IsPlayerSpawn_(false)
{
	AllBackground_.reserve(30);
}

RockmanStage::~RockmanStage()
{
}





void RockmanStage::Loading()
{
	//Bgm 셋팅
	Bgm_ = GameEngineSound::SoundPlayControl(GetNameConstRef() + ".mp3", 30);

	//모든 백그라운드 생성
	InitBackground();

	//모든 충돌체 생성
	InitColPosNScale();

	//백그라운드 간 관계 셋팅
	ConnectBackground();

	//게임 매니저에 시작 백그라운드 등록 << 이거 수정필요 if(checkPointBackgournd != nullptr) > SetCurrentBackGround(체크포인트)
	GameManager::GetInst()->SetCurrentBackGround(StartBackground_);

	//카메라 셋팅
	SetCameraPos(GameManager::GetInst()->GetCurrentBackGround()->GetPosition());

	//UI 셋팅
	CreateActor<HPBar>(static_cast<int>(GameLayer::UI), "HPBar");
	CreateActor<Scoreboard>(static_cast<int>(GameLayer::UI), "Scoreboard");
	//CreateActor<ReadyUI>(static_cast<int>(GameLayer::UI), "ReadyUI"); //릴리즈 상태에선 주석 해제
	GameManager::GetInst()->IsGameStart = true;//릴리즈 상태에선 주석


	//몬스터 로드
	InitMonster();
}

void RockmanStage::Update()
{
	if (GameManager::GetInst()->IsGameStart == true && IsPlayerSpawn_ == false)
	{
		//플레이어 로드
		Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");
		GameManager::GetInst()->SetPlayer(RockMan);
		RockMan->SetPosition(GameManager::GetInst()->GetCurrentBackGround()->GetSpawnPoint());
		IsPlayerSpawn_ = true;
	}
}

void RockmanStage::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void RockmanStage::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void RockmanStage::UserResetEnd()
{
	AllBackground_.clear();
	StartBackground_ = nullptr;
	IsPlayerSpawn_ = false;
	GameManager::GetInst()->IsGameStart = false;
	RockmanStage::Loading();
}

