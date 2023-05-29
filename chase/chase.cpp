
#include "chase.h"

State::State(){
    time = 0;
    players[0] = Pos(0, 0);
    players[1] = Pos(gridH-1, gridW-1);
    endState = false;
}

vector<int> State::validActions(int agentID){
    vector<int> actions;
    for(int d=0; d<4; d++){
        Pos newPos = players[agentID].shift(d);
        if(newPos.inBound()){
            actions.push_back(d);
        }
    }
    return actions;
}

vector<int> State::validChanceActions(){
    return vector<int>{0, 1, 2, 3};
}

void State::makeAction(double* reward, int chanceAction){
    // Sample random transition if not specified
    if(chanceAction == -1){
        chanceAction = rand() % 4;
    }
    int move0 = chanceAction / 2;
    int move1 = chanceAction % 2;
    if(move0){
        players[0] = players[0].shift(actions[0]);
    }
    if(move1){
        players[1] = players[1].shift(actions[1]);
    }
    if(players[0] == players[1]){
        endState = true;
        reward[0] = 0;
        reward[1] = 1;
    }
    else{
        reward[0] = 1;
        reward[1] = 0;
    }
    time ++;
    if(time == TIME_HORIZON){
        endState = true;
    }
}

string State::toString() const {
    if(endState) return "End State\n";
    return "Time " + to_string(time) + " Runner " + players[0].toString() + " Chaser " + players[1].toString() + "\n";
}

bool State::equals(const State& s) const {
    if(endState && s.endState) return true;
    return (time == s.time) && (players[0] == s.players[0]) && (players[1] == s.players[1]);
}

size_t State::hashValue() const {
    return hash<string>{}(toString());
}

