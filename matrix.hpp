#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <algorithm>
#include <iostream>

template <class type>
    class Matrix{
        private:
            type* coefficients_;
            unsigned long rows_;
            unsigned long columns_;
        public:
            Matrix();
            Matrix(unsigned long rows, unsigned long columns);
            ~Matrix();

            unsigned long get_rows() const;
            unsigned long get_columns() const;

            int set(unsigned long row, unsigned long column, type value);
            type get(unsigned long row, unsigned long column) const;

            Matrix<type> operator+(const Matrix<type> &m) const;
            Matrix<type> &operator+=(const Matrix<type> &m);
            Matrix<type> operator-(const Matrix<type> &m) const;
            Matrix<type> &operator-=(const Matrix<type> &m);
            Matrix<type> operator*(const Matrix<type> &m) const;
            Matrix<type> &operator*=(const Matrix<type> &m);

            long int det(char* n = nullptr) const;
    };

template <class type>
    Matrix <type>::Matrix(){
            rows_ = 0;
            columns_ = 0;
            coefficients_ = nullptr;

    }
template <class type>
    Matrix <type>::Matrix(unsigned long rows, unsigned long columns){
        rows_ = rows;
        columns_ = columns;
        if (rows == 0 || columns == 0)
            coefficients_ = nullptr;
        else {
            coefficients_ = new type[rows*columns];

            for (unsigned long i = 0; i < rows; i++){
                for (unsigned long j = 0; j < columns; j++){
                    coefficients_[i*columns+j] = type(0);
                }
            }
            //std::fill(coefficients_, coefficients_+rows*columns*sizeof(type), type(0));
        }
    }
template <class type>
    Matrix <type>::~Matrix(){
        //if (coefficients_ != nullptr) delete[] coefficients_;
    }

template <class type>
    unsigned long Matrix<type>::get_rows() const{
        return rows_;
    }

template <class type>
    unsigned long Matrix<type>::get_columns() const{
        return columns_;
    }

template <class type>
    int Matrix<type>::set(unsigned long row, unsigned long column, type value){
        if (row >= rows_ || column >= columns_) return 1; //setting value beyond matrix
        coefficients_[row*columns_+column] = value;
        return 0;
    }

template <class type>
    type Matrix<type>::get(unsigned long row, unsigned long column) const{
        if (row >= rows_ || column >= columns_) return type(0); //getting value beyond matrix
        return coefficients_[(row*columns_)+column];
    }

template <class type>
    Matrix<type> Matrix<type>::operator+(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    temp->set(i, j, this->get(i,j)+m.get(i,j));
                }
            }
        }
        return *temp;
    }

template <class type>
    Matrix<type> &Matrix<type>::operator+=(const Matrix<type> &m){
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    this->set(i, j, this->get(i,j)+m.get(i,j));
                }
            }
        }
        return *this;
    }

template <class type>
    Matrix<type> Matrix<type>::operator-(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    temp->set(i, j, this->get(i,j)-m.get(i,j));
                }
            }
        }
        return *temp;
    }

template <class type>
    Matrix<type> &Matrix<type>::operator-=(const Matrix<type> &m){
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    this->set(i, j, this->get(i,j)-m.get(i,j));
                }
            }
        }
        return *this;
    }

template <class type>
    Matrix<type> Matrix<type>::operator*(const Matrix<type> &m) const{
        Matrix<type> *temp;
        if (this->columns_ != m.get_rows()) {
                temp = new Matrix<type>;
                return *temp; //mul is not possible
        } else {
            type sum;
            temp = new Matrix <type> (this->rows_, this->columns_);
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < m.get_columns(); j++){
                    sum = type(0);
                    for (unsigned long k = 0; k < this->columns_; k++){
                        sum += (this->get(i,k)*m.get(k,j));
                    }
                    temp->set(i, j, sum);
                }
            }
            return *temp;
        }
    }

template <class type>
    Matrix<type> &Matrix<type>::operator*=(const Matrix<type> &m){
        type sum;
        if (this->columns_ == m.get_rows()) {
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < m.get_columns(); j++){
                    sum = type(0);
                    for (unsigned long k = 0; k < this->columns_; k++){
                        sum += (this->get(i,k)*m.get(k,j));
                    }
                    this->set(i, j, sum);
                }
            }
        }
            return *this;
    }

template <class type>
    long int Matrix<type>::det(char* n) const{
        long int determination = 0;
        unsigned long j = 0, k[3] = {0,0,0};
        if (rows_ != columns_ || rows_ == 0) return 0;

        if (n == nullptr){
            n = new char[rows_];
            std::fill(n, n+rows_*columns_*sizeof(char), 0);
            }

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 0) {
                if (j < 3) k[j] = i;
                j++;
                }

        if (j == 3){ //matrix 3x3 detected
            return coefficients_[(k[0]*columns_)+k[0]]*coefficients_[(k[1]*columns_)+k[1]]*coefficients_[(k[2]*columns_)+k[2]]+
            coefficients_[(k[1]*columns_)+k[0]]*coefficients_[(k[2]*columns_)+k[1]]*coefficients_[(k[0]*columns_)+k[2]]+
            coefficients_[(k[2]*columns_)+k[0]]*coefficients_[(k[0]*columns_)+k[1]]*coefficients_[(k[1]*columns_)+k[2]]-
            (coefficients_[(k[0]*columns_)+k[2]]*coefficients_[(k[1]*columns_)+k[1]]*coefficients_[(k[2]*columns_)+k[0]]+
            coefficients_[(k[1]*columns_)+k[2]]*coefficients_[(k[2]*columns_)+k[1]]*coefficients_[(k[0]*columns_)+k[0]]+
            coefficients_[(k[2]*columns_)+k[2]]*coefficients_[(k[0]*columns_)+k[1]]*coefficients_[(k[1]*columns_)+k[0]]);
        } else if (j == 2){ //matrix 2x2 detected
            return coefficients_[(k[0]*columns_)+k[0]]*coefficients_[(k[1]*columns_)+k[1]]-coefficients_[(k[1]*columns_)+k[1]]*coefficients_[(k[1]*columns_)+k[0]];
        } else if (j == 1) return k[0]; //matrix 1x1 detected

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 0) {
                n[i] = 1;

                for (unsigned long l = 0; l < rows_; l++){
                    if (n[l] == 0) {
                        if (coefficients_[(i*columns_)+l] == type(0)) continue;
                        std::cout << i << " " << l << std::endl;
                        n[l] = 1;
                        if (i%2==1) determination-=coefficients_[(i*columns_)+l]*det(n);
                        else determination=coefficients_[(i*columns_)+l]*det(n);
                    }
                }
            }
        return determination;
    }

#endif
