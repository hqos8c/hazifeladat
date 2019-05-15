#include <iostream>
#include <future>


int main() {
auto f1 = [](double k, double j,int first, int last){
    double res = 0.0;
    for (int i = first; i < last; i++)
    {
        res +=  i*j + i*k;
    }
    return res;
};

auto t1 = std::async(f1,1.0,2.0,0,3);
auto t2 = std::async(f1,1.0,2.0,3,5);

double a = t1.get()+t2.get();

std::cout<<a<<std::endl;


}
