#pragma once

class AClassDefault
{
public:
	AClassDefault();
	~AClassDefault();

	AClassDefault(const AClassDefault& _Other) = delete;
	AClassDefault(AClassDefault&& _Other) noexcept = delete;
	AClassDefault& operator=(const AClassDefault& _Other) = delete;
	AClassDefault& operator=(const AClassDefault&& _Other) = delete;

protected:

private:

};

