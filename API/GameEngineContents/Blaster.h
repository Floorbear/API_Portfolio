#pragma once
class Blaster
{
public:
	Blaster();
	~Blaster();


	Blaster(const Blaster& _Other) = delete;
	Blaster(const Blaster&& _Other) noexcept = delete;
	Blaster& operator=(const Blaster& _Ohter) = delete;
	Blaster& operator=(const Blaster&& _Other) noexcept = delete;

};

