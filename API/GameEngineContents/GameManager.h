#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

class BackGround;
class Player;
class GameManager
{
public:
	//������Ʈ
	void Update();
	//���� ü���� ����
	bool IsChangeLevel_;
	void ChangeLevel(const std::string& _Name);
	void ResetLevelInfo();

	//��׶��� ����
	BackGround* GetCurrentBackGround() const;

	//����� ��� ����
private:
	bool IsDebugMode_;

public:
	// �ζ���
	inline bool GetIsDebugMode()
	{
		return IsDebugMode_;
	}
	inline std::string& GetLevelString()
	{
		if (ChangeLevelName_.empty() == true)
		{
			MsgBoxAssert("ChangeLevelName_�� ���õ��� �ʾҽ��ϴ�.");
		}

		return ChangeLevelName_;
	}

	inline void SetCurrentBackGround(BackGround* _Other)
	{
		if (_Other == nullptr)
		{
			MsgBoxAssert("Background ���ڰ� nullptr�Դϴ� !");
		}
		CurrentBackGround_ = _Other;
	}

	inline Player* GetPlayer()
	{
		if (CurPlayer_ == nullptr)
		{
			return nullptr;
		}
		return CurPlayer_;
	}

	inline void SetPlayer(Player* _Player)
	{
		CurPlayer_ = _Player;
	}

	inline int GetScore() const
	{
		return Score_;
	}

	inline void AddScore(int _Value)
	{
		Score_ += _Value;
		if (Score_ > 9999999)
		{
			Score_ = 9999999;
		}
	}


public:
	bool IsGameStart; //�� ������ True�� �Ǵ°��� ������ �����ϰ� �÷��̾ �����Ѵ�.


private:

	std::string ChangeLevelName_;
	BackGround* CurrentBackGround_;
	Player*  CurPlayer_;
	int Score_; //���ھ�����

	//�̱���
public:
	inline static GameManager* GetInst()
	{
		return Inst_;
	}

	inline void Destroy()
	{
		if (Inst_ == nullptr)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}
private:
	static GameManager* Inst_;

private:
	GameManager();
	~GameManager();


	GameManager(const GameManager& _Other) = delete;
	GameManager(const GameManager&& _Other) noexcept = delete;
	GameManager& operator=(const GameManager& _Ohter) = delete;
	GameManager& operator=(const GameManager&& _Other) noexcept = delete;

};

