#include "createaccount.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QCheckBox>

CreateAccount::CreateAccount(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void CreateAccount::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Create user account");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    QWidget *formContainer = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setContentsMargins(20, 0, 20, 0);
    formContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    params.resize(6);

    QFont *inputLabelFont = new QFont("", 12, QFont::Medium);

    createInputField("Name*", formLayout, inputLabelFont, 0);
    createInputField("Username*", formLayout, inputLabelFont, 1);
    createInputField("Computer's name*", formLayout, inputLabelFont, 2);
    createInputField("Password*", formLayout, inputLabelFont, 3, true);
    createInputField("Confirm password*", formLayout, inputLabelFont, 4, true);

    QCheckBox *passwordToLogin = new QCheckBox("Require password to login", this);
    passwordToLogin->setFont(*inputLabelFont);

    connect(passwordToLogin, &QCheckBox::toggled, this, [=](bool checked) {
        params[5] = QString::number(checked);
    });

    formLayout->addSpacing(15);
    formLayout->addWidget(passwordToLogin);

    mainLayout->addWidget(formContainer);
    mainLayout->addStretch();
}

QLineEdit* CreateAccount::createInputField(const QString &labelText, QVBoxLayout *layout, QFont *labelFont, int paramIndex, bool isPassword)
{
    QWidget *fieldContainer = new QWidget();
    QVBoxLayout *fieldLayout = new QVBoxLayout(fieldContainer);
    fieldLayout->setSpacing(1);
    fieldContainer->setFixedHeight(68);

    QHBoxLayout *inputLayout = new QHBoxLayout();

    QLabel *label = new QLabel(labelText);
    label->setFont(*labelFont);

    QLineEdit *input = new QLineEdit(this);
    input->setFixedWidth(450);
    if (isPassword) input->setEchoMode(QLineEdit::Password);

    QLabel *errorLabel = new QLabel();
    QFont errorFont("", 8);
    QPalette errorPalette = QPalette();
    errorLabel->setVisible(false);
    errorLabel->setFont(errorFont);
    errorPalette.setColor(QPalette::WindowText, Qt::red);
    errorLabel->setPalette(errorPalette);
    errorLabel->setAlignment(Qt::AlignRight);

    inputLayout->addWidget(label);
    inputLayout->addWidget(input);

    fieldLayout->addSpacing(10);
    fieldLayout->addLayout(inputLayout);
    fieldLayout->addWidget(errorLabel);
    fieldLayout->setAlignment(Qt::AlignTop);
    layout->addWidget(fieldContainer);
    layout->addWidget(createDivider());

    connect(input, &QLineEdit::textChanged, this, [=](const QString &value) {
        params[paramIndex] = value;
        if (error) validateFields();
    });

    errorLabels.append(errorLabel);
    return input;
}

void CreateAccount::validateFields()
{
    bool hasError = false;

    for (int i = 0; i < 5; ++i) {
        if (params[i].trimmed().isEmpty()) {
            errorLabels.at(i)->setText("This field is required.");
            errorLabels.at(i)->setVisible(true);
            hasError = true;
        } else {
            errorLabels.at(i)->clear();
            errorLabels.at(i)->setVisible(false);
        }
    }

    if (params[3].length() < 6 && !params[3].isEmpty()) {
        errorLabels.at(3)->setText("Password must be at least 6 characters long.");
        errorLabels.at(3)->setVisible(true);
        hasError = true;
    }

    if (params[4] != params[3] && !params[4].isEmpty()) {
        errorLabels.at(4)->setText("Passwords do not match.");
        errorLabels.at(4)->setVisible(true);
        hasError = true;
    }

    setError(hasError);
}
