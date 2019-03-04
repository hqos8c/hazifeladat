#include <iostream>
#include<math.h>

double fv(double x,double n){
    double x1 = x*x-n;
    return x1;
}

double sqrt_newton(double n, double x0){

for(int i = 0; i < n; i++)
    {
        x0 =x0-(fv(x0,n)/(2*x0));
    }

return x0;

}

int main(int, char**) {
    double x0 = 10;
    int n = 612;

    double x=sqrt_newton(n,x0);

    std::cout <<x<<std::endl;
}