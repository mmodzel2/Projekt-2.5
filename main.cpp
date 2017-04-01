#include <iostream>

#include "matrix.hpp"

using namespace std;

int main()
{
    Matrix <int> *m = new Matrix <int> (2,2);
    cout << m->get(0,1) << endl;
    cout << m->set(0,1,90) << endl;
    cout << m->get(0,1) << endl;

    Matrix <int> *m1 = new Matrix <int> (2,2);
    cout << m->get(0,1) << endl;
    cout << m->set(0,1,90) << endl;
    cout << m->get(0,1) << endl;

    Matrix <int> m2 = (*m+*m1);
    cout << m2.get(0,1) << endl;

    delete m;
}
