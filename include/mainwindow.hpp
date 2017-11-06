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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    constexpr static const char* INFO_MSG = "INFO: ";
    constexpr static const char* ERROR_MSG = "ERROR: ";

    constexpr static const char* FUNCTION_LABEL = "Math function:";
    constexpr static const char* FUNCTION_IS_SET_MSG = "Function is set";
    static const unsigned FUNCTION_TEXT_HEIGHT = 24;

    constexpr static const char* VARIABLES_COUNT_LABEL = "Variables:";
    static const unsigned VARIABLES_COUNT_MIN = 1;
    static const unsigned VARIABLES_COUNT_MAX = 10;
    static const unsigned VARIABLES_COUNT_DEFAULT = VARIABLES_COUNT_MIN;

    constexpr static const char* SET_FUNCTION_BUTTON_LABEL = "Set function";

    constexpr static const char* LOG_LABEL = "Log:";

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

    unsigned mVariablesCount;

    void configureWindow();

    void setFunctionButtonCallback();
    void variablesCountSpinnerCallback(int value);
};

#endif // MAINWINDOW_HPP
