#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

namespace detail
{

template<typename M1, typename M2, typename F>
	void transform_Matrix1(M1 const& m1, M2& m2, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.begin(), f);
	}

template<typename M1, typename M2, typename M3, typename F>
	void transform_Matrix2(M1 const& m1, M2 const& m2, M3& m3, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m3.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}
 auto add = [](auto const& x, auto const& y){ return x + y; };
 auto sub = [](auto const& x, auto const& y){ return x - y; };

template<typename T>
class Matrix
{
	public: std::vector<T> data;
	public:	int N, M;

	public:	T& operator()( int i, int j ) { return data[N*i+j]; }
	public: T const& operator()( int i, int j ) const { return data[N*i+j]; }
	
	public:	T& operator[]( int i ) { return data[i]; }
	public: T const& operator[]( int i ) const { return data[i]; }

    Matrix() = default;
	Matrix( Matrix const& ) = default;
	Matrix( Matrix && ) = default;

    Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix &&) = default;

	Matrix(int n,int m ,std::vector<T> const& x): N(n), M(m), data(x){}

	template<typename F>
	Matrix(F f, int n)
	{
		data.resize(n);
		for(int i=0; i<n; ++i){ data[i] = f(i); }
	}

    Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, add);
		return *this;
	}

    Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, sub);
		return *this;
	}

    Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
	}

    Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
    }

	int size()const
	{
		return static_cast<int>( data.size() );
	}
		auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}

};

    template<typename T>
    Matrix<T> operator+( Matrix<T> const& m1, Matrix<T> const& m2 )
    {
	Matrix<T> result; result = m1;
	detail::transform_Matrix2(m1, m2, result, add);
	return result;    
	}

    template<typename T>
    Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T> const& m2 )
    {
	detail::transform_Matrix2(m1, m2, m1, add);
	return std::move(m1);
    }
    
    template<typename T>
    Matrix<T>&& operator+( Matrix<T> const& m1, Matrix<T>&& m2 )
    {
	detail::transform_Matrix2(m1, m2, m2, add);
	return std::move(m2);
    }

    template<typename T>
    Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T>&& m2 )
    {
	detail::transform_Matrix2(m1, m2, m2, add);
	return std::move(m2);
    }

    template<typename T>
    Matrix<T> operator-( Matrix<T> const& m1, Matrix<T> const& m2 )
    {
	Matrix<T> result; result = m1;
	detail::transform_Matrix2(m1, m2, result, sub);
	return result;
    }

    template<typename T>
    Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T> const& m2 )
    {
	detail::transform_Matrix2(m1, m2, m1, sub);
	return std::move(m1);
    }

    template<typename T>
    Matrix<T>&& operator-( Matrix<T> const& m1, Matrix<T>&& m2 )
    {
	detail::transform_Matrix2(m1, m2, m2, sub);
	return std::move(m2);
    }

    template<typename T>
    Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T>&& m2 )
    {
	detail::transform_Matrix2(m1, m2, m2, sub);
	return std::move(m2);
    }
	
	template<typename T>
	Matrix<T> operator*(Matrix<T> const& m, T const& scl)
	{
		Matrix<T> result; result = m;
		detail::transform_Matrix1(m, result, [=](T const& x){ return x * scl; });
		return result;
	}

	template<typename T>
	Matrix<T>&& operator*(Matrix<T>&& m, T const& scl)
	{
		detail::transform_Matrix1(m, m, [=](T const& x){ return x * scl; });
		return std::move(m);
	}

	
	template<typename T>
	Matrix<T> operator*(T const& scl,Matrix<T> const& m )
	{
		Matrix<T> result; result = m;
		detail::transform_Matrix1(m, result, [=](T const& x){ return scl*x; });
		return result;
	}

	template<typename T>
	Matrix<T>&& operator*(T const& scl,Matrix<T>&& m )
	{
		detail::transform_Matrix1(m, m, [=](T const& x){ return scl*x; });
		return std::move(m);
	}

	template<typename T>
	Matrix<T> operator/(Matrix<T> const& m, T const& scl)
	{
		Matrix<T> result; result = m;
		detail::transform_Matrix1(m, result, [=](T const& x){ return x / scl; });
		return result;
	}

	template<typename T>
	Matrix<T>&& operator/(Matrix<T>&& m, T const& scl)
	{
		detail::transform_Matrix1(m, m, [=](T const& x){ return x / scl; });
		return std::move(m);
	}

	template<typename T>
	Matrix<T> operator*(Matrix<T> const& m,Matrix<T> const& n)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		result.M=m.M;
		result.N = m.N;
		for(int i = 0; i < m.M; i++)
		{
			for(int k = 0; k < n.N; k++)
			{
				for(int j = 0; j < m.N; j++)
				{
					result(i,k) += m(i,j)*n(j,k);
				}
				
			}
			
		}
	return result;	
	}

	template<typename T>
	Matrix<T> operator*(Matrix<T>&& m,Matrix<T> const& n)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		result.M=m.M;
		result.N = m.N;
		for(int i = 0; i < m.M; i++)
		{
			for(int k = 0; k < n.N; k++)
			{
				for(int j = 0; j < m.N; j++)
				{
					result(i,k) += m(i,j)*n(j,k);
				}
				
			}
		}
	m=result;
	return std::move(m);	
	}

	template<typename T>
	Matrix<T> operator*(Matrix<T> const& m,Matrix<T>&& n)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		result.M=m.M;
		result.N = m.N;
		for(int i = 0; i < m.M; i++)
		{
			for(int k = 0; k < n.N; k++)
			{
				for(int j = 0; j < m.N; j++)
				{
					result(i,k) += m(i,j)*n(j,k);
				}
				
			}
		}
	n=result;
	return std::move(n);	
	}

	template<typename T>
	Matrix<T> operator*(Matrix<T>&& m,Matrix<T>&& n)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		result.M=m.M;
		result.N = m.N;
		for(int i = 0; i < m.M; i++)
		{
			for(int k = 0; k < n.N; k++)
			{
				for(int j = 0; j < m.N; j++)
				{
					result(i,k) += m(i,j)*n(j,k);
				}
				
			}
		}
	n=result;
	return std::move(n);	
	}


template<typename T>
std::ostream& operator<<( std::ostream& o, Matrix<T> const& M ){
    for(int i = 0; i < M.N; i++)
	{
		for(int j = 0; j < M.M; j++)
		{
			o<<M.data[M.N*i+j]<<' ';
		}
		o<<'\n';
	}
    return o;
}