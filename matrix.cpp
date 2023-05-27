
#include "vlearn.h"

State::State(){
    endState = false;
}

bool State::validAction(int action, int playerID){
    return true;
}

void State::makeAction(double* reward){
    endState = true;
    reward[0] = matrix[actions[0]][actions[1]] / MAX_REWARD;
    reward[1] = 1 - matrix[actions[0]][actions[1]] / MAX_REWARD;
}

string State::toString() const {
    if(endState){
        return "End State\n";
    }
    else{
        return "Choice\n";
    }
}

bool State::equals(const State& s) const {
    return endState == s.endState;
}
size_t State::hashValue() const {
    return endState;
}

