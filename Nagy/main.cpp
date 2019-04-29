#include <iostream>
#include <fstream>
#include <string>


int main() {

   auto err = [](auto str){ std::cout << "Error in : " << str << "\n"; std::exit(-1); };

    std::ifstream input("data_2.txt");
    if(input.is_open())
    {
        std::cout<<"so far so good"<<std::endl;
        
        std::string str{std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>()};
        /*std::cout<<str.size()<<std::endl;
        std::cout<<str<<std::endl;*/



    }
    else{err("opening"); }



}
