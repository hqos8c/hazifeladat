#include <iostream>
#include <string>
#include "vector2.h"

using namespace std;

void test(Vector2<double> const& v,Vector2<double> const& v_ref, std::string const& name)
{
    if (length(v-v_ref) > 1e-10) {
        cout<<"error in"; cout<<" ";  cout<<name<<endl;
    }
    
}

void test_double(double w, double ref,std::string const& name)
{
    if (abs(w-ref) > 1e-10) {
        cout<<"error in"; cout<<name<<endl;
    }
}

int main()
{
    const Vector2<double> v = {3.0,5.0};
    const Vector2<double> u = {7.0,11.0};


{
    Vector2<double> w = v;
    w +=u;
    Vector2<double> ell = {10.0,16.0};
    test(w,ell,"addition eq");

}

{
    Vector2<double> w = v;
    w -= u;
    Vector2<double> ell = {-4.0,-6.0};
    test(w,ell,"subsctraction eq");

}

{
    Vector2<double> w = v;
    w *= 2;
    Vector2<double> ell = {6.0,10.0};
    test(w,ell,"multiply eq");
}

{
    Vector2<double> w = v;
    w /= 2;
    Vector2<double> ell = {1.5,2.5};
    test(w,ell,"divide eq");
}

{
    Vector2<double> w = v;
    w = v+u;
    Vector2<double> ell = {10.0,16.0};
    test(w,ell,"add ");
}

{
    Vector2<double> w = v;
    w = v-u;
    Vector2<double> ell = {-4.0,-6.0};
    test(w,ell,"substract");
}

{
    Vector2<double> w = v;
    w = v*2.0;
    Vector2<double> ell = {6.0,10.0};
    test(w,ell,"mult");
}

{
    double w =  sqlength(v);
    double ref = 34.0;
    test_double(w,ref,"sqlength");
}

{
    Vector2<double> w = normalize(v);
    Vector2<double> ell = {3/sqrt(34),5/sqrt(34)};
    test(w,ell,"normalize");
}

{
    double w =  dot(v,u);
    double ref = 76.0;
    test_double(w,ref,"dot");
}


}