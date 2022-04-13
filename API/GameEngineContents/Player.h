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

	void Move(float4 _Dir, float _Speed); //충돌체크하고 이동해주는 함수

	bool IsMoveKeyPress(); //키가 눌렸는지 감지하고, 눌린 키값을 WantDir_에 셋팅

private:
	PlayerState CurState_;

	//애니메이션
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//스테이터스
private:
	float CurSpeed_;
	float Speed_;
	float AccSpeed_;
	float MaxSpeed_;
	float Gravity_;
	float AccGravity_;
	float MaxGravity_;
	float Default_Gravity_;
	float4 WantDir_;//내가 실제로 바꾸고 싶은 방향
	float4 CurDir_; //플레이어의 방향
	float4 MoveVec_;

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

