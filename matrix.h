
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

const double MAX_REWARD = 10;

const int NUM_ACTIONS = 5;

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, 1, 3},
//     {1, 4, 0},
//     {2, 0, 2}
// };

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {1, 2, 0},
//     {0, 1, 2},
//     {2, 0, 1}
// };

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {10,  0,  0},
//     { 9, 10,  0},
//     { 9,  9, 10}
// };

const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
    {10,  0,  0,  0,  0},
    { 9, 10,  0,  0,  0},
    { 9,  9, 10,  0,  0},
    { 9,  9,  9, 10,  0},
    { 9,  9,  9,  9, 10},
};

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