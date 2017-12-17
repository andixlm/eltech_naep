#include <iostream>
#include <cstring>

#include "matrix.hpp"

matrix::matrix(const char* name, std::vector<double> vec)
{
    strcpy(m_name, name);

    m_rows = vec.size();
    m_cols = 1;

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double;

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx][0] = vec[idx];
}

matrix::matrix(const char* name, int rows, int cols) :
    m_rows(rows), m_cols(cols)
{
    strcpy(m_name, name);

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double[m_cols];

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            m_data[alpha][beta] = 0.0;
}

matrix::matrix(const char* name, double initialization_value,
               int rows, int cols) :
    m_rows(rows), m_cols(cols)
{
    strcpy(m_name, name);

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double[m_cols];

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            m_data[alpha][beta] = initialization_value;
}

matrix::matrix(const char* name, double** data, int rows, int cols) :
    m_rows(rows), m_cols(cols)
{
    strcpy(m_name, name);

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double[m_cols];

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            m_data[alpha][beta] = data[alpha][beta];
}

matrix::matrix(const matrix& other)
{
    strcpy(m_name, other.m_name);

    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double[m_cols];

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            m_data[alpha][beta] = other.m_data[alpha][beta];
}

matrix::~matrix()
{
    for (int idx = 0; idx < m_rows; idx++)
        delete[] m_data[idx];
    delete[] m_data;

    m_rows = m_cols = 0;
}

double matrix::determinant()
{
    double det = 0.0;
    double** pd = m_data;

    switch (m_rows)
    {
    case 2:
    {
        det = pd[0][0] * pd[1][1] - pd[0][1] * pd[1][0];

        return det;
    }

    case 3:
    {
        double a = pd[0][0]; double b = pd[0][1]; double c = pd[0][2];
        double d = pd[1][0]; double e = pd[1][1]; double f = pd[1][2];
        double g = pd[2][0]; double h = pd[2][1]; double i = pd[2][2];

        double det = (a * e * i + b * f * g + c * d * h);
        det = det - a * f * h;
        det = det - b * d * i;
        det = det - c * e * g;

        return det;
    }

    case 4:
    {
        matrix* temp[4];

        for (int idx = 0; idx < 4; idx++)
            temp[idx] = new matrix("", 3, 3);

        for (int gamma = 0; gamma < 4; gamma++)
        {
            for (int alpha = 1; alpha < 4; alpha++)
            {
                int delta = 0;

                for (int beta = 0; beta < 4; beta++)
                {
                    if (gamma == beta)
                        continue;

                    temp[gamma]->m_data[alpha - 1][delta++] =
                            this->m_data[alpha][beta];
                }
            }
        }

        return this->m_data[0][0] * temp[0]->determinant() -
                this->m_data[0][1] * temp[1]->determinant() +
                this->m_data[0][2] * temp[2]->determinant() -
                this->m_data[0][3] * temp[3]->determinant();

        return det;
    }

    case 5:
    {
        matrix* temp[5];

        for (int idx = 0; idx < 5; idx++)
            temp[idx] = new matrix("", 4, 4);

        for (int gamma = 0; gamma < 5; gamma++)
        {
            for (int alpha = 1; alpha < 5; alpha++)
            {
                int delta = 0;

                for (int beta = 0; beta < 5; beta++)
                {
                    if (gamma == beta)
                        continue;

                    temp[gamma]->m_data[alpha - 1][delta++] =
                            this->m_data[alpha][beta];
                }
            }
        }

        return this->m_data[0][0] * temp[0]->determinant() -
                this->m_data[0][1] * temp[1]->determinant() +
                this->m_data[0][2] * temp[2]->determinant() -
                this->m_data[0][3] * temp[3]->determinant() +
                this->m_data[0][4] * temp[4]->determinant();
    }

    default:
    {
        int dimensions = m_rows;
        matrix** temp = new matrix*[dimensions];

        for (int idx = 0; idx < dimensions; idx++)
            temp[idx] = new matrix("", dimensions - 1, dimensions - 1);

        for (int gamma = 0; gamma < dimensions; gamma++)
        {
            for (int alpha = 1; alpha < dimensions; alpha++)
            {
                int delta = 0;

                for (int beta = 0; beta < dimensions; beta++)
                {
                    if (gamma == beta)
                        continue;

                    temp[gamma]->m_data[alpha - 1][delta++] =
                            this->m_data[alpha][beta];
                }
            }
        }

        double det = 0.0;

        for (int idx = 0; idx < dimensions; idx++)
        {
            if ((idx % 2) == 0)
                det = det + (this->m_data[0][idx] *
                        temp[idx]->determinant());
            else
                det = det - (this->m_data[0][idx] *
                        temp[idx]->determinant());
        }

        for (int idx = 0; idx < dimensions; idx++)
            delete temp[idx];
        delete[] temp;

        return det;
    }
    }
}

