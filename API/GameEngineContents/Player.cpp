#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "BackGround.h"
#include "Bullet.h"
#include <GameEngine/GameEngine.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineCollision.h>
#include "RockmanStage.h"


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
	case PlayerState::Climb:
		ClimbUpdate();
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
	case PlayerState::Climb:
		ClimbStart();
		break;
	default:
		break;
	}
	CurState_ = _State;
}

void Player::GoToVer(float4 _VerDir)
{
	if (_VerDir.CompareInt2D(float4::UP) == false && _VerDir.CompareInt2D(float4::DOWN) == false)
	{
		MsgBoxAssert("�߸��� _VerDir");
	}
	CanActivate = false;
	PlayerCol_->Off();
	CameraDesY_ = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().y;
	MoveToLadderPos();

}

bool Player::IsMoveVerKeyPress()
{
	if (GameEngineInput::GetInst()->IsPress("MoveUp") == true)
	{
		WantVerDir_ = float4::UP;
		return true;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveDown") == true)
	{
		WantVerDir_ = float4::DOWN;
		return true;
	}
	return false;
}

bool Player::IsMoveHoriKeyPress()
{
	if (GameEngineInput::GetInst()->IsPress("MoveRight") == true)
	{
		WantHoriDir_ = float4::RIGHT;
		return true;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		WantHoriDir_ = float4::LEFT;
		return true;
	}
	return false;
}

void Player::Attack(const float4& _Dir,const float4& _AttackPos)
{
	if (AttackCount_ < MaxAttackCount_)
	{
		//����
		GameEngineSound::SoundPlayOneShot("Bullet.mp3");
		AttackTickTime_ = 0.0f;
		IsAttacking = true;
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(GameLayer::Bullet), "Bullet");
		NewBullet->SetDir(GetPosition()+float4(_Dir.x*_AttackPos.x,_AttackPos.y), _Dir);
		AttackCount_++;
	}
}

Player::Player()
{
	InitPlayerPara();
	PlayerStateStr_[static_cast<int>(PlayerState::Idle)] = "Idle";
	PlayerStateStr_[static_cast<int>(PlayerState::Move)] = "Move";
	PlayerStateStr_[static_cast<int>(PlayerState::Jump)] = "Jump";
	PlayerStateStr_[static_cast<int>(PlayerState::Climb)] = "Climb";


}

Player::~Player()
{
}

void Player::Start()
{

	//SetPosition(GameEngineWindow::GetScale().Half()+float4::UP*200+float4::RIGHT*-300);
	SetPosition({ 3500,700 });
	SetScale({ 100,100 });
	
	LoadAnimation();
	PlayerCol_ = CreateCollision("Player", { 60,80 });
	CameraDesY_ = CameraPosY_;
	StateChange(PlayerState::Idle);
}

void Player::Update()
{
	if (CanActivate == true)
	{
		StateUpdate();

		//���� ������ üũ
		if (IsAttacking == true)
		{
			AttackTickTime_ += GameEngineTime::GetDeltaTime();
			if (AttackTickTime_ >= MaxAttackTickTime_)
			{
				IsAttacking = false;
				AttackTickTime_ = 0.0f;
				AttackCount_ = 0;
				IsAttackEnd_ = true;
			}
		}
	}

	//�� ������ �Ͼ�� ī�޶�� �÷��̾ �ε巴�� �̵�
	if (CameraDesY_ != CameraPosY_)
	{
		float VerDirY = CameraDesY_ - CameraPosY_;
		float4 VerDir = { 0,VerDirY };
		VerDir.Normal2D();
		CameraPosY_ += VerDir.y * 800 * GameEngineTime::GetDeltaTime();

		//�÷��̾��� y��ǥ�� ���ݾ� �̵�
		SetMove(VerDir * GameEngineTime::GetDeltaTime()*150.0f);

		//�ణ�� ������ �Ͼ�� �������ش�.
		VerDir = { 0,CameraPosY_ - CameraDesY_ };
		if (VerDir.Len2D() < 0.5f)
		{
			CameraPosY_ = CameraDesY_;
		}


	}
	else //�� ������ ����Ǹ�
	{
		CanActivate = true;
		PlayerCol_->On();

	}


	//ī�޶� üũ
	float4 CameraPos = { GetPosition().x - GameEngineWindow::GetScale().Half().x,CameraPosY_ };
	float BackGroundScale_X = GameManager::GetInst()->GetCurrentBackGround()->GetScale().x + GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x;


	//ī�޶� ȭ�� ������ ����� ���ϰ� �Ѵ�
	if (CameraPos.x <= GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x)
	{
		CameraPos.x = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x;
	}
	if (CameraPos.x > BackGroundScale_X - GameEngineWindow::GetScale().x)
	{
		CameraPos.x = BackGroundScale_X - GameEngineWindow::GetScale().x;
	}

	GetLevel()->SetCameraPos(CameraPos);

}


bool Player::CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid)
{ 
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4((GetScale().Half().x-15) * CurHoriDir_.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4((GetScale().Half().x-15) * CurHoriDir_.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4((GetScale().Half().x-15 )* CurHoriDir_.x, GetScale().Half().y-10);

		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}

		if (CurBackGround->IsBlocked(CheckPos_Top,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid , _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Bottom, _RGB)
			)
		{
			return true;
		}
	}

	//_Dir == Up or Down
	else if (_Dir.CompareInt2D(float4::DOWN) == true || _Dir.CompareInt2D(float4::UP) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		
		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x+20, _Dir.y*( GetScale().Half().y +1));//�׷���Ƽ�� ������ float4::down�� ���� (�ӷ��� �ƴ� �ӵ���) Gravity�� ��ȣ�� üũ�ؾ��Ѵ�
		float4 CheckPos_Mid = GetPosition() + float4(0, _Dir.y  *(GetScale().Half().y+1));
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x-20, _Dir.y *(GetScale().Half().y +1));


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right,_RGB)
			)
		{
			return true;
		}
	}
	else if (_Dir.CompareInt2D(float4::ZERO) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20,0);
		float4 CheckPos_Mid = GetPosition() + float4(0,0);
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20,0);


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right, _RGB)
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
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(PlayerStateStr_[static_cast<int>(CurState_)]+"\n x :"+
			std::to_string(GetPosition().x) + "\n y :"+ std::to_string(GetPosition().y), GetCameraEffectPosition() + float4(-90, 90));
	}

}

void Player::InitPlayerPara()
{
	CurSpeed_ = 0.0f;
	CurState_ = PlayerState::Idle;
	AccSpeed_ = 800.0f;
	MaxSpeed_ = 350.0;

	Gravity_ = 500.0;
	AccGravity_ = 5000;
	MaxGravity_ = 800;
	JumpStrength_ = -600;

	CurHoriDir_ = float4::RIGHT;
	WantVerDir_=float4::ZERO;

	PlayerRenderer_=nullptr;

	IsColHori=false;
	IsColUP=false;
	IsColDown = false;
	CurJumpTime_=0;
	MaxJumpTime_ = 0.25f;
	CanJump_=true;
	IsAttacking = false;
	IsAttackEnd_=false;
	AttackTickTime_ = 0.0f;
	MaxAttackTickTime_=0.45f;
	AttackCount_=0;
	MaxAttackCount_ = 3;
	PlayerCol_=nullptr;
	CameraPosY_ = 0;
	CanActivate = true;
}

