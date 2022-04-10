#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include <map>

class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineNameObject
{
public:
	GameEngineSound();
	~GameEngineSound();


	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(const GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Ohter) = delete;
	GameEngineSound& operator=(const GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);

private:
	FMOD::Sound* Sound;

	//매니지먼트 사운드 기능
public:
	//사운드 1회 재생, 멈추기 불가능
	static void SoundPlayOneShot(const std::string& _Name);

	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);
	static void Update();

	//리소스 매니지먼트
public:
	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResoucesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;

public:
	void Stop();

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);
	

private:
	GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle);
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;



public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
};

