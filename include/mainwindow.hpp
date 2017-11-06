#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "muParser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    constexpr static const char* FUNCTION_LABEL = "Math function:";
    constexpr static const unsigned FUNCTION_TEXT_HEIGHT = 24;

    constexpr static const char* VARIABLES_COUNT_LABEL = "Variables:";
    constexpr static const unsigned VARIABLES_COUNT_MIN = 1;
    constexpr static const unsigned VARIABLES_COUNT_MAX = 99;
    constexpr static const unsigned VARIABLES_COUNT_DEFAULT = VARIABLES_COUNT_MIN;

    constexpr static const char* SET_FUNCTION_BUTTON_LABEL = "Set function";

    constexpr static const char* LOG_LABEL = "Log:";

    unsigned mVariablesCount;
    std::vector<double> mVariables;

    mu::Parser mParser;

    QWidget mMainWidget;

    QHBoxLayout mMainLayout;

    QVBoxLayout mParametersLayout;

    QVBoxLayout mMathLayout;
    QLabel mFunctionLabel;
    QTextEdit mFunctionText;
    QLabel mVariablesCountLabel;
    QSpinBox mVariablesCountSpinner;
    QPushButton mSetFunctionButton;

    QVBoxLayout mInfoLayout;

    QVBoxLayout mLogLayout;
    QLabel mLogLabel;
    QTextEdit mLogText;

    void configureWindow();

    void setFunctionButtonCallback();
    void variablesCountSpinnerCallback(int value);
};

#endif // MAINWINDOW_HPP
