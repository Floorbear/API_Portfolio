#include "RockMan.h"
#include "TitleLevel.h"

RockMan::RockMan()
{
}

RockMan::~RockMan()
{
}

void RockMan::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	
}
