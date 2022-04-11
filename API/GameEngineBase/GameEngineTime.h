#pragma once
#include <map>
class GameEngineTime
{

private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void Reset();
	void Update();

	static inline float GetDeltaTime()
	{
		
		return Inst_->DeltaTime_;
	}

	static inline float GetDeltaTime(int _Key)
	{
		return Inst_->DeltaTime_ * Inst_->GetTimeScale(_Key);
	}

	void SetTimeScale(int _Key, float _TimeScale)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			_TimeScale = 1.0f;
		}

		TimeScale_[_Key] = _TimeScale;
	}

	float GetTimeScale(int _Key)
	{
		return TimeScale_[_Key];
	}





protected:

private:
	__int64 SecondCount_;
	__int64 CurrentCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;
	std::map<int, float> TimeScale_;

	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};
