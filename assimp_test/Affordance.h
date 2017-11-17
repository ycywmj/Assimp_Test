#ifndef __AFFORDANCE_H
#define __AFFORDANCE_H

class Affordence
{
public:
	void SetActiveAffordence(vector<string> PossiableActions){ ActiveAffordence = PossiableActions; }
	vector<string> GetActiveAffordence(){ return ActiveAffordence; }

	void SetPassiveAffordence(vector<string> PossiableActions){ PassiveAffordence = PossiableActions; }
	vector<string> GetPassiveAffordence(){ return PassiveAffordence; }
private:
	vector<string> ActiveAffordence;
	vector<string> PassiveAffordence;
}

#endif