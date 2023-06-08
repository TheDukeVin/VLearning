
#include <iostream>
#include <fstream>
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

class State{
private:
    bool catchUsed;

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