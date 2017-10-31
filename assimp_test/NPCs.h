#ifndef NPCS_H
#define NPCS_H

#include "GameObject.h"
#include "State.h"
#include "Player.h"

class NPCs :public GameObject
{
public:
	NPCs() :GameObject(){ }
	void InitialState();
	void SetHealth(int HP);
	int GetHealth();

	//Player GetTarget(){ return PL; };
	void changeState(State<NPCs>* newState);
	// state machine
	//void UpdateState(Player P);
	void UpdateState();

	void setCurrentEvent(float x, float y){ CurrentEvent.x = x; CurrentEvent.y = y; };
	void setEmotions(float x, float y){ Emotions.x = x; Emotions.y = y; };
	void setMoods(float x, float y){ Moods.x = x; Moods.y = y; };
	void setTraits(float x, float y){ Traits.x = x; Traits.y = y; };
	void setPersonalities(float x, float y){ Personalities.x = x; Personalities.y = y; };

	glm::vec2 getEmotions(){ return Emotions; };
	glm::vec2 getMoods(){ return Moods; };
	glm::vec2 getTraits(){ return Traits; };
	glm::vec2 getPersonalities(){ return Personalities; };
	glm::vec2 getCurrentEvent(){ return CurrentEvent; };

private:
	int Health;
	//Vector3 TargetPos;
	Player PL;

	glm::vec2 CurrentEvent;
	glm::vec2 Emotions;
	glm::vec2 Moods;
	glm::vec2 Traits;
	glm::vec2 Personalities;

	// state machine
	State<NPCs> *currentState;
};
#endif