#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

class BackGround;
class Player;
class GameManager
{
public:
	//업데이트
	void Update();
	//레벨 체인지 관련
	bool IsChangeLevel_;
	void ChangeLevel(const std::string& _Name);
	void ResetLevelInfo();

	//백그라운드 관련
	BackGround* GetCurrentBackGround() const;

	//디버그 모드 관련
private:
	bool IsDebugMode_;

public:
	// 인라인
	inline bool GetIsDebugMode()
	{
		return IsDebugMode_;
	}
	inline std::string& GetLevelString()
	{
		if (ChangeLevelName_.empty() == true)
		{
			MsgBoxAssert("ChangeLevelName_이 셋팅되지 않았습니다.");
		}

		return ChangeLevelName_;
	}

	inline void SetCurrentBackGround(BackGround* _Other)
	{
		if (_Other == nullptr)
		{
			MsgBoxAssert("Background 인자가 nullptr입니다 !");
		}
		CurrentBackGround_ = _Other;
	}

	inline Player* GetPlayer()
	{
		if (CurPlayer_ == nullptr)
		{
			MsgBoxAssert("CurPlayer가 셋팅되지 않았습니다");
		}
		return CurPlayer_;
	}

	inline void SetPlayer(Player* _Player)
	{
		CurPlayer_ = _Player;
	}



private:

	std::string ChangeLevelName_;
	BackGround* CurrentBackGround_;
	Player*  CurPlayer_;

	//싱글톤
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

