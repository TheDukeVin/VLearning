
#include "matrix.h"

State::State(){
    endState = false;
}

vector<int> State::validActions(int agentID){
    vector<int> actions;
    for(int i=0; i<NUM_ACTIONS; i++){
        actions.push_back(i);
    }
    return actions;
}

vector<int> State::validChanceActions(){
    return vector<int>{0};
}

void State::makeAction(double* reward, int chanceAction){
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

