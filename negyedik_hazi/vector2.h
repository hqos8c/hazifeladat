#include <iostream>
#include<cmath>
#include<numeric>
#include<algorithm>

template<typename T>
struct Vector2
{
    T x;
    T y;

    Vector2<T>& operator+=(Vector2<T> const& v){
    x += v.x;   y += v.y;
    return *this;
    }

    Vector2<T> operator-=(Vector2<T> const& v){
    x -= v.x;   y -= v.y;
    return *this;
    }

    Vector2<T> operator/=(T c){
    x = x/c;    y = y/c;
    return *this;
    }

    Vector2<T> operator*= (T a){
    x = x*a; y = y*a;
    return *this;
    }

};

template<typename T>
T sq(T a){
    return a*a;
}

template<typename T>
 Vector2<T> operator+( Vector2<T> const& a, Vector2<T> const& b){

    return Vector2<T>{ a.x+ b.x, a.y+ b.y};
}

template<typename T>
 Vector2<T> operator-( Vector2<T> const& a, Vector2<T> const& b){

    return Vector2<T>{ a.x- b.x, a.y - b.y};
}

/*
template<typename T>
Vector2<T> operator* (Vector2<T> const& a, Vector2<T> const& b){

    return Vector2<T>{(a.x * b.x) + (a.y * b.y)};
}

*/
template<typename T>
Vector2<T> operator*(Vector2<T> const& a,T b){
    return Vector2<T>{a.x*b,a.y*b};
}
 
template<typename T>
Vector2<T> operator*(T b, Vector2<T> const& a){
    return Vector2<T>{b*a.x,b*a.y};
}


template<typename T>
T length(Vector2<T> const& v){
    return  sqrt(sq(v.x) + sq(v.y)); 
}

template<typename T>
T sqlength(Vector2<T> const& v){
    return sq(v.x) + sq(v.y);
}

template<typename T>
Vector2<T> normalize(Vector2<T> const& v){
    T v_length = sqrt(sq(v.x) + sq(v.y));
    return Vector2<T>{v.x/v_length,v.y/v_length};
}

template<typename T>
void printvector(Vector2<T> const& v){
    std::cout<<v.x<<std::endl;
    std::cout<<v.y<<std::endl;
}

template<typename T>
T dot(Vector2<T> const& v,Vector2<T> const& u){
    return v.x*u.x + v.y*u.y;
}