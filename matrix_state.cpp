
#include "vlearn.h"

State::State(){
    endState = false;
}

bool State::validAction(int action, int playerID){
    return true;
}

void State::makeAction(double* reward){
    endState = true;
    reward[0] = matrix[actions[0]][actions[1]];
    reward[1] = MAX_REWARD-matrix[actions[0]][actions[1]];
}

string State::toString() const {
    if(endState){
        return "End State";
    }
    else{
        return "Choice";
    }
}

bool State::equals(const State& s) const {
    return endState == s.endState;
}
size_t State::hashValue() const {
    return endState;
}

