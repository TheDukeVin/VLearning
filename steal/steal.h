
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <cfloat>
#include <assert.h>
#include <stdlib.h>

#ifndef matrix_h
#define matrix_h

using namespace std;

/*
Steal
Each agent begins with 0 coins, first to get to 10 coins wins
Each agent has (1+N) actions:
0-(N-1) = Steal - steal one coin from another agent
N = Earn - earn either 1, 2, 3 coins (randomly chosen)

Rewards:
+/- 0.05 for gaining/losing a coin
+1 for getting to 10 first, +1/(#winning agents) for ties
*/

const int coinGoal = 10;

const int TIME_HORIZON = 10;

const int NUM_AGENT = 3;

const int NUM_ACTIONS = NUM_AGENT + 1;

const int NUM_CHANCE_ACTIONS = 27;

const double rewardSpace[2] = {-0.05, 1};

const string actionNames[NUM_ACTIONS] = {"Steal0", "Steal1", "Steal2", "Earn"};

const int EARN_ACTION = NUM_AGENT;

class State{
private:
    int coins[NUM_AGENT];
public:
    int time;
    bool endState;

    int actions[NUM_AGENT];

    State();

    vector<int> validActions(int agentID);
    vector<int> validChanceActions(); // reads actions
    void makeAction(double* reward, int chanceAction = -1); // reads actions, modifies reward array.

    string toString() const;

    friend bool operator == (const State& t, const State& s){
        return t.toString() == s.toString();
    }
};

#endif