#include <iostream>

#include "equation.hpp"
#include "matrix.hpp"

#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int main()
{
    srand(time(NULL));
    Matrix <int> *m = new Matrix <int> (2,2);
    Matrix <int> *m1 = new Matrix <int> (2,2);
    Matrix <double> *m6 = new Matrix <double> (3,3);
    Matrix <double> *m2 = new Matrix <double> (6,6);
    Matrix <double> *B = new Matrix <double> (6,1);
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

    /*cout << m1->set(0,0,1) << endl;
    cout << m1->set(0,1,1) << endl;
    cout << m1->set(1,0,2) << endl;
    cout << m1->set(1,1,1) << endl;
    cout << "TEST: " << m1->det() << endl;*/

    /*cout << m6->set(0,0,1) << endl;
    cout << m6->set(0,1,1) << endl;
    cout << m6->set(0,2,2) << endl;
    cout << m6->set(1,0,1) << endl;
    cout << m6->set(1,1,1) << endl;
    cout << m6->set(1,2,1) << endl;
    cout << m6->set(2,0,0) << endl;
    cout << m6->set(2,1,0) << endl;
    cout << m6->set(2,2,0) << endl;

    char k[3] = {0,0,1};
    char l[3] = {1,0,0};
    cout << "TEST6: " << m6->det(k,l) << endl;
    cout << "TEST7: " << m6->deg() << endl;*/

    for (int i = 0; i < 3; i++){
        //for (int j = 0; j < 3; j++) cout << m2->set(i,j,i+j) << endl;
        //cout << m2->set(i,2,i) << endl;
        //cout << m2->set(i,0,0) << endl;
        cout << m2->set(i,i,1) << endl;
    }
    //cout << m2->set(0,0,0) << endl;
    //cout << m2->set(1,1,0) << endl;
    //cout << m2->set(2,2,0) << endl;
     //m2->set(8,8,0);
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

    /*Matrix <int> m3 = *m**m1;
    cout << "Mul: " << m3.get(0,0) << endl;
    cout << "Mul: " << m3.get(0,1) << endl;
    cout << "Mul: " << m3.get(1,0) << endl;
    cout << "Mul: " << m3.get(1,1) << endl;

    cout << m3.det() << endl;
    cout << "1111111111111111111111111111111111111" << endl;
    cout << "Determination: " << m2->det() << endl;

    //Matrix <int>* m4 = m2->inverse();
    //cout << "Determination: " << m4->det() << endl;*/

    cout << "Degree: " << m2->deg() << endl;

    double* charac = m2->characteristic();
    for (unsigned long i = 0; i <= m2->get_rows(); i++){
        cout << charac[m2->get_rows()-i] << " ";
    }
    cout << endl << endl;

    char** minor = m2->get_minor();
    if (minor != nullptr){
        std::cout << "Hehehe: " << (int)minor[0][0] << " " << (int)minor[0][1] << " " << (int)minor[0][2] << " " << (int)minor[1][0] << " " << (int)minor[1][1] << " " << (int)minor[1][2] << std::endl;
    }
    cout << "Start..." << endl;
    m2->set(0,0,2);
    m2->set(0,1,3);
    m2->set(0,2,5);
    m2->set(0,3,0);
    m2->set(1,0,1);
    m2->set(1,1,1);
    m2->set(1,2,0);
    m2->set(2,0,1);
    m2->set(2,1,1);
    m2->set(2,2,1);
    m2->set(3,2,0);
    m2->set(3,3,0);

    B->set(0,0,1);
    B->set(1,0,2);
    B->set(2,0,1);
    B->set(3,0,4);
    cout << "Degree: " << m2->deg() << endl;
    //cout << (equation_independent(*m2, *B)).get(0,0) << endl;
    stringstream *sstream = equation(*m2, *B);
    if (sstream != nullptr){
        for (unsigned long i = 0; i < m2->get_columns(); i++) cout << "x" << i << " = " << sstream[i].str() << endl;
    } else cout << "No solution" << endl;
    delete m;
    delete m1;
}
