#include <iostream>
#include<cmath>
#include<vector>
#include<numeric>
#include<array>

using namespace std;

array<double,2> frame (vector<double> const& X,vector<double> const& Y){

    double xsum = (accumulate(X.begin(),X.end(),0.0)/ X.size());    
    double ysum = (accumulate(Y.begin(),Y.end(),0.0)/ Y.size()); 
    
    double b = 0.0;

    for(int i = 0; i < X.size(); i++)
    {
        if(X[i]-xsum == 0){
            cout<< "We have discovered a mathematical problem" << endl;   //ez a lépés csak azért szükséges, hogy ne legyen nan a végeredmény
            exit(0);
        }

        else{
        b = b + ((X[i]-xsum)*(Y[i]-ysum))/((X[i]-xsum)*(X[i]-xsum));    
        }
    }

    double m = ysum - b*xsum;
    
    cout<< b<< endl;
    cout<<m<<endl;

return {b, m};
}

int main(int, char**) {

vector<double> X ={1,2};
vector<double> Y ={2,3};

frame(X,Y);

}