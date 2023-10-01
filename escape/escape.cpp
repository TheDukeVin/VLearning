
#include "escape.h"

State::State(){
    endState = false;
    time = 0;
    catchUsed = false;
}

vector<int> State::validActions(int agentID){
    if(agentID == 0 || !catchUsed){
        return vector<int>{0, 1};
    }
    return vector<int>{0};
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
}

double State::endValue(int agentID){
    return (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - time);
}

string State::toString() const {
    if(endState) return "End State Time: " + to_string(time);
    return "Time: " + to_string(time) + " Catch Used: " + to_string(catchUsed);
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
    iss >> hold >> time >> hold >> hold >> catchUsed;
}

vector<pair<State, pair<double, double> > > State::transitionDistribution(int agentID) const{
    double reward[2];
    State s = *this;
    s.makeAction(reward);
    return vector<pair<State, pair<double, double> > >{make_pair(s, make_pair(1, reward[agentID]))};
}

vector<pair<State, double> > State::initialDistribution(){
    return vector<pair<State, double> >{make_pair(State("Time: 0 Catch Used: 0"), 1)};
}