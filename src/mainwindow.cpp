#include "mainwindow.hpp"
#include "parser.hpp"
#include "tools.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      mMainWidget(this),
      mMainLayout(&mMainWidget),
      mVariablesCount(VARIABLES_COUNT_DEFAULT),
      mVariablesValues(mVariablesCount),
      mPrecision(PRECISION_DEFAULT)
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

    // Variables values
    mMathLayout.addWidget(&mVariablesValuesText);
    mMathLayout.setAlignment(&mVariablesValuesText, Qt::AlignTop);
    mVariablesValuesText.setSizePolicy(QSizePolicy::Policy::Fixed,
                                       QSizePolicy::Policy::Fixed);
    mVariablesValuesText.setFixedHeight(VARIABLES_VALUES_TEXT_HEIGHT);

    // Precision label
    mMathLayout.addWidget(&mPrecisionLabel);
    mMathLayout.setAlignment(&mPrecisionLabel, Qt::AlignTop);
    mPrecisionLabel.setText(PRECISION_LABEL);

    // Precision spinner
    mMathLayout.addWidget(&mPrecisionSpinner);
    mMathLayout.setAlignment(&mPrecisionSpinner, Qt::AlignTop);
    mPrecisionSpinner.setMinimum(PRECISION_MIN);
    mPrecisionSpinner.setMaximum(PRECISION_MAX);
    mPrecisionSpinner.setValue(PRECISION_DEFAULT);
    connect(&mPrecisionSpinner,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::precisionSpinnerCallback);

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

void MainWindow::setFunctionButtonCallback()
{
    Parser::configureParser(mFunctionText.toPlainText().toStdWString(),
                            mVariablesCount);

    try
    {
        Parser::sPosition = readVariables();
    }
    catch (std::invalid_argument& exc)
    {
        mLogText.append(ERROR_MSG + QString(exc.what()));
        return;
    }

    try
    {
        Parser::sParser.Eval();
    }
    catch (mu::Parser::exception_type& exc)
    {
        mLogText.append(ERROR_MSG + QString::fromWCharArray(exc.GetMsg().c_str()));
    }
}

std::vector<double> MainWindow::readVariables()
{
    QStringList variablesValuesStrings =
            mVariablesValuesText.toPlainText()
                .trimmed()
                .split(VARIABLES_VALUES_SEPARATOR);

    if (mVariablesCount != variablesValuesStrings.size())
        throw std::invalid_argument("Variables counts aren\'t matched.");

    std::vector<double> variables;

    for (auto variableValueString : variablesValuesStrings)
    {
        bool isDoubleOk;
        variables.push_back(static_cast<const QString>
                            (variableValueString).toDouble(&isDoubleOk));

        if (!isDoubleOk)
            throw std::invalid_argument("Variables are incorrect.");
    }

    return variables;
}

void MainWindow::variablesCountSpinnerCallback(int value)
{
    mVariablesCount = value;
}

void MainWindow::precisionSpinnerCallback(int value)
{
    mPrecision = value;
}
