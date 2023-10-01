
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef matrix_h
#define matrix_h

using namespace std;

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 3;

const double rewardSpace[2] = {0, 0};

const string actionNames[NUM_ACTIONS] = {"Lorem", "Ipsum"};

const double LEARN_RATE = 0.001;
const double EXPLORATION_CONSTANT = 0.05;
const int NUM_ROLLOUTS = 5e+06;

class State{
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

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.toString() == s.toString();
    }
};

#endif