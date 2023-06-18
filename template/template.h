
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef matrix_h
#define matrix_h

using namespace std;

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 3;

const int NUM_CHANCE_ACTIONS = 4;

const double rewardSpace[2] = {0, 0};

const string actionNames[NUM_ACTIONS] = {"Lorem", "Ipsum"};

class State{
public:
    int time;
    bool endState;

    int actions[NUM_AGENT];

    State();

    vector<int> validActions(int agentID);
    void makeAction(double* reward); // reads actions, modifies reward array.

    string toString() const;

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.toString() == s.toString();
    }
};

#endif