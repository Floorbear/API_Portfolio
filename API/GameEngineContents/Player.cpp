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
#include "RockmanMonster.h"
#include "MonsterBullet.h"



Player::Player()
{
	InitPlayerPara();
	PlayerStateStr_[static_cast<int>(PlayerState::Idle)] = "Idle";
	PlayerStateStr_[static_cast<int>(PlayerState::Move)] = "Move";
	PlayerStateStr_[static_cast<int>(PlayerState::Jump)] = "Jump";
	PlayerStateStr_[static_cast<int>(PlayerState::Climb)] = "Climb";
	PlayerStateStr_[static_cast<int>(PlayerState::Hit)] = "Hit";

}

void Player::InitPlayerPara()
{
	MaxHP_ = 28;
	CurHP_ = MaxHP_;
	CurSpeed_ = 0.0f;
	CurState_ = PlayerState::Idle;
	AccSpeed_ = 800.0f;
	MaxSpeed_ = 350.0;

	Gravity_ = 500.0;
	AccGravity_ = 5000;
	MaxGravity_ = 800;
	JumpStrength_ = -600;

	CurHoriDir_ = float4::RIGHT;
	WantVerDir_ = float4::ZERO;

	CurHitTimer_ = 0;
	GetOutHitTimer_ = 0.45f;
	MaxHitTimer_ = 1.5f;
	HitAlpha_ = 40; //��Ʈ �ÿ� �µ� ���İ�
	CurBlinkTimer_ = 0;
	MaxBlinkTimer_ =0.12f;//�� �ð��� ������ ���İ��� ��ȭ��
	IsHitAlphaOn_ = false;

	DieTimer_ = 1.5f; //�̽ð��� ������ �״� ����Ʈ�� Ȱ��ȭ��

	PlayerRenderer_ = nullptr;

	IsColHori = false;
	IsColUP = false;
	IsColDown = false;
	CurJumpTime_ = 0;
	MaxJumpTime_ = 0.25f;
	CanJump_ = true;
	IsAttacking = false;
	IsAttackEnd_ = false;
	AttackTickTime_ = 0.0f;
	MaxAttackTickTime_ = 0.45f;
	AttackCount_ = 0;
	MaxAttackCount_ = 3;
	PlayerCol_ = nullptr;
	CameraPosY_ = 0;
	CanActivate = true;

	PlayerRenderer_ = nullptr;
	HitEffect_Center_Renderer_ = nullptr;
	HitEffect_Top_Renderer_ = nullptr;
	PlayerSpawnRenderer_ = nullptr;
}

Player::~Player()
{
}

void Player::Start()
{
	SetScale({ 100,100 });
	
	LoadAnimation();
	PlayerCol_ = CreateCollision("Player", { 60,80 });
	CameraDesY_ = CameraPosY_;
	StateChange(PlayerState::Idle);
	//���������� ���� �Ҹ�
	GameEngineSound::SoundPlayOneShot("PlayerTeleportIn.mp3");
}

