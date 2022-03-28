#include "TitleBackGround.h"

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition({ 600,300 });
	SetScale({ 100,100 });
}

void TitleBackGround::Update()
{
	DebugRectRender();
}
