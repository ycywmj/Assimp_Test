#ifndef __EMOTIONSTATES_H
#define __EMOTIONSTATES_H

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
* @class Happy
* @brief one of the emotion state, represents happy
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
class Happy : public State < NPCs > {
public:
	/**
	* @brief  enter happy state
	* @param target npc
	*/
	void Enter(NPCs *npc);
	/**
	* @brief  happy state execution
	* @param target npc
	*/
	void Execute(NPCs *npc);
	/**
	* @brief  end happy state 
	* @param target npc
	*/
	void Exit(NPCs *npc);
	//Movement *NPCs = new Movement();
private:
	/// the time that runs for this state
	double stateTime;
};

/**
* @class Sad
* @brief one of the emotion state, represents sad
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
class Sad : public State < NPCs > {
public:
	/**
	* @brief  enter Sad state
	* @param target npc
	*/
	void Enter(NPCs *npc);
	/**
	* @brief sad state execution
	* @param target npc
	*/
	void Execute(NPCs *npc);
	/**
	* @brief  end sad state
	* @param target npc
	*/
	void Exit(NPCs *npc);
private:
	/// the time that runs for this state
	double stateTime;
	//Movement *NPCs = new Movement();
};

/**
* @class Normal
* @brief one of the emotion state, represents normal emotion
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
class Normal : public State < NPCs > {
public:
	/**
	* @brief  enter normal state
	* @param target npc
	*/
	void Enter(NPCs *npc);
	/**
	* @brief  normal state execution
	* @param target npc
	*/
	void Execute(NPCs *npc);
	/**
	* @brief  end normal state
	* @param target npc
	*/
	void Exit(NPCs *npc);
private:
	/// the time that runs for this state
	double stateTime;
	//Movement *NPCs = new Movement();
};


typedef singleton<Happy> happy_state;
typedef singleton<Sad> sad_state;
typedef singleton<Normal> normal_state;

#endif