void Player::Update()
{
	if (PlayerSpawnRenderer_->IsEndAnimation() == true)
	{
		PlayerRenderer_->On();
		PlayerSpawnRenderer_->Off();
	}

	if (CanActivate == true)
	{
		StateUpdate();
		CheckObstacleCol();
		if (CurHitTimer_ == 0)
		{
			IsHitAlphaOn_ = false;
			CurBlinkTimer_ = 0;
			CheckMonsterCol();
		}
		else //��Ʈ �� MaxHitTimer_�ð����� ���Ϳ��� �浹üũ�� �����ʴ´�. == �������°� �ȴ�. & ���������϶� ���İ� ����Ʈ�� �����ش�
		{
			CurBlinkTimer_ += GameEngineTime::GetDeltaTime();
			CurHitTimer_ += GameEngineTime::GetDeltaTime();

			if (CurBlinkTimer_ > MaxBlinkTimer_) //���������϶� ���ڰŸ�
			{
				if (IsHitAlphaOn_ == false)
				{
					IsHitAlphaOn_ = true;
					PlayerRenderer_->SetAlpha(HitAlpha_);
					HitEffect_Center_Renderer_->SetAlpha(HitAlpha_);
				}
				else
				{
					IsHitAlphaOn_ = false;
					PlayerRenderer_->SetAlpha(255);
					HitEffect_Center_Renderer_->SetAlpha(200);
				}
			}

			if (CurHitTimer_ >= MaxHitTimer_)
			{
				CurHitTimer_ = 0;
				PlayerRenderer_->SetAlpha(255);
			}
		}
		

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
		SetMove(VerDir * GameEngineTime::GetDeltaTime()*100.0f);

		//�ణ�� ����(ī�޶� ����� ��ŸŸ������ �Ͼ�� ������)�� �Ͼ�� �������ش�.
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

	//����׿� ���� Ű����
	if (GameEngineInput::GetInst()->IsDown("TeleportKey") == true)
	{
		std::vector<BackGround*> AllBackground = dynamic_cast<RockmanStage*>(GetLevel())->GetAllBackground();
		//!!���� Position�� �ε����� �Ѵ� �����������!!
		SetPosition({ 3936, -885 });
		GameManager::GetInst()->SetCurrentBackGround(AllBackground[1]);
		CameraDesY_ = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().y;
		CameraPosY_ = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().y;
	}

	//�÷��̾ ȭ�� ������ ����� ���ϰ�
	if (GetPosition().x < GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x)
	{
		SetPosition(float4(GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x, GetPosition().y));
	}

	//ī�޶� ȭ�� ������ ����� ���ϰ� �Ѵ�
	float4 CameraPos = { GetPosition().x - GameEngineWindow::GetScale().Half().x,CameraPosY_ };
	float BackGroundScale_X = GameManager::GetInst()->GetCurrentBackGround()->GetScale().x + GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x;


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

void Player::Render()
{
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(PlayerStateStr_[static_cast<int>(CurState_)] + "\n x :" +
			std::to_string(GetPosition().x) + "\n y :" + std::to_string(GetPosition().y), GetCameraEffectPosition() + float4(-90, 90));
	}

}

bool Player::CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid)
{ 
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4((GetScale().Half().x-15) * _Dir.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4((GetScale().Half().x-15) * _Dir.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4((GetScale().Half().x-15 )* _Dir.x, GetScale().Half().y-10);

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

void Player::Move(float4 _Dir, float _Speed, unsigned long _RGB, bool _CheckOnlyMid )
{
	if (CheckPixelCol(_Dir,_RGB,_CheckOnlyMid) == true)
	{
		return;
	}

	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
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

void Player::Attack(const float4& _Dir, const float4& _AttackPos)
{
	if (AttackCount_ < MaxAttackCount_)
	{
		//����
		GameEngineSound::SoundPlayOneShot("Bullet.mp3");
		AttackTickTime_ = 0.0f;
		IsAttacking = true;
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(GameLayer::Bullet), "Bullet");
		NewBullet->SetBullet(GetPosition() + float4(_Dir.x * _AttackPos.x, _AttackPos.y), _Dir);
		AttackCount_++;
	}
}
void Player::CheckMonsterCol()
{
	{
		//���Ϳ� ���� �浹���� �� �浹�˻�
		std::vector<GameEngineCollision*> MonsterColList;
		RockmanMonster* Monster = nullptr;
		if (PlayerCol_->CollisionResult("MonsterCol", MonsterColList, CollisionType::Rect, CollisionType::Rect) == true)
		{
			for (GameEngineCollision* MonsterCol : MonsterColList)
			{
				Monster = dynamic_cast<RockmanMonster*>(MonsterCol->GetActor());
				CurHP_ -= Monster->GetAttackDmg();
				CurHoriDir_ = float4(Monster->GetPosition().x - GetPosition().x, 0);
				CurHoriDir_.Normal2D();
				break;
			}

			if (CurHP_ <= 0)
			{
				CurHP_ = 0;
				StateChange(PlayerState::Die);
			}
			else
			{
				StateChange(PlayerState::Hit);
			}
		}
	}
	
	{
		//���� �Ѿ˿� �浹���� �� �浹�˻�
		std::vector<GameEngineCollision*> MonsterBulletList;
		MonsterBullet* MonsterBullet_ = nullptr;
		if (PlayerCol_->CollisionResult("MonsterBullet", MonsterBulletList, CollisionType::Rect, CollisionType::Rect) == true)
		{
			for (GameEngineCollision* MonsterBulletCol : MonsterBulletList)
			{
				MonsterBullet_ = dynamic_cast<MonsterBullet*>(MonsterBulletCol->GetActor());
				CurHP_ -= MonsterBullet_->GetBulletDmg();
				CurHoriDir_ = float4(MonsterBullet_->GetPosition().x - GetPosition().x, 0);
				CurHoriDir_.Normal2D();
				break;
			}

			if (CurHP_ <= 0)
			{
				CurHP_ = 0;
				StateChange(PlayerState::Die);
			}
			else
			{
				StateChange(PlayerState::Hit);
			}
		}
	}

}

void Player::CheckObstacleCol()
{
	if (PlayerCol_->CollisionCheck("ObstacleCol", CollisionType::Rect, CollisionType::Rect) == true)
	{
		if (CurHP_ > 0)
		{
			CurHP_ = 0;
			StateChange(PlayerState::Die);
		}
	}
}

