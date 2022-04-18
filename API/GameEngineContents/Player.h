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
	bool CheckPixelCol(float4 _Dir); //�浹ü�� ������ true, ������ false

	void Move(float4 _Dir, float _Speed); //�ȼ��浹üũ�ϰ� �̵����ִ� �Լ�, �ȼ��浹�� ��� ���⿡ ���� IsCol, IsVerti �� On�Ѵ�

	bool IsMoveKeyPress(); //Ű�� ���ȴ��� �����ϰ�, ���� Ű���� WantDir_�� ����

	void Attack(float4 _Dir);



private:
	PlayerState CurState_;

	//�ִϸ��̼�
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;


	//�������ͽ�
private:
	bool IsColHori;
	bool IsColVer;

	float CurSpeed_; //"�ӷ�"
	float AccSpeed_;
	float MaxSpeed_;
	float4 WantDir_;//���� ������ �ٲٰ� ���� ����
	float4 CurDir_; //�÷��̾��� ����

	//�߷� ����
	float Gravity_;
	float AccGravity_;
	float MaxGravity_;
	float JumpStrength_; //������ ���� ��
	float CurJumpTime_; //����Ű�� �� ���� ��� �� ���� �����ϰ� �� �� �ִ� ����
	float MaxJumpTime_; //����Ű�� �� ���� ��� �� ���� �����ϰ� �� �� �ִ� ����
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



