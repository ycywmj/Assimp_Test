#ifndef __BEHAVIORSTATES_H
#define __BEHAVIORSTATES_H

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

class Response1 : public State < NPCs > {
public:
	void Enter(NPCs *npc);
	void Execute(NPCs *npc);
	void Exit(NPCs *npc);
private:
	double stateTime;
	//Movement *NPCs = new Movement();
};

class Response2 : public State < NPCs > {
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
typedef singleton<Response1> say_stop_state;
typedef singleton<Response2> say_thanks_state;

#endif