#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/RockManEnum.h>
#include <Windows.h>

class Player : public GameEngineActor
{
	//Fsm
public:
	void StateUpdate();
	void StateChange(PlayerState _State);

private:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void ClimbStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void ClimbUpdate();


	//충돌체가 있으면 true, 없으면 false
	//플레이어의 가상 PixelCollision을 만들고 _Dir 방향 픽셀 충돌 검사
	bool CheckPixelCol(float4 _Dir,unsigned long _RGB = RGB(0,0,0),bool _CheckOnlyMid = false);

	void Move(float4 _Dir, float _Speed); //픽셀충돌체크하고 이동해주는 함수, 픽셀충돌할 경우 방향에 맞춰 IsCol, IsVerti 를 On한다

	bool IsMoveHoriKeyPress(); //A or D 키가 눌렸는지 감지하고, 눌린 키값을 WantHoriDir_에 셋팅

	bool IsMoveVerKeyPress();//W or S 키가 눌렸는지 감지하고, 눌린 키값을 WantVerDir_에 셋팅

	void Attack(const float4& _Dir);

	void ResetAttackPara(); //공격관련 변수들을 리셋시키는 함수

	void MoveToLadderPos(); //사다리로 찰싹 붙게하는 함수



private:
	PlayerState CurState_;
	std::string PlayerStateStr_[static_cast<int>(PlayerState::Max)];

	//애니메이션
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//스테이터스
private:
	bool IsColHori; //수평 픽셀 충돌을 했냐
	bool IsColVer; //수직 픽셀 충돌을 했냐

	float CurSpeed_; //"속력"
	float AccSpeed_;
	float MaxSpeed_;
	float4 WantHoriDir_;//내가 실제로 바꾸고 싶은 방향
	float4 CurHoriDir_; //플레이어의 방향

	float4 WantVerDir_;

	//중력 관련
	float Gravity_;
	float AccGravity_;
	float MaxGravity_;
	float JumpStrength_; //점프할 때의 힘
	float CurJumpTime_; //점프키를 꾹 누를 경우 더 높이 점프하게 할 수 있는 변수
	float MaxJumpTime_; //점프키를 꾹 누를 경우 더 높이 점프하게 할 수 있는 변수
	bool CanJump_;

	//공격 관련
	int AttackCount_;
	int MaxAttackCount_;
	bool IsAttacking;
	bool IsAttackEnd_;
	float AttackTickTime_;
	float MaxAttackTickTime_; //연속 공격까지 기다려주는 시간

public:
	Player();
	~Player();


	Player(const Player& _Other) = delete;
	Player(const Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Ohter) = delete;
	Player& operator=(const Player&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;
};



