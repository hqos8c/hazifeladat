#include <iostream>
#include <cmath>

template< typename K,typename D,typename T>
T func(K fv1,D fv2,T x0 ){

    int n = 5;
    for(int i = 0; i < n; i++)
        {
            x0 =x0-(fv1(x0)/fv2(x0));
        }

    return x0;
}

int main() {
    double x1 =func([](double x){ return x*x - 612.0; },
        [](double x){ return 2.0*x; }, 10.0);


    std::cout << x1 <<std::endl;
}
