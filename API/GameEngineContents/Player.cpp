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

void Player::Attack(float4 _Dir)
{

}

Player::Player()
	:
	AccSpeed_(500.0f),
	MaxSpeed_(400.0),
	CurDir_(float4::RIGHT),
	PlayerRenderer_(nullptr),
	Gravity_(500.0),
	AccGravity_(5000),
	MaxGravity_(800),
	JumpStrength_(-600),
	IsColHori(false),
	IsColVer(false),
	CurJumpTime_(0),
	MaxJumpTime_(0.25f),
	CanJump_(true)
{

}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()+float4::UP*200+float4::RIGHT*-300);
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

		float SpeedPos = CurDir_.x*CurSpeed_ * GameEngineTime::GetDeltaTime();
		float4 CheckPos_Top = GetPosition() + float4(SpeedPos+GetScale().Half().x * CurDir_.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4(GetScale().Half().x * CurDir_.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4(GetScale().Half().x * CurDir_.x, GetScale().Half().y-10);


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

		
		float Sign = 0; //Gravity의 부호
		if (Gravity_ >= 0)
		{
			Sign = 1.0f;
		}
		else
		{
			Sign = -1.0f;
		}
		float GravityPos = MaxGravity_ * GameEngineTime::GetDeltaTime(); //현재 중력에 따른 미래위치 추가량
		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x+5, Sign*( GetScale().Half().y +1));//그래비티는 무조건 float4::down이 들어가니 (속력이 아닌 속도라서) Gravity로 부호를 체크해야한다
		float4 CheckPos_Mid = GetPosition() + float4(0,  Sign*(GetScale().Half().y+1));
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x-5, Sign*(GetScale().Half().y +1));


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
		//좀더 정확한 충돌 측정
		if (_Dir.CompareInt2D(float4::DOWN))
		{
			BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();
			float Sign = 0; //Gravity의 부호
			if (Gravity_ >= 0)
			{
				Sign = 1.0f;
			}
			else
			{
				Sign = -1.0f;
			}
			float4 NextPos = float4(0, Sign * (GetScale().Half().y + 1));
			float4 CheckPos_Mid = GetPosition() + float4(0, Sign * (GetScale().Half().y + 1));
			float Len = NextPos.Len2D();

			while (
				true == CurBackGround->IsBlocked(CheckPos_Mid)
				)
			{
				NextPos.Normal2D();
				Len -= 1.0f;
				NextPos *= Len;
				CheckPos_Mid = GetPosition() += NextPos;

				//무한루프 탈출을 위한 안전장치
				if (1.0f >= NextPos.Len2D())
				{
					break;
				}
			}
			float4 WantMovePos = NextPos - float4(0, GetScale().Half().y);
			SetMove(WantMovePos);
			IsColVer = true;
			return;
		}

		return;
	}

	IsColVer = false;
	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
}





void Player::Render()
{
}

