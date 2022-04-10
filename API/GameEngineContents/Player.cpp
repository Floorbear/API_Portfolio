#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "BackGround.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//Idle왼쪽 애니메이션 초기화
	{
		GameEngineRenderer* Render = CreateRenderer();
		Render->CreateAnimation("RockMan_Idle_Left.bmp", "RockMan_Idle_Left", 0, 11, 0.3f);
		Render->CreateAnimation("RockMan_Idle_Right.bmp", "RockMan_Idle_Right", 0, 11, 0.3f);
		Render->ChangeAnimation("RockMan_Idle_Right");
		Render->SetTransColor(RGB(255, 255, 255));
	}


	
	GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
	GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
}

void Player::Update()
{
	if (GameEngineInput::GetInst()->IsPress("MoveRight") == true)
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 3000);
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 3000);
	}


	float4 CameraPos = { GetPosition().x- GameEngineWindow::GetScale().Half().x,0};
	float BackGroundScale_X = GameManager::GetInst()->GetCurrentBackGround()->GetScale().x;

	if (CameraPos.x <= 0)
	{
		CameraPos.x = 0;
	}
	if (CameraPos.x > BackGroundScale_X - GameEngineWindow::GetScale().x)
	{
		CameraPos.x = BackGroundScale_X - GameEngineWindow::GetScale().x;
	}

	GetLevel()->SetCameraPos(CameraPos);
}

void Player::Render()
{
}
