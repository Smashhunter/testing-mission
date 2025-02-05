//lib/lib.cpp
#include<string>
#include<iostream>
#include<algorithm>
#include "lib.h"

/*
Reverse sorting elements from input string(I guess symbols?) and replaces all even elements on "KB"
In this function I guess that even element is meant to be the evement, 
what have even index, but if I misunderstand this I will fix code
*/
void lib::processString(std::string& input){
    std::sort(input.begin(), input.end(), [](const char a, const char b) {return a > b; });

    long int len = input.size();
    const std::string kb = "KB";
    for(long int i = len/2; i >= 0 ;i--){
        input.replace(i*2, 1, kb);
    }
}

/*
Calculetes sum from all char symbols in input string
*/
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