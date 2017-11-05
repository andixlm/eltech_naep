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

    // Math function
    mParametersLayout.addLayout(&mMathLayout);
    mParametersLayout.setAlignment(&mMathLayout, Qt::AlignTop);

    mMathLayout.addWidget(&mFunctionLabel);
    mMathLayout.setAlignment(&mFunctionLabel, Qt::AlignTop);
    mFunctionLabel.setText(FUNCTION_LABEL);

    mMathLayout.addWidget(&mFunctionText);
    mMathLayout.setAlignment(&mFunctionText, Qt::AlignTop);
    mFunctionText.setSizePolicy(QSizePolicy::Policy::Fixed,
                                QSizePolicy::Policy::Fixed);
    mFunctionText.setFixedHeight(FUNCTION_TEXT_HEIGHT);

    mMathLayout.addWidget(&mVariablesCountLabel);
    mMathLayout.setAlignment(&mVariablesCountLabel, Qt::AlignTop);
    mVariablesCountLabel.setText(VARIABLES_COUNT_LABEL);

    mMathLayout.addWidget(&mVariablesCountSpinner);
    mMathLayout.setAlignment(&mVariablesCountSpinner, Qt::AlignTop);
    mVariablesCountSpinner.setMinimum(VARIABLES_COUNT_MIN);
    mVariablesCountSpinner.setMaximum(VARIABLES_COUNT_MAX);
    mVariablesCountSpinner.setValue(VARIABLES_COUNT_DEFAULT);
    connect(&mVariablesCountSpinner,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::variablesCountSpinnerCallback);

    mMathLayout.addWidget(&mSetFunctionButton);
    mMathLayout.setAlignment(&mSetFunctionButton, Qt::AlignRight);
    mSetFunctionButton.setText(SET_FUNCTION_BUTTON_LABEL);
    connect(&mSetFunctionButton, &QPushButton::clicked,
            this, &MainWindow::setFunctionButtonCallback);

    /* Info layout */
    mMainLayout.addLayout(&mInfoLayout);

    // Log output
    mInfoLayout.addLayout(&mLogLayout);
    mInfoLayout.setAlignment(&mLogLayout, Qt::AlignTop);

    mLogLayout.addWidget(&mLogLabel);
    mLogLabel.setText(LOG_LABEL);

    mLogLayout.addWidget(&mLogText);
}

void MainWindow::setFunctionButtonCallback()
{

}

void MainWindow::variablesCountSpinnerCallback(int value)
{

}
