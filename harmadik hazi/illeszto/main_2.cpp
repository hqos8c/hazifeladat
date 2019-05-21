#include <iostream>
#include<cmath>
#include<vector>
#include<numeric>
#include<array>
#include <future>

std::pair<double,double> frame (std::vector<double> const& X,std::vector<double> const& Y){
    double xsum = (accumulate(X.begin(),X.end(),0.0)/ X.size());
    double ysum = (accumulate(Y.begin(),Y.end(),0.0)/ Y.size());
    auto sq = [] (double x){return x*x;};

// az xsum és az ysum kell, őket nem akarjuk újra és újra kiszámolni
// ezért nem tettem őket bele a párhuzamosításba

    auto mylambda = [xsum,ysum ,sq](std::vector<double> X,std::vector<double> Y,int i){
        double up =(X[i]-xsum)*(Y[i]-ysum);
        double down = sq(X[i]-xsum);
        std::pair<double,double> par={up, down};
        return par;
        };


//szálkezelés kezdete
        auto t1=std::async(mylambda,X,Y,0);
        auto t2=std::async(mylambda,X,Y,1);
        auto t3 = std::async(mylambda,X,Y,2);
        std::vector< std::pair<double,double> > vec(3);
        vec[0]=t1.get();
        vec[1]=t2.get();
        vec[2]=t3.get();
// szálkezelés vége

    double up=0.0;
    double down=0.0;
    for(auto e:vec){up +=e.first;}
    for(auto e:vec){down += e.second;}
//szálak adatainak kinyerése
        
        if(std::abs(down)<0.000000001){
            std::cout<<"Mathematical problem detected"<<std::endl;
            exit(-1);
        }
        else{
        double m = up/down;
        double b= ysum-m*xsum;
        return {b,m};
        }
    }
int main() {

std::vector<double> X ={3.0,5.0,7.0};
std::vector<double> Y ={9.0,11.0,13.0};

std::pair<double,double> data = frame(X,Y);
double ref_b = 1;
double ref_m =6; 
std::cout<<"ref b is";std::cout<<' '<< ref_b<<std::endl;
std::cout<< "ref m is";std::cout<<' '<<ref_m<< std::endl;
std::cout<<data.second<<" the real b is"<<std::endl<<data.first<<" the real m is"<<std::endl;
}