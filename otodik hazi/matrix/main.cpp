#include "matrix.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <istream>
#include <ostream>
#include <fstream>
#include <iterator>
#include <algorithm>

int main()
{
    auto err = [](auto str){ std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

    int n = 3;
    std::vector<double> v = {5.0,3.0,1.0,-1.0,-9.0,-11.0,-13.0,15.0,19.0};
    std::vector<double> u = {0.3,0.3,0.9,-0.11,-0.9,0.1,0.3,0.15,0.17}; 
{
    Matrix<double>  M;
    if(M.size() != 0) {err("initializer list constructor test [size]");}
    if(M.begin() != M.end() )  { err("default contructor test [begin == end]");}
    if(M.cbegin() != M.cend()){ err("default contructor test [cbegin == cend]");}
}

{
    Matrix<double>  M(n,n,v);
    if(M.size() != 9) {err("initializer list constructor test [size]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
    { err("initializer list constructor test indexing");}
}


{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N{M};
    if(N.size() != 9){ err("Coppy constructor test [size]");}
    if(
        N(0,0) != 5.0 ||N(0,1)!=3.0||N(0,2)!=1.0
        ||N(1,0)!=-1.0 ||N(1,1)!=-9.0||N(1,2)!=-11.0
        ||N(2,0)!=-13.0 ||N(2,1)!=15.0||N(2,2)!=19.0)
    { err("coppy constructor test indexing");}

    if(M.size() != 9) {err("Coppy constructor test [size]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
    { err("coppy constructor test indexing");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N{std::move(M)};
    if(M.size() !=0) { err("move constructor test [src size]");}
    if(M.begin() != M.end()){ err("move constructor test [src begin == src end]"); }
	if(N.size() != 9){ err("move constructor test [size]");}
    if(
        N(0,0) != 5.0 ||N(0,1)!=3.0||N(0,2)!=1.0
        ||N(1,0)!=-1.0 ||N(1,1)!=-9.0||N(1,2)!=-11.0
        ||N(2,0)!=-13.0 ||N(2,1)!=15.0||N(2,2)!=19.0)
        { err("move constructor test [elements]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N;
    N = M;
    if(N.size() != 9){ err("assignment test  [size]");}
    if(
        N(0,0) != 5.0 ||N(0,1)!=3.0||N(0,2)!=1.0
        ||N(1,0)!=-1.0 ||N(1,1)!=-9.0||N(1,2)!=-11.0
        ||N(2,0)!=-13.0 ||N(2,1)!=15.0||N(2,2)!=19.0)
        { err("assignment test [elements]");}
      if(M.size() != 9) {err("assignment test [scr size]");}
        if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("assignment test [scr elements]");}
}

{
    Matrix<double>  M(n,n,v);
    M=M;
    if(M.size() != 9) {err("self assignment test [ size]");}
        if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("self assignment test [elements]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N;
    N= std::move(M);
    if(M.size() !=0) { err("assignment test [src size]");}
    if(M.begin() != M.end()){ err("assignment test [src begin == src end]"); }
    if(N.size() != 9){ err("assignment test  [size]");}
    if(
        N(0,0) != 5.0 ||N(0,1)!=3.0||N(0,2)!=1.0
        ||N(1,0)!=-1.0 ||N(1,1)!=-9.0||N(1,2)!=-11.0
        ||N(2,0)!=-13.0 ||N(2,1)!=15.0||N(2,2)!=19.0)
        { err("assignment test [elements]");}
}

{
    Matrix<double>  M(n,n,v);
    M = std::move(M);
    if(M.size() != 0) 
    {
        if(M.size() != 9){
            err("self assignment test [ size]");
        }
    }
    if(M.size() != 0){
        if(
            M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
            ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
            ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
            {
                err("self assignment test [elements]");
            }
    }
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {5.3,3.3,1.9,-1.11,-9.9,-10.9,-12.7,15.15,19.17};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = M+N;
    if(M.size() != 9) {err("operator + (l-value, l-value) test [ size]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("operator + (l-value, l-value) test [elements]");}
    if(N.size() != 9) {err("operator + (l-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator + (l-value, l-value) test [elements]");}
    if(res.size() != 9) {err("operator + (l-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator + (l-value, l-value) test [ res]");}

}


{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {5.3,3.3,1.9,-1.11,-9.9,-10.9,-12.7,15.15,19.17};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M)+N;
    if(M.size() !=0) { err("operator +(r-value, l-value)  test [move]");}
    if(N.size() != 9) {err("operator + (r-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator + (r-value, l-value) test [elements N]");}
    if(res.size() != 9) {err("operator + (r-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator + (r-value, l-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {5.3,3.3,1.9,-1.11,-9.9,-10.9,-12.7,15.15,19.17};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = M + std::move(N);
    if(N.size() !=0) { err("operator +(l-value, r-value)  test [move]");}
    if(M.size() != 9) {err("operator + (l-value, r-value) test [ size]");}
    if(res.size() != 9) {err("operator + (l-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator + (l-value, r-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {5.3,3.3,1.9,-1.11,-9.9,-10.9,-12.7,15.15,19.17};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M) + std::move(N);
    if(M.size() !=9) { err("operator +(r-value, r-value)  test [move]");}
    if(N.size() !=0) { err("operator +(r-value, r-value)  test [move]");}
    if(res.size() != 9) {err("operator + (r-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator + (r-value, r-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {4.7,2.7,0.1,-0.89,-8.1,-11.1,-13.3,14.85,18.83};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = M-N;
    if(M.size() != 9) {err("operator - (l-value, l-value) test [ size]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("operator - (l-value, l-value) test [elements]");}
    if(N.size() != 9) {err("operator - (l-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator - (l-value, l-value) test [elements]");}
    if(res.size() != 9) {err("operator - (l-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator - (l-value, l-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {4.7,2.7,0.1,-0.89,-8.1,-11.1,-13.3,14.85,18.83};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M)-N;
    if(M.size() !=0) { err("operator -(r-value, l-value)  test [move]");}
    if(N.size() != 9) {err("operator - (r-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator - (r-value, l-value) test [elements N]");}
    if(res.size() != 9) {err("operator - (r-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator - (r-value, l-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {4.7,2.7,0.1,-0.89,-8.1,-11.1,-13.3,14.85,18.83};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = M - std::move(N);
    if(N.size() !=0) { err("operator -(l-value, r-value)  test [move]");}
    if(M.size() != 9) {err("operator - (l-value, r-value) test [ size]");}
    if(res.size() != 9) {err("operator - (l-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator - (l-value, r-value) test [ res]");}

}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {4.7,2.7,0.1,-0.89,-8.1,-11.1,-13.3,14.85,18.83};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M)-std::move(N);
    if(N.size() !=0) { err("operator -(r-value, r-value)  test [move]");}
    if(M.size() !=9) { err("operator -(r-value, r-value)  test [move]");}
    if(res.size() != 9) {err("operator - (r-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-15||std::abs(res(0,1)-ref(0,1)) >1e-15||std::abs(res(0,2)-ref(0,2)) >1e-15
        ||std::abs(res(1,0)-ref(1,0)) >1e-15||std::abs(res(1,1)-ref(1,1)) >1e-15||std::abs(res(1,2)-ref(1,2)) >1e-15
        ||std::abs(res(2,0)-ref(2,0)) >1e-15||std::abs(res(2,1)-ref(2,1)) >1e-15||std::abs(res(2,2)-ref(2,2)) >1e-15
    )   {err("operator - (r-value, r-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {5.3,3.3,1.9,-1.11,-9.9,-10.9,-12.7,15.15,19.17};
    Matrix<double> ref(n,n,ref_1);
    M += N;
    if(M.size() != 9) {err("operator += (l-value, l-value) test [ size]");}
    if(N.size() != 9) {err("operator += (l-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator += test [elements]");}
    if
    (
        M(0,0)-ref(0,0) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )   {err("operator +=  test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    Matrix<double>  N(n,n,u);
    std::vector<double> ref_1 = {4.7,2.7,0.1,-0.89,-8.1,-11.1,-13.3,14.85,18.83};
    Matrix<double> ref(n,n,ref_1);
    M -=N;
    if(M.size() != 9) {err("operator -=  test [ size]");}
    if(N.size() != 9) {err("operator -=  test [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator -=  test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {10.0,6.0,2.0,-2.0,-18.0,-22.0,-26.0,30.0,38.0};
    Matrix<double> ref(n,n,ref_1);
    M *=2;
    if(M.size() != 9) {err("operator *=  test [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator *=  test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {2.5,1.5,0.5,-0.5,-4.5,-5.5,-6.5,7.5,9.5};
    Matrix<double> ref(n,n,ref_1);
    M /=2;
    if(M.size() != 9) {err("operator /=  test [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator /=  test [ res]");}
}


{
    Matrix<double>  N(n,n,v);
    std::vector<double> ref_1 = {10.0,6.0,2.0,-2.0,-18.0,-22.0,-26.0,30.0,38.0};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  M = N*2.0;
    if(M.size() != 9) {err("operator *  test(l-value, scalar) [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator *  test(l-value ,scalar) [ res]");}
}

{
    Matrix<double>  N(n,n,v);
    std::vector<double> ref_1 = {10.0,6.0,2.0,-2.0,-18.0,-22.0,-26.0,30.0,38.0};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  M = std::move(N)*2.0;
    if(M.size() != 9) {err("operator *  test(r-value, scalar) [ size]");}
    if(N.size() != 0) {err("operator *  test(r-value, scalar) [ move]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator *  test(r-value ,scalar) [ res]");}
}

{
    Matrix<double>  N(n,n,v);
    std::vector<double> ref_1 = {10.0,6.0,2.0,-2.0,-18.0,-22.0,-26.0,30.0,38.0};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  M = 2.0*N;
    if(M.size() != 9) {err("operator *  test( scalar,l-value) [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator *  test(l-value ,scalar) [ res]");}
}

{
    Matrix<double>  N(n,n,v);
    std::vector<double> ref_1 = {10.0,6.0,2.0,-2.0,-18.0,-22.0,-26.0,30.0,38.0};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  M =2.0* std::move(N);
    if(M.size() != 9) {err("operator *  test(scalar,r-value) [ size]");}
    if(N.size() != 0) {err("operator *  test(scalar,r-value) [ move]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator *  test(scalar,r-value) [ res]");}
}

{
    Matrix<double>  N(n,n,v);
    std::vector<double> ref_1 = {2.5,1.5,0.5,-0.5,-4.5,-5.5,-6.5,7.5,9.5};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  M= N/2.0;
    if(M.size() != 9) {err("operator /  test (l-value,scalar) [ size]");}
    if
    (
        (M(0,0)-ref(0,0)) >1e-15||M(0,1)-ref(0,1) >1e-15||M(0,2)-ref(0,2) >1e-15
        ||M(1,0)-ref(1,0) >1e-15||M(1,1)-ref(1,1) >1e-15||M(1,2)-ref(1,2) >1e-15
        ||M(2,0)-ref(2,0) >1e-15||M(2,1)-ref(2,1) >1e-15||M(2,2)-ref(2,2) >1e-15
    )
   {err("operator /  test (l-value,scalar) [ res]");}
}

{
    Matrix<double>  N(n,n,u);
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {1.470,-1.05,4.97,-2.61,6.15,-3.67,0.15,-14.55,-6.97};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double>  res = M*N;
    if(M.size() != 9) {err("operator *[matrix] (l-value, l-value) test [ size]");}
    if(N.size() != 9) {err("operator *[matrix] (l-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator *[matrix] test [elements]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("operator *[matrix] test [elements]");}
    if(res.size() != 9) {err("operator *[matrix] (l-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-10||std::abs(res(0,1)-ref(0,1)) >1e-10||std::abs(res(0,2)-ref(0,2)) >1e-10
        ||std::abs(res(1,0)-ref(1,0)) >1e-10||std::abs(res(1,1)-ref(1,1)) >1e-10||std::abs(res(1,2)-ref(1,2)) >1e-10
        ||std::abs(res(2,0)-ref(2,0)) >1e-10||std::abs(res(2,1)-ref(2,1)) >1e-10||std::abs(res(2,2)-ref(2,2)) >1e-10
    )   {err("operator * [matrix] (l-value, l-value) test [ res]");}
}

{
    Matrix<double>  N(n,n,u);
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {1.470,-1.05,4.97,-2.61,6.15,-3.67,0.15,-14.55,-6.97};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M)*N;
    if(N.size() != 9) {err("operator *[matrix] (r-value, l-value) test [ size]");}
    if(M.size() != 0) {err("operator *[matrix] (r-value, l-value) test [ size]");}
    if(
        N(0,0) != 0.3 ||N(0,1)!=0.3||(N(0,2)!=0.9)
        ||(N(1,0)!=-0.11) ||N(1,1)!=-0.9||N(1,2)!=0.1
        ||N(2,0)!=0.3 ||N(2,1)!=0.15||N(2,2)!=0.17)
        { err("operator *[matrix] test [elements]");}
    if(res.size() != 9) {err("operator *[matrix] (r-value, l-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-10||std::abs(res(0,1)-ref(0,1)) >1e-10||std::abs(res(0,2)-ref(0,2)) >1e-10
        ||std::abs(res(1,0)-ref(1,0)) >1e-10||std::abs(res(1,1)-ref(1,1)) >1e-10||std::abs(res(1,2)-ref(1,2)) >1e-10
        ||std::abs(res(2,0)-ref(2,0)) >1e-10||std::abs(res(2,1)-ref(2,1)) >1e-10||std::abs(res(2,2)-ref(2,2)) >1e-10
    )   {err("operator * [matrix] (r-value, l-value) test [ res]");}
}

{
    Matrix<double>  N(n,n,u);
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {1.470,-1.05,4.97,-2.61,6.15,-3.67,0.15,-14.55,-6.97};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = M*std::move(N);
    if(M.size() != 9) {err("operator *[matrix] (l-value, r-value) test [ size]");}
    if(N.size() != 0) {err("operator *[matrix] (l-value, r-value) test [ size]");}
    if(
        M(0,0) != 5.0 ||M(0,1)!=3.0||(M(0,2)!=1.0)
        ||(M(1,0)!=-1.0) ||M(1,1)!=-9.0||M(1,2)!=-11.0
        ||M(2,0)!=-13.0 ||M(2,1)!=15.0||M(2,2)!=19.0)
        { err("operator *[matrix] test [elements]");}
    if(res.size() != 9) {err("operator *[matrix] (l-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-10||std::abs(res(0,1)-ref(0,1)) >1e-10||std::abs(res(0,2)-ref(0,2)) >1e-10
        ||std::abs(res(1,0)-ref(1,0)) >1e-10||std::abs(res(1,1)-ref(1,1)) >1e-10||std::abs(res(1,2)-ref(1,2)) >1e-10
        ||std::abs(res(2,0)-ref(2,0)) >1e-10||std::abs(res(2,1)-ref(2,1)) >1e-10||std::abs(res(2,2)-ref(2,2)) >1e-10
    )   {err("operator * [matrix] (l-value, r-value) test [ res]");}
}

{    Matrix<double>  N(n,n,u);
    Matrix<double>  M(n,n,v);
    std::vector<double> ref_1 = {1.470,-1.05,4.97,-2.61,6.15,-3.67,0.15,-14.55,-6.97};
    Matrix<double> ref(n,n,ref_1);
    Matrix<double> res = std::move(M)*std::move(N);
    if(N.size() != 0) {err("operator *[matrix] (r-value, r-value) test [ size]");}
    if(M.size() != 9) {err("operator *[matrix] (r-value, r-value) test [ size]");}
    if(res.size() != 9) {err("operator *[matrix] (r-value, r-value) test [ size]");}
    if
    (
        std::abs(res(0,0)-ref(0,0)) >1e-10||std::abs(res(0,1)-ref(0,1)) >1e-10||std::abs(res(0,2)-ref(0,2)) >1e-10
        ||std::abs(res(1,0)-ref(1,0)) >1e-10||std::abs(res(1,1)-ref(1,1)) >1e-10||std::abs(res(1,2)-ref(1,2)) >1e-10
        ||std::abs(res(2,0)-ref(2,0)) >1e-10||std::abs(res(2,1)-ref(2,1)) >1e-10||std::abs(res(2,2)-ref(2,2)) >1e-10
    )   {err("operator * [matrix] (r-value, r-value) test [ res]");}
}

{
    Matrix<double>  M(n,n,v);
    std::cout<< M << std::endl;
}
   std::cout<<"so far so good"<<std::endl;
{
    std::ofstream ofile("time.txt");
    
    for(int j = 2; j<12;j++)
    {
        for(int i=0; i<100; i++)
        {
            std::vector<double> u(j*j);
            std::vector<double> v(j*j);
            std::random_device rd{};
            std::mt19937 gen(rd());
            std::normal_distribution<double> distr(100,20);
            std::generate(u.begin(),u.end(),[&]{ return distr(gen); });
            std::generate(v.begin(),v.end(),[&]{ return distr(gen); });

            Matrix<double> m(j,j,u);
            Matrix<double> n(j,j,v);

            auto t1 = std::chrono::high_resolution_clock::now();
            m=m*n;
            auto t2 = std::chrono::high_resolution_clock::now();
            double x =(static_cast<std::chrono::duration<double, std::milli>>(t2-t1)).count();

            ofile<< x << std::endl;
        }
    }


}

/*    std::vector<double> data;
    std::ifstream input("time.txt");
    if( input.is_open() )
{
std::copy( std::istream_iterator<double>(input),std::istream_iterator<double>(),std::back_inserter(data) );
}
else{ std::cout << "Could not open input file\n"; }

    for(int i=1;i<11;i++)
    {
        std::cout<<std::min_element(data[i*100],data[100])<<std::endl;
    }*/

}