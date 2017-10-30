#include "NPCStates.h"

#include <iostream>
#include "NPCs.h"

using namespace std;

void Flee::Enter(NPCs *npc){
	cout << "Enter Flee state" << endl;
}

void Flee::Execute(NPCs *npc){

	if (0)
	{
		if (0)
			npc->changeState(&wander_state::Instance());
	}


	cout << "Execute Flee state" << endl;
}

void Flee::Exit(NPCs *npc){
	cout << "Exit Flee state" << endl;
}



void Wander::Enter(NPCs *npc){
	cout << "Enter Wander state" << endl;
}

void Wander::Execute(NPCs *npc){


	if (0)
	{
		if (0)
			npc->changeState(&flee_state::Instance());
	}

	//cout << "Execute Wander state" << endl;
}

void Wander::Exit(NPCs *npc){
	cout << "Exit walk state" << endl;
}