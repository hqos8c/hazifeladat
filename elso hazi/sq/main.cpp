#include <iostream>
#include<math.h>

double fv(double x,double n){
    double x2 = x*x-n;
    return x2;
}

double sqrt_newton(double n, double x0){

double x1 =x0-(fv(x0,n)/(2*x0));

return x1;

}

int main(int, char**) {
    double x0 = 10;
    double n = 612;

    for(int i = 0; i < 9; i++){

    double x1 = sqrt_newton(n,x0);
    x0 = sqrt_newton(n,x0);

    }
    std::cout <<x0<<std::endl;
}