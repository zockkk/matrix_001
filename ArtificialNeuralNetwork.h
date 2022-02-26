#ifndef ARTIFICIALNEURALNETWORK_H_INCLUDED
#define ARTIFICIALNEURALNETWORK_H_INCLUDED

#include <iostream>
#include <vector>
#include <cstdlib>

#include "AbstractLayer.h"

class ArtificialNeuralNetwork
{
private:
    Matrix<double> *X = nullptr;
    Matrix<double> *Y = nullptr;

    std::vector<AbstractLayer*> layers;
    std::vector<Matrix<double>*> XY;
    std::vector<Matrix<double>*> error_XY;

public:
    ArtificialNeuralNetwork() {}
    ~ArtificialNeuralNetwork();

    void setX(Matrix<double> *_X);
    void setY(Matrix<double> *_Y);

    void set_error_X(Matrix<double> *_error_X);
    void set_error_Y(Matrix<double> *_error_Y);

    void add(AbstractLayer *layer);

    void forward();
    void backward();
    void calcGrad();
    void learn(const float rate);

    void print();

    void save(std::string a);
    void set_fromfile(std::string a);
};

void ArtificialNeuralNetwork_UnitTest();

#endif // ARTIFICIALNEURALNETWORK_H_INCLUDED
