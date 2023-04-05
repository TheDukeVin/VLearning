
#include "vlearn.h"

int main(){
    srand(time(NULL));

    unordered_set<State, StateHash> states = all_states();
    cout<<"Game size: "<<states.size()<<'\n';

    // size_t start_time = time(NULL);
    // VLearn VL;
    // for(int i=0; i<100000000; i++){
    //     VL.rollOut();
    // }
    // VL.save("VL.out");
    // cout<<"Time: "<<(time(NULL) - start_time)<<'\n';

    VLearn VL;
    VL.load("VL.in");
    VL.printGame();
}