#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      mMainWidget(this),
      mMainLayout(&mMainWidget),
      mVariables(VARIABLES_COUNT_MAX),
      mVariablesCount(VARIABLES_COUNT_DEFAULT)
{
    setCentralWidget(&mMainWidget);
    mMainLayout.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    configureWindow();
    configureParser();
}

MainWindow::~MainWindow()
{

}

void MainWindow::configureWindow()
{
    /* Parameters layout */
    mMainLayout.addLayout(&mParametersLayout);

    // Function block
    mParametersLayout.addLayout(&mMathLayout);
    mParametersLayout.setAlignment(&mMathLayout, Qt::AlignTop);

    // Function label
    mMathLayout.addWidget(&mFunctionLabel);
    mMathLayout.setAlignment(&mFunctionLabel, Qt::AlignTop);
    mFunctionLabel.setText(FUNCTION_LABEL);

    // Function expression
    mMathLayout.addWidget(&mFunctionText);
    mMathLayout.setAlignment(&mFunctionText, Qt::AlignTop);
    mFunctionText.setSizePolicy(QSizePolicy::Policy::Fixed,
                                QSizePolicy::Policy::Fixed);
    mFunctionText.setFixedHeight(FUNCTION_TEXT_HEIGHT);

    // Variables label
    mMathLayout.addWidget(&mVariablesCountLabel);
    mMathLayout.setAlignment(&mVariablesCountLabel, Qt::AlignTop);
    mVariablesCountLabel.setText(VARIABLES_COUNT_LABEL);

    // Variables spinner
    mMathLayout.addWidget(&mVariablesCountSpinner);
    mMathLayout.setAlignment(&mVariablesCountSpinner, Qt::AlignTop);
    mVariablesCountSpinner.setMinimum(VARIABLES_COUNT_MIN);
    mVariablesCountSpinner.setMaximum(VARIABLES_COUNT_MAX);
    mVariablesCountSpinner.setValue(VARIABLES_COUNT_DEFAULT);
    connect(&mVariablesCountSpinner,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::variablesCountSpinnerCallback);

    // Button to set function
    mMathLayout.addWidget(&mSetFunctionButton);
    mMathLayout.setAlignment(&mSetFunctionButton, Qt::AlignRight);
    mSetFunctionButton.setText(SET_FUNCTION_BUTTON_LABEL);
    connect(&mSetFunctionButton, &QPushButton::clicked,
            this, &MainWindow::setFunctionButtonCallback);

    /* Info layout */
    mMainLayout.addLayout(&mInfoLayout);

    // Log block
    mInfoLayout.addLayout(&mLogLayout);
    mInfoLayout.setAlignment(&mLogLayout, Qt::AlignTop);

    // Log label
    mLogLayout.addWidget(&mLogLabel);
    mLogLabel.setText(LOG_LABEL);

    // Log text
    mLogLayout.addWidget(&mLogText);
}

void MainWindow::configureParser()
{
    for (unsigned idx = 0; idx < mVariables.size(); ++idx)
        mParser.DefineVar((QString("x%1").arg(idx)).toStdWString(),
                          &mVariables[idx]);
}

void MainWindow::setFunctionButtonCallback()
{
    mParser.SetExpr(mFunctionText.toPlainText().toStdWString());
}

void MainWindow::variablesCountSpinnerCallback(int value)
{
    mVariablesCount = value;
}
