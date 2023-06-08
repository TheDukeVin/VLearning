
#include "vlearn.h"


int main(){
    srand(time(NULL));
    int start_time = time(0);

    VLearn VL;
    unordered_set<State, StateHash> states = all_states();

    if(1){ // TRAIN MODE
    // if(0){ // TEST MODE
        {
            ofstream fout("log.out");
            fout<<"Game size: "<<states.size()<<'\n';
            fout<<"Simulating games: \n";
        }

        for(int i=0; i<1e+09; i++){
            if(i % 1000000 == 0){
                ofstream fout("log.out", ios::app);
                fout<<"Iteration "<< i << " Time " << (time(0) - start_time) << '\n';
            }
            VL.rollOut();
        }
        VL.save("policy.out");

        {
            ofstream fout("log.out", ios::app);
            fout<<"Run time: "<<(time(0) - start_time)<<'\n';
        }
    }
    else{
        VLearn VL;
        VL.load("policy.out");
        for(int i=0; i<10; i++){
            VL.printGame();
        }
    }
}
