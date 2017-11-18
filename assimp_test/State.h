#ifndef __STATE_H
#define __STATE_H

/**
* @class State
* @brief State class for state machine
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
template <class entity_type>
class State{
public:
	/**
	* @brief  destructor
	*/
	virtual ~State(){}

	/**
	* @brief  this will execute when the state is entered
	* @param  state variable
	*/
	virtual void Enter(entity_type*) = 0;
	/**
	* @brief  this is the state's normal update function
	* @param  state variable
	*/
	virtual void Execute(entity_type*) = 0;
	/**
	* @brief  this will execute when the state is exited
	* @param  state variable
	*/
	virtual void Exit(entity_type*) = 0;
};

#endif