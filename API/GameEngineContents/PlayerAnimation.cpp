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

	PlayerRenderer_->CreateAnimation("RockMan_Move_Right.bmp", "RockMan_Move_Right", 0, 2, 0.1f);
	PlayerRenderer_->CreateAnimation("RockMan_Move_Left.bmp", "RockMan_Move_Left", 0, 2, 0.1f);

	PlayerRenderer_->CreateAnimation("RockMan_Jump_Left.bmp", "RockMan_Jump_Left", 0, 0, 2, false);
	PlayerRenderer_->CreateAnimation("RockMan_Jump_Right.bmp", "RockMan_Jump_Right", 0, 0, 2, false);

	PlayerRenderer_->CreateAnimation("RockMan_Attack_Left.bmp", "RockMan_IdleAttack_Left", 0, 0, 0.2f, false);
	PlayerRenderer_->CreateAnimation("RockMan_Attack_Right.bmp", "RockMan_IdleAttack_Right", 0, 0, 0.2f, false);

	PlayerRenderer_->CreateAnimation("RockMan_Attack_Left.bmp", "RockMan_MoveAttack_Left", 1, 3, 0.1f, true);
	PlayerRenderer_->CreateAnimation("RockMan_Attack_Right.bmp", "RockMan_MoveAttack_Right", 1, 3, 0.1f, true);

	PlayerRenderer_->CreateAnimation("RockMan_Attack_Left.bmp", "RockMan_JumpAttack_Left", 4, 4, 0.5f, false);
	PlayerRenderer_->CreateAnimation("RockMan_Attack_Right.bmp", "RockMan_JumpAttack_Right", 4, 4, 0.5f, false);

	PlayerRenderer_->CreateAnimation("RockMan_Climb.bmp", "RockMan_Climb", 0, 1, 0.2f, true);

	PlayerRenderer_->CreateAnimation("RockMan_ClimbAttack.bmp", "RockMan_ClimbAttack_Left", 0, 0, 0.15f, false);
	PlayerRenderer_->CreateAnimation("RockMan_ClimbAttack.bmp", "RockMan_ClimbAttack_Right", 1, 1, 0.15f, false);

	PlayerRenderer_->CreateAnimation("RockMan_Hit_Right.bmp", "RockMan_Hit_Right", 0, 0, 0.3f, false);
	PlayerRenderer_->CreateAnimation("RockMan_Hit_Left.bmp", "RockMan_Hit_Left", 0, 0, 0.3f, false);


	PlayerRenderer_->ChangeAnimation("RockMan_Idle_Right");


	PlayerRenderer_->SetTransColor(RGB(255, 255, 255));

}