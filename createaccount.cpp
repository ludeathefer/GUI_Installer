#include "createaccount.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QRadioButton>
#include <QButtonGroup>
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
    mainLayout->addWidget(title);

    QVBoxLayout *formLayout = new QVBoxLayout();

    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel("Name");
    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setFixedWidth(520);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput);
    formLayout->addLayout(nameLayout);

    QHBoxLayout *usernameLayout = new QHBoxLayout();
    QLabel *usernameLabel = new QLabel("Username");
    QLineEdit *usernameInput = new QLineEdit();
    usernameInput->setFixedWidth(520);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameInput);
    formLayout->addLayout(usernameLayout);

    QHBoxLayout *computerNameLayout = new QHBoxLayout();
    QLabel *computerNameLabel = new QLabel("Computer's Name");
    QLineEdit *computerNameInput = new QLineEdit();
    computerNameInput->setFixedWidth(520);
    computerNameLayout->addWidget(computerNameLabel);
    computerNameLayout->addWidget(computerNameInput);
    formLayout->addLayout(computerNameLayout);

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    QLabel *passwordLabel = new QLabel("Password");
    QLineEdit *passwordInput = new QLineEdit();
    passwordInput->setFixedWidth(520);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordInput);
    formLayout->addLayout(passwordLayout);

    QHBoxLayout *confirmPasswordLayout = new QHBoxLayout();
    QLabel *confirmPasswordLabel = new QLabel("Confirm Password");
    QLineEdit *confirmPasswordInput = new QLineEdit();
    confirmPasswordInput->setFixedWidth(520);
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordLayout->addWidget(confirmPasswordLabel);
    confirmPasswordLayout->addWidget(confirmPasswordInput);
    formLayout->addLayout(confirmPasswordLayout);

    formLayout->addSpacing(20);
    QCheckBox *passwordToLogin = new QCheckBox("Require password to login", this);
    formLayout->addWidget(passwordToLogin);

    mainLayout->addLayout(formLayout);
}
