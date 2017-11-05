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
    constexpr static const char* MATH_FUNCTION_LABEL = "Math function:";
    static const unsigned MATH_FUNCTION_HEIGHT = 24;

    constexpr static const char* VARIABLES_COUNT_LABEL = "Variables:";
    static const unsigned VARIABLES_COUNT_MIN = 1;
    static const unsigned VARIABLES_COUNT_MAX = 99;
    static const unsigned VARIABLES_COUNT_DEFAULT = VARIABLES_COUNT_MIN;

    constexpr static const char* MATH_FUNCTION_BUTTON_TEXT = "Set function";

    constexpr static const char* LOG_LABEL = "Log:";

    QWidget mMainWidget;

    QHBoxLayout mMainLayout;

    QVBoxLayout mParametersLayout;

    QVBoxLayout mMathFunctionLayout;
    QLabel mMathFunctionLabel;
    QTextEdit mMathFunction;
    QLabel mVariablesCountLabel;
    QSpinBox mVariablesCount;
    QPushButton mMathFunctionButton;

    QVBoxLayout mInfoLayout;

    QVBoxLayout mLogLayout;
    QLabel mLogLabel;
    QTextEdit mLog;

    mu::Parser mParser;

    void configureWindow();

    void setFunctionCallback();
};

#endif // MAINWINDOW_HPP
