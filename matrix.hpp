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
            Matrix(Matrix<type> &M);
            ~Matrix();

            Matrix(const Matrix<type> &M);
            unsigned long get_rows() const;
            unsigned long get_columns() const;

            int set(unsigned long row, unsigned long column, type value);
            type get(unsigned long row, unsigned long column) const;

            void expand(unsigned long rows, unsigned long columns);

            Matrix<type> operator+(const Matrix<type> &m) const;
            Matrix<type> &operator+=(const Matrix<type> &m);
            Matrix<type> operator-(const Matrix<type> &m) const;
            Matrix<type> &operator-=(const Matrix<type> &m);
            Matrix<type> operator*(const Matrix<type> &m) const;
            Matrix<type> &operator*=(const Matrix<type> &m);

            type det(char* n = nullptr, char* m = nullptr) const;
            unsigned long deg(char* n = nullptr, char* m = nullptr) const;

            Matrix<type>* adjugate() const;
            Matrix<type>* inverse() const;
            Matrix<type>* transpose() const;

            double* characteristic() const;

            char** get_minor(char* n = nullptr, char* m = nullptr, unsigned long matrix_degree = 0) const;
    };

template <class type>
    Matrix <type>::Matrix(){
            rows_ = 0;
            columns_ = 0;
            coefficients_ = nullptr;

    }
template <class type>
    Matrix<type>::Matrix(Matrix <type> &M){
            rows_ = M.get_rows();
            columns_ = M.get_columns();

            if (rows_ != 0 && columns_ != 0){
                    coefficients_ = new type[rows_*columns_];
                    for (unsigned long i = 0; i < rows_; i++){
                        for (unsigned long j = 0; j < columns_; j++){
                            coefficients_[(i*columns_)+j] = M.get(i,j);
                        }
                    }
            }
    }
