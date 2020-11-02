//
// Created by ngocq on 11/1/2020.
//

#include<iostream>
#include<map>
#include<deque>

std::deque<int> str_to_deque(std::string s){
    std::deque<int> arr;

    int f[2] ={1, 0};
    for(int i=1; i<s.length(); i++){
        if(s[i] == ',' || s[i] == ']'){
            f[1] = i+1;
            arr.push_back(std::atoi(s.substr(f[0],f[1]-f[0]-1).c_str()));
            f[0]=f[1];
        }
    }
    return arr;
}

std::map<int, int> ctg_cv(std::string id, std::string count){
    std::deque<int> iD = str_to_deque(id);
    std::deque<int> c = str_to_deque(count);
    std::map<int,int> ctg;
    for(int i=0; i<iD.size(); i++){
        ctg[iD.at(i)] = c.at(i);
    }
    return ctg;
}
