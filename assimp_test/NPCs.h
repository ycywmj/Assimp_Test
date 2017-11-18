#ifndef NPCS_H
#define NPCS_H

#include "GameObject.h"
#include "State.h"
#include "Player.h"
#include "AABB.h"

/**
* @class NPCs
* @brief NPCs does stuff
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

class NPCs :public GameObject
{
public:

	/**
	* @brief  Default construcator for npcs
	*/
	NPCs() :GameObject(){ targetObj = -1; }

	/**
	* @brief  initial state for each state machines
	*/
	void InitialState();


	/**
	* @brief  get player object from npcs
	* @return Player, the player object
	*/
	Player *GetPlayer(){ return PL; };

	/**
	* @brief  get other npcs objects from npcs
	* @return map<int, NPCs*>, map of all npcs
	*/
	map<int, NPCs*> GetAgents(){ return Agents; };

	/**
	* @brief  get all affordance objects from npcs
	* @return vector<GameObject*>, vector of all affordance objects
	*/
	vector<GameObject*> GetAffordanceObj(){ return AffordanceObj; }

	/**
	* @brief  set target object that npcs search for
	* @param to, values in number of target object
	*/
	void setTargetObject(int to){ targetObj = to; }

	/**
	* @brief  get target object from npcs
	* @return int, the number of target object
	*/
	int getTargetObject(){ return targetObj; }

	/**
	* @brief  change new state for behavior states
	* @param newState, state instance
	*/
	void changeState(State<NPCs>* newState);

	/**
	* @brief  change new state for emotion states
	* @param newState, state instance
	*/
	void changeEmotionState(State<NPCs> *newState);

	/**
	* @brief  change new state for affordance states
	* @param newState, state instance
	*/
	void changeAffordanceState(State<NPCs> *newState);

	/**
	* @brief  update new states 
	* @param P, player object
	* @param Agent, the map of all other npcs
	* @param AffordanceObjects, the vector of all affordance objects
	*/
	void UpdateState(Player *P, map<int, NPCs*> &Agent, vector<GameObject*> &AffordanceObjects);

	/**
	* @brief  Set text dialog model objects
	* @param t, the object of text model
	*/
	void SetTexts(GameObject *t){ texts = t; };

	/**
	* @brief  get text models from npcs
	* @return GameObject, the text models
	*/
	GameObject *GetTexts(){ return texts; };

	/**
	* @brief  Set current event value that will influnce npcs emotions
	* @param x, value of x on axis
	* @param y, value of y on axis
	*/
	void setCurrentEvent(float x, float y){ CurrentEvent.x = x; CurrentEvent.y = y; };

	/**
	* @brief  Set current emotions value for npcs
	* @param x, value of x on axis
	* @param y, value of y on axis
	*/
	void setEmotions(float x, float y){ Emotions.x = x; Emotions.y = y; CheckMaxValues(); };

	/**
	* @brief  Set current moods value for npcs
	* @param x, value of x on axis
	* @param y, value of y on axis
	*/
	void setMoods(float x, float y){ Moods.x = x; Moods.y = y; CheckMaxValues(); };

	/**
	* @brief  Set current traits value for npcs
	* @param x, value of x on axis
	* @param y, value of y on axis
	*/
	void setTraits(float x, float y){ Traits.x = x; Traits.y = y; CheckMaxValues(); };

	/**
	* @brief  Set current personalities value for npcs
	* @param x, value of x on axis
	* @param y, value of y on axis
	*/
	void setPersonalities(float x, float y){ Personalities.x = x; Personalities.y = y; CheckMaxValues(); };

	/**
	* @brief  make sure the value of emotions, moods, traits, and personalities all in the range between (-1,-1) and (1,1)
	*/
	void CheckMaxValues();

	/**
	* @brief  get current emotion from npcs
	* @return glm::vec2, the value of emotion
	*/
	glm::vec2 getEmotions(){ return Emotions; };

	/**
	* @brief  get current Moods from npcs
	* @return glm::vec2, the value of Moods
	*/
	glm::vec2 getMoods(){ return Moods; };

	/**
	* @brief  get current Traits from npcs
	* @return glm::vec2, the value of Traits
	*/
	glm::vec2 getTraits(){ return Traits; };

	/**
	* @brief  get current Personalities from npcs
	* @return glm::vec2, the value of Personalities
	*/
	glm::vec2 getPersonalities(){ return Personalities; };

	/**
	* @brief  get current Event from npcs
	* @return glm::vec2, the value of Event
	*/
	glm::vec2 getCurrentEvent(){ return CurrentEvent; };

	/**
	* @brief  set initial speed for npcs
	* @param s, the initial speed of npcs
	*/
	void SetMoveSpeed(float s){ MoveSpeed = s; };

	/**
	* @brief  get initial speed from npc
	* @param float, the initial speed of npc
	*/
	float GetMoveSpeed(){ return MoveSpeed; };

	/**
	* @brief  set view box for npc
	* @param x,y,z , the size of view box
	*/
	void SetDetectView(float x, float y, float z);

	/**
	* @brief  check if npc see any thing
	* @return bool, if npc see any thing
	*/
	bool processDetectView(GameObject *obj);

private:
	int Health;
	float MoveSpeed;
	//Vector3 TargetPos;
	Player *PL;
	map<int, NPCs*> Agents;
	int targetObj;

	vector<GameObject*> AffordanceObj;

	GameObject *texts;

	glm::vec2 CurrentEvent;
	glm::vec2 Emotions;
	glm::vec2 Moods;
	glm::vec2 Traits;
	glm::vec2 Personalities;

	// state machine
	State<NPCs> *currentState;
	State<NPCs> *currentEmotion;
	State<NPCs> *currentAffordance;

	/// Bounding Box vertices
	glm::vec3 model[8];
	/// Bounding Box
	AABB ViewBox;
};
#endif