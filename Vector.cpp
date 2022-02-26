
#include "Vector.h"

void Vector_UnitTest_001()
{
    Vector<double> A({ 1.0, 2.0, 3.0, 4.0 });
    Vector<double> B({ 2.0, 3.0, 5.0, 7.0 });

    A += B;
    A.print();
    B.print();

    A /= 5.0;
    A.print();

    A = B;
    A.print();

    Vector<int> C(3, 5);
    C.print();

    Vector<int> D(C);
    D.print();

    C.resize(7, 0);
    C.print();
    //D.set(3, C[5]);

    A = B + B;
    A.print();

    Vector<double> F = Vector<double>::vector(4);
    F.print();
}

void Vector_UnitTest()
{
    Vector_UnitTest_001();
}
