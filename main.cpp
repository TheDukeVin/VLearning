
#include "vlearn.h"

int main(){
    srand(time(NULL));
    unordered_set<State, StateHash> states = all_states();
    cout<<states.size()<<'\n';
    for(auto s : all_states()){
        cout<<s.toString()<<'\n';
    }

    VLearn VL;
    ofstream fout("probs.out");
    for(int i=0; i<3000000; i++){
        VL.rollOut();
        for(int j=0; j<NUM_ACTIONS; j++){
            if(j > 0) fout<<',';
            fout<<VL.policy[0][State()].actionProb[j];
        }
        fout<<'\n';
    }
    fout<<'\n';
    for(int i=0; i<NUM_ACTIONS; i++){
        cout<<VL.policy[0][State()].aggPolicy[i]<<' ';
    }
    cout<<'\n';
    for(int i=0; i<NUM_ACTIONS; i++){
        cout<<VL.policy[1][State()].aggPolicy[i]<<' ';
    }
    cout<<'\n';
    // for(int i=0; i<NUM_AGENT; i++){
    //     cout<<"AGENT: "<<i<<'\n';
    //     for(auto s : all_states()){
    //         cout<<"State: "<<s.toString()<<'\n';
    //         cout<<"Policy\n";
    //         for(int j=0; j<NUM_ACTIONS; j++){
    //             cout<<VL.policy[i][s].actionProb[j]<<' ';
    //         }
    //         cout<<'\n';
    //     }
    // }
}