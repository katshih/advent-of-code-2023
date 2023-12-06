#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

int main(){
    std::ifstream input_file("./Inputs/input_06.txt");
    std::vector<int> times, records;
    std::string line;

    std::getline(input_file, line);
    int ii_s = line.find_first_of("123456789"), ii_e;
    while(ii_e < std::string::npos){
        ii_e = line.find(' ', ii_s);
        times.push_back(stoi(line.substr(ii_s, ii_e - ii_s)));
        ii_s = line.find_first_of("123456789", ii_e);
    }
    std::getline(input_file, line);
    ii_s = line.find_first_of("123456789"), ii_e = 0;
    while(ii_e < std::string::npos){
        ii_e = line.find(' ', ii_s);
        records.push_back(stoi(line.substr(ii_s, ii_e - ii_s)));
        ii_s = line.find_first_of("123456789", ii_e);
    }

    int total = 1;

    for(int ii = 0; ii < times.size(); ii++){
        int sols;
        float det = times[ii]*times[ii] - 4*(records[ii] + 0.01);
        if(det < 0){
            sols = 0;
        }
        else if(det == 0){
            if(times[ii]  % 2 == 0){
                sols = 1;
            }
            else{
                sols = 0;
            }
        }
        else{
            sols = (int)(sqrt(det));
        }
        total *= sols;
    }

std::cout << total << '\n';
}