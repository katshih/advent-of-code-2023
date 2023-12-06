#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

// using a double is important here, otherwise we get rounding errors
int main(){
    std::ifstream input_file("./Inputs/input_06.txt");
    std::string time_str = "", record_str = "";
    long time, record;
    std::string line;

    std::getline(input_file, line);
    int ii_s = line.find_first_of("123456789"), ii_e;
    while(ii_e < std::string::npos){
        ii_e = line.find(' ', ii_s);
        time_str.append(line.substr(ii_s, ii_e - ii_s));
        ii_s = line.find_first_of("123456789", ii_e);
    }
    time = stol(time_str);
    std::getline(input_file, line);
    ii_s = line.find_first_of("123456789"), ii_e = 0;
    while(ii_e < std::string::npos){
        ii_e = line.find(' ', ii_s);
        record_str.append(line.substr(ii_s, ii_e - ii_s));
        ii_s = line.find_first_of("123456789", ii_e);
    }
    record = stol(record_str);

    int sols;
    double det = time*time - 4*(record + 0.01);
    if(det < 0){
        sols = 0;
    }
    else if(det == 0){
        if(time % 2 == 0){
            sols = 1;
        }
        else{
            sols = 0;
        }
    }
    else{
        sols = (int)(sqrt(det));
    }

    std::cout<<sols<< '\n';

}