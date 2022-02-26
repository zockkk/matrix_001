#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>

/// Vector()
/// Vector(const size_t _size, const T v = static_cast<T>(0.0))
/// Vector(const std::vector<T> &v)
/// Vector(const Vector &A)
/// Vector(Vector &&A)
/// virtual ~Vector()
/// void resize(const size_t _size, const T v = static_cast<T>(0.0))
/// void clear()
/// const T* getData() const
/// size_t getSize() const
/// T operator [] (const size_t i)
/// const T operator [] (const size_t i) const
/// void set(const size_t i, const T v)
/// T& get(const size_t i)
/// const T& get(const size_t i) const
/// void operator = (const Vector &A)
/// void operator = (Vector &&A)
/// void operator += (const Vector &A)
/// void operator -= (const Vector &A)
/// void operator *= (const T &lambda)
/// void operator /= (const T &lambda)
/// friend Vector operator + (const Vector &A)
/// friend Vector operator - (const Vector &A)
/// friend Vector operator + (const Vector &A, const Vector &B)
/// friend Vector operator - (const Vector &A, const Vector &B)
/// friend Vector operator * (const Vector &A, const T &lambda)
/// friend Vector operator * (const T &lambda, const Vector &A)
/// friend Vector operator / (const Vector &A, const T &lambda)
/// static double absValue(const T &x)
/// static Vector zero(const size_t size)
/// static Vector vector(const size_t size, const T v = static_cast<T>(0.0))
/// friend T dotProduct(const Vector &A, const Vector &B)
/// friend double normL1(const Vector &A)
/// friend double normLinf(const Vector &A)
/// friend double normL2_pow_2(const Vector &A)
/// friend double normL2(const Vector &A)
/// friend double normLp(const Vector &A, const double p)
/// void print() const

template <typename T>
class Vector
{
protected:
    size_t size = 0;
    T *data = nullptr;

public:
    Vector() {}
    Vector(const size_t _size, const T v = static_cast<T>(0.0))
    {
        size = _size;
        data = new T[size];

        for (size_t i = 0; i < size; i++)
        {
            data[i] = v;
        }
    }

    Vector(const std::vector<T> &v)
    {
        size = v.size();
        data = new T[size];

        for (size_t i = 0; i < size; i++)
        {
            data[i] = v[i];
        }
    }

