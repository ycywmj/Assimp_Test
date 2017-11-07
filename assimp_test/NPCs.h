#ifndef NPCS_H
#define NPCS_H

#include "GameObject.h"
#include "State.h"
#include "Player.h"

class NPCs :public GameObject
{
public:
	NPCs() :GameObject(){ }
	void InitialState();
	void SetHealth(int HP);
	int GetHealth();

	Player GetTarget(){ return PL; };
	void changeState(State<NPCs>* newState);
	// state machine
	void UpdateState(Player P);
private:
	int Health;
	//Vector3 TargetPos;
	Player PL;
	// state machine
	State<NPCs> *currentState;
};
#endif