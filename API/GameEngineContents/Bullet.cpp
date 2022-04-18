#include "Bullet.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>

Bullet::Bullet()
	:HaveDir_(false),
	Speed_(1000.0f),
	Dir_({0,0}),
	DeathTime_(0.8f),
	Renderer_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetDir(const float4& _Pos,const float4& _Dir)
{
	if (_Dir.CompareInt2D(float4::RIGHT) || _Dir.CompareInt2D(float4::LEFT))
	{
		Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Bullet), RenderPivot::CENTER);
		Renderer_->SetImage("Bullet.bmp");
		Renderer_->SetTransColor(RGB(255, 255, 255));
		HaveDir_ = true;
		Dir_ = _Dir;
		SetPosition(_Pos);
		Death(DeathTime_);
		if (_Dir.CompareInt2D(float4::RIGHT))
		{
			Renderer_->SetIndex(1);
		}
		else if (_Dir.CompareInt2D(float4::LEFT))
		{
			Renderer_->SetIndex(0);
		}
		return;
	}
	
	MsgBoxAssert("Àß¸øµÈ Bullet Dir_ ");
	return;
}

void Bullet::Start()
{

}

void Bullet::Update()
{
	if (HaveDir_ == true)
	{
		SetMove(Dir_ * Speed_ * GameEngineTime::GetDeltaTime());
	}
}
