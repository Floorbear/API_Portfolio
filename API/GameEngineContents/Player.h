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
	inline PlayerState GetCurPlayerState()
	{
		return CurState_;
	}

private:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void ClimbStart();
	void HitStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void ClimbUpdate();
	void HitUpdate();


	//�浹ü�� ������ true, ������ false
	//�÷��̾��� ���� PixelCollision�� ����� _Dir ���� �ȼ� �浹 �˻�
	bool CheckPixelCol(float4 _Dir,unsigned long _RGB = RGB(0,0,0),bool _CheckOnlyMid = false);

	void Move(float4 _Dir, float _Speed); //�ȼ��浹üũ�ϰ� �̵����ִ� �Լ�, �ȼ��浹�� ��� ���⿡ ���� IsCol, IsVerti �� On�Ѵ�

	bool IsMoveHoriKeyPress(); //A or D Ű�� ���ȴ��� �����ϰ�, ���� Ű���� WantHoriDir_�� ����

	bool IsMoveVerKeyPress();//W or S Ű�� ���ȴ��� �����ϰ�, ���� Ű���� WantVerDir_�� ����

	void Attack(const float4& _Dir,const float4& _AttackPos = {55,0});

	void ResetAttackPara(); //���ݰ��� �������� ���½�Ű�� �Լ�

	void MoveToLadderPos(); //��ٸ��� ���� �ٰ��ϴ� �Լ�

	//ColCheck
	void CheckMonsterCol();





private:
	PlayerState CurState_;
	std::string PlayerStateStr_[static_cast<int>(PlayerState::Max)];

	//�ִϸ��̼�
private:
	void LoadAnimation();

private:
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* HitEffect_Center_Renderer_;
	GameEngineRenderer* HitEffect_Top_Renderer_;


private:
	//���� ����
	bool IsColHori; //���� �ȼ� �浹�� �߳�
	bool IsColUP; // �� �ȼ� �浹�� �߳�
	bool IsColDown; // �Ʒ� �ȼ� �浹�� �߳�

	float CurSpeed_; //"�ӷ�"
	float AccSpeed_; // ���ӷ�
	float MaxSpeed_; //�ִ� �ӷ�
	float4 WantHoriDir_;//���� ������ �ٲٰ� ���� ����
	float4 CurHoriDir_; //�÷��̾��� ����
	float4 WantVerDir_; //���� Ű�� �÷��̾��� ���� ����

	//�߷� ����
	float Gravity_; // �߷� ����̸� �������� ����
	float AccGravity_; // �߷� ���ӵ�
	float MaxGravity_; // �ִ� �߷�
	float JumpStrength_; //������ ���� ��
	float CurJumpTime_; //����Ű�� �� ���� ��� �� ���� �����ϰ� �� �� �ִ� ����
	float MaxJumpTime_; //����Ű�� �� ���� ��� ���� �ϴ� �ð�
	bool CanJump_; // ���� �� �� �ִ� ���¸� üũ

	//���� ����
	int AttackCount_; 
	int MaxAttackCount_; // �ִ� �߻� ������ �߻��ϸ�, ��Ÿ�� ���� �������� ���ϰ� �ϴ� ����
	bool IsAttacking;
	bool IsAttackEnd_;
	float AttackTickTime_;
	float MaxAttackTickTime_; //���� ���ݱ��� ��ٷ��ִ� �ð�

	//��Ʈ ����
	float CurHitTimer_; //���� ��Ʈ ���� ���ӽð�
	float GetOutHitTimer_; //�� �ð��� �Ǹ� Hit���¸� ����ϴ�
	float MaxHitTimer_; //�� �ð��� �Ǹ� �������¸� ����ϴ�.
	int HitAlpha_; //��Ʈ �ÿ� �µ� ���İ�
	bool IsHitAlphaOn_;
	float CurBlinkTimer_;
	float MaxBlinkTimer_;//�� �ð��� ������ ���İ��� ��ȭ��

	//����
	int MaxHP_;
	int CurHP_;

	//�浹ü
	GameEngineCollision* PlayerCol_;

	//ī�޶�
	float CameraPosY_;
	float CameraDesY_; //Y�� �� �̵��� �Ͼ ��� �̵��� ���� Y��ǥ

	//Ȱ��ȭ
	bool CanActivate;


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



