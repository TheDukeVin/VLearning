
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

double State::endValue(int agentID){
    return 0;
}

void State::makeAction(double* reward){
    // Sample random transition if not specified
    int hold_coins[NUM_AGENT];
    for(int i=0; i<NUM_AGENT; i++){
        hold_coins[i] = coins[i];
    }
    // Distribute earned coins
    for(int i=0; i<NUM_AGENT; i++){
        if(actions[i] == EARN_ACTION){
            coins[i] += 1 + rand() % 3;
            // coins[i] += 1 + ((chanceAction / (int) pow(3, i)) % 3);
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
}

string State::toString() const {
    if(endState) return "End State Time: " + to_string(time);
    string s = "Time " + to_string(time) + " Coins ";
    for(int i=0; i<NUM_AGENT; i++){
        s += to_string(coins[i]) + " ";
    }
    return s;
}

State::State(string s){
    istringstream iss(s);
    string hold;
    if(s.substr(0, 9) == "End State"){
        endState = true;
        iss >> hold >> hold >> hold >> time;
        return;
    }
    endState = false;
    iss >> hold >> time >> hold;
    for(int i=0; i<NUM_AGENT; i++){
        iss >> coins[i];
    }
}

vector<pair<State, pair<double, double> > > State::transitionDistribution(int agentID){
    double reward[NUM_AGENT];
    vector<pair<State, pair<double, double> > > possibilities;
    for(int c=0; c<27; c++){
        State s = *this;
        // Distribute earned coins
        for(int i=0; i<NUM_AGENT; i++){
            s.coins[i] = coins[i];
            if(actions[i] == EARN_ACTION){
                // coins[i] += 1 + rand() % 3;
                s.coins[i] += 1 + ((c / (int) pow(3, i)) % 3);
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
            if(actions[i] != EARN_ACTION && numSteals[actions[i]] <= s.coins[actions[i]]){
                s.coins[i] ++;
                s.coins[actions[i]] --;
            }
        }
        // Assign rewards for gained/lost coins
        for(int i=0; i<NUM_AGENT; i++){
            reward[i] = 0.05 * (s.coins[i] - coins[i]);
        }
        // Assign rewards for winning the game
        vector<int> winners;
        for(int i=0; i<NUM_AGENT; i++){
            if(s.coins[i] >= coinGoal){
                winners.push_back(i);
            }
        }
        if(winners.size() > 0){
            for(auto i : winners){
                reward[i] = 1.0 / winners.size();
            }
            s.endState = true;
        }
        s.time ++;
        if(s.time == TIME_HORIZON){
            s.endState = true;
        }

        // Normalize reward to between 0 and 1
        for(int i=0; i<NUM_AGENT; i++){
            reward[i] = (reward[i] - rewardSpace[0]) / (rewardSpace[1] - rewardSpace[0]);
            assert(0 <= reward[i] && reward[i] <= 1);
        }
        possibilities.push_back(make_pair(s, make_pair(1.0 / 27, reward[agentID])));
    }
    
    return possibilities;
}

vector<pair<State, double> > State::initialDistribution(){
    return vector<pair<State, double> >{make_pair(State(), 1)};
}