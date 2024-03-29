
/*
Compilation
g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp matrix/matrix.cpp

g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp escape/escape.cpp

g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp smat/smat.cpp

g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp chase/chase.cpp

g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp steal/steal.cpp

Syncing with FASRC
rsync -r Classic_V_Learn kevindu@login.rc.fas.harvard.edu:./MultiagentSnake
rsync -r kevindu@login.rc.fas.harvard.edu:./MultiagentSnake/Classic_V_Learn .

Running
g++ -O2 -std=c++17 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp steal/steal.cpp && sbatch vlearn.slurm
*/

// #include "matrix/matrix.h"
// #include "escape/escape.h"
// #include "smat/smat.h"
// #include "chase/chase.h"
#include "steal/steal.h"
#include <ctime>

#ifndef vlearn_h
#define vlearn_h

#define END 0
#define REC 1
#define VALUE_FLAG END

using namespace std;

int sampleDist(double* dist, int N);

class StateHash{
public:
    size_t operator()(const State& s) const {
        return hash<string>{}(s.toString());
    }
};

// VLearning algorithm

// unordered_set<State, StateHash> all_states();

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

    double explorationRate(){
        return EXPLORATION_CONSTANT/sqrt(TIME_HORIZON+visitCount);
        // return 0;
    }

public:
    AdvBandit(){};
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

    // VLearn(){};
    void rollOut();
    void printGame();

    void save(string outFile);
    void load(string inFile);
};

#endif