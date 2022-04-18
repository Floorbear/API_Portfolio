#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>

RockmanUtility::RockmanUtility()
{
}

RockmanUtility::~RockmanUtility()
{
}

std::string RockmanUtility::DirToStr(float4& _Dir)
{
	std::string ReturnValue = "";
	if (_Dir.CompareInt2D(float4::RIGHT) == true)
	{
		ReturnValue = "Right";
	}
	else if (_Dir.CompareInt2D(float4::LEFT) == true)
	{
		ReturnValue = "Left";
	}
	else if (_Dir.CompareInt2D(float4::DOWN) == true)
	{
		ReturnValue = "Down";
	}
	else if (_Dir.CompareInt2D(float4::UP) == true)
	{
		ReturnValue = "Down";
	}

	if (ReturnValue == "")
	{
		MsgBoxAssert("_Dir�� �߸��� ���� �Է��߽��ϴ�.");
	}

	return ReturnValue;
}
