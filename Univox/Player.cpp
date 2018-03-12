#include "Player.h"

Player::Player()
{
	camera = new WE::FirstPersonCamera();
}

Player::~Player()
{
}

void Player::create()
{
	camera->create();
}

void Player::destroy()
{
	camera->destroy();
}

void Player::update()
{
	camera->update();
}

WE::FirstPersonCamera *Player::getCamera()
{
	return camera;
}
