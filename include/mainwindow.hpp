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

    static const unsigned VARIABLES_VALUES_TEXT_HEIGHT = 24;

    constexpr static const char* PRECISION_LABEL = "Precision:";
    static const int PRECISION_MIN = -9;
    static const int PRECISION_MAX = -1;
    static const int PRECISION_DEFAULT = -3;

    constexpr static const char* SET_FUNCTION_BUTTON_LABEL = "Set function";

    constexpr static const char* LOG_LABEL = "Log:";

    QWidget mMainWidget;

    QHBoxLayout mMainLayout;

    QVBoxLayout mParametersLayout;

    QVBoxLayout mMathLayout;
    QLabel mFunctionLabel;
    QTextEdit mFunctionText;

    unsigned mVariablesCount;
    QLabel mVariablesCountLabel;
    QSpinBox mVariablesCountSpinner;

    std::vector<double> mVariablesValues;
    QTextEdit mVariablesValuesText;

    int mPrecision;
    QLabel mPrecisionLabel;
    QSpinBox mPrecisionSpinner;

    QPushButton mSetFunctionButton;

    QVBoxLayout mInfoLayout;

    QVBoxLayout mLogLayout;
    QLabel mLogLabel;
    QTextEdit mLogText;

    void configureWindow();

    void setFunctionButtonCallback();
    void variablesCountSpinnerCallback(int value);
    void precisionSpinnerCallback(int value);
};

#endif // MAINWINDOW_HPP
