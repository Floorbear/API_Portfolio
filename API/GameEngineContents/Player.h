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

	void Move(); //MoveDir_ �������� Speed��ŭ �̵���Ű�� ī�޶� �̵��� ���ִ� �Լ�

	bool IsMoveKeyPress();

private:
	PlayerState CurState_;
	std::string PlayerDirStr_[static_cast<int>(PlayerDir::Max)];

	//�ִϸ��̼�
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//�������ͽ�
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

