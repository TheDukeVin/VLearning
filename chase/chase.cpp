
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

double State::endValue(int agentID){
    if(agentID == 0){
        return 0;
    }
    else{
        return TIME_HORIZON - time;
    }
}

void State::makeAction(double* reward){
    if(rand() % 2 == 0){
        players[0] = players[0].shift(actions[0]);
    }
    if(rand() % 2 == 0){
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
    if(endState) return "End State Time: " + to_string(time);
    return "Time " + to_string(time) + " Runner " + players[0].toString() + " Chaser " + players[1].toString();
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
    iss >> hold >> time 
        >> hold >> players[0].r >> players[0].c 
        >> hold >> players[1].r >> players[1].c;
}

vector<pair<State, pair<double, double> > > State::transitionDistribution(int agentID){
    vector<pair<State, pair<double, double> > > possibilities;
    double reward[2];
    for(int c=0; c<4; c++){
        State s = *this;
        if(c % 2 == 0){
            s.players[0] = s.players[0].shift(actions[0]);
        }
        if(c / 2 == 0){
            s.players[1] = s.players[1].shift(actions[1]);
        }
        if(s.players[0] == s.players[1]){
            s.endState = true;
            reward[0] = 0;
            reward[1] = 1;
        }
        else{
            reward[0] = 1;
            reward[1] = 0;
        }
        s.time ++;
        if(s.time == TIME_HORIZON){
            s.endState = true;
        }
        possibilities.push_back(make_pair(s, make_pair(1.0 / 4, reward[agentID])));
    }
    return possibilities;
}

vector<pair<State, double> > State::initialDistribution(){
    return vector<pair<State, double> >{make_pair(State(), 1)};
}