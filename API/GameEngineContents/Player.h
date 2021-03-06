#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/RockManEnum.h>
#include <Windows.h>

class Player : public GameEngineActor
{
	//Fsm
private:
	void StateUpdate();
	void StateChange(PlayerState _State);
public:
	void GoToVer(float4 _VerDir);
	void GoToRight(float _Value);
	inline PlayerState GetCurPlayerState()
	{
		return CurState_;
	}

	inline int GetPlayerHP()
	{
		return CurHP_;
	}

	inline void AddPlayerHP(int _Value) //Value만큼 HP를 증감시켜주는 함수
	{
		CurHP_ += _Value;
		if (CurHP_ >= 28)
		{
			CurHP_ = 28;
		}

		if (CurHP_ <= 0)
		{
			CurHP_ = 0;
		}
	}

	inline bool GetCanActivate()
	{
		return CanActivate;
	}

	inline void SwitchCanActivate()
	{
		CanActivate = !CanActivate;
	}

	inline void OnCanActivate()
	{
		CanActivate = true;
	}

	inline void OffCanActivate()
	{
		CanActivate = false;
	}

	inline GameEngineRenderer* GetPlayerRenderer()
	{
		return PlayerRenderer_;
	}

	inline bool GetIsHoriCameraMove()
	{
		return IsHoriCameraMove_;
	}

private:
	void IdleStart();
	void IdleEnd();
	void MoveStart();
	void MoveEnd();
	void JumpStart();
	void JumpEnd();
	void ClimbStart();
	void ClimbEnd();
	void HitStart();
	void HitEnd();
	void DieStart();
	void DieEnd();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void ClimbUpdate();
	void HitUpdate();
	void DieUpdate();


	//충돌체가 있으면 true, 없으면 false
	//플레이어의 가상 PixelCollision을 만들고 _Dir 방향 픽셀 충돌 검사
	bool CheckPixelCol(float4 _Dir,unsigned long _RGB = RGB(0,0,0),bool _CheckOnlyMid = false);

	void Move(float4 _Dir, float _Speed, unsigned long _RGB = RGB(0, 0, 0), bool _CheckOnlyMid = false); //픽셀충돌체크하고 이동해주는 함수

	bool IsMoveHoriKeyPress(); //A or D 키가 눌렸는지 감지하고, 눌린 키값을 WantHoriDir_에 셋팅

	bool IsMoveVerKeyPress();//W or S 키가 눌렸는지 감지하고, 눌린 키값을 WantVerDir_에 셋팅

	void Attack(const float4& _Dir,const float4& _AttackPos = {55,0});

	void ResetAttackPara(); //공격관련 변수들을 리셋시키는 함수

	void MoveToLadderPos(); //사다리로 찰싹 붙게하는 함수

	//ColCheck
	void CheckMonsterCol();
	void CheckObstacleCol();





private:
	PlayerState CurState_;
	std::string PlayerStateStr_[static_cast<int>(PlayerState::Max)];

	//애니메이션
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerSpawnRenderer_;
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* HitEffect_Center_Renderer_;
	GameEngineRenderer* HitEffect_Top_Renderer_;


private:
	//기하 관련
	bool IsColHori; //수평 픽셀 충돌을 했냐
	bool IsColUP; // 윗 픽셀 충돌읠 했냐
	bool IsColDown; // 아랫 픽셀 충돌을 했냐

	float CurSpeed_; //"속력"
	float AccSpeed_; // 가속력
	float MaxSpeed_; //최대 속력
	float4 WantHoriDir_;//내가 실제로 바꾸고 싶은 방향
	float4 CurHoriDir_; //플레이어의 방향
	float4 WantVerDir_; //눌른 키값 플레이어의 수직 방향

	//중력 관련
	float Gravity_; // 중력 양수이면 떨어지는 상태
	float AccGravity_; // 중력 가속도
	float MaxGravity_; // 최대 중력
	float JumpStrength_; //점프할 때의 힘
	float CurJumpTime_; //점프키를 꾹 누를 경우 더 높이 점프하게 할 수 있는 변수
	float MaxJumpTime_; //점프키를 꾹 누를 경우 점프 하는 시간
	bool CanJump_; // 점프 할 수 있는 상태를 체크

	//공격 관련
	int AttackCount_; 
	int MaxAttackCount_; // 최대 발사 수까지 발사하면, 쿨타임 동안 공격하지 못하게 하는 변수
	bool IsAttacking;
	bool IsAttackEnd_;
	float AttackTickTime_;
	float MaxAttackTickTime_; //연속 공격까지 기다려주는 시간

	//히트 관련
	float CurHitTimer_; //현재 히트 상태 지속시간
	float GetOutHitTimer_; //이 시간이 되면 Hit상태를 벗어납니다
	float MaxHitTimer_; //이 시간이 되면 무적상태를 벗어납니다.
	int HitAlpha_; //히트 시에 셋될 알파값
	bool IsHitAlphaOn_;
	float CurBlinkTimer_;
	float MaxBlinkTimer_;//이 시간이 지나면 알파값이 변화함

	//스텟
	int MaxHP_;
	int CurHP_;

	//충돌체
	GameEngineCollision* PlayerCol_;

	//카메라
	float CameraPosY_;
	float CameraDesY_; //Y축 맵 이동이 일어날 경우 이동할 맵의 Y좌표
	float CameraDesX_;
	bool IsHoriCameraMove_;
	float HoriCameraMoveTimer_;

	//활성화
	bool CanActivate;
	float DieTimer_;
	bool IsGod_;


public:
	Player();
	~Player();


	Player(const Player& _Other) = delete;
	Player(const Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Ohter) = delete;
	Player& operator=(const Player&& _Other) noexcept = delete;

private:
	void InitPlayerPara();
	void Start() override;
	void Update() override;
	void Render() override;
};



