#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
std::ifstream input_file("./Inputs/input_02.txt");

int sum = 0;
int id = 1;
int pos; int pos_end; bool valid; int num; char type;
std::unordered_map<char, int> max_map = {{'r', 12}, {'g', 13}, {'b', 14}};

std::string line;
for(std::string line; std::getline(input_file, line);){
    valid = true;
    pos = line.find(':') + 1;

    while(pos < line.length()){
        pos_end = line.find(' ', pos + 1);
        num = stoi(line.substr(pos, pos_end));
        type = line[pos_end + 1];

        if(num > max_map[type]){
            valid = false;
            break;
        }

        pos = line.find(' ', pos_end + 1);
    }

    sum += valid*id;
    id += 1;
}

std::cout << sum;

}