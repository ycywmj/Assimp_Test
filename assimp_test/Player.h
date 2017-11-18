#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

/**
* @class Player
* @brief Manage the specific GameObject with entities of a Player
*
* @author ChengYu Yang
* @version 01
* @date 15/09/2017
*
*
*/
class Player :public GameObject
{
public:
	/**
	* @brief  constructor
	*/
	Player() :GameObject(){ Health = 100; isKicking = false; isPraise = false; isLifting = false; obj = -1; }

	/**
	* @brief  set method for health point
	* @param  new value to set
	*/
	void SetHealth(int HP);
	/**
	* @brief  get method for health point
	* @return value of member variable hp
	*/
	int GetHealth();

	/**
	* @brief  set method for action to do
	* @param  new value to set
	*/
	void setActions(int ac);

	void setActionsValue(double x, double y){ actionValue.x = x; actionValue.y = y; }
	glm::vec2 getActionsValue(){ return actionValue; }

	/**
	* @brief  set method for is lifting action
	* @param  new value to set
	*/
	void setIsLifting(bool il){ isLifting = il; }

	/**
	* @brief  get the status of player that is kicking
	* @return true if is kicking
	*/
	bool isPlayerKicking(){ return isKicking; };
	/**
	* @brief  get the status of player that is praising
	* @return true if is praising
	*/
	bool isPlayerPraising(){ return isPraise; };
	/**
	* @brief  get the status of player that is lifting thing
	* @return true if is lifting thing
	*/
	bool isPlayerLifting(){ return isLifting; };

	/**
	* @brief  set the thing that player is lifting
	* @param object index that is lifting
	*/
	void SetObjectToLift(int o){ obj = o; };
	/**
	* @brief  get the object index that player is lifting
	* @return object index that is lifting
	*/
	int GetObjectToLift(){ return obj; };

private:
	/// object index that player is lifting
	int obj;
	/// health point
	int Health;
	/// status of player kicking sth
	bool isKicking;
	/// status of player praising sth
	bool isPraise;
	/// status of player lifting sth
	bool isLifting;

	///events value
	glm::vec2 actionValue;
};

#endif