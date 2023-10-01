
#include "vlearn.h"

VLearn VL;

double testExploitability(int agentID);

void train(){
    int start_time = time(0);
    unordered_set<State, StateHash> states = all_states();
    ofstream expOut("exploit.out");
    ofstream polOut("conv.out");
    {
        ofstream fout("log.out");
        fout<<"Game size: "<<states.size()<<'\n';
        fout<<"Simulating games: \n";
    }

    for(int i=0; i<1e+05; i++){
        if(i % 1000000 == 0){
            ofstream fout("log.out", ios::app);
            fout<<"Iteration "<< i << " Time " << (time(0) - start_time) << '\n';
        }
        VL.rollOut();
        // if(i % 10000 == 0){
        //     expOut<<(testExploitability(0) + testExploitability(1))<<',';
        //     for(int j=0; j<NUM_ACTIONS; j++){
        //         polOut<<VL.policy[0][State()].actionProb[j]<<',';
        //     }
        //     polOut<<'\n';
        // }
    }
    VL.save("policy.out");

    {
        ofstream fout("log.out", ios::app);
        fout<<"Run time: "<<(time(0) - start_time)<<'\n';
    }
}

void printGames(){
    VL.load("policy.out");
    for(int i=0; i<10; i++){
        VL.printGame();
    }
}

// double getReward(int agentID, int action0, int action1){
//     if(agentID == 0) return matrix0[action0][action1];
//     return matrix1[action0][action1];
// }

// double testExploitability(int agentID){
//     double value = 0;
//     for(int i=0; i<NUM_ACTIONS; i++){
//         for(int j=0; j<NUM_ACTIONS; j++){
//             value += VL.policy[0][State()].aggPolicy[i] * VL.policy[1][State()].aggPolicy[j] * getReward(agentID, i, j);
//         }
//     }
//     // cout<<"Value: "<<value<<'\n';
//     double maxValue = -1000;
//     for(int i=0; i<NUM_ACTIONS; i++){
//         double candValue = 0;
//         for(int j=0; j<NUM_ACTIONS; j++){
//             int actions[2];
//             actions[agentID] = i;
//             actions[1-agentID] = j;
//             candValue += VL.policy[1-agentID][State()].aggPolicy[j] * getReward(agentID, actions[0], actions[1]);
//         }
//         if(maxValue < candValue){
//             maxValue = candValue;
//         }
//         // cout<<"Utility of action "<<i<<": "<<candValue<<'\n';
//     }
//     // cout<<"Difference from optimal response: "<<(maxValue - value)<<'\n';
//     return maxValue - value;
// }

int main(){
    srand(time(NULL));
    train();
    printGames();
    // testExploitability(0);
    // testExploitability(1);
}
