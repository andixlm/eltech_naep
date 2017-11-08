#include <QString>
#include <QStringBuilder>

#include "result.hpp"

int Result::getIterations() const
{
    return mIterations;
}

void Result::setIterations(int iterations)
{
    mIterations  = iterations;
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

    message.append("Result:\n\t");

    if (mIterations > 0)
    {
        message.append("Iterations: ");
        message.append(QString::number(mIterations));
        message.append("\n");
    }

    unsigned vectorCount = mVector.size();
    if (vectorCount > 0)
    {
        message.append("Vector: { ");

        for (unsigned idx = 0; idx < vectorCount - 1; ++idx)
            message.append(QString::number(mVector[idx]) + QString("; "));

        message.append(QString::number(mVector[vectorCount - 1]) +
                QString("}"));
    }

    return std::move(message);
}
