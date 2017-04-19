#ifndef _EQUATION_HPP
#define _EQUATION_HPP

#include <string>
#include <sstream>

#include "console.hpp"
#include "matrix.hpp"

Matrix<double> equation_independent(Matrix<double> A, Matrix<double> B);
std::stringstream* equation(Matrix<double> A, Matrix<double> B);

unsigned int matrix_equation(Console* console, void** args);

#endif // _EQUATION_HPP
