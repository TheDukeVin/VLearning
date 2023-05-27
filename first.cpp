
#include "vlearn.h"

State::State(){
    time = 0;
    catchUsed = false;
}

bool State::validAction(int action, int playerID){
    return (playerID == 0) || (action == 0) || (! catchUsed);
}

void State::makeAction(double* reward){
    if(actions[0] == 1){
        if(actions[1] == 1){
            reward[0] = catReward;
            reward[1] = -catReward;

        }
        else{
            reward[0] = escReward;
            reward[1] = -escReward;
        }
        endState = true;
    }
    else{
        reward[0] = 0;
        reward[1] = 0;
    }
    if(actions[1] == 1){
        catchUsed = true;
    }
    time ++;

    if(time == steps){
        endState = true;
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
    if(endState) return "End State\n";
    return "Time: " + to_string(time) + " Catch Used: " + to_string(catchUsed) + "\n";
}

bool State::equals(const State& s) const {
    if(endState && s.endState) return true;
    return (endState == s.endState) && (time == s.time) && (catchUsed == s.catchUsed);
}

size_t State::hashValue() const {
    if(endState) return -1;
    return time + catchUsed * steps;
}

