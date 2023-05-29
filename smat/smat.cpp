
#include "smat.h"

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
    return vector<int>{0, 1};
}

void State::makeAction(double* reward, int chanceAction){
    if(chanceAction == -1){
        double prob = reward_prob[actions[0]][actions[1]];
        chanceAction = 0;
        if((double) rand() / RAND_MAX < prob){
            chanceAction = 1;
        }
    }
    endState = true;
    reward[0] = chanceAction;
    reward[1] = 1-chanceAction;
}

string State::toString() const {
    if(endState) return "End State\n";
    else return "Choice\n";
}

bool State::equals(const State& s) const {
    return endState == s.endState;
}

size_t State::hashValue() const {
    return endState;
}

