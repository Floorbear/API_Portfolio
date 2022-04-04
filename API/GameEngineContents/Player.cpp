#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* Render = CreateRenderer();
	Render->CreateAnimation("RockMan_Idle_Right.bmp", "RockMan_Idle_Right", 0, 2, 1.0f);
	Render->ChangeAnimation("RockMan_Idle_Right");
	Render->SetTransColor(RGB(255, 255, 255));
	GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
}

void Player::Update()
{

}

void Player::Render()
{
}
