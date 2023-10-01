
#include "template.h"

State::State(){
    time = 0;
    endState = false;
}

vector<int> State::validActions(int agentID){
}

void State::makeAction(double* reward){

    // Normalize reward to between 0 and 1
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = (reward[i] - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
        assert(0 <= reward[i] && reward[i] <= 1);
    }

    // If ending the game early, add extra rewards immediately
    // if(endState){
    //     for(int i=0; i<NUM_AGENT; i++){
    //         reward[i] += (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (steps - time);
    //     }
    // }
}

double State::endValue(int agentID){
    return (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - time);
}

string State::toString() const {
    if(endState){
        return "End State";
    }
}

State::State(string s){
    istringstream iss(s);
    string hold;
    if(s.substr(0, 9) == "End State"){
        endState = true;
        iss >> hold >> hold >> hold >> time;
        return;
    }
    endState = false;
}