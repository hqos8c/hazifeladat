#include <iostream>
#include<cmath>
#include<vector>
#include<numeric>
#include<array>

using namespace std;

array<double,2> frame (vector<double> const& X,vector<double> const& Y){

    double xsum = (accumulate(X.begin(),X.end(),0.0)/ X.size());    
    double ysum = (accumulate(Y.begin(),Y.end(),0.0)/ Y.size()); 

   for(int i = 0; i < X.size(); i++){
       if (X[i]-xsum == 0.0) {
           cout<<"We have a mathematical problem"<<endl;
           exit(0);
        }
   }

    auto lambda = [xsum,ysum](double X,double Y) {return ((X-xsum) * (Y-ysum))/((X-xsum)*(X-xsum));};
    auto sum = [](double X, double Y){return X+Y;};

    double b = inner_product(X.begin(),X.end(),Y.begin(),0.0,sum,lambda);
    auto m = ysum - b*xsum;
    
    cout<< b<< endl;
    cout<<m<<endl;

return {b, m};
}

int main(int, char**) {

vector<double> X ={1,5};
vector<double> Y ={2,5};

frame(X,Y);

}