#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

void Player::LoadAnimation()
{
	//애니메이션 초기화
	
	PlayerRenderer_ = CreateRenderer(2, RenderPivot::CENTER, float4{ 0,50 });

	//Idle
	PlayerRenderer_->CreateAnimation("RockMan_Idle_Left.bmp", "RockMan_Idle_Left", 0, 11, 0.3f);
	PlayerRenderer_->CreateAnimation("RockMan_Idle_Right.bmp", "RockMan_Idle_Right", 0, 11, 0.3f);

	PlayerRenderer_->CreateAnimation("RockMan_Move_Right.bmp", "RockMan_Move_Right", 0, 2, 0.13f);
	PlayerRenderer_->CreateAnimation("RockMan_Move_Left.bmp", "RockMan_Move_Left", 0, 2, 0.13f);
	PlayerRenderer_->ChangeAnimation("RockMan_Idle_Right");


	PlayerRenderer_->SetTransColor(RGB(255, 255, 255));

}