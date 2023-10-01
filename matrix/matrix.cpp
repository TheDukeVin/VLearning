
#include "matrix.h"

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

// vector<int> State::validChanceActions(){
//     return vector<int>{0};
// }

void State::makeAction(double* reward){
    time = 1;
    endState = true;
    reward[0] = matrix0[actions[0]][actions[1]];
    reward[1] = matrix1[actions[0]][actions[1]];

    // Normalize reward to between 0 and 1
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = (reward[i] - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
        assert(0 <= reward[i] && reward[i] <= 1);
    }

    // // If ending the game early, add extra rewards immediately
    // if(endState){
    //     for(int i=0; i<NUM_AGENT; i++){
    //         reward[i] += (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - time);
    //     }
    // }
}

double State::endValue(int agentID){
    return 0;
}

string State::toString() const {
    if(endState){
        return "End State";
    }
    else{
        return "Choice";
    }
}

State::State(string s){
    if(s == "End State"){
        time = 0;
        endState = true;
        return;
    }
    if(s == "Choice"){
        time = 0;
        endState = false;
        return;
    }
    assert(false);
}

vector<pair<State, pair<double, double> > > State::transitionDistribution(int agentID){
    double reward;
    if(agentID == 0){
        reward = matrix0[actions[0]][actions[1]];
    }
    else{
        reward = matrix1[actions[0]][actions[1]];
    }
    reward = (reward - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
    assert(0 <= reward && reward <= 1);
    return vector<pair<State, pair<double, double> > >{make_pair(State("End State"), make_pair(1, reward))};
}

vector<pair<State, double> > State::initialDistribution(){
    return vector<pair<State, double> >{make_pair(State("Choice"), 1)};
}