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
	SetScale({ 100,100 });
	GameEngineRenderer* Render = CreateRenderer("Rock_Man.bmp");
	Render->SetTransColor(RGB(128, 0, 128));

	GameEngineInput::GetInst_()->CreateKey("MoveRight", 'D');

}

void Player::Update()
{

}

void Player::Render()
{
}
