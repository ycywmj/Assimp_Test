#include "NPCs.h"
#include "NPCStates.h"

void NPCs::SetHealth(int HP)
{
	Health = HP;

}

void NPCs::InitialState()
{
	currentState = &wander_state::Instance();
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

// state machine
void NPCs::UpdateState(Player p){

	this->PL = p;
	if (currentState)
	{
		currentState->Execute(this);
	}
}