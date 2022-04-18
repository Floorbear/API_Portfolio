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
	static std::string DirToStr(float4& _Dir); //_Dir�� ���� ex(Left , Right)�� String�� ���۷����� �������ִ� �Լ�

};

