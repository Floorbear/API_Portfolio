#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"
#include <GameEngine/GameEngineCollision.h>
#include "GameManager.h"
#include "Player.h"

BackGround::BackGround()
	:
	DownBackground_(nullptr),
	UpBackground_(nullptr),
	Renderer_(nullptr),
	BackGroundImage_(nullptr),
	BackGroundColImage_(nullptr),
	SpawnPoint_(float4::ZERO)
{
	AllMovePrevCol_.reserve(5);
	AllMoveNextCol_.reserve(5);
}

BackGround::~BackGround()
{
}



void BackGround::Start()
{
	BackGroundImage_ = GameEngineImageManager::GetInst()->Find(GetNameConstRef() + ".bmp");

	BackGroundColImage_ = GameEngineImageManager::GetInst()->Find(GetNameConstRef() + "_Col.bmp");

	if (BackGroundImage_ == nullptr || BackGroundColImage_ == nullptr)
	{
		MsgBoxAssertString("BackGroundImage_ 혹은 BackGroundColImage를 찾을 수 없습니다." + GetNameConstRef() + ".bmp");
	}

	Renderer_ = CreateRenderer(GetNameConstRef() + ".bmp", static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	SetScale(BackGroundImage_->GetScale());
}

void BackGround::Update()
{
	//충돌체크
	//맵 방향 체크 >> 업 백그라운드와 좌표값 빼고 그 벡터로 방향을 잡자
	if (Index_ == GameManager::GetInst()->GetCurrentBackGround()->GetIndex()) //현재 백그라운드 일때만 충돌체크
	{
		for (GameEngineCollision* MoveUpCol : AllMoveNextCol_)
		{
			if (MoveUpCol->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
			{
				Player* CurPlayer = GameManager::GetInst()->GetPlayer();
				float4 Dir = float4(0, UpBackground_->GetPosition().y - GetPosition().y);
				Dir.Normal2D();
				if (Dir.CompareInt2D(float4::UP) == true) //내가 윗맵으로 올라가는 상태라면 사다리에 타고있는 상태여야한다
				{
					if (CurPlayer->GetCurPlayerState() == PlayerState::Climb)
					{
						GameManager::GetInst()->SetCurrentBackGround(UpBackground_);
						CurPlayer->GoToVer(Dir);
					}
				}
				else //다음맵이 아래면, 그냥 옮긴다
				{
					GameManager::GetInst()->SetCurrentBackGround(UpBackground_);
					CurPlayer->GoToVer(Dir);
				}
				
			}
		}

		for (GameEngineCollision* MoveDownCol : AllMovePrevCol_)
		{
			if (MoveDownCol->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
			{
				Player* CurPlayer = GameManager::GetInst()->GetPlayer();
				GameManager::GetInst()->SetCurrentBackGround(DownBackground_);
				float4 Dir = float4(0, DownBackground_->GetPosition().y -GetPosition().y);
				Dir.Normal2D();
				CurPlayer->GoToVer(Dir);
			}
		}
	}
	
}


bool BackGround::IsBlocked(const float4& _Pos , unsigned long _RGB)
{
	return _RGB == BackGroundColImage_->GetImagePixel(_Pos-GetPosition());
}
