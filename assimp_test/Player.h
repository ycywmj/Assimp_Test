#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player :public GameObject
{
public:
	Player() :GameObject(){ Health = 100; isKicking = false; isPraise = false; isLifting = false; obj = -1; }

	void SetHealth(int HP);
	int GetHealth();

	void setActions(int ac);
	void setIsLifting(bool il){ isLifting = il; }

	bool isPlayerKicking(){ return isKicking; };
	bool isPlayerPraising(){ return isPraise; };
	bool isPlayerLifting(){ return isLifting; };

	void SetObjectToLift(int o){ obj = o; };
	int GetObjectToLift(){ return obj; };

private:
	int obj;
	int Health;
	bool isKicking;
	bool isPraise;
	bool isLifting;

};

#endif