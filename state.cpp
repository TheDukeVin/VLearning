
#include "vlearn.h"

// unordered_set<State, StateHash> nextStates(State& s, int recAgent){
//     unordered_set<State, StateHash> states;
//     if(recAgent == NUM_AGENT){
//         double hold[NUM_AGENT];
//         for(auto c : s.validChanceActions()){
//             State s_new = s;
//             s_new.makeAction(hold, c);
//             states.insert(s_new);
//         }
//         return states;
//     }
//     for(auto a : s.validActions(recAgent)){
//         s.actions[recAgent] = a;
//         for(auto t : nextStates(s, recAgent+1)){
//             states.insert(t);
//         }
//     }
//     return states;
// }

// unordered_set<State, StateHash> all_states(){
//     unordered_set<State, StateHash> states;
//     vector<State> currStates;
//     currStates.push_back(State());
//     // int counter = 0;
//     while(!currStates.empty()){
//         // if(counter % 10000 == 0){
//         //     cout<<counter<<'\n';
//         // }
//         // counter++;
//         State s = currStates.back();
//         // cout<<s.toString();
//         states.insert(s);
//         currStates.pop_back();
//         if(s.endState){
//             continue;
//         }
//         int i = 0;
//         for(auto t : nextStates(s, 0)){
//             if(states.find(t) == states.end()){
//                 currStates.push_back(t);
//             }
//             i ++;
//         }
//     }
//     return states;
// }