matrix matrix::co_factor()
{
    matrix cofactor("COF", m_rows, m_cols);

    if (m_rows != m_cols)
        return cofactor;
    if (m_rows < 2)
        return cofactor;
    else if (m_rows == 2)
    {
        cofactor.m_data[0][0] = m_data[1][1];
        cofactor.m_data[0][1] = -m_data[1][0];
        cofactor.m_data[1][0] = -m_data[0][1];
        cofactor.m_data[1][1] = m_data[0][0];

        return cofactor;
    }
    else if (m_rows >= 3)
    {
        int dimensions = m_rows;
        matrix*** temp = new matrix**[dimensions];

        for (int idx = 0; idx < dimensions; idx++)
            temp[idx] = new matrix*[dimensions];

        for (int alpha = 0; alpha < dimensions; alpha++)
            for (int beta = 0; beta < dimensions; beta++)
                temp[alpha][beta] = new matrix("", dimensions - 1, dimensions - 1);

        for (int gamma = 0; gamma < dimensions; gamma++)
        {
            for (int delta = 0; delta < dimensions; delta++)
            {
                int epsilon = 0;

                for (int alpha = 0; alpha < dimensions; alpha++)
                {
                    int eta = 0;

                    for (int beta = 0; beta < dimensions; beta++)
                    {
                        if (gamma == alpha || delta == beta)
                            continue;

                        temp[gamma][delta]->m_data[epsilon][eta++] =
                                this->m_data[alpha][beta];
                    }

                    if (gamma != alpha)
                        epsilon++;
                }
            }
        }

        bool flag_positive = true;

        for (int alpha = 0; alpha < dimensions; alpha++)
        {
            flag_positive = ((alpha % 2) == 0);

            for (int beta = 0; beta < dimensions; beta++)
            {
                if (flag_positive == true)
                {
                    cofactor.m_data[alpha][beta] =
                            temp[alpha][beta]->determinant();
                    flag_positive = false;
                }
                else
                {
                    cofactor.m_data[alpha][beta] =
                            -temp[alpha][beta]->determinant();
                    flag_positive = true;
                }
            }
        }

        for (int alpha = 0; alpha < dimensions; alpha++)
            for (int beta = 0; beta < dimensions; beta++)
                delete temp[alpha][beta];

        for (int idx = 0; idx < dimensions; idx++)
            delete[] temp[idx];
        delete[] temp;
    }

    return cofactor;
}

matrix matrix::adjoint()
{
    matrix cofactor("COF", m_rows, m_cols);
    matrix adj("ADJ", m_rows, m_cols);

    if (m_rows != m_cols)
        return adj;

    cofactor = this->co_factor();

    // Adjoint is transpose of a cofactor of a matrix.
    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            adj.m_data[beta][alpha] = cofactor.m_data[alpha][beta];

    return adj;
}

matrix matrix::transpose()
{
    matrix trans("TR", m_cols, m_rows);

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            trans.m_data[beta][alpha] = m_data[alpha][beta];

    return trans;
}

