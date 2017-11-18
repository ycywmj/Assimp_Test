#include "AffordanceStates.h"

#include <iostream>
#include "NPCs.h"
#include "World.h"
#include "Singleton.h"
using namespace std;


void SearchAffordanceObj::Enter(NPCs *npc){
	cout << "Enter SearchAffordanceObj state" << endl;
}

void SearchAffordanceObj::Execute(NPCs *npc){



}

void SearchAffordanceObj::Exit(NPCs *npc){
	cout << "Exit SearchAffordanceObj state" << endl;
}