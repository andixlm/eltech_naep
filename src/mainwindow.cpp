#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      mMainWidget(this),
      mMainLayout(&mMainWidget)
{
    setCentralWidget(&mMainWidget);
    configureWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::configureWindow()
{
    mMainLayout.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    /* Parameters layout */
    mMainLayout.addLayout(&mParametersLayout);

    // Math formula
    mParametersLayout.addLayout(&mMathFunctionLayout);
    mParametersLayout.setAlignment(&mMathFunctionLayout, Qt::AlignTop);

    mMathFunctionLayout.addWidget(&mMathFunctionLabel);
    mMathFunctionLayout.setAlignment(&mMathFunctionLabel, Qt::AlignTop);
    mMathFunctionLabel.setText(MATH_FUNCTION_LABEL);

    mMathFunctionLayout.addWidget(&mMathFunction);
    mMathFunctionLayout.setAlignment(&mMathFunction, Qt::AlignTop);
    mMathFunction.setSizePolicy(QSizePolicy::Policy::Fixed,
                                QSizePolicy::Policy::Fixed);
    mMathFunction.setFixedHeight(MATH_FUNCTION_HEIGHT);

    /* Info layout */
    mMainLayout.addLayout(&mInfoLayout);

    // Log output
    mInfoLayout.addLayout(&mLogLayout);
    mInfoLayout.setAlignment(&mLogLayout, Qt::AlignTop);

    mLogLayout.addWidget(&mLogLabel);
    mLogLabel.setText(LOG_LABEL);

    mLogLayout.addWidget(&mLog);
}
