
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#ifndef matrix_h
#define matrix_h

using namespace std;

// Matrix game

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 3;

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

// ############################# ROCK PAPER SCICCORS MATRIX GAME #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     { 0, -1,  1},
//     { 1,  0, -1},
//     {-1,  1,  0}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     { 0,  1, -1},
//     {-1,  0,  1},
//     { 1, -1,  0}
// };

// const double rewardSpace[2] = {-1, 1};

// const string actionNames[NUM_ACTIONS] = {"R", "P", "S"};

// ############################# SURPRISE EXECUTION GAME #############################

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     { 1, -9, -9, -9, -9},
//     { 0,  1, -9, -9, -9},
//     { 0,  0,  1, -9, -9},
//     { 0,  0,  0,  1, -9},
//     { 0,  0,  0,  0,  1},
// };

// const double rewardSpace[2] = {-9, 9};

// const string actionNames[NUM_ACTIONS] = {"M", "T", "W", "Th", "F"};

// ############################# PRISONERS DILEMMA #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {2, 0},
//     {3, 1}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {2, 3},
//     {0, 1}
// };

// const double rewardSpace[2] = {0, 3};

// const string actionNames[NUM_ACTIONS] = {"COOPERATE", "BETRAY"};

// ############################# CHICKEN #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {-10, 1},
//     {-1, 0}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {-10, -1},
//     {1, 0}
// };

// const double rewardSpace[2] = {-10, 1};

// const string actionNames[NUM_ACTIONS] = {"STAY", "YIELD"};

// ############################# MODIFIED RPS #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0.5, -1,  1},
//     { 1,  0, -1},
//     {-1,  1,  0}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0.5,  1, -1},
//     {-1,  0,  1},
//     { 1, -1,  0}
// };

// const double rewardSpace[2] = {-1, 1};

// const string actionNames[NUM_ACTIONS] = {"ROCK", "PAPER", "SCISSORS"};

// ############################# COORDINATE #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {1, 0, -2},
//     {0, 2, -2},
//     {-2, -2, 3}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {1, 0, -2},
//     {0, 2, -2},
//     {-2, -2, 3}
// };

// const double rewardSpace[2] = {-2, 3};

// const string actionNames[NUM_ACTIONS] = {"0", "1", "2"};

// ############################# CHEATING #############################

// const double matrix0[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, 0},
//     {1, -10}
// };

// const double matrix1[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, -1},
//     {-10, -1}
// };

// const double rewardSpace[2] = {-10, 1};

// const string actionNames[NUM_ACTIONS] = {"Relax", "Observe"};

const double LEARN_RATE = 0.01;
const double EXPLORATION_CONSTANT = 0.1;
const int NUM_ROLLOUTS = 1e+07;


class State{
public:
    int time;
    bool endState;

    int actions[NUM_AGENT];

    State();
    State(string s);

    vector<int> validActions(int agentID);
    // vector<int> validChanceActions(); // reads actions
    void makeAction(double* reward); // reads actions, modifies reward array.
    double endValue(int agentID);

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