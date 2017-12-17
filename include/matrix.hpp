#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class matrix
{
private:
    static const int BUFFER_SIZE = 16;

    int m_rows;
    int m_cols;
    char m_name[BUFFER_SIZE];

public:
    double** m_data;

    matrix() = delete;
    matrix(const char* name, std::vector<double> vec);
    matrix(const char* name, int rows, int cols);
    matrix(const char* name, double initialization_value, int rows, int cols);
    matrix(const char* name, double** data, int rows, int cols);
    matrix(const matrix& other);
    ~matrix();

    double determinant();
    matrix co_factor();
    matrix adjoint();
    matrix transpose();
    matrix inverse();

    int get_rows() const;
    int get_cols() const;

    void set_name(const char* name);
    const char* get_name() const;

    matrix& operator=(const matrix& other);
    matrix operator+(const matrix& other) const;
    matrix operator-(const matrix& other) const;
    matrix operator*(const double value) const;
    matrix operator*(const matrix& other) const;
    matrix operator/(const double value) const;
    std::vector<double> operator*(const std::vector<double>& vec) const;
    bool operator==(const matrix& other) const;
};

#endif // MATRIX_HPP
