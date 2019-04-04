#include <iostream>
#include<cmath>
#include<vector>
#include<numeric>
#include<array>

using namespace std;

array<double,2> frame (vector<double> const& X,vector<double> const& Y){

    double xsum = (accumulate(X.begin(),X.end(),0.0)/ X.size());    
    double ysum = (accumulate(Y.begin(),Y.end(),0.0)/ Y.size()); 
    auto sq = [] (double x){return x*x;};


    auto lambda = [xsum,ysum](double X,double Y) {return ((X-xsum) * (Y-ysum));};
    auto sum = [](double X, double Y){return X+Y;};
    auto sum_2 = [xsum,sq] (double x, double y){return x + sq(y-xsum);} ;

    double b_I = inner_product(X.begin(),X.end(),Y.begin(),0.0,sum,lambda);
    double b_II = accumulate(X.begin(),X.end(),0.0,sum_2);
    if(b_II == 0.0)
    {
        cout<<"mathematical problem detected"<<endl;
        exit(-1);
    }
    
    else
    {
        double b = b_I/b_II;
        double m = ysum - b*xsum;
    
        cout<< b<< endl;
        cout<<m<<endl;

        return {b, m};
    }
}

int main() {

vector<double> X ={3.0,5.0,7.0};
vector<double> Y ={9.0,11.0,13.0};

frame(X,Y);
double ref_b = 1;
double ref_m =6; 
std::cout<<"ref b is";std::cout<<' ';
std::cout<< ref_b<<std::endl;
std::cout<< "ref m is";std::cout<<' ';
std::cout<<ref_m<< std::endl;

}