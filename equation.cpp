#include "equation.hpp"

#include <assert.h>

Matrix<double> equation_independent(Matrix<double> A, Matrix<double> B){
    Matrix<double> *I = A.inverse();
    if (I == nullptr) return A;
    /*std::cout << "OK: " << I->get(1,1) << std::endl;
    std::cout << "Hmm: " << ((*I)*B).get(0,0) << std::endl;
    std::cout << "Hmm: " << ((*I)*B).get(1,0) << std::endl;
    std::cout << "OK1: " << I->get(1,1) << std::endl;
    Matrix<double> *II = new Matrix<double>;
    std::cout << "OK2: " << I->get(1,1) << std::endl;
    (*II) = ((*I)*B);
    std::cout << "OK3: " << I->get(1,1) << std::endl;*/
    return ((*I)*B);
}

std::stringstream* equation(Matrix<double> A, Matrix<double> B){
    unsigned long k = 0, l = 0, p = 0;
    double *s, *x;
    char** minor;
    std::stringstream* str;

    Matrix<double> *AB = new Matrix<double> (A);

    AB->expand(A.get_rows(),A.get_columns()+1);

    for (unsigned long i = 0; i < A.get_rows(); i++)
        AB->set(i, A.get_columns(), B.get(i,0));

    if (AB->deg() != A.deg()){ //Rouché–Capelli theorem
        delete AB;
        return nullptr;
    }
    delete AB;

    minor = A.get_minor();

    if (minor != nullptr){
        for (unsigned long i = 0; i < A.get_rows(); i++)
            if (minor[0][i] == 0) k++;
        Matrix<double> *m = new Matrix<double> (k,k);
        for (unsigned long i = 0; i < A.get_rows(); i++){
            if (minor[0][i] == 0){
                for (unsigned long j = 0, p = 0; j < A.get_columns(); j++){
                        if (minor[1][j] == 0){
                            m->set(l,p,A.get(i,j));
                            p++;
                        }
                }
                l++;
            }
        }

        Matrix<double> *inv = m->inverse();
        assert (inv != nullptr);

        delete m;

        k = A.get_columns() - k;

        s = new double [l*(k+1)];
        x = new double [l*(k+1)];

        for (unsigned long i = 0, p = 0; i < A.get_rows(); i++)
            if (minor[0][i] == 0) {
                for (unsigned long j = 0; j <= k; j++) x[p*(k+1)+j] = 0;
                s[p*(k+1)+k] = B.get(i,0);
                p++;
            }

        for (unsigned long i = 0, l = 0; i < A.get_rows(); i++){
            if (minor[0][i] == 0){
                for (unsigned long j = 0, p = 0; j < A.get_columns(); j++){
                     if (minor[1][j] == 1){
                           s[l*(k+1)+p] = (-1)*A.get(i,j);
                           p++;
                     }
                }
                l++;
            }
        }

        for (unsigned long i = 0; i < inv->get_rows(); i++){
            for (unsigned long j = 0; j < inv->get_columns(); j++){
                for (l = 0; l <= k; l++){
                    x[i*(k+1)+l] += inv->get(i,j)*s[j*(k+1)+l];
                }

            }
        }

        str = new std::stringstream[B.get_rows()];

        for (unsigned long i = 0, l = 0; i < A.get_rows(); i++){
            if (minor[1][i] == 0){
                str[i].str("");
                for (unsigned long j = 0, p = 0; j < A.get_columns(); j++){
                     if (minor[1][j] == 1){
                            if (x[l*(k+1)+p] != 0) str[i] << x[l*(k+1)+p] << "*x" << j << "+";
                            p++;
                     }
                     if (p == k){
                            if (x[l*(k+1)+p] != 0) str[i] << x[l*(k+1)+p];
                                else {
                                    if (str[i].str().empty()){
                                        str[i] << 0;
                                    } else {
                                        str[i].seekp(-1,std::ios_base::end);
                                        str[i] << " ";
                                    }
                            }
                            break;
                        }
                }
                l++;
            } else {
                str[i] << "x" << i;
            }
        }

        delete inv;
        delete[] s;
        delete[] x;

        return str;
    }

    return nullptr;
}
