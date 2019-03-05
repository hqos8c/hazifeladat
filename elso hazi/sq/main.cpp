#include <iostream>
#include<cmath>

double fv(double x,double x0){
    double x1 = x*x-x0;
    return x1;
}

double sqrt_newton(double x0, double x){

for(int i = 0; i < 100; i++)
    {
        x =x-(fv(x,x0)/(2*x));
    }

return x0;

}

int main(int, char**) {
    double x = 10;
    double x0 = 612;

    double x1=sqrt_newton(x0,x);

    std::cout <<x1<<std::endl;
}