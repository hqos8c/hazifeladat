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
        std::string tmp;
        for(std::string line;std::getline(input,tmp,','); )
        {
            double b = std::stod(tmp);
            std::cout<< b<< std::endl;
        } 
    }
    else{err("opening"); }
}