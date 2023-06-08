
#include "template.h"

State::State(){
    time = 0;
    endState = false;
}

vector<int> State::validActions(int agentID){
}

vector<int> State::validChanceActions(){
}

void State::makeAction(double* reward, int chanceAction){
    // Sample random transition if not specified
    if(chanceAction == -1){
    }

    // Normalize reward to between 0 and 1
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = (reward[i] - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
        assert(0 <= reward[i] && reward[i] <= 1);
    }

    // If ending the game early, add extra rewards immediately
    if(endState){
        for(int i=0; i<NUM_AGENT; i++){
            reward[i] += (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (steps - time);
        }
    }
}

string State::toString() const {
}