template <class type>
    Matrix<type>::Matrix(const Matrix<type> &M){
            rows_ = M.get_rows();
            columns_ = M.get_columns();

            if (rows_ != 0 && columns_ != 0){
                    coefficients_ = new type[rows_*columns_];
                    for (unsigned long i = 0; i < rows_; i++){
                        for (unsigned long j = 0; j < columns_; j++){
                            coefficients_[(i*columns_)+j] = M.get(i,j);
                        }
                    }
            }
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
        if (coefficients_ != nullptr) delete[] coefficients_;
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
    void Matrix <type>::expand(unsigned long rows, unsigned long columns){
        type* pointer;
        unsigned long k,l;

        if (rows == rows_ && columns == columns_) return;
        else if (rows == 0 || columns == 0){
            if (coefficients_ != nullptr) delete[] coefficients_;
            rows_ = rows;
            columns_ = columns;
        } else {
            pointer = new type[rows*columns];
            for (unsigned long i = 0; i < rows; i++){
                for (unsigned long j = 0; j < columns; j++){
                    pointer[i*columns+j] = type(0);
                }
            }

            if (rows_ <= rows) k = rows_;
            else k = rows;
            if (columns_ <= columns) l = columns_;
            else l = columns;

            for (unsigned long i = 0; i < k; i++){
                for (unsigned long j = 0; j < l; j++){
                    pointer[i*columns+j] = coefficients_[i*columns_+j];
                }
            }

            delete[] coefficients_;
            coefficients_ = pointer;
            rows_ = rows;
            columns_ = columns;
        }
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
    type Matrix<type>::det(char* n, char* m) const{
        type determination = 0;
        unsigned long j = 0, g = 0, k[3][2] = {{0,0},{0,0},{0,0}};

        if (coefficients_ == nullptr) return 0;
        if (rows_ != columns_ || rows_ == 0) return 0;
        bool flag1 = 0, flag2 = 0;

        if (n == nullptr){
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            flag1 = 1;
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            flag2 = 1;
            }

        for (unsigned long i = 0; i < rows_; i++){
            if (n[i] == 0) {
                if (j < 3) k[j][0] = i;
                j++;
                }
            if (m[i] == 0) {
                if (g < 3) k[g][1] = i;
                g++;
                }
        }

        if (j == 3){ //matrix 3x3 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]*coefficients_[(k[2][0]*columns_)+k[2][1]]+
            coefficients_[(k[1][0]*columns_)+k[0][1]]*coefficients_[(k[2][0]*columns_)+k[1][1]]*coefficients_[(k[0][0]*columns_)+k[2][1]]+
            coefficients_[(k[2][0]*columns_)+k[0][1]]*coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[2][1]]-
            (coefficients_[(k[0][0]*columns_)+k[2][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]*coefficients_[(k[2][0]*columns_)+k[0][1]]+
            coefficients_[(k[1][0]*columns_)+k[2][1]]*coefficients_[(k[2][0]*columns_)+k[1][1]]*coefficients_[(k[0][0]*columns_)+k[0][1]]+
            coefficients_[(k[2][0]*columns_)+k[2][1]]*coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[0][1]]);
        } else if (j == 2){ //matrix 2x2 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]-(coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[0][1]]);
        } else if (j == 1) { //matrix 1x1 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]];
        } else {
            n[k[0][0]] = 1;
            for (unsigned long i = 0; i < rows_; i++)
                if (m[i] == 0) {
                    if (coefficients_[(k[0][0]*columns_)+i] == type(0)) continue;

                    m[i] = 1;
                    if ((i+k[0][0])%2==1) determination-=coefficients_[(k[0][0]*columns_)+i]*det(n,m);
                    else determination+=coefficients_[(k[0][0]*columns_)+i]*det(n,m);
                    m[i] = 0;
                }
            n[k[0][0]] = 0;
        }

        if (flag1 == 1) delete[] n;
        if (flag2 == 1) delete[] m;
        return determination;
    }

template <class type>
    Matrix<type>* Matrix<type>::adjugate() const{
        char *n, *m;
        long int determination;
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        n = new char[rows_];
        std::fill(n, n+rows_*sizeof(char), 0);

        m = new char[columns_];
        std::fill(m, m+columns_*sizeof(char), 0);

        Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);

        for (unsigned long i = 0; i < rows_; i++){
            n[i] = 1;
            for (unsigned long j = 0; j < columns_; j++){
                m[j] = 1;
                if ((i+j)%2 == 1) determination = (-1)*this->det(n,m);
                else determination = this->det(n,m);
                matrix->set(j,i, determination);
                m[j] = 0;
            }
            n[i] = 0;
        }

        delete[] n;
        delete[] m;
        return matrix;
    }

template <class type>
    Matrix<type>* Matrix<type>::inverse() const{
        char *n, *m;
        long int determination, div;
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        div = this->det();
        if (div == 0) return nullptr; //inverse matrix does not exist

        if (rows_ == 1){
            Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);
            matrix->set(0,0,this->get(0,0)/div);
            return matrix;
        }

        n = new char[rows_];
        std::fill(n, n+rows_*sizeof(char), 0);

        m = new char[columns_];
        std::fill(m, m+columns_*sizeof(char), 0);

        Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);

        for (unsigned long i = 0; i < rows_; i++){
            n[i] = 1;
            for (unsigned long j = 0; j < columns_; j++){
                m[j] = 1;
                if ((i+j)%2 == 1) determination = (-1)*this->det(n,m);
                else determination = this->det(n,m);
                matrix->set(j,i, determination/div);
                m[j] = 0;
            }
            n[i] = 0;
        }

        delete[] n;
        delete[] m;
        return matrix;
    }

template <class type>
    Matrix<type>* Matrix<type>::transpose() const{
        if (coefficients_ == nullptr) return nullptr;

        Matrix<type> *matrix = new Matrix<type> (columns_, rows_);

        for (unsigned long i = 0; i < rows_; i++)
            for (unsigned long j = 0; j < columns_; j++)
                matrix->set(j,i,this->coefficients_[(i*this->columns_)+j]);
        return matrix;
    }

