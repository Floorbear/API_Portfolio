#pragma once
#include <crtdbg.h>
#include <assert.h>
#include <windows.h>
#include <string>

// ��üũ, ���� �޼��� �ڽ� ���� Ŭ����
class GameEngineDebug
{
public:
	static void LeakCheckOn();

private:
	GameEngineDebug();
	~GameEngineDebug();


	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(const GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Ohter) = delete;
	GameEngineDebug& operator=(const GameEngineDebug&& _Other) noexcept = delete;

};

#define MsgBoxAssert(Text)	MessageBeep(0); \
MessageBoxA(nullptr,Text,"Error",MB_OK);	\
assert(false);