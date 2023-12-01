#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
std::ifstream input_file("./Inputs/input_01.txt");

int sum = 0;
int first_digit = -1;
int last_digit = -1;
std::vector<std::string> digit_str = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
std::string line = "";

if(input_file.is_open()){
    char c;
    while(input_file){
        c = input_file.get();
        if(c == '\n'){
            sum += first_digit*10 + last_digit;
            first_digit = -1;
            last_digit = -1;
            line = "";
        }
        else if(isdigit(c)){
            last_digit = c - '0';
            if(first_digit == -1){
                first_digit = c - '0';
            }
        }
        else{
            line += c;
            for(std::vector<int>::size_type ii = 0; ii != digit_str.size(); ii++){
                if(line.find(digit_str[ii]) != std::string::npos){
                    last_digit = ii + 1;
                    if(first_digit == -1){
                        first_digit = ii + 1;
                    }
                    line = c;
                    break;
                }
            }
        }
    }
}

std::cout << sum;

}