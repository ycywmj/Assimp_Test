#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player :public GameObject
{
public:
	Player() :GameObject(){ Health = 100; isKicking = false; }

	void SetHealth(int HP);
	int GetHealth();

	void setActions(int ac);
	bool isPlayerKicking(){ return isKicking; };

private:
	int Health;
	bool isKicking;

};

#endif