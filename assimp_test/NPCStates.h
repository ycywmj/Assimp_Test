#ifndef __NPCSTATES_H
#define __NPCSTATES_H

#include "AISingleton.h"
#include "State.h"
#include <math.h>
#include <stdio.h> 
#include "vector2D.h"
#include "Movement.h"

#define PI 3.14159265
class NPCs;
using namespace std;

class Flee : public State <NPCs> {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
	float distance;
	//string new_state_str;
};

class Wander : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
	float distance;
	//string new_state_str;
};

typedef singleton<Flee> flee_state;
typedef singleton<Wander> wander_state;

#endif