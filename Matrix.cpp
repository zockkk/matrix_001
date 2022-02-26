
#include "Matrix.h"

void Matrix_UnitTest_001()
{
    Matrix<double> A(4, 3);
    A[0][0] = 9.0;  A[0][1] = 1.0;  A[0][2] = 1.0;
    A[1][0] = 1.0;  A[1][1] = 2.0;  A[1][2] = 7.0;
    A[2][0] = 2.0;  A[2][1] = 5.0;  A[2][2] = 3.0;
    A[3][0] = 3.0;  A[3][1] = 2.0;  A[3][2] = 3.0;

    Matrix<double> B(4, 3);
    B[0][0] = 9.0;  B[0][1] = 3.0;  B[0][2] = 4.0;
    B[1][0] = 1.0;  B[1][1] = 2.0;  B[1][2] = 2.0;
    B[2][0] = 8.0;  B[2][1] = 7.0;  B[2][2] = 5.0;
    B[3][0] = 1.0;  B[3][1] = 2.0;  B[3][2] = 3.0;

    A.print();
    B.print();

    (A + B).print();
    (A - B).print();
}

void Matrix_UnitTest_002()
{
    std::cout << "Matrix_UnitTest" << std::endl << std::endl;

    /*
    Matrix<float> A(5, 5);
    A[0][0] =  0.0; A[0][1] =  1.0; A[0][2] =  1.0; A[0][3] =  5.0; A[0][4] =  4.0;
    A[1][0] = -1.0; A[1][1] = -4.0; A[1][2] =  0.0; A[1][3] =  0.0; A[1][4] = -2.0;
    A[2][0] =  3.0; A[2][1] =  1.0; A[2][2] =  7.0; A[2][3] =  1.0; A[2][4] =  0.0;
    A[3][0] =  0.0; A[3][1] =  0.0; A[3][2] =  2.0; A[3][3] =  0.0; A[3][4] = -3.0;
    A[4][0] = -1.0; A[4][1] =  0.0; A[4][2] =  4.0; A[4][3] =  2.0; A[4][4] =  2.0;
    */

    std::vector<std::vector<double>> a = {
        { 0.0,  1.0,  1.0,  5.0,  4.0},
        {-1.0, -4.0,  0.0,  0.0, -2.0},
        { 3.0,  1.0,  7.0,  1.0,  0.0},
        { 0.0,  0.0,  2.0,  0.0, -3.0},
        {-1.0,  0.0,  4.0,  2.0,  2.0}
    };

    Matrix<double> A = Matrix<double>::matrix(a);
    Matrix<double> x = Matrix<double>::colVector({2.0, 8.0, 7.0, 4.0, 5.0});
    Matrix<double> b = A * x;

    //x.getSize().print();

    //Matrix<double>(MSize(3, 9), 3.0).t().print();

    //A.solve(b).print();

    //std::cout << A.det() << std::endl;

    //Matrix<double> A_inv = A.inv();
    //(A_inv * A).print();

    //A.print();
    //A.t().print();
}

void Matrix_UnitTest_003()
{
    Matrix<double> A = Matrix<double>::square(7);

    A.print();
}

void Matrix_UnitTest()
{
    //Matrix_UnitTest_001();
    //Matrix_UnitTest_002();
    Matrix_UnitTest_003();
}
