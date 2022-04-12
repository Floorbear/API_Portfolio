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

	void IdleUpdate();
	void MoveUpdate();

	//Sub Function
	bool CheckPixelCol(PlayerDir _Dir);

	void Move(); //MoveDir_ 방향으로 Speed만큼 이동시키고 카메라 이동을 해주는 함수

	bool IsMoveKeyPress();

private:
	PlayerState CurState_;
	std::string PlayerDirStr_[static_cast<int>(PlayerDir::Max)];

	//애니메이션
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//스테이터스
private:
	float Speed_;
	float AccSpeed_;
	float MaxSpeed_;
	PlayerDir CurDir_;
	float4 MoveDir_;
	float DirValue_[static_cast<int>(PlayerDir::Max)];

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

