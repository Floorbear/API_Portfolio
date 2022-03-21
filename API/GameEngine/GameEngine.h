#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
//���ӿ��� = ���� ����ü�� ������, ����, �������� ����ϴ� �༮

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


	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();
		//���ø������� Ÿ���� �����ϴ� ��
		GameType UserGame;
		UserContents_ = &UserGame;
		WindowCreate();
		EngineEnd();
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

};

