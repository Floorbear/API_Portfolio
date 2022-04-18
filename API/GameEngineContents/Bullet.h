#pragma once
#include <GameEngine/GameEngineActor.h>


class Bullet : public GameEngineActor
{
public:
	Bullet();
	~Bullet();


	Bullet(const Bullet& _Other) = delete;
	Bullet(const Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Ohter) = delete;
	Bullet& operator=(const Bullet&& _Other) noexcept = delete;
public:
	void SetDir(const float4& _Pos,const float4& _Dir);

protected:
	void Start() override;
	void Update() override;

private:
	bool HaveDir_;
	float DeathTime_;
	float Speed_;
	float4 Dir_;

	GameEngineRenderer* Renderer_;

};

