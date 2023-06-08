
#include "steal.h"

State::State(){
    for(int i=0; i<NUM_AGENT; i++){
        coins[i] = 0;
    }
    time = 0;
    endState = false;
}

vector<int> State::validActions(int agentID){
    vector<int> actions{EARN_ACTION};
    for(int i=0; i<NUM_AGENT; i++){
        if(i != agentID && coins[i] > 0){
            actions.push_back(i);
        }
    }
    return actions;
}

vector<int> State::validChanceActions(){
    vector<int> actions;
    for(int i=0; i<pow(3, NUM_AGENT); i++){
        actions.push_back(i);
    }
    return actions;
}

void State::makeAction(double* reward, int chanceAction){
    // Sample random transition if not specified
    if(chanceAction == -1){
        chanceAction = rand() % (int) pow(3, NUM_AGENT);
    }
    int hold_coins[NUM_AGENT];
    for(int i=0; i<NUM_AGENT; i++){
        hold_coins[i] = coins[i];
    }
    // Distribute earned coins
    for(int i=0; i<NUM_AGENT; i++){
        if(actions[i] == EARN_ACTION){
            coins[i] += 1 + ((chanceAction / (int) pow(3, i)) % 3);
        }
    }
    // Move stolen coins
    // Check for how many times each player is stolen from
    // If its more than how many coins they have, no steals happen on that player.
    int numSteals[NUM_AGENT];
    for(int i=0; i<NUM_AGENT; i++){
        numSteals[i] = 0;
    }
    for(int i=0; i<NUM_AGENT; i++){
        if(actions[i] != EARN_ACTION){
            numSteals[actions[i]] ++;
        }
    }
    for(int i=0; i<NUM_AGENT; i++){
        if(actions[i] != EARN_ACTION && numSteals[actions[i]] <= coins[actions[i]]){
            coins[i] ++;
            coins[actions[i]] --;
        }
    }
    // Assign rewards for gained/lost coins
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = 0.05 * (coins[i] - hold_coins[i]);
    }
    // Assign rewards for winning the game
    vector<int> winners;
    for(int i=0; i<NUM_AGENT; i++){
        if(coins[i] >= coinGoal){
            winners.push_back(i);
        }
    }
    if(winners.size() > 0){
        for(auto i : winners){
            reward[i] = 1.0 / winners.size();
        }
        endState = true;
    }
    time ++;
    if(time == TIME_HORIZON){
        endState = true;
    }

    // Normalize reward to between 0 and 1
    for(int i=0; i<NUM_AGENT; i++){
        reward[i] = (reward[i] - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
        assert(0 <= reward[i] && reward[i] <= 1);
    }

    // If ending the game early, add extra rewards immediately
    if(endState){
        for(int i=0; i<NUM_AGENT; i++){
            reward[i] += (0 - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]) * (TIME_HORIZON - time);
        }
    }
}

string State::toString() const {
    if(endState) return "End State\n";
    string s = "Time " + to_string(time) + " Coins ";
    for(int i=0; i<NUM_AGENT; i++){
        s += to_string(coins[i]) + " ";
    }
    return s + "\n";
}
