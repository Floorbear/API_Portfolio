#pragma once
#include <GameEngine/GameEngineLevel.h>

class BackGround;
class GameManager
{
	friend GameEngineLevel;
	//�������̽� �Լ�
public:
	BackGround* GetCurrentBackGround() const;
	inline void SetCurrentBackGround(BackGround* _Other)
	{
		CurrentBackGround_ = _Other;
	}

private:
	

private:
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

