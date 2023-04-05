
/*
Compilation
g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp matrix_state.cpp matrix_type.cpp
g++ -std=c++11 main.cpp common.cpp vlearn.cpp bandit.cpp state.cpp dummypoker_state.cpp dummypoker_type.cpp
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

// Matrix game

/*

const int TIME_HORIZON = 1;

const int NUM_AGENT = 2;

const double MAX_REWARD = 4;

const int NUM_ACTIONS = 3;

const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
    {0, 1, 3},
    {1, 4, 0},
    {2, 0, 2}
};

// const double matrix[NUM_ACTIONS][NUM_ACTIONS] = {
//     {0, 1, -1},
//     {-1, 0, 1},
//     {1, -1, 0}
// };

class Type{
public:
    Type(){}
    string toString() const;
    size_t hashValue() const ;
    bool equals(const Type& t) const;

    friend bool operator == (const Type& t, const Type& s){
        return t.equals(s);
    }
};

class State{
public:
    bool endState;

    Type revealed_types[NUM_AGENT];
    int actions[NUM_AGENT];

    State();

    bool validAction(int action, int playerID);
    void makeAction(double* reward); // reads actions and revealed_types, modifies reward array.

    string toString() const;

    bool equals(const State& s) const;
    size_t hashValue() const;

    friend bool operator == (const State& t, const State& s){
        return t.equals(s);
    }
};

*/

// Dummy's poker



const int deckSize = 6;
const int maxBet = 10;


// TIME_HORIZON = maximum game length.
// Here, TIME_HORIZON = NUM_AGENT * (1 + ceil log2(maxBet))
const int TIME_HORIZON = 15;

const int NUM_AGENT = 3;

const double MAX_REWARD = 20;

const int NUM_ACTIONS = maxBet + 1;

// Actions:
// 0 = fold
// k>0 = call k or raise to k

// Nonacting players use action 0

const int FOLD = 0;

// large prime for hashing
const int M = 1000000019;

class Type{
public:
    int cardVal;

    Type(){}
    Type(int val);
    string toString();

    friend bool operator == (const Type& t, const Type& s){
        return t.equals(s);
    }
    size_t hashValue() const ;
    bool equals(const Type& t) const;
};

class State{
private:
    int committed_chips[NUM_AGENT];
    bool folded[NUM_AGENT];
    int currTime;

    
    // Events:
    // Positive number = bet of that size (starts at 1).
    // 0 = fold
    // -1 = not yet set.
    
    int topBet();

    int event_seq[TIME_HORIZON]; // sequence of actions taken. default is -1.
    int currPlayer; // 0, 1, 2.

    void showdown(double* reward);

public:
    // State info
    bool endState;

    State();

    Type revealed_types[NUM_AGENT];
    int actions[NUM_AGENT];

    bool validAction(int action, int playerID);
    void makeAction(double* reward); // reads actions and revealed_types, modifies reward array.

    string toString();

    friend bool operator == (const State& t, const State& s){
        return t.equals(s);
    }

    bool equals(const State& s) const;
    size_t hashValue() const;
};



class TypeHash{
public:
    size_t operator()(const Type& t) const {
        return t.hashValue();
    }
};

class StateHash{
public:
    size_t operator()(const State& s) const {
        return s.hashValue();
    }
};

unordered_set<Type, TypeHash> all_types();
void init_type(Type* types);




// VLearning algorithm

unordered_set<State, StateHash> nextStates(State& s, int recAgent);
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
        //return (TIME_HORIZON+1)/(TIME_HORIZON+visitCount);
        return 0.01;
    }
    double explorationRate(){
        //return 1/sqrt(TIME_HORIZON+visitCount);
        return 0;
    }
    double lossWeight(){
        // double prod = 1;
        // for(int i=1; i<visitCount; i++){
        //     prod *= 1 - (TIME_HORIZON+1)/(TIME_HORIZON+1+i);
        // }
        // return learnRate() / prod;
        return 1;
    }
    double sampleSkew(){
        return 1/sqrt(TIME_HORIZON+visitCount);
    }

public:
    AdvBandit(){
        value = 0;
    }
    AdvBandit(State& s_, int ag);

    double value;
    double actionProb[NUM_ACTIONS];
    double aggPolicy[NUM_ACTIONS];

    int sampleAction();
    void update(int action, double newValue);
};

class VLearn{
public:
    unordered_map<State, unordered_map<Type, AdvBandit, TypeHash>, StateHash> policy[NUM_AGENT];

    VLearn();
    void rollOut();
    void train(int numIter);

    void printGame();

    void save(string outFile);
    void load(string inFile);
};

#endif