matrix matrix::inverse()
{
    matrix cofactor("COF", m_rows, m_cols);
    matrix inv("INV", m_rows, m_cols);

    if (m_rows != m_cols)
        return inv;

    // To find out Determinant.
    double det = determinant();
    cofactor = this->co_factor();

    // inv = transpose of cofactor / Determinant.
    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            inv.m_data[beta][alpha] = cofactor.m_data[alpha][beta] / det;

    return inv;
}

int matrix::get_rows() const
{
    return m_rows;
}

int matrix::get_cols() const
{
    return m_cols;
}

void matrix::set_name(const char* name)
{
    strcpy(m_name, name);
}

const char* matrix::get_name() const
{
    return m_name;
}

matrix& matrix::operator=(const matrix& other)
{
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
        throw std::runtime_error("WARNING: Assignment is taking place "
                                 "with by changing the number of rows "
                                 "and columns of the matrix");

    for (int idx = 0; idx < m_rows; idx++)
        delete[] m_data[idx];
    delete[] m_data;

    strcpy(m_name, other.m_name);

    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_data = new double*[m_rows];

    for (int idx = 0; idx < m_rows; idx++)
        m_data[idx] = new double[m_cols];

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            m_data[alpha][beta] = other.m_data[alpha][beta];

    return *this;
}

matrix matrix::operator+(const matrix& other) const
{
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
    {
        throw std::runtime_error("Addition could not take place because "
                                 "number of rows and columns are different "
                                 "between the two matrices");
    }

    matrix result("", m_rows, m_cols);

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            result.m_data[alpha][beta] = this->m_data[alpha][beta] +
                    other.m_data[alpha][beta];

    return result;
}

matrix matrix::operator-(const matrix& other) const
{
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
    {
        throw std::runtime_error("Subtraction could not take place because "
                                 "number of rows and columns are different "
                                 "between the two matrices");
    }

    matrix result("", m_rows, m_cols);

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            result.m_data[alpha][beta] = this->m_data[alpha][beta] -
                    other.m_data[alpha][beta];

    return result;
}

matrix matrix::operator*(const double value) const
{
    matrix result("", this->m_rows, this->m_cols);

    for (int alpha = 0; alpha < this->m_rows; alpha++)
        for (int beta = 0; beta < this->m_cols; beta++)
            result.m_data[alpha][beta] = value * this->m_data[alpha][beta];

    return result;
}

matrix matrix::operator*(const matrix& other) const
{
    if (this->m_cols != other.m_rows)
    {
        throw std::runtime_error("Multiplication could not take place "
                                 "because number of columns of 1st Matrix and "
                                 "number of rows in 2nd Matrix are different");
    }

    matrix result("", this->m_rows, other.m_cols);

    for (int alpha = 0; alpha < this->m_rows; alpha++)
        for (int beta = 0; beta < other.m_cols; beta++)
            for (int gamma = 0; gamma < this->m_cols; gamma++)
                result.m_data[alpha][beta] +=
                        this->m_data[alpha][gamma] *
                        other.m_data[gamma][beta];

    return result;
}

matrix matrix::operator/(const double value) const
{
    return this->operator*(1.0 / value);
}

std::vector<double> matrix::operator*(const std::vector<double>& vec) const
{
    matrix matrix_vec("", vec.size(), 1);
    for (unsigned idx = 0; idx < vec.size(); ++idx)
        matrix_vec.m_data[idx][0] = vec[idx];

    matrix matrix_vec_product = this->operator*(matrix_vec);

    std::vector<double> result;
    for (int idx = 0; idx < matrix_vec_product.get_rows(); ++idx)
        result.push_back(matrix_vec_product.m_data[idx][0]);

    return result;
}

bool matrix::operator==(const matrix& other) const
{
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
    {
        throw std::runtime_error("Comparision could not take place because "
                                 "number of rows and columns are different "
                                 "between the two matrices");
    }

    bool isEqual = true;

    for (int alpha = 0; alpha < m_rows; alpha++)
        for (int beta = 0; beta < m_cols; beta++)
            if (this->m_data[alpha][beta] != other.m_data[alpha][beta])
                isEqual = false;

    return isEqual;
}
