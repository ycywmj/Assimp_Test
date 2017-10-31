#include "Player.h"

void Player::SetHealth(int HP)
{
	Health = HP;
}

int Player::GetHealth()
{
	return Health;
}

void Player::setActions(int ac)
{
	if (ac == 0)
	{
		isKicking = false;
	}

	if (ac == 1)
	{
		isKicking = true;
	}
}
