#include <QString>
#include <QStringBuilder>

#include "result.hpp"

int Result::getNormalItrs() const
{
    return mNormalItrs;
}

void Result::setNormalItrs(int iterations)
{
    mNormalItrs  = iterations;
}

int Result::getAccelerationItrs() const
{
    return mAccelerationItrs;
}

void Result::setAccelerationItrs(int iterations)
{
    mAccelerationItrs = iterations;
}

std::vector<double> Result::getVector() const
{
    return mVector;
}

void Result::setVector(const std::vector<double>& vector)
{
    mVector = vector;
}

QString Result::getMessage() const
{
    QString message;

    message.append("Result:\n");

    if (mNormalItrs > 0)
    {
        message.append("* Normal iterations: ");
        message.append(QString::number(mNormalItrs));
        message.append("\n");
    }

    if (mAccelerationItrs > 0)
    {
        message.append("* Acceleration iterations: ");
        message.append(QString::number(mAccelerationItrs));
        message.append("\n");
    }

    unsigned vectorCount = mVector.size();
    if (vectorCount > 0)
    {
        message.append("* Vector: { ");

        for (unsigned idx = 0; idx < vectorCount - 1; ++idx)
            message.append(QString::number(mVector[idx], 'g', 12) + QString("; "));

        message.append(QString::number(mVector[vectorCount - 1], 'g', 12) +
                QString(" }"));
    }

    return std::move(message);
}
