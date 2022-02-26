#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>

struct MatrixSize
{
    size_t rows = 0;
    size_t cols = 0;

    MatrixSize(const size_t _rows, const size_t _cols)
    {
        rows = _rows;
        cols = _cols;
    }

    ~MatrixSize() {}

    void print() const
    {
        std::cout << "(" << rows << ", " << cols << ")" << std::endl;
    }
};

typedef MatrixSize MSize;

template <typename T>
class Matrix
{
protected:
    size_t rows = 0;
    size_t cols = 0;
    T *data = nullptr;
    T **p = nullptr;

public:
    Matrix() {}
    Matrix(const size_t _rows, const size_t _cols, const T v = static_cast<T>(0.0))
    {
        rows = _rows;
        cols = _cols;
        data = new T[rows * cols];
        p = new T*[rows];

        p[0] = data;
        for (size_t i = 1; i < rows; i++)
        {
            p[i] = p[i - 1] + cols;
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] = v;
            }
        }
    }

    Matrix(const MatrixSize &s, const T v = static_cast<T>(0.0)) : Matrix(s.rows, s.cols, v) {}

    Matrix(const Matrix &M) : Matrix(M.rows, M.cols)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] = M.p[i][j];
            }
        }
    }

    Matrix(Matrix &&M)
    {
        std::swap(rows, M.rows);
        std::swap(cols, M.cols);
        std::swap(data, M.data);
        std::swap(p, M.p);
    }

    virtual ~Matrix()
    {
        if (data != nullptr)
        {
            delete [] data;
        }

        if (p != nullptr)
        {
            delete [] p;
        }
    }

    void resize(const size_t _rows, const size_t _cols, const T v = static_cast<T>(0.0))
    {
        size_t old_rows = rows;
        size_t old_cols = cols;

        rows = _rows;
        cols = _cols;

        if (old_rows * old_cols != rows * cols)
        {
            if (data != nullptr)
            {
                delete data;
            }

            data = new T[rows * cols];
        }

        if (old_rows != rows)
        {
            if (p != nullptr)
            {
                delete p;
            }

            p = new T*[rows];
        }

        if ((old_rows != rows) || (old_cols != cols))
        {
            p[0] = data;
            for (size_t i = 1; i < rows; i++)
            {
                p[i] = p[i - 1] + cols;
            }
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] = v;
            }
        }
    }

    void clear()
    {
        if (data != nullptr)
        {
            delete [] data;
        }

        if (p != nullptr)
        {
            delete [] p;
        }

        size_t rows = 0;
        size_t cols = 0;
        T *data = nullptr;
        T **p = nullptr;
    }

    const T* getData() const { return data; }
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    MatrixSize getSize() { return MatrixSize(rows, cols); }

    T* operator [] (const size_t i)
    { 
        if (i >= rows) {
            std::cout << "Error (168: out of range)" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return p[i]; 
    }//!!!!ÎØÈÁÊÈ
    const T* operator [] (const size_t i) const 
    { 
        if (i >= rows) {
            std::cout << "Error (177: out of range)" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return p[i]; 
    }

    void set(const size_t i, const size_t j, const T v) 
    { 
        if (i >= rows || j >=cols) {
            std::cout << "Error (187: out of range)" << std::endl;
            std::cin.get();
            exit(-1);
        }
        p[i][j] = v; 
    }
    T& get(const size_t i, const size_t j) 
    {
        if (i >= rows || j >= cols) {
            std::cout << "Error (196: out of range)" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return p[i][j]; 
    }
    const T& get(const size_t i, const size_t j) const 
    { 
        if (i >= rows || j >= cols) {
            std::cout << "Error (205: out of range)" << std::endl;
            std::cin.get();
            exit(-1);
        }
        return p[i][j]; 
    }

    void operator = (const Matrix &A)
    {
        resize(A.rows, A.cols);

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] = A.p[i][j];
            }
        }
    }

    void operator = (Matrix &&A)
    {
        std::swap(rows, A.rows);
        std::swap(cols, A.cols);
        std::swap(data, A.data);
        std::swap(p, A.p);
    }

    void operator += (const Matrix &A)
    {
        if ((A.rows != rows) || (A.cols != cols))
        {
            std::cout << "Error (237): (A.rows != rows) || (A.cols != cols)" << std::endl;
            std::cin.get();
            exit(-1);
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] += A.p[i][j];
            }
        }
    }

    void operator -= (const Matrix &A)
    {
        if ((A.rows != rows) || (A.cols != cols))
        {
            std::cout << "Error (255): (A.rows != rows) || (A.cols != cols)" << std::endl;
            std::cin.get();
            exit(-1);
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] -= A.p[i][j];
            }
        }
    }

    void operator *= (const T lambda)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                p[i][j] *= lambda;
            }
        }
    }

    friend Matrix operator + (const Matrix &A)
    {
        Matrix B(A.rows, A.cols);

        for (size_t i = 0; i < B.rows; i++)
        {
            for (size_t j = 0; j < B.cols; j++)
            {
                B.p[i][j] = +A.p[i][j];
            }
        }

        return std::move(B);
    }

    friend Matrix operator - (const Matrix &A)
    {
        Matrix B(A.rows, A.cols);

        for (size_t i = 0; i < B.rows; i++)
        {
            for (size_t j = 0; j < B.cols; j++)
            {
                B.p[i][j] = -A.p[i][j];
            }
        }

        return std::move(B);
    }

    friend Matrix operator + (const Matrix &A, const Matrix &B)
    {
        if ((A.rows != B.rows) || (A.cols != B.cols))
        {
            std::cout << "Error (314): (A.rows != B.rows) || (A.cols != B.cols)" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix C(A.rows, A.cols);

        for (size_t i = 0; i < C.rows; i++)
        {
            for (size_t j = 0; j < C.cols; j++)
            {
                C.p[i][j] = A.p[i][j] + B.p[i][j];
            }
        }

        return std::move(C);
    }

    friend Matrix operator - (const Matrix &A, const Matrix &B)
    {
        if ((A.rows != B.rows) || (A.cols != B.cols))
        {
            std::cout << "Error (336): (A.rows != B.rows) || (A.cols != B.cols)" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix C(A.rows, A.cols);

        for (size_t i = 0; i < C.rows; i++)
        {
            for (size_t j = 0; j < C.cols; j++)
            {
                C.p[i][j] = A.p[i][j] - B.p[i][j];
            }
        }

        return std::move(C);
    }

    friend Matrix operator * (const Matrix &A, const T lambda)
    {
        Matrix B(A.rows, A.cols);

        for (size_t i = 0; i < B.rows; i++)
        {
            for (size_t j = 0; j < B.cols; j++)
            {
                B.p[i][j] = A.p[i][j] * lambda;
            }
        }

        return std::move(B);
    }

    friend Matrix operator * (const T lambda, const Matrix &A)
    {
        Matrix B(A.rows, A.cols);

        for (size_t i = 0; i < B.rows; i++)
        {
            for (size_t j = 0; j < B.cols; j++)
            {
                B.p[i][j] = lambda * A.p[i][j];
            }
        }

        return std::move(B);
    }

    friend Matrix operator * (const Matrix &A, const Matrix &B)
    {
        if (A.cols != B.rows)
        {
            std::cout << "Error (388): A.cols != B.rows" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix C(A.rows, B.cols);

        for (size_t i = 0; i < C.rows; i++)
        {
            for (size_t j = 0; j < C.cols; j++)
            {
                T sum = static_cast<T>(0.0);

                for (size_t k = 0; k < A.cols; k++)
                {
                    sum += A.p[i][k] * B.p[k][j];
                }

                C.p[i][j] = sum;
            }
        }

        return std::move(C);
    }

    Matrix t() const
    {
        Matrix B(cols, rows);

        for (size_t i = 0; i < B.rows; i++)
        {
            for (size_t j = 0; j < B.cols; j++)
            {
                B.p[i][j] = p[j][i];
            }
        }

        return std::move(B);
    }

    Matrix inv() const
    {
        if (rows != cols)
        {
            std::cout << "Error (432): rows != cols" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix E = one(rows);
        Matrix X = solve(E);

        return std::move(X);
    }

    static double absValue(const T &x)
    {
        return static_cast<double>(fabs(x));
    }

    T det()
    {
        T d = static_cast<T>(1.0);

        if (rows != cols)
        {
            std::cout << "Error (454): rows != cols" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix A(*this);

        for (size_t j = 0; j < cols; j++)
        {
            size_t i_max = j;
            double max = absValue(A.p[j][j]);

            for (size_t i = j + 1; i < rows; i++)
            {
                if (absValue(A.p[i][j]) > max)
                {
                    i_max = i;
                    max = absValue(A.p[i][j]);
                }
            }

            std::swap(A.p[i_max], A.p[j]);

            if (i_max != j)
            {
                d = -d;
            }

            T General = A.p[j][j];

            d *= General;

            A.p[j][j] = static_cast<T>(1.0);
            for (size_t j1 = j + 1; j1 < cols; j1++)
            {
                A.p[j][j1] /= General;
            }

            for (size_t i = j + 1; i < rows; i++)
            {
                General = A.p[i][j];

                for (size_t j1 = j; j1 < cols; j1++)
                {
                    A.p[i][j1] -= A.p[j][j1] * General;
                }
            }
        }

        return d;
    }

    Matrix solve(const Matrix &_B) const
    {
        if ((rows != cols) || (cols != _B.rows))
        {
            std::cout << "Error (510): (rows != cols) || (cols != B.rows)" << std::endl;
            std::cin.get();
            exit(-1);
        }

        Matrix A(*this);
        Matrix B(_B);
        Matrix X(cols, B.cols);

        for (size_t j = 0; j < cols; j++)
        {
            size_t i_max = j;
            double max = absValue(A.p[j][j]);

            for (size_t i = j + 1; i < rows; i++)
            {
                if (absValue(A.p[i][j]) > max)
                {
                    i_max = i;
                    max = absValue(A.p[i][j]);
                }
            }

            std::swap(A.p[i_max], A.p[j]);
            std::swap(B.p[i_max], B.p[j]);

            T General = A.p[j][j]; /// General != 0 TODO

            A.p[j][j] = static_cast<T>(1.0);
            for (size_t j1 = j + 1; j1 < cols; j1++)
            {
                A.p[j][j1] /= General;
            }

            for (size_t j1 = 0; j1 < B.cols; j1++)
            {
                B.p[j][j1] /= General;
            }

            for (size_t i = j + 1; i < rows; i++)
            {
                General = A.p[i][j];

                for (size_t j1 = j; j1 < cols; j1++)
                {
                    A.p[i][j1] -= A.p[j][j1] * General;
                }

                for (size_t j1 = 0; j1 < B.cols; j1++)
                {
                    B.p[i][j1] -= B.p[j][j1] * General;
                }
            }
        }

        for(size_t j1 = 0; j1 < B.cols; j1++)
        {
            for(size_t i = rows; i > 0; i--)
            {
                T sum = B.p[i - 1][j1];

                for(size_t j = i; j < cols; j++)
                {
                    sum -= A.p[i - 1][j] * X.p[j][j1];
                }

                X.p[i - 1][j1]= sum;
            }
        }

        return std::move(X);
    }

    static Matrix matrix(const size_t rows, const size_t cols, const T v)
    {
        Matrix A(rows, cols, v);

        return std::move(A);
    }

    static Matrix matrix(const std::vector<std::vector<T>> &m)
    {
        size_t rows = m.size();
        size_t cols = m[0].size();

        Matrix A(rows, cols);

        for (size_t i = 0; i < rows; i++)
        {
            if (m[i].size() != cols)
            {
                std::cout << "Error (601): m[i].size() != cols" << std::endl;
                std::cin.get();
                exit(-1);
            }

            for (size_t j = 0; j < cols; j++)
            {
                A.p[i][j] = m[i][j];
            }
        }

        return std::move(A);
    }

    static Matrix square(const size_t size, const T v = static_cast<T>(0.0))
    {
        Matrix A(size, size, v);

        return std::move(A);
    }

    static Matrix zero(const size_t rows, const size_t cols)
    {
        Matrix A(rows, cols);

        return std::move(A);
    }

    static Matrix one(const size_t size, const T d = static_cast<T>(1.0))
    {
        Matrix A(size, size);

        for (size_t i = 0; i < size; i++)
        {
            A.p[i][i] = d;
        }

        return std::move(A);
    }

    static Matrix diag(const std::vector<T> &d)
    {
        Matrix A(d.size(), d.size());

        for (size_t i = 0; i < d.size(); i++)
        {
            A.p[i][i] = d[i];
        }

        return std::move(A);
    }

    static Matrix rowVector(const size_t size, const T v = static_cast<T>(0.0))
    {
        Matrix A(1, size, v);

        return std::move(A);
    }

    static Matrix rowVector(const std::vector<T> &v)
    {
        Matrix A(1, v.size());

        for (size_t i = 0; i < v.size(); i++)
        {
            A.p[0][i] = v[i];
        }

        return std::move(A);
    }

    static Matrix colVector(const size_t size, const T v = static_cast<T>(0.0))
    {
        Matrix A(size, 1, v);

        return std::move(A);
    }

    static Matrix colVector(const std::vector<T> &v)
    {
        Matrix A(v.size(), 1);

        for (size_t i = 0; i < v.size(); i++)
        {
            A.p[i][0] = v[i];
        }

        return std::move(A);
    }

    friend double normL1(const Matrix &A)
    {
        double max = 0.0;

        for (size_t j = 0; j < A.cols; j++)
        {
            double sum = 0.0;

            for (size_t i = 0; i < A.rows; i++)
            {
                double v = absValue(A.p[i][j]);

                sum += v;
            }

            if (sum > max)
            {
                max = sum;
            }
        }

        return max;
    }

    friend double normLinf(const Matrix &A)
    {
        double max = 0.0;

        for (size_t i = 0; i < A.rows; i++)
        {
            double sum = 0.0;

            for (size_t j = 0; j < A.cols; j++)
            {
                double v = absValue(A.p[i][j]);

                sum += v;
            }

            if (sum > max)
            {
                max = sum;
            }
        }

        return max;
    }

    friend double normFrobenius_pow_2(const Matrix &A)
    {
        double sum = 0.0;

        for (size_t i = 0; i < A.rows; i++)
        {
            for (size_t j = 0; j < A.cols; j++)
            {
                double v = absValue(A.p[i][j]);

                sum += v * v;
            }
        }

        return sum;
    }

    friend double normFrobenius(const Matrix &A)
    {
        return sqrt(normFrobenius_pow_2(A));
    }

    void print() const
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                std::cout << " " << p[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

void Matrix_UnitTest();

#endif // MATRIX_H_INCLUDED
