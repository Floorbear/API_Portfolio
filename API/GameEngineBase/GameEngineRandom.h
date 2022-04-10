#pragma once
#include <random>

class GameEngineRandom
{
public:
	std::mt19937_64 mt_;

public:
	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

public:
	GameEngineRandom();
	~GameEngineRandom();


	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(const GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Ohter) = delete;
	GameEngineRandom& operator=(const GameEngineRandom&& _Other) noexcept = delete;

};

