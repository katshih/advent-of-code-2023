#include <iostream>
#include <fstream>
#include <string>

int main() {
std::ifstream input_file("./Inputs/input_01.txt");

int sum = 0;
int first_digit = -1;
int last_digit = -1;

if(input_file.is_open()){
    char c;
    while(input_file){
        c = input_file.get();
        if(c == '\n'){
            sum += first_digit*10 + last_digit;
            first_digit = -1;
            last_digit = -1;
        }
        else if(isdigit(c)){
            last_digit = c - '0';
            if(first_digit == -1){
                first_digit = c - '0';
            }
        }
    }
}

std::cout << sum;

}