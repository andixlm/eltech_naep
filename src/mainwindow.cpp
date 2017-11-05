#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      mMainWidget(this),
      mMainLayout(&mMainWidget)
{
    setCentralWidget(&mMainWidget);
    mMainLayout.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    configureWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::configureWindow()
{
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

    mMathFunctionLayout.addWidget(&mVariablesCountLabel);
    mMathFunctionLayout.setAlignment(&mVariablesCountLabel, Qt::AlignTop);
    mVariablesCountLabel.setText(VARIABLES_COUNT_LABEL);

    mMathFunctionLayout.addWidget(&mVariablesCount);
    mMathFunctionLayout.setAlignment(&mVariablesCount, Qt::AlignTop);
    mVariablesCount.setMinimum(VARIABLES_COUNT_MIN);
    mVariablesCount.setMaximum(VARIABLES_COUNT_MAX);
    mVariablesCount.setValue(VARIABLES_COUNT_DEFAULT);

    mMathFunctionLayout.addWidget(&mMathFunctionButton);
    mMathFunctionLayout.setAlignment(&mMathFunctionButton, Qt::AlignRight);
    mMathFunctionButton.setText(MATH_FUNCTION_BUTTON_TEXT);
    connect(&mMathFunctionButton, &QPushButton::clicked,
            this, &MainWindow::setFunctionCallback);

    /* Info layout */
    mMainLayout.addLayout(&mInfoLayout);

    // Log output
    mInfoLayout.addLayout(&mLogLayout);
    mInfoLayout.setAlignment(&mLogLayout, Qt::AlignTop);

    mLogLayout.addWidget(&mLogLabel);
    mLogLabel.setText(LOG_LABEL);

    mLogLayout.addWidget(&mLog);
}

void MainWindow::setFunctionCallback()
{

}
