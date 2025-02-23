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
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    QWidget *formContainer = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setContentsMargins(20, 0, 20, 0);
    formLayout->setSpacing(15);
    formContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFont inputLabelFont("", 12, QFont::Medium);

    formLayout->addWidget(createDivider());

    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel("Name");
    QLineEdit *nameInput = new QLineEdit(this);
    nameLabel->setFont(inputLabelFont);
    nameInput->setFixedWidth(450);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput);
    formLayout->addLayout(nameLayout);

    formLayout->addWidget(createDivider());

    QHBoxLayout *usernameLayout = new QHBoxLayout();
    QLabel *usernameLabel = new QLabel("Username");
    QLineEdit *usernameInput = new QLineEdit();
    usernameLabel->setFont(inputLabelFont);
    usernameInput->setFixedWidth(450);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameInput);
    formLayout->addLayout(usernameLayout);

    formLayout->addWidget(createDivider());

    QHBoxLayout *computerNameLayout = new QHBoxLayout();
    QLabel *computerNameLabel = new QLabel("Computer's Name");
    QLineEdit *computerNameInput = new QLineEdit();
    computerNameLabel->setFont(inputLabelFont);
    computerNameInput->setFixedWidth(450);
    computerNameLayout->addWidget(computerNameLabel);
    computerNameLayout->addWidget(computerNameInput);
    formLayout->addLayout(computerNameLayout);

    formLayout->addWidget(createDivider());

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    QLabel *passwordLabel = new QLabel("Password");
    QLineEdit *passwordInput = new QLineEdit();
    passwordLabel->setFont(inputLabelFont);
    passwordInput->setFixedWidth(450);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordInput);
    formLayout->addLayout(passwordLayout);

    formLayout->addWidget(createDivider());

    QHBoxLayout *confirmPasswordLayout = new QHBoxLayout();
    QLabel *confirmPasswordLabel = new QLabel("Confirm Password");
    QLineEdit *confirmPasswordInput = new QLineEdit();
    confirmPasswordLabel->setFont(inputLabelFont);
    confirmPasswordInput->setFixedWidth(450);
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordLayout->addWidget(confirmPasswordLabel);
    confirmPasswordLayout->addWidget(confirmPasswordInput);
    formLayout->addLayout(confirmPasswordLayout);

    formLayout->addWidget(createDivider());

    formLayout->addSpacing(20);
    QCheckBox *passwordToLogin = new QCheckBox("Require password to login", this);
    formLayout->addWidget(passwordToLogin);

    mainLayout->addWidget(formContainer);
    mainLayout->addStretch();

    params.resize(6);
    connect(nameInput, &QLineEdit::textChanged, this, [=](const QString &value) { params[0] = value; });
    connect(usernameInput, &QLineEdit::textChanged, this, [=](const QString &value) { params[1] = value; });
    connect(computerNameInput, &QLineEdit::textChanged, this, [=](const QString &value) { params[2] = value; });
    connect(passwordInput, &QLineEdit::textChanged, this, [=](const QString &value) { params[3] = value; });
    connect(confirmPasswordInput, &QLineEdit::textChanged, this, [=](const QString &value) { params[4] = value; });
    connect(passwordToLogin, &QCheckBox::toggled, this, [=](bool checked) { params[5] = QString::number(checked); });
}
