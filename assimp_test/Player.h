#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player :public GameObject
{
public:
	Player() :GameObject(){ Health = 100; isKicking = false; isPraise = false; }

	void SetHealth(int HP);
	int GetHealth();

	void setActions(int ac);
	bool isPlayerKicking(){ return isKicking; };
	bool isPlayerPraising(){ return isPraise; };

private:
	int Health;
	bool isKicking;
	bool isPraise;

};

#endif