#ifndef __AFFORDANCE_H
#define __AFFORDANCE_H
#include <vector>

/**
* @class Affordance
* @brief A class that manages affordance system
* can the object afford to do sth? or afford to be done sth? 
*
* @author ChengYu Yang
* @version 01
* @date 25/10/2017
*
*
*/
class Affordance
{
public:
	/**
	* @brief  set method for active affordance list
	* @param  new value to set
	*/
	void SetActiveAffordence(vector<string> PossiableActions){ ActiveAffordence = PossiableActions; }
	/**
	* @brief  get method for active affordance list
	* @return active affordance list in a string vector
	*/
	vector<string> GetActiveAffordence(){ return ActiveAffordence; }

	/**
	* @brief  set method for passive affordance list
	* @param  new value to set
	*/
	void SetPassiveAffordence(vector<string> PossiableActions){ PassiveAffordence = PossiableActions; }
	/**
	* @brief  set method for passive affordance list
	* @return passive affordance list in a string vector
	*/
	vector<string> GetPassiveAffordence(){ return PassiveAffordence; }
private:
	/// list of active affordance (what actions can do)
	vector<string> ActiveAffordence;
	/// list of passive affordance (what actions can be acted on)
	vector<string> PassiveAffordence;
};

#endif