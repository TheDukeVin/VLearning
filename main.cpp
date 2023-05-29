
#include "vlearn.h"

int main(){
    srand(time(NULL));
    unordered_set<State, StateHash> states = all_states();
    cout<<"Game size: "<<states.size()<<'\n';
    cout<<states.size()<<'\n';
    // for(auto s : all_states()){
    //     cout<<s.toString();
    // }

    VLearn VL;
    ofstream fout("probs.out");
    for(int i=0; i<1000000; i++){
        VL.rollOut();
        fout<<VL.policy[0][State()].value<<'\n';
    }
    fout<<'\n';

    // for(auto s : all_states()){
    //     cout<<"State: "<<s.toString();
    //     for(int i=0; i<NUM_AGENT; i++){
    //         cout<<"Agent "<<i<<" value: "<<VL.policy[i][s].value<<'\n';
    //         cout<<"Agent "<<i<<" policy: ";
    //         for(int j=0; j<NUM_ACTIONS; j++){
    //             cout<<VL.policy[i][s].aggPolicy[j]<<' ';
    //         }
    //         cout<<'\n';
    //     }
    //     cout<<'\n';
    // }

    for(int i=0; i<10; i++){
        VL.printGame();
    }
}