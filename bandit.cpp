
#include "vlearn.h"

// AdvBandit::AdvBandit(){
//     value = 0; // End state should still have value 0 for base case
//     for(int i=0; i<NUM_ACTIONS; i++){
//         aggPolicy[i] = actionProb[i] = -1;
//     }
// }

AdvBandit::AdvBandit(State s_, int ag){
    // value = 0;
    // rescale initialized rewards to match 0 reward in the reward space
    value = (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - s_.time);
    if(s_.endState){
        value = s_.endValue(ag);
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        aggPolicy[i] = actionProb[i] = -1;
    }
    s = s_;
    agentID = ag;
    validActions = s.validActions(ag);
    for(auto a : validActions){
        sumLoss[a] = 0;
        aggPolicy[a] = actionProb[a] = 1.0 / validActions.size();
    }
    visitCount = 0;
}

void AdvBandit::update(int action, double newValue){
    assert(!s.endState);
    // Update value
    double explorationRate = EXPLORATION_CONSTANT/sqrt(TIME_HORIZON+visitCount);
    visitCount ++;
    value = (1 - LEARN_RATE) * value + LEARN_RATE * (newValue + explorationRate);
    if(validActions.size() == 1) return;

    // Update policy
    double loss = 1 - newValue / (TIME_HORIZON - s.time);
    // if(!(actionProb[action] > 0)){
    //     for(int i=0; i<NUM_ACTIONS; i++){
    //         cout<<actionProb[i]<<' ';
    //     }
    //     cout<<'\n';
    // }
    // assert(actionProb[action] > 0);
    sumLoss[action] += loss / (actionProb[action] + explorationRate);

    double minLoss = 1e+10;
    for(auto a : validActions){
        if(sumLoss[a] < minLoss) minLoss = sumLoss[a];
    }
    double sum = 0;
    for(auto a : validActions){
        sumLoss[a] -= minLoss;
        actionProb[a] = exp(-LEARN_RATE * sumLoss[a]);
        sum += actionProb[a];
    }
    assert(!::isnan(sum) && sum > 0);
    for(auto a : validActions){
        actionProb[a] /= sum;
        assert(!::isnan(actionProb[a]));
        aggPolicy[a] = (aggPolicy[a] * (visitCount-1) + actionProb[a]) / visitCount;
    }
}

int AdvBandit::sampleAction(){
    if(validActions.size() == 1) return validActions[0];
    return sampleDist(actionProb, NUM_ACTIONS);
}