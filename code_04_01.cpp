#include <iostream>
#include <fstream>
#include <set>

int main(){
    std::ifstream input_file("./Inputs/input_04.txt");

    int sum = 0;

    for(std::string line; std::getline(input_file, line);){
        double score = 0.5;
        std::set<int> win_nums;

        int idx = line.find_first_not_of(' ', line.find(':') + 1), idx_next;

        while(idx < line.find('|') - 1){
            idx_next = line.find_first_of(' ', idx + 1);
            win_nums.insert(stoi(line.substr(idx, idx_next - idx)));
            idx = line.find_first_not_of(' ', idx_next);
        }

        idx = line.find_first_not_of(' ', line.find('|') + 1);

        while(idx < line.length()){
            idx_next = line.find_first_of(' ', idx + 1);
            if((win_nums.find(stoi(line.substr(idx, idx_next - idx))) != win_nums.end())){
                score *= 2;
            }

            idx = line.find_first_not_of(' ', idx_next);
        }

        sum += (int)score;

    }

std::cout<<sum;

}