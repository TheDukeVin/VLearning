
#include "template.h"

State::State(){
}

vector<int> State::validActions(int agentID){
}

vector<int> State::validChanceActions(){
}

void State::makeAction(double* reward, int chanceAction){
    // Sample random transition if not specified
    if(chanceAction == -1){
    }
}

string State::toString() const {
}

bool State::equals(const State& s) const {
}

size_t State::hashValue() const {
}

