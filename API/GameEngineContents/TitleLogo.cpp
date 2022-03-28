#include "TitleLogo.h"

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	SetPosition({300,300});
	SetScale({ 100,100 });
	
}

void TitleLogo::Update()
{
	DebugRectRender();
}
