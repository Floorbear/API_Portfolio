#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 50,50 });
	GameEngineRenderer* Render = CreateRenderer("Rock_Man.bmp");
}

void Player::Update()
{
}

void Player::Render()
{
}
