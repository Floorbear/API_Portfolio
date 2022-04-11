#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

class GameEngineImage;
class GameEngineLevel;
class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(const GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Ohter) = delete;
	GameEngine& operator=(const GameEngine&& _Other) noexcept = delete;

public:
	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();
		GameType UserGame;
		UserContents_ = &UserGame;
		WindowCreate();
		EngineEnd();
	}
	static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GameEngine Error Engine is not start");
		}
		return *UserContents_;
	}

protected:
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		GameEngineLevel* Level = NewLevel;
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}
	void ChangeLevel(const std::string& _Name);

	static inline GameEngineLevel* GetPrevLevel()
	{
		return PrevLevel_;
	}

private:
	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();


private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngine* UserContents_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* PrevLevel_;


	static GameEngineImage* WindowMainImage_;
	static GameEngineImage* BackBufferImage_;

};

