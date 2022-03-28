#pragma once
class GameEngineMath
{
public:
	GameEngineMath();
	~GameEngineMath();


	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(const GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Ohter) = delete;
	GameEngineMath& operator=(const GameEngineMath&& _Other) noexcept = delete;

};

class float4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	int ix() const
	{
		return static_cast<int>(x);
	}
	int iy() const
	{
		return static_cast<int>(y);
	}
	int iz() const
	{
		return static_cast<int>(z);
	}
	int iw() const
	{
		return static_cast<int>(w);
	}
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}
	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}
	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}
	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x,y + _Other.y,z + _Other.z,1.0f };
	}
	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x,y - _Other.y,z - _Other.z,1.0f };
	}

	float4 Half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,1.0f };
	}

	bool IsZero2D()
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	float4()
		: x(0.0f),y(0.0f),z(0.0f),w(1.0f){}
	float4(float _x, float _y)
		:x(_x), y(_y),z(0.0f),w(1.0f){}
	float4(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z), w(1.0f) {}
	float4(float _x, float _y, float _z,float _w)
		:x(_x), y(_y), z(_z), w(_w) {}
};

struct GameEngineRect 
{
public:
	float4 Pos;
	float4 Scale;

public:
	int CenterTop()
	{
		return Pos.iy() - Scale.hiy();
	}
	int CenterBot()
	{
		return Pos.iy() + Scale.hiy();
	}
	int CenterLeft()
	{
		return Pos.ix() - Scale.hix();
	}
	int CenterRight()
	{
		return Pos.ix() + Scale.hix();
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		:Pos(_Pos),
		Scale(_Scale)
	{

	}

};

