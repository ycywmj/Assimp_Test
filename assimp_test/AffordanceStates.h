#ifndef __AFFORDANCESTATES_H
#define __AFFORDANCESTATES_H

#include "AISingleton.h"
#include "State.h"
#include <math.h>
#include <stdio.h> 
#include "vector2D.h"
#include "Movement.h"
#include <vector>
#include <cstdlib>
#define PI 3.14159265
class NPCs;
using namespace std;

class SearchAffordanceObj : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
private:
	double stateTime;
	//Movement *NPCs = new Movement();
};

typedef singleton<SearchAffordanceObj> search_AO_state;


#endif