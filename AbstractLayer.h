#ifndef ABSTRACTLAYER_H_INCLUDED
#define ABSTRACTLAYER_H_INCLUDED

#include "Matrix.h"
#include <string>
#include <fstream>

class AbstractLayer
{
protected:
    size_t n_in = 0;
    size_t n_out = 0;

    Matrix<double> *X;
    Matrix<double> *Y;

    Matrix<double> *error_X = nullptr;
    Matrix<double> *error_Y = nullptr;

public:
    AbstractLayer(const size_t _n_in = 0, const size_t _n_out = 0) : n_in(_n_in), n_out(_n_out) {}
    virtual ~AbstractLayer() {}

    void setX(Matrix<double> *_X) { X = _X; }
    void setY(Matrix<double> *_Y) { Y = _Y; }

    void set_error_X(Matrix<double> *_error_X) { error_X = _error_X; }
    void set_error_Y(Matrix<double> *_error_Y) { error_Y = _error_Y; }

    size_t get_n_in() const { return n_in; }
    size_t get_n_out() const { return n_out; }

    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void calcGrad() = 0;
    virtual void learn(const double rate) = 0;

    virtual void print() = 0;

    virtual void save(std::string a) = 0;
    virtual void set_fromfile(std::string a) = 0;
};

class FullyConnectedLayer : public AbstractLayer
{
protected:
    Matrix<double> W, b;
    Matrix<double> G, g;

public:
    FullyConnectedLayer(const size_t _n_in, const size_t _n_out);
    virtual ~FullyConnectedLayer() {}

    void set_w(const Matrix<double> &_W) { W = _W;}
    void set_b(const Matrix<double> &_b) { b = _b;}

    virtual void forward() override;
    virtual void backward() override;
    virtual void calcGrad() override;
    virtual void learn(const double rate) override;

    virtual void print() override;

    void virtual save(std::string a) override;
    void virtual set_fromfile(std::string a) override;
};

class AbstractActivationFunction
{
public:
    AbstractActivationFunction() {}
    virtual ~AbstractActivationFunction() {}

    virtual double f(const double x) = 0;
    virtual double df(const double x) = 0;
};

class ActivationFunctionSigmoid : public AbstractActivationFunction
{
public:
    ActivationFunctionSigmoid() : AbstractActivationFunction() {}
    virtual ~ActivationFunctionSigmoid() {}

    virtual double f(const double x) override { return 1.0 / (1.0 + std::exp(-x)); }
    virtual double df(const double x) override { double y = f(x); return y * (1.0 - y); }
};

class ActivationFunctionTh : public AbstractActivationFunction
{
public:
    ActivationFunctionTh() : AbstractActivationFunction() {}
    virtual ~ActivationFunctionTh() {}

    virtual double f(const double x) override { return -1.0 + 2.0 / (1.0 + std::exp(-2 * x)); }
    virtual double df(const double x) override { return 4.0 / (exp(2 * x) + 2.0 + exp(-2 * x)); }
};

class ActivationLayer : public AbstractLayer
{
protected:
    AbstractActivationFunction *func;

public:
    ActivationLayer(const size_t _n_in, AbstractActivationFunction *_func);
    virtual ~ActivationLayer() { delete func; }

    virtual void forward() override;
    virtual void backward() override;
    virtual void calcGrad() override {};
    virtual void learn(const double rate) override {};

    virtual void print() override {};

    virtual void save(std::string a) override {};
    virtual void set_fromfile(std::string a) override {};
};

class ActivationFunctionSoftmax : public AbstractLayer
{
protected:
    Matrix<double> J;

public:
    ActivationFunctionSoftmax(size_t _n_in) : AbstractLayer(_n_in, _n_in) { J = Matrix<double>::matrix(_n_in, _n_in, 0.0); }
    virtual ~ActivationFunctionSoftmax() {}

    virtual void forward() override;
    virtual void backward() override;
    virtual void calcGrad() override {};
    virtual void learn(const double rate) override {};

    virtual void print() override {};

    virtual void save(std::string a) override {};
    virtual void set_fromfile(std::string a) override {};
};

void AbstractLayer_UnitTest();

#endif // ABSTRACTLAYER_H_INCLUDED
