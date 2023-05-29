
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef smat_h
#define smat_h

using namespace std;

// Stochastic Matrix game

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 3;

const int NUM_CHANCE_ACTIONS = 2;

const double reward_prob[NUM_ACTIONS][NUM_ACTIONS] = {
    {0.2, 0.0, 0.7},
    {0.4, 0.6, 0.3},
    {0.1, 0.6, 1.0}
};

class State{
public:
    bool endState;

    int actions[NUM_AGENT];

    State();

    // bool validAction(int action, int playerID);
    vector<int> validActions(int agentID);
    vector<int> validChanceActions(); // reads actions
    void makeAction(double* reward, int chanceAction = -1); // reads actions, modifies reward array.

    string toString() const;

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.equals(s);
    }
};

#endif