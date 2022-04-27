#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

void Player::LoadAnimation()
{
	//렌더러 초기화
	PlayerRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, float4{0,50});
	PlayerSpawnRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, float4{ 0,50 });
	HitEffect_Center_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER);
	HitEffect_Top_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER,float4(0,-50));
	//
	PlayerSpawnRenderer_->CreateAnimation("RockMan_Spawn.bmp", "RockMan_Spawn", 0, 2, 0.07f,false);

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

	HitEffect_Center_Renderer_->CreateAnimation("HitEffect_Center.bmp", "HitEffect_Center_On", 0, 0, 0.05f, true);
	HitEffect_Center_Renderer_->CreateAnimation("HitEffect_Center.bmp", "HitEffect_Center_Off", 1, 1, 0.05f, false);
	HitEffect_Top_Renderer_->CreateAnimation("HitEffect_Top.bmp", "HitEffect_Top_On", 0, 3, 0.07f, false);
	HitEffect_Top_Renderer_->CreateAnimation("HitEffect_Top.bmp", "HitEffect_Top_Off", 3, 3, 0.07f, false);

	PlayerSpawnRenderer_->ChangeAnimation("RockMan_Spawn");
	PlayerRenderer_->ChangeAnimation("RockMan_Idle_Right");
	PlayerRenderer_->Off();
	HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
	HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");


	PlayerSpawnRenderer_->SetTransColor(RGB(255, 255, 255));
	PlayerRenderer_->SetTransColor(RGB(255, 255, 255));
	HitEffect_Center_Renderer_->SetTransColor(RGB(255, 255, 255));
	HitEffect_Top_Renderer_->SetTransColor(RGB(255, 255, 255));

	HitEffect_Center_Renderer_->SetAlpha(140);
}