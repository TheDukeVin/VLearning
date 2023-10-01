
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef smat_h
#define smat_h

using namespace std;

// Stochastic Matrix game

// ############################# PRISONERS DILLEMA #############################

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 2;

const double reward_prob0[NUM_ACTIONS][NUM_ACTIONS] = {
    {0.5, 0.0},
    {1.0, 0.2}
};

const double reward_prob1[NUM_ACTIONS][NUM_ACTIONS] = {
    {0.5, 1.0},
    {0.0, 0.2}
};

const double rewardSpace[2] = {0, 1};

const string actionNames[NUM_ACTIONS] = {"COOPERATE", "BETRAY"};

const double LEARN_RATE = 0.001;
const double EXPLORATION_CONSTANT = 0.05;
const int NUM_ROLLOUTS = 5e+06;

// ############################# CHEATING #############################

// const int TIME_HORIZON = 1;

// const int NUM_AGENT = 2;

// const int NUM_ACTIONS = 2;

// const double reward_prob0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0.9, 0.9},
//     {1.0, 0.0}
// };

// const double reward_prob1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {1.0, 0.9},
//     {0.0, 0.9}
// };

// const double rewardSpace[2] = {0, 1};

// const string actionNames[NUM_ACTIONS] = {"Relax", "Observe"};

// const double LEARN_RATE = 0.001;
// const double EXPLORATION_CONSTANT = 0.05;
// const int NUM_ROLLOUTS = 5e+06;

class State{
public:
    int time;
    bool endState;

    int actions[NUM_AGENT];

    State();
    State(string s);

    vector<int> validActions(int agentID);
    void makeAction(double* reward); // reads actions, modifies reward array.

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