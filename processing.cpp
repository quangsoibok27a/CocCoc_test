//
// Created by ngocq on 11/2/2020.
//

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include<iostream>
#include<map>
#include<deque>
#include "myLibrary.h"

int main() {
    // read file csv
    std::ifstream myFile("./hash_catid_count.csv");
    std::string line;


    std::pair<int, int> max_freq(0, 0);
    std::map<int, int> freq;
    std::pair<int, int> most_popular(0, 0);
    std::map<int, int> exper;

    // get line csv
    while(std::getline(myFile, line)) {
        std::string delimiter = "\t";
        size_t pos = 0;
        std::string token[2];
        for(int i=0; i<2; i++){
            pos = line.find(delimiter);
            token[i] = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }

        User user = User(token[0], token[1], line);
        std::map<int,int> s = user.get_ctg();
        for (auto it=s.begin(); it!=s.end(); ++it){
            if ( freq[it->first] ){
                freq[it->first] += it->second;
                exper[it->first] += 1;
            }
            else{
                freq[it->first] = it->second;
                exper[it->first] = 1;
            }
//            find most appearent
            if(freq[it->first] > max_freq.second){
                max_freq.first = it->first;
                max_freq.second = freq[it->first];
            }
//            find most popular
            if(exper[it->first] > most_popular.second){
                most_popular.first = it->first;
                most_popular.second = exper[it->first];
            }
        }
    }

//  print data after processing
    for(auto it=freq.begin(); it!=freq.end(); ++it){
        std::cout<<"category_id: "<<it->first<<"\tfrequency: "<<it->second<<"     \tAppeared in: "<<exper[it->first]<<" objects"<<std::endl;
    }
    std::cout<<"max fre: "<<max_freq.first<<" "<<max_freq.second<<std::endl;
    std::cout<<"most popular category: "<<most_popular.first<<" "<<most_popular.second<<std::endl;

    return 0;
}