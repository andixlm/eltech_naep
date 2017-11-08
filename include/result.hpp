#ifndef RESULT_HPP
#define RESULT_HPP

#include <QString>

class Result
{
public:
    Result(const std::vector<double>& vector) :
        mIterations(-1), mVector(vector) {}
    Result(const std::vector<double>& vector, int iterations) :
        mIterations(iterations), mVector(vector) {}

    int getIterations() const;
    void setIterations(int iterations);

    std::vector<double> getVector() const;
    void setVector(const std::vector<double>& vector);

    QString getMessage() const;

private:
    int mIterations;

    std::vector<double> mVector;
};

#endif // RESULT_HPP
