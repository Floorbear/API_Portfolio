#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

class BackGround;
class GameManager
{
	friend GameEngineLevel;
	//�������̽� �Լ�
public:
	bool IsChangeLevel_;

	BackGround* GetCurrentBackGround() const;
	void ChangeLevel(const std::string& _Name);
	void ResetLevelInfo();

public:

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

