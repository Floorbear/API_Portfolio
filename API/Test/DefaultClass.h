#pragma once
class DefaultClass
{
public:
	DefaultClass();
	~DefaultClass();


	DefaultClass(const DefaultClass& _Other) = delete;
	DefaultClass(const DefaultClass&& _Other) noexcept = delete;
	DefaultClass& operator=(const DefaultClass& _Ohter) = delete;
	DefaultClass& operator=(const DefaultClass&& _Other) noexcept = delete;

};

