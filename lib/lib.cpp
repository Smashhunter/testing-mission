#include<string>
#include<iostream>
#include<algorithm>
#include "lib.h"

void lib::processString(std::string& input){
    std::sort(input.begin(), input.end(), [](const char a, const char b) {return a > b; });

    long int len = input.size();
    const std::string kb = "KB";
    for(long int i = len/2; i >= 0 ;i--){
        input.replace(i*2, 1, kb);
    }
}

int lib::calculateSum(std::string& input){
    int res = 0;
    for(const char c: input){
        if(c >= '0' && c <= '9'){
            res += c-'0';
        }
    }
    return res;
}

bool lib::checkLength(std::string& input){
    return (input.size() > 2 ) && (input.size() % 32 == 0);
}