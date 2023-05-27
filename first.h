
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

class State{
private:
    int time;
    bool catchUsed;

public:
    bool endState;

    int actions[NUM_AGENT];

    State();

    bool validAction(int action, int playerID);
    void makeAction(double* reward); // reads actions, modifies reward array.

    string toString() const;

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.equals(s);
    }
};

#endif