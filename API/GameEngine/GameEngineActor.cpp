#include "GameEngineActor.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{		
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
	
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();
		for (; StartIter != EndIter;StartIter++)
		{
			if ((*StartIter)->IsDeath() == false)
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}


}

void GameEngineActor::DebugRectRender()
{
	// �������� �⺻������ �߾��� ���������ϴ°� �����մϴ�.

	GameEngineRect DebugRect(Position_, Scale_);


	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

//���Ϳ� �ִ� ������ ������ �������� �浹ü�� �޸𸮿��� �������ִ� �Լ�
void GameEngineActor::Release()
{
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();
		for (; StartIter != EndIter;)
		{
			if ((*StartIter)->IsDeath() == false)
			{
				StartIter++;
				continue;
			}
			delete (*StartIter);
			StartIter = RenderList_.erase(StartIter);
		}

	}

	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();
		for (; StartIter != EndIter;)
		{
			if ((*StartIter)->IsDeath() == false)
			{
				StartIter++;
				continue;
			}
			delete (*StartIter);
			StartIter = CollisionList_.erase(StartIter);
		}

	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(int _Order,RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->SetOrder(_Order);
	}
	else
	{
		NewRenderer->SetOrder(GetOrder());
	}
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	GetLevel()->AddRenderer(NewRenderer);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;

}

//������ ���� �Լ�, ����Ʈ�� �ǹ��� CenterType, (0,0)���� �����ǰ� ������������ �̹����� �������� ���󰣴�.
GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	int _Order,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/,
	const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);
	GetLevel()->AddRenderer(NewRenderer);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}


GameEngineRenderer* GameEngineActor::CreateRendererToScale(
	const std::string& _Image, const float4& _Scale,
	int _Order,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}

	NewRenderer->SetImage(_Image);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	GetLevel()->AddRenderer(NewRenderer);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot /*= { 0, 0 }*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetScale(_Scale);
	NewCollision->SetPivot(_Pivot);

	GetLevel()->AddCollision(_GroupName, NewCollision);
	CollisionList_.push_back(NewCollision);
	return NewCollision;
}