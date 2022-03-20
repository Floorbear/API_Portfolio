#pragma once
#include <GameEngineBase/GameEngineNameObject.h>


class GameEngineLevel : public GameEngineNameObject
{
public:
	GameEngineLevel();

	//�̰� ¯�߿��� 
	virtual ~GameEngineLevel();


	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(const GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Ohter) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _Other) noexcept = delete;
protected:
	// ��������鼭 ���ҽ��� ���͸� ����� �Լ�....
	virtual void Loading() = 0;

};

