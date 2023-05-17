
/*
Compilation
g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp matrix_state.cpp
g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp snake_state.cpp
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef vlearn_h
#define vlearn_h

using namespace std;

// common functions

int sampleDist(double* dist, int N);

// 2-player Snake game

// Note: there are conflicting variable names here including
/*
numAgents/NUM_AGENT
maxTime/TIME_HORIZON
numActions/NUM_ACTION
validAgentAction/validAction - the two arguments are flipped.
*/
/*
const int numAgents = 2; //repeat - should fix
const int NUM_AGENT = 2;

const int boardx = 4;
const int boardy = 4;

const int maxTime = 20; //repeat - should fix
const int TIME_HORIZON = 20;

const int numAgentActions = 4;
const int numChanceActions = (boardx * boardy);
// const int maxNumActions = (boardx * boardy);

const int LosePenalty = 5;

// const int numActions[2] = {numAgentActions, numChanceActions};
const int NUM_ACTIONS = numAgentActions; //repeat - should fix

const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

const double MAX_REWARD = 10;

class Pos{
public:
    int x, y;

    Pos(){
        x = y = -1;
    }

    Pos(int _x, int _y){
        x = _x; y = _y;
    }

    bool inBounds(){
        return 0 <= x && x < boardx && 0 <= y && y < boardy;
    }

    Pos shift(int d){
        return Pos(x + dir[d][0], y + dir[d][1]);
    }

    friend bool operator == (const Pos& p, const Pos& q){
        return (p.x == q.x) && (p.y == q.y);
    }

    friend bool operator != (const Pos& p, const Pos& q){
        return (p.x != q.x) || (p.y != q.y);
    }
};

class Snake{
public:
    int size;
    Pos head;
    Pos tail;

    Snake(){
        size = -1;
    }

    friend bool operator != (const Snake& r, const Snake& s){
        return (r.size != s.size) || (r.head != s.head) || (r.tail != s.tail);
    }
};

// Class to encode action info at a time step
class Action{
public:
    int actionType;
    int agentActions[numAgents];
    int chanceAction;

    int actionID(){
        if(actionType == 0) return agentActions[0] + agentActions[1] * numAgentActions;
        return chanceAction;
    }
};

class State{
public:
    int timer;
    int actionType; // 0 = action state, 1 = reaction state.

    Snake snakes[numAgents];
    Pos apple;

     // -1 = not snake. 0 to 3 = snake unit pointing to next unit. 4 = head.
     // +5k for agent k
    int grid[boardx][boardy];

    void setGridValue(Pos p, int val);
    int getGridValue(Pos p);

    bool validChanceAction(int pos);
    void chanceAction(int actionIndex);

    

    bool endState;

    int actions[NUM_AGENT];

    State();

    bool validAction(int action, int playerID);

    // reads actions, modifies reward array.
    // changes state info and endState.
    void makeAction(double* reward);

    string toString();

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.equals(s);
    }
};

class StateHash{
public:
    size_t operator()(const State& env) const {
        return env.hashValue();
    }
};
*/


// Matrix game



const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const double MAX_REWARD = 10;

const int NUM_ACTIONS = 3;

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, 1, 3},
//     {1, 4, 0},
//     {2, 0, 2}
// };

const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
    {0, 10, 10},
    {1,  0, 10},
    {1,  1,  0}
};

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, 1, -1},
//     {-1, 0, 1},
//     {1, -1, 0}
// };

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

class StateHash{
public:
    size_t operator()(const State& s) const {
        return s.hashValue();
    }
};



// VLearning algorithm

unordered_set<State, StateHash> all_states();

class AdvBandit{
private:
    State s;
    int agentID;
    bool validAction[NUM_ACTIONS];
    int numValidAction;
    int visitCount;
    double sumLoss[NUM_ACTIONS];

    double learnRate(){
        // return sqrt((TIME_HORIZON+1.0)/(TIME_HORIZON+visitCount));
        return 0.001;
    }
    double explorationRate(){
        // return 1/sqrt(TIME_HORIZON+visitCount);
        return 0;
    }

    double lossWeight(){
        //return learnRate() / prod_learn;
        return 1;
    }
    double sampleSkew(){
        // return 1/sqrt(TIME_HORIZON+visitCount);
        return 0;
    }

public:
    AdvBandit();
    AdvBandit(State s_, int ag);

    double value;
    double actionProb[NUM_ACTIONS];
    double aggPolicy[NUM_ACTIONS];

    int sampleAction();
    void update(int action, double newValue);
};

class VLearn{
public:
    unordered_map<State, AdvBandit, StateHash> policy[NUM_AGENT];

    VLearn();
    void rollOut();
};

#endif