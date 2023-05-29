
/*
Compilation
g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp matrix/matrix.cpp

g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp escape/escape.cpp

g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp smat/smat.cpp

g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp chase/chase.cpp
*/

// #include "matrix/matrix.h"
// #include "escape/escape.h"
// #include "smat/smat.h"
#include "chase/chase.h"

#ifndef vlearn_h
#define vlearn_h

using namespace std;

int sampleDist(double* dist, int N);

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
    // bool validAction[NUM_ACTIONS];
    vector<int> validActions;
    // int numValidAction;
    // int soleAction;
    int visitCount;
    double sumLoss[NUM_ACTIONS];

    double learnRate(){
        // return sqrt((TIME_HORIZON+1.0)/(TIME_HORIZON+visitCount));
        return 0.01;
    }
    double explorationRate(){
        return 1/sqrt(TIME_HORIZON+visitCount);
        // return 0;
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
    void printGame();
};

#endif