
#include "ArtificialNeuralNetwork.h"

void ArtificialNeuralNetwork::add(AbstractLayer *layer)
{
    if (!layers.empty())
    {
        if (layers.back()->get_n_out() != layer->get_n_in())
        {
            std::cout << "layers.back()->get_n_out() != layer->get_n_in()" << std::endl;
            std::cin.get();
            exit(-1);
        }

        XY.push_back(new Matrix<double>(layers.back()->get_n_out(), 1));
        error_XY.push_back(new Matrix<double>(layers.back()->get_n_out(), 1));

        layers.back()->setY(XY.back());
        layer->setX(XY.back());

        layers.back()->set_error_Y(error_XY.back());
        layer->set_error_X(error_XY.back());
    }

    layers.push_back(layer);
}

void ArtificialNeuralNetwork::forward()
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        layers[i]->forward();
    }
}

void ArtificialNeuralNetwork::backward()
{
    for (size_t i = layers.size(); i > 0; i--)
    {
        layers[i - 1]->backward();
    }
}

void ArtificialNeuralNetwork::calcGrad()
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        layers[i]->calcGrad();
    }
}

void ArtificialNeuralNetwork::learn(const double rate)
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        layers[i]->learn(rate);
    }
}

void ArtificialNeuralNetwork::print()
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        layers[i]->print();
    }
}

ArtificialNeuralNetwork::~ArtificialNeuralNetwork()
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        delete layers[i];
    }

    for (size_t i = 0; i < XY.size(); i++)
    {
        delete XY[i];
    }
}

void ArtificialNeuralNetwork::setX(Matrix<double> *_X)
{
    if (!layers.empty())
    {
        layers.front()->setX(_X);
    }
}

void ArtificialNeuralNetwork::setY(Matrix<double> *_Y)
{
    if (!layers.empty())
    {
        layers.back()->setY(_Y);
    }
}

void ArtificialNeuralNetwork::set_error_X(Matrix<double> *_error_X)
{
    if (!layers.empty())
    {
        layers.front()->set_error_X(_error_X);
    }
}

void ArtificialNeuralNetwork::set_error_Y(Matrix<double> *_error_Y)
{
    if (!layers.empty())
    {
        layers.back()->set_error_Y(_error_Y);
    }
}

void ArtificialNeuralNetwork::save(std::string a) 
{
    for (size_t i = 0; i < layers.size(); i += 2) 
    {
        layers[i]->save("w_directory/" + std::to_string(i) + '_' + a);
    }
}

void ArtificialNeuralNetwork::set_fromfile(std::string a)
{
    for (size_t i = 0; i < layers.size(); i += 2)
    {
        layers[i]->set_fromfile("w_directory/" + std::to_string(i) + '_' + a);
    }
}

