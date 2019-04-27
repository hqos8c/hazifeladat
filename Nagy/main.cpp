#include <iostream>
#include <fstream>


int main() {

   auto err = [](auto str){ std::cout << "Error in : " << str << "\n"; std::exit(-1); };

    std::ifstream input("data.txt");
    if(input.is_open()){
        std::cout<<"so far so good"<<std::endl;
    }
    else{err("opening"); }
}
