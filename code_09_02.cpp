#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

std::vector<int> diff(std::vector<int> v){
    std::vector<int> result;

    for(int ii = 1; ii < v.size(); ii++){
        result.push_back(v[ii] - v[ii - 1]);
    }

    return result;
}

int main(){
    std::ifstream input_file("./Inputs/input_09.txt");

    int sum = 0;

    for(std::string line; std::getline(input_file, line);){
        std::vector<int> val_history;
        int num; std::stringstream stream(line);
        while(stream >> num){
            val_history.push_back(num);
        }        

        int ii = 0;
        while(!std::all_of(val_history.begin(), val_history.end(), [](int i) {return i == 0;})){
            sum += val_history[0]*pow(-1, (ii % 2));
            val_history = diff(val_history);
            ii += 1;
        }
    }

    std::cout << sum << '\n';

}