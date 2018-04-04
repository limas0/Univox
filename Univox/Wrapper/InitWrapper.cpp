#include "InitWrapper.h"
#include "..\Game.h"

InitWrapper::InitWrapper()
{

}

InitWrapper::~InitWrapper()
{

}

void InitWrapper::create(Game *instance)
{
	p_game = instance;
}

void InitWrapper::destory()
{

}

BlockRegistry &InitWrapper::getBlockRegistry()
{
	return p_game->getBlockRegistry();
}
