#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <list>
#include <map>

class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
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

	//�� ������ ���� ������ �� �ؾ��� ��
	virtual void Update() = 0;

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd(){}
	
	template<typename ActorType>
	ActorType* CreateActor(const std::string _Name, int _Order)
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		return nullptr;
	}
private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

