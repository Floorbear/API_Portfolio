#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "BackGround.h"


void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	default:
		break;
	}
}

void Player::StateChange(PlayerState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	case PlayerState::Jump:
		JumpStart();
		break;
	default:
		break;
	}
	CurState_ = _State;
}


bool Player::IsMoveKeyPress()
{
	if (GameEngineInput::GetInst()->IsPress("MoveRight") == true)
	{
		WantDir_ = float4::RIGHT;
		return true;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		WantDir_ = float4::LEFT;
		return true;
	}
	return false;
}

Player::Player()
	:Speed_(100.0),
	AccSpeed_(500.0f),
	MaxSpeed_(400.0),
	CurDir_(float4::RIGHT),
	MoveVec_({ 0,0 }),
	PlayerRenderer_(nullptr),
	Gravity_(500.0),
	AccGravity_(1000),
	MaxGravity_(100000),
	Default_Gravity_(-500)
{

}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()+float4::UP*200+float4::RIGHT*200);
	SetScale({ 100,100 });
	
	LoadAnimation();



	StateChange(PlayerState::Idle);
}

void Player::Update()
{
	StateUpdate();

	

	//카메라 체크
	float4 CameraPos = { GetPosition().x - GameEngineWindow::GetScale().Half().x,0 };
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

bool Player::CheckPixelCol(float4 _Dir)
{
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4(50 * CurDir_.x, -50);
		float4 CheckPos_Mid = GetPosition() + float4(50 * CurDir_.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4(50 * CurDir_.x, 50);


		if (CurBackGround->IsBlocked(CheckPos_Top) ||
			CurBackGround->IsBlocked(CheckPos_Mid) ||
			CurBackGround->IsBlocked(CheckPos_Bottom)
			)
		{
			return true;
		}
	}

	//_Dir == Up or Down
	else if (_Dir.CompareInt2D(float4::DOWN) == true || _Dir.CompareInt2D(float4::UP) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Left = GetPosition() + float4(-45,_Dir.y*54);
		float4 CheckPos_Mid = GetPosition() + float4(0, _Dir.y * 54);
		float4 CheckPos_Right = GetPosition() + float4(45, _Dir.y * 54);


		if (CurBackGround->IsBlocked(CheckPos_Left) ||
			CurBackGround->IsBlocked(CheckPos_Mid) ||
			CurBackGround->IsBlocked(CheckPos_Right)
			)
		{
			return true;
		}
	}
	


	return false;
}

void Player::Move(float4 _Dir, float _Speed)
{
	if (CheckPixelCol(_Dir) == true)
	{
		return;
	}

	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
}





void Player::Render()
{
	DebugRectRender();
}
