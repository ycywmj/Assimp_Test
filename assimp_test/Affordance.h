#ifndef __AFFORDANCE_H
#define __AFFORDANCE_H
#include <vector>

class Affordance
{
public:
	void SetActiveAffordence(vector<string> PossiableActions){ ActiveAffordence = PossiableActions; }
	vector<string> GetActiveAffordence(){ return ActiveAffordence; }

	void SetPassiveAffordence(vector<string> PossiableActions){ PassiveAffordence = PossiableActions; }
	vector<string> GetPassiveAffordence(){ return PassiveAffordence; }
private:
	vector<string> ActiveAffordence;
	vector<string> PassiveAffordence;
};

#endif