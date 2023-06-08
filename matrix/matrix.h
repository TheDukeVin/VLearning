
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

const int NUM_CHANCE_ACTIONS = 1;

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

const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
    { 0, -1,  1},
    { 1,  0, -1},
    {-1,  1,  0}
};

const double rewardSpace[2] = {-1, 1};

const string actionNames[NUM_ACTIONS] = {"R", "P", "S"};

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     { 1, -9, -9, -9, -9},
//     { 0,  1, -9, -9, -9},
//     { 0,  0,  1, -9, -9},
//     { 0,  0,  0,  1, -9},
//     { 0,  0,  0,  0,  1},
// };

// const double rewardSpace[2] = {-9, 9};

// const string actionNames[NUM_ACTIONS] = {"M", "T", "W", "Th", "F"};

class State{
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