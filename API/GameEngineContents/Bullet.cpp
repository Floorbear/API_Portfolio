#include "Bullet.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>

Bullet::Bullet()
	:HaveDir_(false),
	Speed_(100.0f),
	Dir_({0,0}),
	DeathTime_(1.0f),
	Renderer_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetDir(const float4& _Dir)
{
	if (_Dir.CompareInt2D(float4::RIGHT) || _Dir.CompareInt2D(float4::LEFT))
	{
		HaveDir_ = true;
		Dir_ = _Dir;
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
}
