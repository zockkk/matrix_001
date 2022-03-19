#ifndef ABSTRACTENVIRONMENT_H_INCLUDED
#define ABSTRACTENVIRONMENT_H_INCLUDED

#include "Matrix.h"
#include "xo.h"

class AbstractEnvironment
{
protected:
    Matrix<double> currentState;
    double currentReward = 0.0;

public:
    AbstractEnvironment() {}
    virtual ~AbstractEnvironment() {}

    virtual const Matrix<double>& getCurrentState() { return currentState; }
    virtual double getCurrentReward() { return currentReward; }
    virtual bool nextState(const Matrix<double> &action) = 0;
};

class EnvironmentXO : AbstractEnvironment
{
    XO board;
    Matrix<double> currentState = *board.get_board();
public:
    EnvironmentXO() {}
    virtual ~EnvironmentXO() {}

    virtual bool nextState(const Matrix<double>& action) override
    {
        currentState += action;
        board.set_board(currentState);
        if (board.check_victory(-1) || board.check_victory(1) || board.check_draw()) {
            return false;
        }
        return true;
    }

    Matrix<double>& getBoard() 
    {
        return *board.get_board();
    }

    Matrix<double>& getArr() 
    {
        return *board.get_arr();
    }

    double win() {
        if (board.check_victory(1)) return 1;
        if (board.check_victory(-1)) return -1;
        if (board.check_draw()) return 0;
    }

    void restart() { board.restart(); currentState = *board.get_board(); }

    void inversion() { board.inversion(); currentState = *board.get_board(); }

    void print() 
    { board.Print(); }
};

#endif // ABSTRACTENVIRONMENT_H_INCLUDED
