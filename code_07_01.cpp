#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>

int getType(std::string hand){
    std::unordered_map<char, int> reps;
    int score;

    for(auto &c : hand){
        reps[c] += 1;
    }

    std::unordered_map<char, int>::iterator max_loc = std::max_element(reps.begin(), reps.end(), [](const std::pair<char, int> &p1, const std::pair<char, int> &p2){return p1.second < p2.second;});
    int max_val = (*max_loc).second;
    reps[(*max_loc).first] = 0;
    int next_val = (*std::max_element(reps.begin(), reps.end(), [](const std::pair<char, int> &p1, const std::pair<char, int> &p2){return p1.second < p2.second;})).second;

    switch(max_val*10 + next_val){
        case 50: score = 7; break;
        case 41: score = 6; break;
        case 32: score = 5; break;
        case 31: score = 4; break;
        case 22: score = 3; break;
        case 21: score = 2; break;
        default: score = 1;
    }
    return score;
}

int getScore(std::string hand){
    std::unordered_map<char, int> val_dict = {{'A', 13}, {'K', 12}, {'Q', 11}, {'J', 10}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6}, {'6', 5}, {'5', 4}, {'4', 3}, {'3', 2}, {'2', 1}};
    int type = getType(hand);
    
    int score = type*pow(16, 5) + val_dict[hand[0]]*pow(16, 4) + val_dict[hand[1]]*pow(16, 3) + val_dict[hand[2]]*pow(16, 2) + val_dict[hand[3]]*16 + val_dict[hand[4]];

    return score;
}

int main(){
    std::ifstream input_file("./Inputs/input_07.txt");
    std::vector<std::vector<int>> hands;

    for(std::string line; std::getline(input_file, line);){
        int space_idx = line.find(' ');
        std::string cards = line.substr(0, space_idx);
        int bid = stoi(line.substr(space_idx, line.size() - space_idx));

        int score = getScore(cards);

        hands.push_back(std::vector<int>{score, bid});
    }

    std::sort(hands.begin(), hands.end());
    int sum = 0;
    for(int ii = 0; ii < hands.size(); ii ++){
        sum += (ii + 1)*hands[ii][1];
    }

    std::cout << sum << '\n';


}