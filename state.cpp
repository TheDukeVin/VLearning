
#include "vlearn.h"

unordered_set<State, StateHash> nextStates(State& s, int recAgent){
    // cout<<"Call: \n";
    // cout<<"Agent "<<recAgent<<'\n';
    // cout<<s.toString()<<'\n';
    unordered_set<State, StateHash> states;
    if(recAgent == NUM_AGENT){
        double hold[NUM_AGENT];
        State s_new = s;
        s_new.makeAction(hold);
        states.insert(s_new);
        return states;
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!s.validAction(i, recAgent)) continue;
        s.actions[recAgent] = i;
        for(auto t : nextStates(s, recAgent+1)){
            states.insert(t);
        }
    }
    return states;
}

unordered_set<State, StateHash> all_states(){
    unordered_set<State, StateHash> states;
    vector<State> currStates;
    currStates.push_back(State());
    while(!currStates.empty()){
        State s = currStates.back();
        // cout<<"Curr State: "<<s.toString()<<'\n';
        states.insert(s);
        currStates.pop_back();
        if(s.endState){
            continue;
        }
        for(auto t : nextStates(s, 0)){
            if(states.find(t) == states.end()){
                currStates.push_back(t);
            }
        }
        // int numValidActions = 0;
        // for(int i=0; i<NUM_ACTIONS; i++){
        //     if(s.validAction(i)){
        //         State next_s = s;
        //         next_s.makeAction(i);
        //         currStates.push_back(next_s);
        //         numValidActions++;
        //     }
        // }
        // assert(numValidActions > 1);
    }
    return states;
}