#ifndef NPCS_H
#define NPCS_H

#include "GameObject.h"
#include "State.h"
#include "Player.h"
#include "AABB.h"

class NPCs :public GameObject
{
public:
	NPCs() :GameObject(){ targetObj = -1; }
	void InitialState();
	void SetHealth(int HP);
	int GetHealth();

	Player *GetPlayer(){ return PL; };
	map<int, NPCs*> GetAgents(){ return Agents; };
	vector<GameObject*> GetAffordanceObj(){ return AffordanceObj; }

	void setTargetObject(int to){ targetObj = to; }
	int getTargetObject(){ return targetObj; }

	void changeState(State<NPCs>* newState);
	void changeEmotionState(State<NPCs> *newState);
	void changeAffordanceState(State<NPCs> *newState);
	// state machine
	//void UpdateState(Player P);
	void UpdateState(Player *P, map<int, NPCs*> &Agent, vector<GameObject*> &AffordanceObjects);

	void SetTexts(GameObject *t){ texts = t; };
	GameObject *GetTexts(){ return texts; };

	void setCurrentEvent(float x, float y){ CurrentEvent.x = x; CurrentEvent.y = y; };
	void setEmotions(float x, float y){ Emotions.x = x; Emotions.y = y; CheckMaxValues(); };
	void setMoods(float x, float y){ Moods.x = x; Moods.y = y; CheckMaxValues(); };
	void setTraits(float x, float y){ Traits.x = x; Traits.y = y; CheckMaxValues(); };
	void setPersonalities(float x, float y){ Personalities.x = x; Personalities.y = y; CheckMaxValues(); };
	void CheckMaxValues();

	glm::vec2 getEmotions(){ return Emotions; };
	glm::vec2 getMoods(){ return Moods; };
	glm::vec2 getTraits(){ return Traits; };
	glm::vec2 getPersonalities(){ return Personalities; };
	glm::vec2 getCurrentEvent(){ return CurrentEvent; };

	void SetMoveSpeed(float s){ MoveSpeed = s; };
	float GetMoveSpeed(){ return MoveSpeed; };

	void SetDetectView(float x, float y, float z);
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