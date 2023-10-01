
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef matrix_h
#define matrix_h

using namespace std;

// Matrix game

const int steps = 5;

const int TIME_HORIZON = steps;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 2;

// Must be between 0 and 1:
// Make sure rewards are normalized between 0 and 1.
const double escReward = 1;
const double catReward = -1;

const double rewardSpace[2] = {-1, 1};

const string actionNames[NUM_ACTIONS] = {"Stay", "Move"};

const double LEARN_RATE = 0.001;
const double EXPLORATION_CONSTANT = 0.05;
const int NUM_ROLLOUTS = 5e+06;

class State{
private:
    bool catchUsed;

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
    vector<pair<State, pair<double, double> > > transitionDistribution(int agentID) const;

    vector<pair<State, double> > initialDistribution();
};

#endif