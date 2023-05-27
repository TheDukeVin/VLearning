
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef matrix_h
#define matrix_h

using namespace std;

// Matrix game

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 3;

class State{
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