#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <array>
#include "vector2.h"

std::pair<double,double> frame (std::vector<double> const& X,std::vector<double> const& Y){

    Vector2<double> start={0.0,0.0};

    auto second = [](Vector2<double> const& v, Vector2<double> const& old){
        return old+v;
        };
    auto sq = [] (double x){return x*x;};
   
    auto sums = [](double X, double Y){
        Vector2<double> vec = {X,Y};
        return vec;
    };

    Vector2<double> result = inner_product(X.begin(),X.end(),Y.begin(),start,second,sums);
    double x_sum= result.x /X.size();
    double y_sum =result.y /Y.size();


    auto lambda = [x_sum,y_sum,sq](double X,double Y) {
        double b_up = (X-x_sum) * (Y-y_sum);
        double b_down = sq(X-x_sum);
        Vector2<double> v ={b_up,b_down};
        return v;
        };

    result = std::inner_product(X.begin(),X.end(),Y.begin(),start,second,lambda);

    if(std::abs(result.y) < 0.0000000000001)
    {
        std::cout<<"mathematical problem detected"<<std::endl;
        exit(-1);
    }
    else
    {
        double b = result.x/result.y;
        double m = y_sum - b*x_sum;
        std::cout<< b<< std::endl;
        std::cout<<m<<std::endl;

        return {b,m};
    }
}

int main() {

std::vector<double> X ={3.0,5.0,7.0};
std::vector<double> Y ={9.0,11.0,13.0};

frame(X,Y);
double ref_b = 1;
double ref_m =6; 
std::cout<<"ref b is";std::cout<<' ';
std::cout<< ref_b<<std::endl;
std::cout<< "ref m is";std::cout<<' ';
std::cout<<ref_m<< std::endl;
}