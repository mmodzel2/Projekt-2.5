#ifndef _EQUATION_HPP
#define _EQUATION_HPP

#include <string>
#include <sstream>
#include "matrix.hpp"

Matrix<double> equation_independent(Matrix<double> A, Matrix<double> B);
std::stringstream* equation(Matrix<double> A, Matrix<double> B);

#endif // _EQUATION_HPP
