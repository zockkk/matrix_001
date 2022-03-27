
#include "AbstractLayer.h"

FullyConnectedLayer::FullyConnectedLayer(const size_t _n_in, const size_t _n_out) : AbstractLayer(_n_in, _n_out)
{
    //W = Matrix<double>::zero(_n_out, _n_in);
    //b = Matrix<double>::colVector(_n_out);
    //double r = static_cast<double>(rand()) / RAND_MAX;

    W = Matrix<double>(_n_out, _n_in, 0.0);
    for (size_t i = 0; i < _n_out; i++) {
        for (size_t j = 0; j < _n_in; j++) {
            W.set(i, j, static_cast<double>(rand()) / RAND_MAX);
        }
    }
    b = Matrix<double>::colVector(_n_out, 0.0);

    G = Matrix<double>(_n_out, _n_in, 0.0);
    g = Matrix<double>::colVector(_n_out, 0.0);
}

void FullyConnectedLayer::forward()
{
    (*Y) = W * (*X) + b;
    //Y->print();
}

void FullyConnectedLayer::backward()
{
    (*error_X) = W.t() * (*error_Y);
    //std::cout << "errors" << std::endl;
    //error_X->print();
}

void FullyConnectedLayer::calcGrad()
{
    for (size_t i = 0; i < n_out; i++)
    {
        for (size_t j = 0; j < n_in; j++)
        {
            G.set(i, j, error_Y->get(i, 0) * X->get(j, 0));
        }
    }

    for (size_t i = 0; i < n_out; i++)
    {
        g.set(i, 0, error_Y->get(i, 0));
    }
    //Y->print();
    //error_Y->print();
    //G.print();
}

void FullyConnectedLayer::learn(const double rate)
{
    W -= rate * G;
    b -= rate * g;
}

void FullyConnectedLayer::print()
{
    std::cout << "FullyConnectedLayer:" << std::endl;
    W.print();
    b.print();
}

void FullyConnectedLayer::save_w(std::string a) {
    std::ofstream file;
    file.open(a, std::ios_base::out | std::ios_base::binary);
    for (size_t i = 0; i < n_out; i++) {
        for (size_t j = 0; j < n_in; j++) {
            file << W[i][j] << ' ';
        }
    }
    file.close();
}

void FullyConnectedLayer::save_b(std::string a) {
    std::ofstream file;
    file.open(a, std::ios_base::out | std::ios_base::binary);
    for (size_t i = 0; i < n_out; i++) {
        file << b[i][0] << ' ';
    }
    file.close();
}

void FullyConnectedLayer::set_w_fromfile(std::string a) {
    std::ifstream file;
    file.open(a, std::ios_base::in | std::ios_base::binary);
    for (size_t i = 0; i < n_out; i++) {
        for (size_t j = 0; j < n_in; j++) {
            file >> W[i][j];
        }
    }
    file.close();
}

void FullyConnectedLayer::set_b_fromfile(std::string a) {
    std::ifstream file;
    file.open(a, std::ios_base::in | std::ios_base::binary);
    for (size_t i = 0; i < n_out; i++) {
        file >> b[i][0];
    }
    file.close();
}

ActivationLayer::ActivationLayer(const size_t _n_in, AbstractActivationFunction *_func) : AbstractLayer(_n_in, _n_in), func(_func)
{
}

void ActivationLayer::forward()
{
    for (size_t i = 0; i < n_in; i++)
    {
        Y->set(i, 0, func->f(X->get(i, 0)));
    }
}

void ActivationLayer::backward()
{
    for (size_t i = 0; i < n_in; i++)
    {
        error_X->set(i, 0, error_Y->get(i, 0) * func->df(X->get(i, 0)));
    }
    //std::cout << "errorFunc" << std::endl;
    //error_X->print();
}

void ActivationFunctionSoftmax::forward()
{
    double m = X->get(0, 0);
    for (size_t i = 1; i < n_in; i++)
    {
        double v = X->get(i, 0);
        if (v > m)
        {
            m = v;
        }
    }

    double Z = 0.0;
    for (size_t i = 0; i < n_in; i++)
    {
        double v = exp(X->get(i, 0) - m);
        Y->set(i, 0, v);
        Z += v;
    }

    for (size_t i = 0; i < n_in; i++)
    {
        Y->set(i, 0, Y->get(i, 0) / Z);
    }
}

void ActivationFunctionSoftmax::backward()
{
    for (size_t i = 0; i < n_in; i++)
    {
        double vi = Y->get(i, 0);

        for (size_t j = 0; j < n_in; j++)
        {
            double vj = Y->get(j, 0);

            if (i == j)
            {
                J.set(i, j, vi - vi * vi);
            }
            else
            {
                J.set(i, j, -vi * vj);
            }
        }
    }

    (*error_X) = J * (*error_Y);
    //std::cout << "errorFunc" << std::endl;
    //error_X->print();
}



void AbstractLayer_UnitTest_001()
{
    FullyConnectedLayer fcl(5, 4);

    Matrix<double> X = Matrix<double>::colVector({1.0, 2.0, 3.0, 4.0, 5.0});
    Matrix<double> Y = Matrix<double>::colVector(4);

    fcl.setX(&X);
    fcl.setY(&Y);

    fcl.forward();

    Y.print();
}

void AbstractLayer_UnitTest_002()
{
    ActivationLayer fcl(5, new ActivationFunctionSigmoid);

    Matrix<double> X = Matrix<double>::colVector({0.0, 1.0, 2.0, 3.0, 4.0});
    Matrix<double> Y = Matrix<double>::colVector({0.0, 0.0, 0.0, 0.0, 0.0});

    fcl.setX(&X);
    fcl.setY(&Y);

    fcl.forward();

    Y.print();
}

void AbstractLayer_UnitTest_003()
{
    ActivationFunctionSoftmax afs(5);

    Matrix<double> X = Matrix<double>::colVector({0.0, 0.0, 0.0, 0.0, 200000.0});
    Matrix<double> Y = Matrix<double>::colVector({0.0, 0.0, 0.0, 0.0, 0.0});

    afs.setX(&X);
    afs.setY(&Y);

    afs.forward();

    Y.print();
}

void FullyConnectedLayer_UnitTest_SaveSet() 
{
    FullyConnectedLayer fcl(3, 2);
    Matrix<double> w = Matrix<double>::matrix({ { 1.0,2.0,3.0 }, { 2.0,1.0,3.0 } });
    fcl.set_w(w);
    fcl.save("test.txt");
    w = Matrix<double>::matrix({ { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 } });
    fcl.set_w(w);
    fcl.set_fromfile("test.txt");
    fcl.print();
}

void AbstractLayer_UnitTest()
{
    //AbstractLayer_UnitTest_001();
    //AbstractLayer_UnitTest_002();
    //AbstractLayer_UnitTest_003();
    FullyConnectedLayer_UnitTest_SaveSet();
}