double sigmoid(const double x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

std::vector<Matrix<double>> Train_X(const size_t n, const size_t m)
{
    std::vector<Matrix<double>> X(n);

    for (size_t i = 0; i < n; i++)
    {
        X[i] = Matrix<double>::colVector(m);

        for (size_t j = 0; j < m; j++)
        {
            double r = static_cast<double>(rand()) / RAND_MAX;
            X[i].set(j, 0, -0.1 * (1.0 - r) + 0.1 * r);
        }
    }

    return std::move(X);
}

std::vector<Matrix<double>> Train_Y(std::vector<Matrix<double>> x)
{
    std::vector<Matrix<double>> Y(x.size());
    std::vector<Matrix<double>> Z(x.size());

    FullyConnectedLayer ann1(3, 2);
    Matrix<double> w = Matrix<double>::matrix({ {2.0, 4.0, -2.0}, {-2.0, -4.0, 2.0} });
    Matrix<double> b = Matrix<double>::matrix({{0.0}, {0.0}});
    ann1.set_w(w);
    ann1.set_b(b);

    //ActivationLayer ann2(2, new ActivationFunctionSigmoid);
    ActivationFunctionSoftmax ann2(2);
    for (size_t i = 0; i < x.size(); i++)
    {
        Y[i] = Matrix<double>::colVector(2);
        Z[i] = Matrix<double>::colVector(2);
        ann1.setX(&x[i]);
        ann1.setY(&Y[i]);
        ann1.forward();
        ann2.setX(&Y[i]);
        ann2.setY(&Z[i]);
        ann2.forward();
    }
    return Z;
}

void ArtificialNeuralNetwork_UnitTest_001()
{
    ArtificialNeuralNetwork ann;
    ann.add(new FullyConnectedLayer(5, 7));
    ann.add(new FullyConnectedLayer(7, 7));
    ann.add(new FullyConnectedLayer(7, 5));

    Matrix<double> X = Matrix<double>::colVector({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    Matrix<double> Y = Matrix<double>::colVector(5);

    Matrix<double> error_X = Matrix<double>::colVector(5);
    Matrix<double> error_Y = Matrix<double>::colVector({ 1.0, 2.0, 3.0, 4.0, 5.0 });

    ann.setX(&X);
    ann.setY(&Y);

    ann.set_error_X(&error_X);
    ann.set_error_Y(&error_Y);

    ann.forward();

    Y.print();
    /// —читаю ошибка

    ann.backward();

    error_X.print();
}

void ArtificialNeuralNetwork_UnitTest_002()
{
    Matrix<double> A = Matrix<double>::matrix({ {1.0, 2.0}, {3.0, 1.0} });
    Matrix<double> b = Matrix<double>::matrix({ {4.0}, {5.0} });
    b.print();

    std::vector<Matrix<double>> X_train(3);
    std::vector<Matrix<double>> Y_train(3);
    X_train[0] = Matrix<double>::colVector({ 0.0, 0.0 }); Y_train[0] = A * X_train[0] + b;
    X_train[1] = Matrix<double>::colVector({ 1.0, 0.0 }); Y_train[1] = A * X_train[1] + b;
    X_train[2] = Matrix<double>::colVector({ 0.0, 1.0 }); Y_train[2] = A * X_train[2] + b;

    std::vector<Matrix<double>> X_test(3);
    std::vector<Matrix<double>> Y_test(3);
    X_test[0] = Matrix<double>::colVector({ 3.0, 5.0 }); Y_test[0] = A * X_test[0] + b;
    X_test[1] = Matrix<double>::colVector({ 7.0, 2.0 }); Y_test[1] = A * X_test[1] + b;
    X_test[2] = Matrix<double>::colVector({ 4.0, 4.0 }); Y_test[2] = A * X_test[2] + b;

    ArtificialNeuralNetwork ann;
    ann.add(new FullyConnectedLayer(2, 2));
    ann.add(new FullyConnectedLayer(2, 2));

    Matrix<double> X = Matrix<double>::colVector({ 0.0, 0.0 });
    Matrix<double> Y = Matrix<double>::colVector({ 0.0, 0.0 });

    Matrix<double> error_X = Matrix<double>::colVector({ 0.0, 0.0 });
    Matrix<double> error_Y = Matrix<double>::colVector({ 0.0, 0.0 });

    ann.set_error_X(&error_X);
    ann.set_error_Y(&error_Y);

    for (size_t j = 0; j < 10000; j++)
    {
        for (size_t i = 0; i < X_train.size(); i++)
        {
            ann.setX(&X_train[i]);
            ann.setY(&Y);

            ann.forward();

            error_Y = Y - Y_train[i];

            ann.backward();
            ann.calcGrad();
            ann.learn(0.001);

            std::cout << "Learn: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
        }
    }

    for (size_t i = 0; i < X_train.size(); i++)
    {
        Y_train[i].print();
    }

    ann.print();

    for (size_t i = 0; i < X_test.size(); i++)
    {
        ann.setX(&X_test[i]);

        ann.forward();

        error_Y = Y - Y_test[i];
        std::cout << "Test: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
    }
}



void ArtificialNeuralNetwork_UnitTest_003()
{
    const size_t n = 20;
    std::vector<Matrix<double>> X_train(n);
    std::vector<Matrix<double>> Y_train(n);

    X_train = Train_X(n, 3);
    Y_train = Train_Y(X_train);

    std::vector<Matrix<double>> X_test(30);
    std::vector<Matrix<double>> Y_test(30);
    X_test = Train_X(30, 3);
    Y_test = Train_Y(X_test);

    ArtificialNeuralNetwork ann;
    ann.add(new FullyConnectedLayer(3, 2));
    //ann.add(new FullyConnectedLayer(2, 2));
    //ActivationLayer ann2(2, new ActivationFunctionSigmoid);
    ann.add(new ActivationFunctionSoftmax(2));

    Matrix<double> X = Matrix<double>::colVector(3);
    Matrix<double> Y = Matrix<double>::colVector(2);

    Matrix<double> error_X = Matrix<double>::colVector(3);
    Matrix<double> error_Y = Matrix<double>::colVector(2);

    ann.set_error_X(&error_X);
    ann.set_error_Y(&error_Y);

    for (size_t j = 0; j < 50000; j++)
    {
        for (size_t i = 0; i < X_train.size(); i++)
        {
            ann.setX(&X_train[i]);
            ann.setY(&Y);

            ann.forward();

            error_Y = Y - Y_train[i];

            ann.backward();
            ann.calcGrad();
            ann.learn(0.1);

            //std::cout << "Learn: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
        }
    }

    /*for (size_t i = 0; i < X_train.size(); i++)
    {
        Y_train[i].print();
    }*/

    ann.print();

    for (size_t i = 0; i < X_test.size(); i++)
    {
            ann.setX(&X_test[i]);
            ann.setY(&Y);

            ann.forward();

            error_Y = Y - Y_test[i];
            std::cout << "Test: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
        }
}

std::vector<Matrix<double>> Train_X_004(const size_t n, const size_t m)
{
    std::vector<Matrix<double>> X(n);

    for (size_t i = 0; i < n; i++)
    {
        X[i] = Matrix<double>::colVector(m);

        for (size_t j = 0; j < m; j++)
        {
            double r = static_cast<double>(rand()) / RAND_MAX;
            X[i].set(j, 0, -0.1 * (1.0 - r) + 0.1 * r);
        }
    }

    return std::move(X);
}

std::vector<Matrix<double>> Train_Y_004(std::vector<Matrix<double>> x)
{
    std::vector<Matrix<double>> Y1(x.size());
    std::vector<Matrix<double>> Y2(x.size());
    std::vector<Matrix<double>> Y3(x.size());
    std::vector<Matrix<double>> Y4(x.size());
    std::vector<Matrix<double>> Y5(x.size());
    std::vector<Matrix<double>> Z(x.size());

    FullyConnectedLayer ann1(3, 4);
    Matrix<double> w = Matrix<double>::matrix({ {2.0, 4.0, -2.0}, {-2.0, -4.0, 2.0}, {-1.0, 2.0, 4.0}, {-1.0, 2.0, -3.0} });
    Matrix<double> b = Matrix<double>::matrix({ {0.0}, {0.0}, {0.0}, {0.0} });
    ann1.set_w(w);
    ann1.set_b(b);
    ActivationLayer ann2(4, new ActivationFunctionTh());
    FullyConnectedLayer ann3(4, 3);
    Matrix<double> w2 = Matrix<double>::matrix({ {2.0, 4.0, 1.0, 2.0}, {-2.0, -2.0, 2.0, -1.0}, {-4.0, 2.0, 3.0, -1.0} });
    Matrix<double> b2 = Matrix<double>::matrix({ {0.0}, {0.0}, {0.0} });
    ann3.set_w(w2);
    ann3.set_b(b2);
    ActivationLayer ann4(3, new ActivationFunctionTh());
    FullyConnectedLayer ann5(3, 2);
    Matrix<double> w3 = Matrix<double>::matrix({ {2.0, 4.0, -2.0}, {-2.0, -4.0, 2.0} });
    Matrix<double> b3 = Matrix<double>::matrix({ {0.0}, {0.0} });
    ann5.set_w(w3);
    ann5.set_b(b3);
    ActivationFunctionSoftmax ann6(2);

    for (size_t i = 0; i < x.size(); i++)
    {
        Y1[i] = Matrix<double>::colVector(4);
        Y2[i] = Matrix<double>::colVector(4);
        Y3[i] = Matrix<double>::colVector(3);
        Y4[i] = Matrix<double>::colVector(3);
        Y5[i] = Matrix<double>::colVector(2);
        Z[i] = Matrix<double>::colVector(2);
        ann1.setX(&x[i]);
        ann1.setY(&Y1[i]);
        ann1.forward();
        ann2.setX(&Y1[i]);
        ann2.setY(&Y2[i]);
        ann2.forward();
        ann3.setX(&Y2[i]);
        ann3.setY(&Y3[i]);
        ann3.forward();
        ann4.setX(&Y3[i]);
        ann4.setY(&Y4[i]);
        ann4.forward();
        ann5.setX(&Y4[i]);
        ann5.setY(&Y5[i]);
        ann5.forward();
        ann6.setX(&Y5[i]);
        ann6.setY(&Z[i]);
        ann6.forward();
    }
    return Z;
}

void ArtificialNeuralNetwork_UnitTest_004() 
{
    const size_t n = 20;
    std::vector<Matrix<double>> X_train(n);
    std::vector<Matrix<double>> Y_train(n);

    X_train = Train_X_004(n, 3);
    Y_train = Train_Y_004(X_train);

    std::vector<Matrix<double>> X_test(30);
    std::vector<Matrix<double>> Y_test(30);
    X_test = Train_X_004(30, 3);
    Y_test = Train_Y_004(X_test);

    ArtificialNeuralNetwork ann;
    ann.add(new FullyConnectedLayer(3, 4));
    ann.add(new ActivationLayer(4, new ActivationFunctionTh()));
    ann.add(new FullyConnectedLayer(4, 3));
    ann.add(new ActivationLayer(3, new ActivationFunctionTh()));
    ann.add(new FullyConnectedLayer(3, 2));
    ann.add(new ActivationFunctionSoftmax(2));

    Matrix<double> X = Matrix<double>::colVector(3);
    Matrix<double> Y = Matrix<double>::colVector(2);//!изменить

    Matrix<double> error_X = Matrix<double>::colVector(3);
    Matrix<double> error_Y = Matrix<double>::colVector(2);//!изменить

    ann.set_error_X(&error_X);
    ann.set_error_Y(&error_Y);

    for (size_t j = 0; j < 1000; j++)
    {
        for (size_t i = 0; i < X_train.size(); i++)
        {
            ann.setX(&X_train[i]);
            ann.setY(&Y);

            ann.forward();

            error_Y = Y - Y_train[i];

            ann.backward();
            ann.calcGrad();
            ann.learn(0.1);

            //std::cout << "Learn: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
        }
    }

    /*for (size_t i = 0; i < X_train.size(); i++)
    {
        Y_train[i].print();
    }*/

    ann.print();

    for (size_t i = 0; i < X_test.size(); i++)
    {
        ann.setX(&X_test[i]);
        ann.setY(&Y);

        ann.forward();

        error_Y = Y - Y_test[i];
        std::cout << "Test: ||error_Y|| = " << normFrobenius(error_Y) << std::endl;
    }
}

void ArtificialNeuralNetwork_UnitTest() 
{
    //ArtificialNeuralNetwork_UnitTest_001();
    //ArtificialNeuralNetwork_UnitTest_002();
    //ArtificialNeuralNetwork_UnitTest_003();
    ArtificialNeuralNetwork_UnitTest_004();
}