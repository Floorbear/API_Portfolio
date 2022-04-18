#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/RockManEnum.h>

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

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();


	//Sub Function
	bool CheckPixelCol(float4 _Dir); //충돌체가 있으면 true, 없으면 false

	void Move(float4 _Dir, float _Speed); //픽셀충돌체크하고 이동해주는 함수, 픽셀충돌할 경우 방향에 맞춰 IsCol, IsVerti 를 On한다

	bool IsMoveKeyPress(); //키가 눌렸는지 감지하고, 눌린 키값을 WantDir_에 셋팅

	void Attack(float4 _Dir);



private:
	PlayerState CurState_;

	//애니메이션
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//스테이터스
private:
	bool IsColHori;
	bool IsColVer;

	float CurSpeed_; //"속력"
	float AccSpeed_;
	float MaxSpeed_;
	float4 WantDir_;//내가 실제로 바꾸고 싶은 방향
	float4 CurDir_; //플레이어의 방향

	//중력 관련
	float Gravity_;
	float AccGravity_;
	float MaxGravity_;
	float JumpStrength_; //점프할 때의 힘
	float CurJumpTime_; //점프키를 꾹 누를 경우 더 높이 점프하게 할 수 있는 변수
	float MaxJumpTime_; //점프키를 꾹 누를 경우 더 높이 점프하게 할 수 있는 변수
	bool CanJump_;

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



