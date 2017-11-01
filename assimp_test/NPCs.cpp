#include "NPCs.h"
#include "NPCStates.h"

void NPCs::SetHealth(int HP)
{
	Health = HP;

}

void NPCs::InitialState()
{
	currentState = &wander_state::Instance();
	currentEmotion = &normal_state::Instance();
}

int NPCs::GetHealth()
{
	return Health;
}

void NPCs::changeState(State<NPCs> *newState)
{
	//call the exit method of the existing state
	currentState->Exit(this);
	//change state to the new state
	currentState = newState;
	//call the entry method of the new state
	currentState->Enter(this);
}

void NPCs::changeEmotionState(State<NPCs> *newState)
{
	//call the exit method of the existing state
	currentEmotion->Exit(this);
	//change state to the new state
	currentEmotion = newState;
	//call the entry method of the new state
	currentEmotion->Enter(this);
}

// state machine
void NPCs::UpdateState(Player *P){

	this->PL = P;
	if (currentState)
	{
		currentState->Execute(this);
	}

	if (currentEmotion)
	{
		currentEmotion->Execute(this);
	}

	if (Emotions.x > 0)
	{
		Emotions.x -= 0.0001;
	}
	if (Emotions.x < 0)
	{
		Emotions.x += 0.0001;
	}
	if (Emotions.y > 0)
	{
		Emotions.y -= 0.0001;
	}
	if (Emotions.y < 0)
	{
		Emotions.y += 0.0001;
	}
}

void NPCs::CheckMaxValues()
{
	if (Emotions.x > 1)
	{
		Emotions.x = 1;
	}
	if (Emotions.x < -1)
	{
		Emotions.x = -1;
	}
	if (Emotions.y > 1)
	{
		Emotions.y = 1;
	}
	if (Emotions.y < -1)
	{
		Emotions.y = -1;
	}



	if (Moods.x > 1)
	{
		Moods.x = 1;
	}
	if (Moods.x < -1)
	{
		Moods.x = -1;
	}
	if (Moods.y > 1)
	{
		Moods.y = 1;
	}
	if (Moods.y < -1)
	{
		Moods.y = -1;
	}

	if (Traits.x > 1)
	{
		Traits.x = 1;
	}
	if (Traits.x < -1)
	{
		Traits.x = -1;
	}
	if (Traits.y > 1)
	{
		Traits.y = 1;
	}
	if (Traits.y < -1)
	{
		Traits.y = -1;
	}

	if (Personalities.x > 1)
	{
		Personalities.x = 1;
	}
	if (Personalities.x < -1)
	{
		Personalities.x = -1;
	}
	if (Personalities.y > 1)
	{
		Personalities.y = 1;
	}
	if (Personalities.y < -1)
	{
		Personalities.y = -1;
	}
}