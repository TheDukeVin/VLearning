
#include "vlearn.h"

AdvBandit::AdvBandit(State& s_, int ag){
    s = s_;
    agentID = ag;
    numValidAction = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        validAction[i] = s.validAction(i, ag);
        if(validAction[i]){
            numValidAction ++;
        }
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        if(validAction[i]){
            sumLoss[i] = 0;
            actionProb[i] = 1.0 / numValidAction;
            aggPolicy[i] = 1.0 / numValidAction;
        }
        else{
            actionProb[i] = -1;
        }
    }
    visitCount = 1;
    value = 0;
}

void AdvBandit::update(int action, double newValue){
    // Update value
    double lr = learnRate();
    double er = explorationRate();
    double skew = sampleSkew();
    double currWeight = lossWeight();
    visitCount ++;
    value = (1 - lr) * value + lr * (newValue + er);
    if(numValidAction == 1){
        return;
    }
    // Update policy
    double loss = 1 - newValue / MAX_REWARD;
    sumLoss[action] += currWeight * loss / (actionProb[action] + skew);

    double minLoss = 1e+10;
    for(int i=0; i<NUM_ACTIONS; i++){
        if(validAction[i] && sumLoss[i] < minLoss) minLoss = sumLoss[i];
    }
    double sum = 0;
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!validAction[i]){
            actionProb[i] = -1;
            continue;
        }
        actionProb[i] = exp(-skew / currWeight * (sumLoss[i] - minLoss));
        sum += actionProb[i];
    }
    for(int i=0; i<NUM_ACTIONS; i++){
        if(!validAction[i]) continue;
        actionProb[i] /= sum;
        assert(!isnan(actionProb[i]));
        aggPolicy[i] = (aggPolicy[i] * (visitCount-1) + actionProb[i]) / visitCount;
    }
}

int AdvBandit::sampleAction(){
    return sampleDist(actionProb, NUM_ACTIONS);
}