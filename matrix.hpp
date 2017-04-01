#ifndef _MATRIX_HPP
#define _MATRIX_HPP

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
            Matrix<type> &operator+=(const Matrix<type> &m) const;
            Matrix<type> operator-(const Matrix<type> &m) const;
            Matrix<type> &operator-=(const Matrix<type> &m) const;

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
        if (rows == 0 && columns == 0)
            coefficients_ = nullptr;
        else
            coefficients_ = new type[rows*columns] {};
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
        coefficients_[(row*columns_+column)*sizeof(type)] = value;
        return 0;
    }

template <class type>
    type Matrix<type>::get(unsigned long row, unsigned long column) const{
        if (row >= rows_ || column >= columns_) return type(0); //getting value beyond matrix
        return coefficients_[(row*columns_+column)*sizeof(type)];
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
    Matrix<type> &Matrix<type>::operator+=(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
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
    Matrix<type> &Matrix<type>::operator-=(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    this->set(i, j, this->get(i,j)-m.get(i,j));
                }
            }
        }
        return *this;
    }

#endif
