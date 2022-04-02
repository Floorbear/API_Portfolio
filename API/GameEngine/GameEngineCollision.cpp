#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>


bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (_Left == nullptr || _Right == nullptr)
	{
		return false;
	}
	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRc = _Right->GetRect();

	return LeftRc.OverLap(RightRc);
}


class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};

CollisionInit InitInst = CollisionInit();


GameEngineCollision::GameEngineCollision()
	: Pivot_(float4::ZERO),
	Scale_(float4::ZERO)
{

}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Rect*/
)
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollision::CollisionResult(const std::string& _TargetGroup, std::vector<GameEngineCollision*>& _ColResult, CollisionType _This, CollisionType _Target)
{
	return false;
}

void GameEngineCollision::DebugRender()
{
}
