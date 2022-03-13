#pragma once
#include <crtdbg.h>
#include <assert.h>
#include <Windows.h>
#include <string>

#define MsgBoxAssert(Text)	MessageBeep(0); \
MessageBoxA(nullptr,Text,"Error",MB_OK); \
assert(false);


class GameEngineDebug
{
public:
	static void LeakCheckOn();

private:

private:
	GameEngineDebug();
	~GameEngineDebug();

	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(const GameEngineDebug&& _Other) = delete;
};

