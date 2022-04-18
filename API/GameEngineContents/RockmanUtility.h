#pragma once
#include <string>
#include <GameEngineBase/GameEngineMath.h>
class RockmanUtility
{
public:
	RockmanUtility();
	~RockmanUtility();


	RockmanUtility(const RockmanUtility& _Other) = delete;
	RockmanUtility(const RockmanUtility&& _Other) noexcept = delete;
	RockmanUtility& operator=(const RockmanUtility& _Ohter) = delete;
	RockmanUtility& operator=(const RockmanUtility&& _Other) noexcept = delete;

public:
	static std::string DirToStr(float4& _Dir); //_Dir의 방향 ex(Left , Right)를 String의 레퍼런스로 리턴해주는 함수

};

