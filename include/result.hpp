#ifndef RESULT_HPP
#define RESULT_HPP

#include <QString>

class Result
{
public:
    Result(const std::vector<double>& vector) :
        mNormalItrs(-1),
        mAccelerationItrs(-1),
        mVector(vector) {}
    Result(int normalItrs, const std::vector<double>& vector) :
        mNormalItrs(normalItrs),
        mAccelerationItrs(-1),
        mVector(vector) {}
    Result(int normalItrs, int accelerationItrs,
           const std::vector<double>& vector) :
        mNormalItrs(normalItrs),
        mAccelerationItrs(accelerationItrs),
        mVector(vector) {}

    int getNormalItrs() const;
    void setNormalItrs(int iterations);

    int getAccelerationItrs() const;
    void setAccelerationItrs(int iterations);

    std::vector<double> getVector() const;
    void setVector(const std::vector<double>& vector);

    QString getMessage() const;

private:
    int mNormalItrs;
    int mAccelerationItrs;

    std::vector<double> mVector;
};

#endif // RESULT_HPP
