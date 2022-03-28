#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator ActorStart = Group.begin();
		std::list<GameEngineActor*>::iterator ActorEnd = Group.end();
		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			if ((*ActorStart) == nullptr)
			{
				continue;
			}
			delete (*ActorStart);
			(*ActorStart) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	std::list<GameEngineActor*>::iterator ActorStart;
	std::list<GameEngineActor*>::iterator ActorEnd;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		ActorStart = Group.begin();
		ActorEnd = Group.end();
		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			(*ActorStart)->Update();
		}
	}
}

void GameEngineLevel::ActorRender()
{
}
