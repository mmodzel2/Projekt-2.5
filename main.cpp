#include <iostream>

#include "matrix.hpp"

#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(NULL));
    Matrix <int> *m = new Matrix <int> (2,2);
    Matrix <int> *m1 = new Matrix <int> (2,2);
    Matrix <int> *m2 = new Matrix <int> (4,4);
    cout << m->get(0,0) << endl;
    cout << m->get(0,1) << endl;
    cout << m->get(1,0) << endl;
    cout << m->get(1,1) << endl;
    cout << m->set(0,1,90) << endl;
    cout << m->get(0,1) << endl;

    cout << m1->get(0,0) << endl;
    cout << m1->get(0,1) << endl;
    cout << m1->get(1,0) << endl;
    cout << m1->get(1,1) << endl;
    cout << m1->set(0,1,1) << endl;
    cout << m1->set(1,1,1) << endl;
    cout << m1->get(0,1) << endl;

    for (int i = 0; i < 4; i++){
        //for (int j = 0; j < 3; j++) cout << m2->set(i,j,i+j) << endl;
        //cout << m2->set(i,2,i) << endl;
        //cout << m2->set(i,0,0) << endl;
        cout << m2->set(i,i,1) << endl;
    }
    cout << m->set(0,0,1) << endl;
    cout << m->set(0,0,1) << endl;


    /**m+=*m1;
    cout << "Sum: " << m->get(0,1) << endl;
    *m+=*m1;
    *m+=*m1;
    *m+=*m1;
    *m+=*m1;
    *m+=*m1;
    cout << "Sum: " << m->get(0,1) << endl;

    Matrix <int> m2 = *m+*m1;
    cout << "Sum: " << m2.get(0,1) << endl;*/

    Matrix <int> m3 = *m**m1;
    cout << "Mul: " << m3.get(0,0) << endl;
    cout << "Mul: " << m3.get(0,1) << endl;
    cout << "Mul: " << m3.get(1,0) << endl;
    cout << "Mul: " << m3.get(1,1) << endl;

    cout << m3.det() << endl;
    cout << "1111111111111111111111111111111111111" << endl;
    cout << m2->det() << endl;

    delete m;
    delete m1;
}
