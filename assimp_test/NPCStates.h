#ifndef __NPCSTATES_H
#define __NPCSTATES_H

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
private:
	int i = 0;
	vector<vector2D> targetPoss;

};

class Emotions : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
private:
	double stateTime;
};

class Response : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
private:
	double stateTime;
};

class Happy : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
private:
	double stateTime;
};

class Sad : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
private:
	double stateTime;
	//Movement *NPCs = new Movement();
};

class Normal : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
private:
	double stateTime;
	//Movement *NPCs = new Movement();
};

typedef singleton<Flee> flee_state;
typedef singleton<Wander> wander_state;
typedef singleton<Emotions> emotions_state;
typedef singleton<Response> response_state;
typedef singleton<Happy> happy_state;
typedef singleton<Sad> sad_state;
typedef singleton<Normal> normal_state;


#endif