#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <array>

std::pair<double,double> frame (std::vector<double> const& X,std::vector<double> const& Y){

    auto zero = [](double X, double Y){return 0.0;};
    auto sq = [] (double x){return x*x;};
    double xsum = 0.0;
    double ysum = 0.0;
    
    auto sums = [&xsum,&ysum](double X, double Y){
        xsum += X;
        ysum += Y;
        return 0.0;
    };

    std::inner_product(X.begin(),X.end(),Y.begin(),0.0,zero,sums);
    xsum/=X.size();
    ysum/=Y.size();

    double b_up = 0.0;
    double b_down=0.0;
   
    auto lambda = [xsum,ysum,sq,&b_up,&b_down](double X,double Y) {
        b_up += (X-xsum) * (Y-ysum);
        b_down += sq(X-xsum);
        return 0.0;
        };

    std::inner_product(X.begin(),X.end(),Y.begin(),0.0,zero,lambda);

    if(b_down == 0.0)
    {
        std::cout<<"mathematical problem detected"<<std::endl;
        exit(-1);
    }
    
    else
    {
        double b = b_up/b_down;
        double m = ysum - b*xsum;

        std::cout<< b<< std::endl;
        std::cout<<m<<std::endl;

        return {b, m};
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