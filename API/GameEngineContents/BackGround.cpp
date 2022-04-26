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
	BackGroundColImage_(nullptr)
{
	AllMoveDownCol_.reserve(5);
	AllMoveUPCol_.reserve(5);
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
	for (GameEngineCollision* MoveUpCol : AllMoveUPCol_)
	{
		if(MoveUpCol->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
		{
			Player* CurPlayer = GameManager::GetInst()->GetPlayer();
			if (CurPlayer->GetCurPlayerState() == PlayerState::Climb)
			{
				GameManager::GetInst()->SetCurrentBackGround(UpBackground_);
				CurPlayer->GoToVer(float4::UP);
			}
		}
	}

	for (GameEngineCollision* MoveDownCol : AllMoveDownCol_)
	{
		if (MoveDownCol->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
		{
			Player* CurPlayer = GameManager::GetInst()->GetPlayer();
			GameManager::GetInst()->SetCurrentBackGround(DownBackground_);
			CurPlayer->GoToVer(float4::DOWN);
		}
	}
}


bool BackGround::IsBlocked(const float4& _Pos , unsigned long _RGB)
{
	return _RGB == BackGroundColImage_->GetImagePixel(_Pos-GetPosition());
}
