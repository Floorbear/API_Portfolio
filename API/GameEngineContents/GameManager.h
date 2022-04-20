#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

class BackGround;
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
		CurrentBackGround_ = _Other;
	}


private:

	std::string ChangeLevelName_;
	BackGround* CurrentBackGround_;

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

