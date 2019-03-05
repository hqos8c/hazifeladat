#include <iostream>
#include <math.h>

double integrate(int n,double b, double a ){
 
    auto fv = [](double x){return cos(x)*exp(-(x*x));};

    double h = (b-a)/(n);
    double sum = 0.0;

    for(int  j = 1; j < (n-1); j++)
    {
        double x = a + j*h;
        sum += fv(x);
    }
    
    double res  =(h/2)*( fv(a) +2*sum + fv(b) );
    
    std::cout<< n << std::endl;
    std::cout.precision(16);
    std::cout<< res <<std::endl; 
    std::cout<< "real = 1.34638795680345037669816"<<std::endl;
    return res;
}

int main(int, char**) {
    double a = -1.0;
    double b  = 3.0;
    
    for(int n = 1; n < 10000;n = n*10)
    {
        integrate(n,b,a);
    }
    


}
