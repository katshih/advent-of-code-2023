#include <iostream>
#include <fstream>
#include <set>

int find_matches(std::string card){
    int matches = 0;
    std::set<int> win_nums;

    int idx = card.find_first_not_of(' ', card.find(':') + 1), idx_next;

    while(idx < card.find('|') - 1){
        idx_next = card.find_first_of(' ', idx + 1);
        win_nums.insert(stoi(card.substr(idx, idx_next - idx)));
            idx = card.find_first_not_of(' ', idx_next);
    }

    idx = card.find_first_not_of(' ', card.find('|') + 1);

    while(idx < card.length()){
        idx_next = card.find_first_of(' ', idx + 1);
        if((win_nums.find(stoi(card.substr(idx, idx_next - idx))) != win_nums.end())){
            matches++;
        }

        idx = card.find_first_not_of(' ', idx_next);
    }
    return matches;
}

int main(){
    std::ifstream input_file("./Inputs/input_04_test.txt");

//(ID, children, total_cards)


    int sum = 0;

    for(std::string line; std::getline(input_file, line);){
        int id_s = line.find_first_not_of(' ', line.find_first_of(' ')), id_e = line.find_first_of(':');
        int id = stoi(line.substr(id_s, id_e - id_s));

        std::cout<< "ID: " << id << ", " << find_matches(line)<<'\n';
    }

std::cout<<sum;

}