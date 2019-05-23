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

    Vector2<T>& operator-=(Vector2<T> const& v){
    x -= v.x;   y -= v.y;
    return *this;
    }

    Vector2<T>& operator/=(T c){
    x = x/c;    y = y/c;
    return *this;
    }

    Vector2<T>& operator*= (T a){
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

template<typename T>
Vector2<T> operator/(Vector2<T> const& a,T b){
    return Vector2<T>{a.x/b,a.y/b};
}

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
    return v/length(v);
}


template<typename T>
T dot(Vector2<T> const& v,Vector2<T> const& u){
    return v.x*u.x + v.y*u.y;
}

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2<T> const& v ){
    o << v.x << " " << v.y;
    return o;
}


template<typename T>
std::ofstream& operator<<( std::ofstream& s, Vector2<T> const& m )
{
	if( s.is_open() )
	{
	std::copy( m.begin(),m.end(),std::ostream_iterator<T>(output, " ") );
	}
	else{ std::cout << "Could not open output file\n"; }
}


template<typename T>
std::istream& operator>>( std::istream& i, Vector2<T> const& v ){
    i >> v.x;
    i >> v.y;
return i;
}

template<typename T>
std::ifstream& operator>>( std::ifstream& s, Vector2<T> const& m )
{
	if( s.is_open() )
	{
	std::copy( std::istream_iterator<T>(input),
	std::istream_iterator<T>(),
	std::back_inserter(m));
	}
	else{ std::cout << "Could not open input file\n"; }
}