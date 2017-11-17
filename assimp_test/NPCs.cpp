#include "NPCs.h"
#include "BehaviorStates.h"
#include "EmotionStates.h"

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


void NPCs::SetDetectView(float x, float y, float z)
{
	//model[0].set(0, 0, 0);  //front face
	model[0] = glm::vec3(0, 0, 0);
	model[1] = glm::vec3(x, 0, 0);
	model[2] = glm::vec3(x, y, 0);
	model[3] = glm::vec3(0, y, 0);

	model[4] = glm::vec3(0, 0, z);  //rear face
	model[5] = glm::vec3(x, 0, z);
	model[6] = glm::vec3(x, y, z);
	model[7] = glm::vec3(0, y, z);
	ViewBox.createAABB(model, 8);

}


bool NPCs::processDetectView(NPCs *npc)
{
	//glm::vec3 collisionPoint;
	if (ViewBox.checkCollision(this->GetPosition(), npc->ViewBox, npc->GetPosition()))
	{
		return true;
	}
	return false;
}


// state machine
void NPCs::UpdateState(Player *P, map<int, NPCs*> &Agent){

	this->PL = P;
	this->Agents = Agent;

	if (currentEmotion)
	{
		currentEmotion->Execute(this);
	}


	if (currentState)
	{
		currentState->Execute(this);
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