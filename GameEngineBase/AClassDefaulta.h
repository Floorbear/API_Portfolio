#pragma once

class AClassDefaulta
{
public:
	AClassDefaulta();
	~AClassDefaulta();

	AClassDefaulta(const AClassDefaulta& _Other) = delete;
	AClassDefaulta(AClassDefaulta&& _Other) noexcept = delete;
	AClassDefaulta& operator=(const AClassDefaulta& _Other) = delete;
	AClassDefaulta& operator=(const AClassDefaulta&& _Other) = delete;

protected:

private:

};