    Vector(const Vector &A) : Vector(A.size)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = A.data[i];
        }
    }

    Vector(Vector &&A)
    {
        std::swap(size, A.size);
        std::swap(data, A.data);
    }

    virtual ~Vector()
    {
        if (data != nullptr)
        {
            delete [] data;
        }
    }

    void resize(const size_t _size, const T v = static_cast<T>(0.0))
    {
        size_t old_size = size;

        size = _size;

        if (old_size != size)
        {
            if (data != nullptr)
            {
                delete data;
            }

            data = new T[size];
        }

        for (size_t i = 0; i < size; i++)
        {
            data[i] = v;
        }
    }

    void clear()
    {
        if (data != nullptr)
        {
            delete [] data;
        }

        size_t size = 0;
        T *data = nullptr;
    }

    const T* getData() const { return data; }
    size_t getSize() const { return size; }

    T operator [] (const size_t i) 
    {
        if (i>=size)
        {
            std::cout << "Error (140): out of range" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return data[i]; 
    }
    const T operator [] (const size_t i) const 
    { 
        if (i >= size)
        {
            std::cout << "Error (150):  out of range" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return data[i]; 
    }

    void set(const size_t i, const T v) 
    { 
        if (i >= size)
        {
            std::cout << "Error (161):  out of range" << std::endl;
            std::cin.get();
            exit(-1);
        }
        data[i] = v; 
    }
    T& get(const size_t i) 
    { 
        if (i >= size)
        {
            std::cout << "Error (171):  out of range" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return data[i]; 
    }
    const T& get(const size_t i) const 
    {
        if (i >= size)
        {
            std::cout << "Error (181):  out of range" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return data[i]; 
    }

    void operator = (const Vector &A)
    {
        resize(A.size);

        for (size_t i = 0; i < size; i++)
        {
            data[i] = A.data[i];
        }
    }

    void operator = (Vector &&A)
    {
        std::swap(size, A.size);
        std::swap(data, A.data);
    }

    void operator += (const Vector &A)
    {
        if (A.size != size)
        {
            std::cout << "Error (208): A.size != size" << std::endl;
            std::cin.get();
            exit(-1);
        }

        for (size_t i = 0; i < size; i++)
        {
            data[i] += A.data[i];
        }
    }

    void operator -= (const Vector &A)
    {
        if (A.size != size)
        {
            std::cout << "Error (223): A.size != size" << std::endl;
            std::cin.get();
            exit(-1);
        }

        for (size_t i = 0; i < size; i++)
        {
            data[i] -= A.data[i];
        }
    }

    void operator *= (const T &lambda)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] *= lambda;
        }
    }

    void operator /= (const T &lambda)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] /= lambda;
        }
    }

    friend Vector operator + (const Vector &A)
    {
        Vector B(A.size);

        for (size_t i = 0; i < B.size; i++)
        {
            B.data[i] = +A.data[i];
        }

        return std::move(B);
    }

    friend Vector operator - (const Vector &A)
    {
        Vector B(A.size);

        for (size_t i = 0; i < B.rows; i++)
        {
            B.data[i] = -A.data[i];
        }

        return std::move(B);
    }

    friend Vector operator + (const Vector &A, const Vector &B)
    {
        if (A.size != B.size)
        {
            std::cout << "Error (186): A.size != B.size" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Vector C(A.size);

        for (size_t i = 0; i < C.size; i++)
        {
            C.data[i] = A.data[i] + B.data[i];
        }

        return std::move(C);
    }

    friend Vector operator - (const Vector &A, const Vector &B)
    {
        if (A.size != B.size)
        {
            std::cout << "Error (297): A.size != B.size" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Vector C(A.size);

        for (size_t i = 0; i < C.size; i++)
        {
            C.data[i] = A.data[i] - B.data[i];
        }

        return std::move(C);
    }

    friend Vector operator * (const Vector &A, const T &lambda)
    {
        Vector B(A.size);

        for (size_t i = 0; i < B.size; i++)
        {
            B.data[i] = A.data[i] * lambda;
        }

        return std::move(B);
    }

    friend Vector operator * (const float &lambda, const Vector &A)
    {
        Vector B(A.size);

        for (size_t i = 0; i < B.size; i++)
        {
            B.data[i] = lambda * A.data[i];
        }

        return std::move(B);
    }

    friend Vector operator / (const Vector &A, const T &lambda)
    {
        Vector B(A.size);

        for (size_t i = 0; i < B.size; i++)
        {
            B.data[i] = A.data[i] / lambda;
        }

        return std::move(B);
    }

    static double absValue(const T &x)
    {
        return static_cast<double>(fabs(x));
    }

    static Vector zero(const size_t size)
    {
        Vector A(size);

        return std::move(A);
    }

    static Vector one(const size_t size, const T d = static_cast<T>(1.0))
    {
        Vector A(size);

        for (size_t i = 0; i < size; i++)
        {
            A.data[i] = d;
        }

        return std::move(A);
    }

    static Vector vector(const size_t size, const T v = static_cast<T>(0.0))
    {
        Vector A(size, v);

        return std::move(A);
    }

    static Vector vector(const std::vector<T> &v)
    {
        Vector A(v.size());

        for (size_t i = 0; i < v.size(); i++)
        {
            A.p[i] = v[i];
        }

        return std::move(A);
    }

    friend T dotProduct(const Vector &A, const Vector &B)
    {
        if (A.size != B.size)
        {
            std::cout << "Error (395): A.size != B.size" << std::endl;
            std::cin.get();
            exit(-1);
        }

        T sum = static_cast<T>(0.0);

        for (size_t i = 0; i < A.size; i++)
        {
            sum += A.data[i] * B.data[i];
        }

        return sum;
    }

    friend double normL1(const Vector &A)
    {
        double sum = 0.0;

        for (size_t i = 0; i < A.size; i++)
        {
            double v = absValue(A.data[i]);

            sum += v;
        }

        return sum;
    }

    friend double normLinf(const Vector &A)
    {
        double max = 0.0;

        for (size_t i = 0; i < A.size; i++)
        {
            double v = absValue(A.data[i]);

            if (v > max)
            {
                max = v;
            }
        }

        return max;
    }

    friend double normL2_pow_2(const Vector &A)
    {
        double sum = 0.0;

        for (size_t i = 0; i < A.size; i++)
        {
            double v = absValue(A.data[i]);

            sum += v * v;
        }

        return sum;
    }

    friend double normL2(const Vector &A)
    {
        return sqrt(normL2_pow_2(A));
    }

    friend double normLp(const Vector &A, const double p)
    {
        double sum = 0.0;

        for (size_t i = 0; i < A.size; i++)
        {
            double v = absValue(A.data[i]);

            sum += pow(v, p);
        }

        if (p > 1.0)
        {
            return pow(sum, 1.0 / p);
        }

        return sum;
    }

    void print() const
    {
        for (size_t i = 0; i < size; i++)
        {
            std::cout << " " << data[i];
        }
        std::cout << std::endl;
    }
};

void Vector_UnitTest();

#endif // VECTOR_H_INCLUDED
