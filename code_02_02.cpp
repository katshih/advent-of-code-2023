#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

int main() {
std::ifstream input_file("./Inputs/input_02.txt");

int sum = 0;
int id = 1;
int pos; int pos_end; int num; char type;
std::unordered_map<char, int> max_map;

std::string line;
for(std::string line; std::getline(input_file, line);){
    max_map = {{'r', 0}, {'g', 0}, {'b', 0}};
    pos = line.find(':') + 1;

    while(pos < line.length()){
        pos_end = line.find(' ', pos + 1);
        num = stoi(line.substr(pos, pos_end));
        type = line[pos_end + 1];

        max_map[type] = std::max(max_map[type], num);

        pos = line.find(' ', pos_end + 1);
    }

    sum += max_map['r']*max_map['g']*max_map['b'];
    id += 1;
}

std::cout << sum;

}