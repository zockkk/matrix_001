#ifndef ABSTRACTAGENT_H_INCLUDED
#define ABSTRACTAGENT_H_INCLUDED

#include "Matrix.h"
#include "ArtificialNeuralNetwork.h"

class AbstractAgent
{
public:
    AbstractAgent() {}
    virtual ~AbstractAgent() {}

    virtual void doAction(const Matrix<double> &currentState, Matrix<double> &action) = 0;
    virtual void setReward(const double reward) = 0;
};

class AgentXO : AbstractAgent
{
    ArtificialNeuralNetwork agent;
    double reward = 0.0;
    Matrix<double> y = Matrix<double>::colVector(9);
    Matrix<double> x = Matrix<double>::colVector(9);
    Matrix<double> error_X = Matrix<double>::colVector(9);
public:
    AgentXO(size_t n_layers, std::vector<size_t> n_neuros)
    {
        for (size_t i = 0; i < n_layers-2; i++) 
        {
            agent.add(new FullyConnectedLayer(n_neuros[i], n_neuros[i + 1]));
            agent.add(new ActivationLayer(n_neuros[i + 1],new ActivationFunctionTh()));
        }
        agent.add(new FullyConnectedLayer(n_neuros[n_layers - 2], n_neuros[n_layers - 1]));
        agent.add(new ActivationFunctionSoftmax(n_neuros[n_layers - 1]));
        agent.set_error_X(&error_X);
        agent.setY(&y);
    }
    virtual ~AgentXO() {}

    virtual void doAction(const Matrix<double>& currentState, Matrix<double>& action) override
    {
        x = currentState;
        agent.setX(&x);
        agent.forward();
        action = y;
    };
    virtual void setReward(const double _reward) override
    {
        reward += _reward;
    };

    double getReward() {
        return reward;
    }

    void learning(Matrix<double>* _error_Y) {
        agent.set_error_Y(_error_Y);
        agent.backward();
        agent.calcGrad();
        agent.learn(-0.1);
    }
};

#endif // ABSTRACTAGENT_H_INCLUDED
