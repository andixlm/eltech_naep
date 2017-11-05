#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
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
    constexpr static const char* MATH_FUNCTION_LABEL = "Math function:";
    static const unsigned MATH_FUNCTION_HEIGHT = 24;

    constexpr static const char* LOG_LABEL = "Log:";

    QWidget mMainWidget;

    QHBoxLayout mMainLayout;

    QVBoxLayout mParametersLayout;

    QVBoxLayout mMathFunctionLayout;
    QLabel mMathFunctionLabel;
    QTextEdit mMathFunction;

    QVBoxLayout mInfoLayout;

    QVBoxLayout mLogLayout;
    QLabel mLogLabel;
    QTextEdit mLog;

    void configureWindow();
};

#endif // MAINWINDOW_HPP
