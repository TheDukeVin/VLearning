
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef matrix_h
#define matrix_h

using namespace std;

/*
Chase
Two players are on an HxW board
Agent 0 is the runner
Agent 1 is the chaser

Each picks a rectangular direction to move
Move occurs with probabiliy 0.5.

Chaser receives +1 reward when touching runner before time limit
Runner recieves +1 reward each time step until that happens
*/

const int gridH = 3;
const int gridW = 2;

const int TIME_HORIZON = 10;

const int NUM_AGENT = 2;

const int NUM_ACTIONS = 4;

const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

const double rewardSpace[2] = {0, 1};

const string actionNames[NUM_ACTIONS] = {"Right", "Down", "Left", "Up"};

const double LEARN_RATE = 0.01;
const double EXPLORATION_CONSTANT = 0.01;
const int NUM_ROLLOUTS = 1e+07;

class Pos{
public:
    int r,c;

    Pos(){};

    Pos(int r_, int c_){
        r = r_, c = c_;
    }

    Pos shift(int d){
        return Pos(r + dir[d][0], c + dir[d][1]);
    }

    bool inBound(){
        return 0 <= r && r < gridH && 0 <= c && c < gridW;
    }

    friend bool operator == (const Pos& p, const Pos& q){
        return p.r == q.r && p.c == q.c;
    }

    string toString() const{
        return to_string(r) + " " + to_string(c);
    }
};

class State{
private:
    Pos players[NUM_AGENT];

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
    vector<pair<State, pair<double, double> > > transitionDistribution(int agentID);

    vector<pair<State, double> > initialDistribution();
};

#endif