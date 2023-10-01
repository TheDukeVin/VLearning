
#include <iostream>
#include <fstream>
#include <sstream>
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

const double rewardSpace[2] = {-0.05, 1};

const string actionNames[NUM_ACTIONS] = {"Steal0", "Steal1", "Steal2", "Earn"};

const int EARN_ACTION = NUM_AGENT;

const double LEARN_RATE = 0.01;
const double EXPLORATION_CONSTANT = 0.01;
const int NUM_ROLLOUTS = 5e+08;

class State{
private:
    int coins[NUM_AGENT];
public:
    int time;
    bool endState;

    int actions[NUM_AGENT];

    State();
    State(string s);

    vector<int> validActions(int agentID);
    void makeAction(double* reward); // reads actions, modifies reward array.
    double endValue(int agentID);

    string toString() const;

    friend bool operator == (const State& t, const State& s){
        return t.toString() == s.toString();
    }

    // OPTIONAL: to get exploitability
    // reads actions, returns distribution of transition states and rewards.
    // (State, probability, reward for given agentID)
    vector<pair<State, pair<double, double> > > transitionDistribution(int agentID);

    vector<pair<State, double> > initialDistribution();
};

#endif