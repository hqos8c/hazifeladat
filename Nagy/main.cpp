#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<variant>
#include<cmath>
#include<vector>

int main() {

   auto err = [](auto str){ std::cout << "Error in : " << str << "\n"; std::exit(-1); };
    struct Nope{};

    std::ifstream input("data_2.txt");
    if(input.is_open())
    {
        std::cout<<"so far so good"<<std::endl;
        
        int sum =0;
        std::string tmp_1;
        std::string tmp_2;
        for(std::string line;std::getline(input,tmp_1,';'); )
        {
            sum += 1;
        } 
        std::cout<<sum<<std::endl;
    }
    else{err("opening"); }
}