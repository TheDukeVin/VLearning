
#include "smat.h"

State::State(){
    time = 0;
    endState = false;
}

vector<int> State::validActions(int agentID){
    vector<int> actions;
    for(int i=0; i<NUM_ACTIONS; i++){
        actions.push_back(i);
    }
    return actions;
}

void State::makeAction(double* reward){
    endState = true;
    time = 1;
    reward[0] = (double) rand() / RAND_MAX < reward_prob0[actions[0]][actions[1]];
    reward[1] = (double) rand() / RAND_MAX < reward_prob1[actions[0]][actions[1]];
}

string State::toString() const {
    if(endState) return "End State";
    else return "Choice";
}

State::State(string s){
    if(s == "End State"){
        endState = true;
        time = 1;
        return;
    }
    if(s == "Choice"){
        endState = false;
        time = 0;
        return;
    }
    assert(false);
}

vector<pair<State, pair<double, double> > > State::transitionDistribution(int agentID){
    double rewardProb;
    if(agentID == 0){
        rewardProb = reward_prob0[actions[0]][actions[1]];
    }
    else{
        rewardProb = reward_prob1[actions[0]][actions[1]];
    }
    return vector<pair<State, pair<double, double> > >{
        make_pair(State("End State"), make_pair(rewardProb, 1)),
        make_pair(State("End State"), make_pair(1-rewardProb, 0))
    };
}

vector<pair<State, double> > State::initialDistribution(){
    return vector<pair<State, double> >{make_pair(State("Choice"), 1)};
}