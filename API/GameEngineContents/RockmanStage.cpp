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


	//��� ��׶��� ����
	InitBackground();

	//��� �浹ü ����
	InitColPosNScale();

	//��׶��� �� ���� ����
	ConnectBackground();

	//���� �Ŵ����� ���� ��׶��� ��� << �̰� �����ʿ� if(checkPointBackgournd != nullptr) > SetCurrentBackGround(üũ����Ʈ)
	GameManager::GetInst()->SetCurrentBackGround(StartBackground_);

	//ī�޶� ����
	SetCameraPos(GameManager::GetInst()->GetCurrentBackGround()->GetPosition());

	//UI ����
	CreateActor<HPBar>(static_cast<int>(GameLayer::UI), "HPBar");
	CreateActor<Scoreboard>(static_cast<int>(GameLayer::UI), "Scoreboard");
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		GameManager::GetInst()->IsGameStart = true;//������ ���¿��� �ּ�
	}
	else
	{
		CreateActor<ReadyUI>(static_cast<int>(GameLayer::UI), "ReadyUI"); //������ ���¿��� �ּ� ����
	}


	//���� �ε�
	InitMonster();
}

void RockmanStage::Update()
{
	if (GameManager::GetInst()->IsGameStart == true && IsPlayerSpawn_ == false)
	{
		//�÷��̾� �ε�
		Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");
		GameManager::GetInst()->SetPlayer(RockMan);
		RockMan->SetPosition(GameManager::GetInst()->GetCurrentBackGround()->GetSpawnPoint());
		IsPlayerSpawn_ = true;
	}
}

void RockmanStage::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//Bgm ����
	Bgm_ = GameEngineSound::SoundPlayControl(GetNameConstRef() + ".mp3", 30);
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
	//Bgm ����
	Bgm_ = GameEngineSound::SoundPlayControl(GetNameConstRef() + ".mp3", 30);
	RockmanStage::Loading();
}

