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

/**
* @class BehaviorStates
* @brief BehaviorStates that controll the basic respnose of actions of npcs by different outside conditions
*
*
*
*
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
class Wander : public State < NPCs > {
public:

	/**
	* @brief  enter wander state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  execute wander state that implement path finding for npcs, check if there is any 
	* outside events that happen to npcs, check if npc see any thing
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit wander state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

	//Movement *NPCs = new Movement();
	float distance;
	//string new_state_str;
private:

	///the total time runs during this state 
	double stateTime;

	///initial the number of target obejct
	int i = 0;

	///target position of object
	vector<vector2D> targetPoss;

};

class Emotions : public State < NPCs > {
public:

	/**
	* @brief  enter emotion calculate state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  calculate new value of emotions based on events 
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit emotion calculate state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response : public State < NPCs > {
public:

	/**
	* @brief  enter response state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  change into specific response state based on the actions from player 
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit response state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response1 : public State < NPCs > {
public:

	/**
	* @brief  enter say stop state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  responce to player if is kicking
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit say stop state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response2 : public State < NPCs > {
public:

	/**
	* @brief  enter say thanks state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  responce to player if is Praising
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit say thanks state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response3 : public State < NPCs > {
public:

	/**
	* @brief  enter say hi state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  implement the communication between npcs (say hi to each other)
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit say hi state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response4 : public State < NPCs > {
public:

	/**
	* @brief  enter lift state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  implement the action of lifting objects by npc
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit lift state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

class Response5 : public State < NPCs > {
public:

	/**
	* @brief  enter stand state
	* @param npc, the npc object
	*/
	void Enter(NPCs *npc);

	/**
	* @brief  implement the action of standing up on objects by npc
	* @param npc, the npc object
	*/
	void Execute(NPCs *npc);

	/**
	* @brief  Exit stand state
	* @param npc, the npc object
	*/
	void Exit(NPCs *npc);

private:
	///the total time runs during this state
	double stateTime;
};

typedef singleton<Wander> wander_state;
typedef singleton<Emotions> emotions_state;
typedef singleton<Response> response_state;
typedef singleton<Response1> say_stop_state;
typedef singleton<Response2> say_thanks_state;
typedef singleton<Response3> say_hi_state;
typedef singleton<Response4> lift_state;
typedef singleton<Response5> stand_state;
#endif