template <class type>
    double* Matrix<type>::characteristic() const{
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        double* a = new double[rows_+1];
        type* tr = new type[rows_];

        Matrix<type> *matrix = new Matrix<type> (this->columns_, this->rows_);

        for (unsigned long i = 0; i < rows_; i++){
            a[i] = type(0);
            tr[i] = type(0);

            for (unsigned long j = 0; j < columns_; j++)
                matrix->set(i,j,coefficients_[(i*columns_)+j]);
        }

        a[rows_] = 1;

        for (unsigned long i = 0; i < rows_; i++){
            for (unsigned long j = 0; j < rows_; j++){
                tr[i] += matrix->get(j,j);
            }
            if (i != rows_-1) (*matrix)*=(*this);
        }

        for (unsigned long i = 1; i <= this->rows_; i++){
              for (unsigned long j = 0; j < i; j++){
                    a[rows_-i] += a[rows_-j]*tr[i-j-1];
              }
              a[rows_-i] = ((double)((-1.0)*a[rows_-i]))/(double)i;
        }

        if((rows_%2) == 1)
                for (unsigned long i = 0; i <= rows_; i++) a[i] *= -1;

        delete matrix;
        return a;
    }

template <class type>
    unsigned long Matrix<type>::deg(char* n, char* m) const{
        bool flag1 = 0, flag2 = 0;
        unsigned long k = 0;
        unsigned long degree = 0, temp_degree;

        if (coefficients_ == nullptr) return 0;
        if (rows_ != columns_){
                Matrix<type> *e = new Matrix<type> (*this);
                if (rows_ > columns_) e->expand(rows_,rows_);
                else e->expand(columns_,columns_);

                degree = e->deg();
                delete e;
                return degree;
        }

        if (n == nullptr){
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            flag1 = 1;
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            flag2 = 1;
            }

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 1) k++;

        if (det(n,m) != 0)
                degree = rows_-k;
        else if (rows_-1 <= k) degree = 0;
        else {
            for (unsigned long i = 0; i < rows_; i++){
                if (n[i] == 0){
                    n[i] = 1;
                    for (unsigned long j = 0; j < columns_; j++){
                        if (m[j] == 0){
                            m[j] = 1;
                            temp_degree = deg(n,m);
                            if (temp_degree > degree) degree = temp_degree;
                            m[j] = 0;
                            if (degree == rows_-k-1) break;
                        }
                    }
                    n[i] = 0;
                    if (degree == rows_-k-1) break;
                }
            }
        }

        if (flag1 == 1) delete[] n;
        if (flag2 == 1) delete[] m;
        return degree;
    }

template <class type>
    char** Matrix<type>::get_minor(char* n, char* m, unsigned long matrix_degree) const{
        unsigned long k = 0;
        char** ret;
        char** temp;

        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        if (matrix_degree == 0){
            matrix_degree = deg();
            if (matrix_degree == 0) return nullptr;
        }

        if (n == nullptr){
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            }

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 1) k++;

        if (det(n,m) != 0) {
            ret = new char* [2];
            ret[0] = n;
            ret[1] = m;
        } else if (matrix_degree >= rows_-k) ret = nullptr;
        else {
            for (unsigned long i = 0; i < rows_; i++){
                if (n[i] == 0){
                    n[i] = 1;
                    for (unsigned long j = 0; j < columns_; j++){
                        if (m[j] == 0){
                            m[j] = 1;
                            temp = get_minor(n,m,matrix_degree);
                            if (temp != nullptr) {
                                    ret = temp;
                                    break;
                            }
                            m[j] = 0;
                        }
                    }
                    if (temp != nullptr) break;
                    n[i] = 0;
                }
            }
        }
        return ret;
    }

#endif
